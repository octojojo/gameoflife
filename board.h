#pragma once

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include <map>

#include "creature.h"

using namespace std;

#define OK 0

class Board
{
    public:
        Board(int rows,int columns,std::string json);
        void play(int turns);
        friend std::ostream& operator<<(std::ostream& os, const Board& b);
        std::string json() const;
    private:
        void parse(std::string& json);
        inline int index(int row,int column) const;
 
        std::map<int,std::shared_ptr<Creature> > mCreatures;
        int mRows;
        int mColumns;
        int mNumCells ;
};

  