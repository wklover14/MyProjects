#include "database/category_db.h"
#include "logic/projectException.h"
#include "database/connexion_db.h"

Category_db::Category_db(){
}

Category_db::~Category_db() {
}

void Category_db::insert(Category& c) {

    if( c.getId_category() != -1 ) {
        throw new ProjectException("!!PB can't insert a category who is already there ") ;
    }

    QSqlDatabase db = connexion_db::get_instance() ;

    if( db.open() ) {
        qDebug() << " connected to database ";
        try {
            QSqlQuery query(db) ;
            query.prepare(" INSERT INTO category(name,color) VALUES (:name, :color ) ; ") ;
            query.bindValue(":name" , c.getName() ) ;
            query.bindValue(":color", c.getColor() ) ;
            if ( query.exec() )
                qDebug() << "insertion category ok" ;
            else
                qDebug() << "Echec d'insertion de category" ;

            //update of the a_project id, who is normally unknow
            query.prepare( "SELECT MAX(id_project) FROM category ; " ) ;

            if( query.exec() && query.next() ) {
                qDebug() << "RECUPERATION ID category ok" ;
                c.setId_category( query.value(0).toInt() ) ;
            } else {
                qDebug() << "!!PB RECUPERATION ID category" ;
            }
        } catch (QException *e) {
            qDebug() << e->what() ;
        }
    } else {
        throw new ProjectException("Unable to make connection with database") ;
    }
    db.close() ;
}

void Category_db::remove(const Category& c){
    QSqlDatabase db = connexion_db::get_instance() ;

    if( db.open() ) {
        qDebug() << " connected to database ";
        try {
            QSqlQuery query(db) ;
            query.prepare(" DELETE FROM category WHERE name = :name;  ") ;
            query.bindValue(":name" , c.getName() ) ;
            query.exec() ;
            qDebug() << "Suppression ok" ;
        } catch (QException *e) {
            qDebug() << e->what() ;
        }
    } else {
        throw new ProjectException("Unable to make connection with database") ;
    }
    db.close() ;
}

list<Category*>* Category_db::fetch(){
        list<Category*>* categories = new list<Category*>() ;
        QSqlDatabase db = connexion_db::get_instance() ;

        if (!db.open()) {
            qDebug() << "Error: connection with database failed";
        } else {
            qDebug() << "Database: connection ok";
            QSqlQuery query(db);
            if ( query.exec(" SELECT id_category, name, color FROM category ; ") ) {
                while (query.next()) {
                    int id_category =  query.value(0).toInt() ;
                    QString name = query.value(1).toString();
                    QString color = query.value(2).toString();
                    Category* tmp = new Category( name, color ) ;
                    tmp->setId_category( id_category) ;
                    categories->push_back( tmp ) ;
                }
                return categories ;
            } else {
                qDebug() << "Error: Fetch failed" ;
            }
            db.close();
        }
        return nullptr ;
}

void Category_db::update(const Category& c){

    QSqlDatabase db = connexion_db::get_instance() ;
    if( db.open() ) {
            qDebug() << " connected to database ";
            try {
                QSqlQuery query(db) ;
                query.prepare(" UPDATE TABLE category SET name= :name, color = :color WHERE name = :name; ") ;
                query.bindValue(":name" , c.getName() ) ;
                query.bindValue(":color" ,  c.getColor() ) ;
                query.exec() ;
                qDebug() << "update ok" ;
        } catch (QException *e) {
            qDebug() << e->what() ;
        }
    } else {
        throw new ProjectException("Unable to make connection with database") ;
    }
    db.close() ;
}
