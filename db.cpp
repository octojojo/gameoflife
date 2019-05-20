#include <iostream>
#include <sstream>

#include "sqlite3.h"
#include "db.h"
#include "common.h"


static int callback(void* data, int argc, char** argv, char** azColName) 
{ 
    int i; 
    fprintf(stderr, "%s: ", (const char*)data); 
  
    for (i = 0; i < argc; i++) { 
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL"); 
    } 
  
    printf("\n"); 
    return 0; 
} 
  

DB::DB ()
{ 
    int exit = 0; 
    exit = sqlite3_open("gameoflife.db", &mDB); 
  
    if (exit) {
        std::cerr << "Error open DB " << sqlite3_errmsg(mDB) << std::endl;

        std::ostringstream os;
        os << "Error open DB " << sqlite3_errmsg(mDB) << std::endl;
        throw std::runtime_error(os.str()); 
    }
} 


DB::~DB ()
{
    sqlite3_close(mDB); 
    mDB=nullptr;
}


int DB::createTable(const std::string& table)
{
   
    std::string sql = "CREATE TABLE GAME("
                      "TURN INT PRIMARY KEY     NOT NULL, "
                      "JSON           TEXT    NOT NULL);"; 

    int exit = 0; 
   
    char* messaggeError; 
    exit = sqlite3_exec(mDB, sql.c_str(), NULL, 0, &messaggeError); 
  
    if (exit != SQLITE_OK) { 
        std::cerr << "Error Create Table" <<  messaggeError << std::endl; 
        sqlite3_free(messaggeError);
        return -1;
    } 
    
    return OK; 
}

int DB::add(const std::string& table, int turn,const std::string& json)
{
    char* messaggeError;
    std::ostringstream os;
    os << "INSERT INTO GAME VALUES(" << turn << ", " <<"'" <<json << "');" ; 
    std::cout << "sqlAdd: " << os.str();

    std::string sql(os.str());
               
    int exit = sqlite3_exec(mDB, sql.c_str(), NULL, 0, &messaggeError); 
    if (exit != SQLITE_OK) { 
        std::cerr << "Error Insert" << std::endl; 
        sqlite3_free(messaggeError);
        return -1;
    }

    return OK;
}

std::string DB::get(const std::string& table, int turn)
{
    std::ostringstream os;
    os << "SELECT " << turn <<  " FROM " << table << ";" ; 
    std::string sql(os.str()); 
    
    std::string data("CALLBACK FUNCTION"); 

    int rc = sqlite3_exec(mDB, sql.c_str(), callback, (void*)data.c_str(), NULL); 
  
    if (rc != SQLITE_OK)
    {
        std::cerr << "Error SELECT" << std::endl;
        return std::string(); // empty string
    }

    return data;
}
