#ifndef CATEGORY_DB_H
#define CATEGORY_DB_H

#include <iostream>
#include <list>
#include "logic/category.h"

using namespace std ;

class Category_db
{
public :
    Category_db() ;
    ~Category_db() ;
    void insert(const Category& ) ;
    void remove(const Category& ) ;
    void update(const Category& ) ;
    list<Category*>* fetch() ;

};

#endif // CATEGORY_DB_H
