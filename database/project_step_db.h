#ifndef PROJECT_STEP_DB_H
#define PROJECT_STEP_DB_H

#include <list>

#include "logic/project_step.h"
#include "database/a_project_db.h"
#include "database/step_db.h"

class Project_step_db
{
private:
    step_db  step_db ;
    a_project_db a_project_db ;

public:
    Project_step_db();
    ~Project_step_db() ;
    void insert(Project_step& , int ) const;
    void remove(const Project_step& ) const;
    void update(const Project_step& ) const;
    void add_step(const Project_step&, Step&) const;
    list<Project_step*>* fetch_all_for_category(int category_id) const ;
    list<Project_step*>* fetch_all() const ;
};

#endif // PROJECT_STEP_DB_H
