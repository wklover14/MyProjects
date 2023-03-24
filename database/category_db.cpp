#include "database/category_db.h"
#include "logic/projectException.h"

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>

Category_db::Category_db(){
}

Category_db::~Category_db() {
    //nothing
}

void Category_db::insert(const Category& c) {
    qDebug() << QSqlDatabase::drivers() ;
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL") ;
    db.setHostName("localhost") ;
    db.setDatabaseName("postgres") ;
    db.setUserName("tuto") ;
    db.setPassword("tuto") ;

    if( db.open() ) {
        qDebug() << " connected to database ";
        QSqlQuery query ;
        query.prepare(" INSERT INTO manager VALUES (:name, :surname, :age) ; ") ;
        query.bindValue(":name " , c.getName() ) ;
        query.bindValue(":surname " , c.getName() ) ;
        query.bindValue(":age" , 22 ) ;
        query.exec() ;
        qDebug() << "insertion ok" ;
    } else {
        throw new ProjectException("Unable to make connection with database") ;
    }
    db.close() ;
}

void Category_db::remove(const Category&){

}

void Category_db::fetch(){

        QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
        db.setHostName("localhost");
        db.setDatabaseName("projectManager");
        db.setUserName("gabby");
        db.setPassword("gabby");

        if (!db.open()) {
            qDebug() << "Error: connection with database failed";
        } else {
            qDebug() << "Database: connection ok";
            QSqlQuery query;
            if ( query.exec(" SELECT name, password FROM manager ; ") ) {
                while (query.next()) {
                    QString login = query.value(0).toString();
                    QString password = query.value(1).toString();
                    qDebug() << login << " : " << password ;
                }
            } else {
                qDebug() << "Error: SELECT failed" ;
            }
            db.close();
        }

}
