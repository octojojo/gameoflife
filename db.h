#pragma once

#include <string>
#include "sqlite3.h"


class DB {
    public:
        DB();
        ~DB();
        int createTable(const std::string& table);
        int add(const std::string& table, int turn,const std::string& json);
        std::string get(const std::string& table, int turn);
    private:
        sqlite3* mDB;
};

