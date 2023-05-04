#include "a_project_db.h"
#include "logic/projectException.h"

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

a_project_db::a_project_db()
{

}

a_project_db::~a_project_db()
{

}

void a_project_db::insert(const A_project & p, int id_category ) const
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL") ;
    db.setHostName("localhost") ;
    db.setDatabaseName("postgres") ;
    db.setUserName("tuto") ;
    db.setPassword("tuto") ;

    if( db.open() ) {
        qDebug() << " connected to database ";
        try {
            QSqlQuery query ;
            query.prepare("INSERT INTO a_project"
            " ( id_category, name, begin_date, end_date, comment, description, priority)"
            " VALUES( :id_category, ':name', ':begin_date', ':end_date', ':comment', ':description', :priority ); " ) ;
            query.bindValue(":id_category" , id_category ) ;
            query.bindValue(":name", p.getName()) ;
            query.bindValue(":begin_date", p.getBegin_date()) ;
            query.bindValue(":end_date", p.getEnd_date()) ;
            query.bindValue(":comment", p.getComment()) ;
            query.bindValue(":description", p.getDescription());
            query.bindValue(":priority", p.getPriority());
            query.exec() ;
            qDebug() << "INSERTION ok" ;
        } catch (QSqlError *e) {
            qDebug() << e->text() ;
        }
    } else {
        throw new ProjectException("Unable to make connection with database") ;
    }
    db.close() ;
}

void a_project_db::remove(const A_project& p) const
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL") ;
    db.setHostName("localhost") ;
    db.setDatabaseName("postgres") ;
    db.setUserName("tuto") ;
    db.setPassword("tuto") ;

    if( db.open() ) {
        qDebug() << " connected to database ";
        try {
            QSqlQuery query ;
            query.prepare("DELETE FROM a_project "
                          "WHERE id_project = :id " ) ;
            query.bindValue(":id", p.getId_project() ) ;
            query.exec() ;
            qDebug() << "DELETE ok" ;
        } catch (QSqlError *e) {
            qDebug() << e->text() ;
        }
    } else {
        throw new ProjectException("Unable to make connection with database") ;
    }
    db.close() ;
}

void a_project_db::update(const A_project & p) const
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL") ;
    db.setHostName("localhost") ;
    db.setDatabaseName("postgres") ;
    db.setUserName("tuto") ;
    db.setPassword("tuto") ;

    if( db.open() ) {
        qDebug() << " connected to database ";
        try {
            QSqlQuery query ;
            query.prepare("UPDATE a_project"
            " SET ( id_category = :id_category , name = ':name', "
            " begin_date = :begin_date , end_date = :end_date , comment = :':comment'"
            " , description = ':description', priority = :priority ) "
            " WHERE id_project = :id ; " ) ;
            query.bindValue(":name", p.getName()) ;
            query.bindValue(":begin_date", p.getBegin_date()) ;
            query.bindValue(":end_date", p.getEnd_date()) ;
            query.bindValue(":comment", p.getComment()) ;
            query.bindValue(":description", p.getDescription());
            query.bindValue(":priority", p.getPriority());
            query.bindValue(":id" , p.getId_project() ) ;
            query.exec() ;
            qDebug() << "DELETE ok" ;
        } catch (QSqlError *e) {
            qDebug() << e->text() ;
        }
    } else {
        throw new ProjectException("Unable to make connection with database") ;
    }
    db.close() ;
}

bool a_project_db::is_present(const A_project &) const
{
    return true ;
}
