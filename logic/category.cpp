#include "category.h"
#include "view/category_view.h"

Category::Category(QString name, QString color) : list<A_project*>() ,name(name), color(color)
{
}

void Category::update_name(QString new_name){
    name = new_name ;
}

void Category::remove_project(A_project* a){
    list<A_project*>::remove(a) ;

    //widget
    Category_view* tmp = dynamic_cast<Category_view*>( widget() ) ;
    tmp->remove_project(a) ;
}

void Category::add_project(A_project* a){
    for(auto it = list<A_project*>::begin() ; it != list<A_project*>::end(); it++ ){
        if ( *it == a ){
            qDebug() << "Element déjà present \n" ;
            return ;
        }
    }
    list<A_project*>::push_back( a );

    //widget
    Category_view* tmp = dynamic_cast<Category_view*>(widget()) ;
    tmp->add_project(a) ;
}

QWidget* Category::widget() {
    if( view == nullptr ) {
        view = new Category_view(this) ;
    }
    return view ;
}

void Category::reload() {
    if( view == nullptr ) return  ;
    Category_view* tmp = dynamic_cast<Category_view*>(view) ;
    qDebug() << "Widget = " << view ;
    qDebug() << " Tmp =" << tmp ;
    tmp->reload() ;
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
