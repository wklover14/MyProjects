#include "database/category_db.h"
#include "logic/projectException.h"
#include "database/connexion_db.h"

Category_db::Category_db(){
}

Category_db::~Category_db() {
}

void Category_db::insert(const Category& c) {
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
            if ( query.exec(" SELECT name, color FROM category ; ") ) {
                while (query.next()) {
                    QString name = query.value(0).toString();
                    QString color = query.value(1).toString();
                    qDebug() << "fetch = " << name << " : " << color ;
                    categories->push_back( new Category( name, color ) ) ;
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
