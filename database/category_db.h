#ifndef CATEGORY_DB_H
#define CATEGORY_DB_H

#include "logic/category.h"

class Category_db
{
public :
    Category_db() ;
    ~Category_db() ;
    void insert(const Category& ) ;
    void remove(const Category& ) ;
    void fetch() ;

};

#endif // CATEGORY_DB_H
