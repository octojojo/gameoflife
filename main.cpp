

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include <iterator>

#include "common.h"
#include "sqlite3.h"
#include "board.h"
#include "creature.h"
#include "db.h"

DB db; // global db

int main(int argc,char* argv[])
{
    // either provide input file as argument or use default file
    std::string inputFile;
    if (argc==2)
    {
        inputFile = argv[1];
    }
    else
    {
        inputFile = "input.txt";
    }

    std::ifstream infile;
    infile.exceptions(std::ifstream::failbit); // throw if file open/read fails

    try {
        infile.open(inputFile);
    }
    catch (const std::exception& e) {
        std::cout << e.what() << "Exception opening/reading file: " << inputFile
        << endl << "It either doesn't exist or is not accessible." << endl;
        return -1;
    }

    int turns = 0 ;
    std::string jsonStr;
    infile >> turns;
    infile >> jsonStr;
    std::cout << "turns: " << turns  << endl;
    std::cout << "json: " << jsonStr << endl;

    Board amiAndDoody(10,10,jsonStr);
    std::cout << "INITIAL:\n"<< amiAndDoody.json() <<endl << amiAndDoody<< endl;
    amiAndDoody.play(turns);
    std::cout << "FINAL:\n"<< amiAndDoody.json() <<endl << amiAndDoody<< endl;

   // persist DB

    if (db.createTable("GAME") != OK)
    {

    }

    if (db.add("GAME",1,"json_turn_1") != OK)
    {

    }

    std::string s = db.get("GAME",1);

    if (!s.empty())
    {
        std::cout << "json turn 1: "<< s << std::endl;
    }

    return OK;
}

