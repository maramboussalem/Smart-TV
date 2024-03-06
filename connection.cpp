#include "connection.h"
Connection::Connection(){}
bool Connection::createconnection()
{
    db = QSqlDatabase::addDatabase("QODBC");
    bool test = false ;
    db.setDatabaseName("test_db");
    db.setUserName("alaa");
    db.setPassword("alaa");
    if (db.open())
    {
        test = true;
    }
    return test;
}
void Connection::closeConnection(){db.close();}
