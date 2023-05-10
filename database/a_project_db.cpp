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

void a_project_db::insert(A_project & p, int id_category ) const
{
    if( p.getId_project() != -1 ) {
        throw new ProjectException("!!PB can't insert a project who is already there ") ;
    }

    QSqlDatabase db = connexion_db::get_instance() ;

    if( db.open() ) {
        qDebug() << " connected to database ";
        try {
            QSqlQuery query(db) ;
            query.prepare("INSERT INTO a_project"
            " ( id_category, name, begin_date, end_date, comment, description, priority)"
            " VALUES( :id_category, :name, :begin_date, :end_date, :comment, :description, :priority ); " ) ;
            query.bindValue(":id_category" , id_category ) ;
            query.bindValue(":name", p.getName()) ;
            query.bindValue(":begin_date", p.getBegin_date()) ;
            query.bindValue(":end_date", p.getEnd_date()) ;
            query.bindValue(":comment", p.getComment()) ;
            query.bindValue(":description", p.getDescription());
            query.bindValue(":priority", p.getPriority());
            if( query.exec() ) {
                qDebug() << "INSERTION a_project ok" ;
            } else {
                qDebug() << "!!PB INSERTION a_project" ;
            }

            //update of the a_project id, who is normally unknow
            query.prepare( "SELECT MAX(id_project) FROM a_project ; " ) ;
            if( query.exec() && query.next() ) {
                qDebug() << "RECUPERATION ID a_project ok" ;
                p.setId_project( query.value(0).toInt() ) ;
            } else {
                qDebug() << "!!PB RECUPERATION ID a_project" ;
            }

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
    QSqlDatabase db = connexion_db::get_instance() ;
    if( db.open() ) {
        try {
            QSqlQuery query(db) ;
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

void a_project_db::remove(int id_project) const {
    QSqlDatabase db = connexion_db::get_instance() ;

    if( db.open() ){
        try {
            QSqlQuery query(db) ;
            query.prepare("DELETE FROM a_project "
                          "WHERE id_project = :id " ) ;
            query.bindValue(":id", id_project ) ;
            query.exec() ;
            qDebug() << "DELETE ok" ;
        } catch (QSqlError *e) {
            qDebug() << e->text() ;
        }
    }
}

void a_project_db::update(const A_project & p) const
{
    QSqlDatabase db = connexion_db::get_instance() ;

    if( db.open() ) {
        qDebug() << " connected to database ";
        try {
            QSqlQuery query(db) ;
            query.prepare("UPDATE a_project"
            " SET ( id_category = :id_category , name = :name, "
            " begin_date = :begin_date , end_date = :end_date , comment = :comment"
            " , description = :description, priority = :priority ) "
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
