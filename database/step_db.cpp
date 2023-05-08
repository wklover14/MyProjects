#include "step_db.h"
#include "logic/step.h"
#include "logic/projectException.h"
#include "database/connexion_db.h"

step_db::step_db()
{
}

step_db::~step_db()
{
}

void step_db::insert(const Step& s, const int& project_step_id ) const
{
    QSqlDatabase db = connexion_db::get_instance() ;

    if( db.open() ) {
        qDebug() << " connected to database ";
        try {
            QSqlQuery query ;
            query.prepare(" INSERT INTO step "
                          " ( id_project_step, date, is_done, comment )"
                          "VALUES( :id_project_step, :date, :is_done, :comment );" ) ;
            query.bindValue(":id_project_step " , project_step_id ) ;
            query.bindValue(":date" ,  s.getDate() ) ;
            query.bindValue(":is_done", s.getIs_done() ) ;
            query.bindValue(":comment" , s.getComment() ) ;
            query.exec() ;
            qDebug() << "INSERTION from step ok" ;
        } catch (QSqlError *e) {
            qDebug() << e->text() ;
        }
    } else {
        throw new ProjectException("Unable to make connection with database") ;
    }
    db.close() ;
}

void step_db::remove(const Step & s) const
{
    QSqlDatabase db = connexion_db::get_instance() ;

    if( db.open() ) {
        qDebug() << " connected to database ";
        try {
            QSqlQuery query(db) ;
            query.prepare("DELETE FROM step"
                          " WHERE id_step =  :id_step ;" ) ;
            query.bindValue(":id_step" , s.getId_step() ) ;
            query.exec() ;
            qDebug() << "DELETE from step ok" ;
        } catch (QSqlError *e) {
            qDebug() << e->text() ;
        }
    } else {
        throw new ProjectException("Unable to make connection with database") ;
    }
    db.close() ;
}

void step_db::update(const Step & s) const
{
    QSqlDatabase db = connexion_db::get_instance() ;

    if( db.open() ) {
        qDebug() << " connected to database ";
        try {
            QSqlQuery query(db) ;
            query.prepare(" UPDATE step "
                          " SET date = :date, is_done = :is_done, comment = :comment "
                          " WHERE id_step = :id_step ; " ) ;
            query.bindValue(":date" , s.getDate() ) ;
            query.bindValue(":is_done", s.getIs_done() ) ;
            query.bindValue(":comment", s.getComment()) ;
            query.bindValue(":id_step" , s.getId_step() ) ;
            query.exec() ;
            qDebug() << "Update from step ok" ;
        } catch (QSqlError *e) {
            qDebug() << e->text() ;
        }
    } else {
        throw new ProjectException("Unable to make connection with database") ;
    }
    db.close() ;
}

void step_db::remove_for_project(const int id_project_step) const {
    QSqlDatabase db = connexion_db::get_instance() ;

    if( db.open() ) {
        qDebug() << " connected to database ";
        try {
            QSqlQuery query(db) ;
            query.prepare("DELETE FROM step"
                          "WHERE id_project_step = :id_project_step") ;
            query.bindValue(":id_project_step", id_project_step) ;
            query.exec() ;
            qDebug() << "DELETE for a project from step ok" ;
        } catch (QSqlError *e) {
            qDebug() << e->text() ;
        }
    } else {
        throw new ProjectException("Unable to make connection with database") ;
    }
    db.close() ;
}
