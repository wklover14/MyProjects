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

list<A_project*> Category::get_project() const {
    list<A_project*> categories  ;
    for( auto it = list<A_project*>::begin() ; it != list<A_project*>::end(); it++){
        categories.push_back( *it ) ;
    }
    return categories ;
}

const QString &Category::getColor() const
{
    return color;
}

void Category::setColor(const QString &newColor)
{
    color = newColor;
}

const QString &Category::getName() const
{
    return name;
}

void Category::setName(const QString &newName)
{
    name = newName;
}
