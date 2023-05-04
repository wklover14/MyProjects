#ifndef STEP_DB_H
#define STEP_DB_H

#include "logic/step.h"

class step_db
{
public:
    step_db();
    ~step_db() ;
    void insert(const Step& , const int& ) const ;
    void remove(const Step& ) const ;
    void update(const Step& ) const ;
};

#endif // STEP_DB_H
