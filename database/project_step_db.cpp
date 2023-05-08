#include "project_step_db.h"
#include "logic/projectException.h"
#include "database/connexion_db.h"

project_step_db::project_step_db()
{

}

project_step_db::~project_step_db()
{

}

void project_step_db::insert(const Project_step & p, int category_id )
{

    QSqlDatabase db = connexion_db::get_instance() ;

    //create the a_project
    a_project_db.insert( p , category_id ) ;

    //create the project_step
    if( db.open() ) {
        try {
            QSqlQuery query(db) ;
            query.prepare(" INSERT INTO project_step "
                          " ( id_project, message) "
                          " VALUES( :id_project, :message " ) ;
            query.bindValue(":id_project" , p.getId_project() ) ;
            query.bindValue(":message" , p.getComment() ) ;
            query.exec() ;
            qDebug() << "INSERTION project_step ok" ;
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

void project_step_db::remove(const Project_step & p)
{
    QSqlDatabase db = connexion_db::get_instance() ;

    if( db.open() ){
        //delete all the steps
        step_db.remove_for_project( p.getId_project_step() ) ;

        //delete the project_step
        try{
            QSqlQuery query(db);
            query.prepare("DELETE FROM project_step"
                          "WHERE id_project_step = :id_project_step ; ");
            query.bindValue(":id_project_step", p.getId_project_step() ) ;
            query.exec() ;
            qDebug() << "DELETE project step value ok" ;
        }catch (QSqlError *e){

        }

        //delete the relative a_project corresponding
        a_project_db.remove( p.getId_project() ) ;
    }

}

void project_step_db::update(const Project_step & p)
{
    QSqlDatabase db = connexion_db::get_instance() ;

    if( db.open() ){

        //add the a_project corresponding
        a_project_db.update( p );

        //add the project_step
        try {
            QSqlQuery query(db) ;
            query.prepare(" UPDATE project_step "
                          " SET date = id_project_step = :id_project_step, id_project = :id_project, message= :message"
                          " WHERE id_project_step = :id_project_step ; " ) ;
            query.bindValue(":id_project_step" , p.getId_project_step() ) ;
            query.bindValue(":id_project", p.getId_project() ) ;
            query.bindValue(":message", p.getComment() ) ;
            query.bindValue(":id_project_step" , p.getId_project_step() ) ;
            query.exec() ;
            qDebug() << "UPDATE project_step ok" ;
        } catch (QSqlError *e) {
            qDebug() << e->text() ;
        }

        //update all the steps
        step_db.remove_for_project( p.getId_project_step() ) ;

        for( auto step: p){
            step_db.insert(*step , p.getId_project_step() );
        }
    }
}
