#include "project_step_db.h"
#include "logic/projectException.h"

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

project_step_db::project_step_db()
{

}

project_step_db::~project_step_db()
{

}

void project_step_db::insert(const Project_step & p, int category_id )
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL") ;
        db.setHostName("localhost") ;
        db.setDatabaseName("postgres") ;
        db.setUserName("tuto") ;
        db.setPassword("tuto") ;

        //create the a_project
        a_project_db.insert( p , category_id ) ;

        //create the project_step
        if( db.open() ) {
            qDebug() << " connected to database ";
            try {
                QSqlQuery query ;
                query.prepare(" INSERT INTO project_step "
                              " ( id_project, message) "
                              " VALUES( 0, ':message' " ) ;
                query.bindValue(":id_project" , p.getId_project() ) ;
                query.bindValue(":message" , p.getComment() ) ;
                query.exec() ;
                qDebug() << "DELETE ok" ;
            } catch (QSqlError *e) {
                qDebug() << e->text() ;
            }

            //create all steps if they exist
            for(auto step : p ){
                step_db.insert( *step , p.getId_project_step() ) ;
            }

        } else {
            throw new ProjectException("Unable to make connection with database") ;
        }
        db.close() ;
}

void project_step_db::remove(const Project_step &)
{

}

void project_step_db::update(const Project_step &)
{

}
