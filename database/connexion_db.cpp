#include "connexion_db.h"
#include "logic/projectException.h"

QSqlDatabase* connexion_db::unique_instance  = nullptr ;
const QString connexion_db::host_name = "localhost";
const QString connexion_db::database_name = "projectManager";
QString connexion_db::user_name = "";
QString connexion_db::password = "" ;

connexion_db::connexion_db(const QString user_name,const QString password)
{
    this->user_name = user_name ;
    this->password = password ;

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", "unique_instance") ;
    db.setHostName(this->host_name) ;
    db.setDatabaseName(this->database_name) ;
    db.setUserName(this->user_name) ;
    db.setPassword(this->password) ;

    unique_instance = new QSqlDatabase(db) ;
}

connexion_db::connexion_db(const connexion_db& c){
    this->user_name = c.user_name ;
    this->password = c.password ;
}

connexion_db::~connexion_db(){

}

void connexion_db::operator=(const connexion_db& c){
    connexion_db::unique_instance = c.unique_instance ;
}

QSqlDatabase connexion_db::get_instance() {
    if( unique_instance == nullptr  ){
        throw new ProjectException("You can't create a connection from here!!\n Contact your administration") ;
    }
    return *( connexion_db::unique_instance );
}

void connexion_db::init_connexion(const QString user_name,const QString password){
    connexion_db::user_name = user_name ;
    connexion_db::password = password ;

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", "unique_instance") ;
    db.setHostName(connexion_db::host_name) ;
    db.setDatabaseName(connexion_db::database_name) ;
    db.setUserName(connexion_db::user_name) ;
    db.setPassword(connexion_db::password) ;

    unique_instance = new QSqlDatabase(db) ;
}

void connexion_db::free_instance() {
    delete unique_instance ;
}

