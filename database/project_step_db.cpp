#include "Project_step_db.h"
#include "logic/projectException.h"
#include "database/connexion_db.h"

Project_step_db::Project_step_db()
{

}

Project_step_db::~Project_step_db()
{

}

void Project_step_db::insert(Project_step& p, int category_id ) const
{
    if( p.getId_project_step() != -1 ) {
        throw new ProjectException("!!PB can't insert a project_step who is already there ") ;
    }

    QSqlDatabase db = connexion_db::get_instance() ;

    //create the a_project
    a_project_db.insert( p , category_id ) ;

    //create the project_step
    if( db.open() ) {
        try {
            QSqlQuery query(db) ;
            query.prepare(" INSERT INTO project_step "
                          " ( id_project, message) "
                          " VALUES( :id_project, :message ); " ) ;
            query.bindValue(":id_project" , p.getId_project() ) ;
            query.bindValue(":message" , p.getComment() ) ;
            if( query.exec() )
            {
                qDebug() << "INSERTION project_step ok" ;
            } else {
                qDebug() << "Echec de l'insertion " << query.executedQuery() ;
            }

            //update of the project id, who is normally unknow, and it is the last insert
            query.prepare( "SELECT MAX(id_project_step) FROM project_step ; " ) ;
            if( query.exec() && query.next() ) {
                qDebug() << "RECUPERATION ID project_step ok" ;
                p.setId_project_step( query.value(0).toInt() ) ;
            } else {
                qDebug() << "!!PB RECUPERATION ID a_project" ;
            }

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

void Project_step_db::remove(const Project_step & p) const
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
            qDebug() << "!!PB  DELETE project step value ok" ;
        }

        //delete the relative a_project corresponding
        a_project_db.remove( p.getId_project() ) ;
    }

}

void Project_step_db::update(const Project_step & p)  const
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

void Project_step_db::add_step(const Project_step& p, Step& s) const {
   step_db.insert( s , p.getId_project_step() ) ; //because step will be modify in order to have a wriht id gave by the database
}

list<Project_step*>* Project_step_db::fetch_all() const {
    list<Project_step*>* projects = new list<Project_step*>() ;
    QSqlDatabase db = connexion_db::get_instance() ;

    if (!db.open()) {
        qDebug() << "Error: connection with database failed";
    } else {
        qDebug() << "Database: connection ok";
        QSqlQuery query(db);
        if ( query.exec("SELECT id_project_step, name, priority, begin_date, end_date, "
                        "comment, description ,"
                        "id_project, id_category FROM category ; ") ) {
            while (query.next()) {
                int id_project_step = query.value(0).toInt() ;
                QString name = query.value(1).toString() ;
                int priority = query.value(2).toInt() ;
                QDate begin  = query.value(3).toDate() ;
                QDate end = query.value(4).toDate() ;
                QString comment = query.value(5).toString() ;
                QString description = query.value(6).toString() ;
                int id_project = query.value(7).toInt();
                int id_category = query.value(8).toInt() ;

                Project_step* tmp = new Project_step(id_project_step, name, priority, begin, end,
                                                     comment, description ,
                                                     id_project, id_category) ;
                tmp->setId_category( id_category) ;
                projects->push_back( tmp ) ;
            }
            return projects ;
        } else {
            qDebug() << "Error: Fetch failed" ;
        }
        db.close();
    }
    return nullptr ;
}


list<Project_step*>* Project_step_db::fetch_all_for_category(int id_category) const {
    list<Project_step*>* projects = new list<Project_step*>() ;
    QSqlDatabase db = connexion_db::get_instance() ;

    if (!db.open()) {
        qDebug() << "Error: connection with database failed";
    } else {
        try {
            qDebug() << "Database: connection ok";
            QSqlQuery query(db);
            query.prepare("SELECT p.id_project_step, a.name, a.priority, a.begin_date, a.end_date, "
                          "a.comment, a.description ,"
                          "a.id_project, a.id_category "
                          "FROM project_step p "
                          "INNER JOIN a_project a ON a.id_project = p.id_project "
                          "WHERE a.id_category = :id_category ;") ;
            query.bindValue(":id_category", id_category) ;
            query.exec() ;
            while (query.next()) {
                int id_project_step = query.value(0).toInt() ;
                QString name = query.value(1).toString() ;
                int priority = query.value(2).toInt() ;
                QDate begin  = query.value(3).toDate() ;
                QDate end = query.value(4).toDate() ;
                QString comment = query.value(5).toString() ;
                QString description = query.value(6).toString() ;
                int id_project = query.value(7).toInt();
                int id_category = query.value(8).toInt() ;
                qDebug() << name ;
                Project_step* tmp = new Project_step(id_project_step, name, priority, begin, end,
                                                     comment, description ,
                                                     id_project, id_category) ;
                tmp->setId_category( id_category) ;
                projects->push_back( tmp ) ;
            }
            qDebug() << "fetch for projects for categories ok " ;
            return projects ;
        } catch (QSqlError* e) {
            qDebug() << "Error: Fetch failed" ;
        }
        db.close();
    }
    return nullptr ;
}


