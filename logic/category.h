#ifndef CATEGORY_H
#define CATEGORY_H

#include <QString>
#include <iostream>
#include <list>

#include "parameters.h"
#include "a_project.h"

using namespace std ;

//Class Adaptator design pattern
class Category : private list<A_project*>
{
public:
    Category(QString name, QString color = Parameters::colors_name[ COLORS::salmon ]);
    void update_name(QString new_name) ;
    void remove_project(A_project* a) ;
    void add_project(A_project* a) ;

private :
    QString name ;
    QString color ;
};

#endif // CATEGORY_H
