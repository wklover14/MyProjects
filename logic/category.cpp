#include "category.h"

Category::Category(QString name, QString color) : list<A_project*>() ,name(name), color(color)
{
}

void Category::update_name(QString new_name){
    name = new_name ;
}

void Category::remove_project(A_project* a){
    list<A_project*>::remove(a) ;
}

void Category::add_project(A_project* a){
    for(auto it = list<A_project*>::begin() ; it != list<A_project*>::end(); it++ ){
        if ( *it == a ){
            qDebug() << "Element déjà present \n" ;
            return ;
        }
    }
    list<A_project*>::push_back( a );
}
