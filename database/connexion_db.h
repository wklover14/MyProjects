#ifndef CONNEXION_DB_H
#define CONNEXION_DB_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QString>

//this class provide a singleton for a connexion to a databasesql
//For security reason, a connexion can't be create by using get_instance()
//A friend class such as manager or main must initialize an instance of connexion with the wright parameters
//in order to ensure the connexion

class connexion_db
{
private:
    static QSqlDatabase* unique_instance ;
    connexion_db(const QString user_name,const QString password) ;
    connexion_db(const connexion_db& );
    virtual ~connexion_db() ;
    void operator=(const connexion_db& ) ;

    //attributes
    static const QString host_name;
    static const QString database_name ;
    static QString user_name;
    static QString password ;

public:
    static QSqlDatabase get_instance() ;
    static void init_connexion(const QString user_name,const QString password) ;
    static void free_instance() ;
};

#endif // CONNEXION_DB_H
