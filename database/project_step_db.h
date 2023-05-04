#ifndef PROJECT_STEP_DB_H
#define PROJECT_STEP_DB_H

#include "logic/project_step.h"
#include "database/a_project_db.h"
#include "database/step_db.h"

class project_step_db
{
private:
    step_db  step_db ;
    a_project_db a_project_db ;
public:
    project_step_db();
    ~project_step_db() ;
    void insert(const Project_step& , int ) ;
    void remove(const Project_step& ) ;
    void update(const Project_step& ) ;
};

#endif // PROJECT_STEP_DB_H
