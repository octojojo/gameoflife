#include <iostream>
#include <string>
#include <memory>
#include <fstream>
#include <sstream>
#include <iterator>
#include <map>
#include <set>

#include "common.h"
#include "sqlite3.h"
#include "board.h"
#include "creature.h"


Board::Board (int rows, int columns,std::string json)
:  mRows(rows), mColumns(columns),mNumCells(rows*columns)
{
    parse(json); // populate initial creatures

    // save initial state in DB
    // db.add(0,jsonState...)
}


std::ostream& operator<<(std::ostream& os, const Board& b)
{
    for (int row =0;row < b.mRows;row++ )
    {
        for (int column =0;column<b.mColumns;column++ )
        {
            auto iter = b.mCreatures.find(b.index(row,column));
            if(iter != b.mCreatures.end())
            {
                os << iter->second->symbol();
            }
            else
            {
                os << ' ';
            }
            os << ' ';
        }
        os << endl;
    }    
    return os;
}


// parsing help function 
std::vector<std::string> split(const std::string& s, char delimiter)
{
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }
   return tokens;
}

// quick and a little dirty parser instead of a professional Json::Reader
void Board::parse(std::string& json )
{
    //std::string json ("{'0':'b','1':'b','2':'b','3':'b','4':'b','5':'b','6':'b','7':'b','8':'b','9':'b'}");
    json = json.substr(1, json.size() - 2); // remove surrounding braces

    auto cells = split(json, ',');
    for (std::string& cell : cells )
    {
        auto elements = split(cell, ':');

        std::string indexStr(elements[0]);
        indexStr.erase(0,1);
        indexStr.pop_back();
        std::string type(elements[1]);
        type.erase(0,1);
        type.pop_back();
        
        auto pair = make_pair(std::stoi(indexStr),std::shared_ptr<Creature>(CreatureFactory::make(type) ));
        mCreatures.insert(pair);
    }

    return ;
}

// the play method is optimized for big number of turns
// instead of create and delete actual creatures on Heap
// a lightweight representation is manipulated
// till the last turn, then state is commited.
// It can be optimized for HUGE board with tradeoff of more searches
// we can even provide several play strategies and choose the best in runtime.
void Board::play(int turns)
{
    std::vector<int>  neighbours;
    neighbours.reserve(mNumCells);

    std::map<int,Creature*> alive; // tmp copy for play, use prototypes creatures are not duplicated
    
    for ( auto& cell : mCreatures)
    {
        alive.insert(make_pair(cell.first,cell.second->prototype()));
    }

    for (int turn = 0; turn < turns; turn++)
    {
        std::set<int> newBorns; // newBorns type is always 'Basic'
        int i = 0;
        // for each alive update neighbours count & newBorns
        for (auto& cell : alive)
        {    
            i = cell.first;
           
            int adjacents[] = 
            {
                index((i+mRows-1)/mRows,i%mRows),
                index((i+1)/mRows,i%mRows),
                index(i/mRows,(i+1)%mRows),
                index(i/mRows,(i+mRows-1)%mRows)
            };

            for (int& neighbour : adjacents)
            {
                //update neighbours matrix
                neighbours[neighbour]++;

                // update newBorns
                if (neighbours[neighbour]==3 )
                {
                    newBorns.insert(neighbour);
                }
                else if (neighbours[neighbour]==4 )
                {
                    newBorns.erase(neighbour);
                }

            }
           
        }

        // remove deads
        for (auto& cell : alive)
        {
            i = cell.first;
            if (!cell.second->isSurviving(neighbours[i]))
            {
                alive.erase(i);

                int adjacents[] = 
                {
                    index((i+mRows-1)/mRows,i%mRows),
                    index((i+1)/mRows,i%mRows),
                    index(i/mRows,(i+1)%mRows),
                    index(i/mRows,(i+mRows-1)%mRows)
                };
                for (int& neighbour : adjacents)
                {
                    //update neighbours matrix
                    neighbours[neighbour]--;
                }
            }
        }

        // create new-borns
        for (auto& born : newBorns )
        {
            alive.insert(make_pair(born,Basic::proto));
        }

        // save state in DB
        // db.add(turn,jsonState...)
    }

    // commit to actual board
    mCreatures.clear();

    for (auto& cell : alive)
    {
        mCreatures.insert(make_pair(cell.first,
        std::shared_ptr<Creature>(CreatureFactory::make(cell.second->symbol()))));
    }

    return;
}

int Board::index(int row,int column) const
{
    return row*mRows + column;
}

std::string Board::json() const
{
    std:string json = "{";

    for (auto& cell : mCreatures)
    {
        
        std::ostringstream os;
        os << "'" << cell.first << "':'" << cell.second->symbol() << "',"; 
        json.append(os.str());
    }
    json.pop_back(); // remove trailing comma
    json.append("}");

    return json;
}
