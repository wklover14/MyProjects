#ifndef PROJECT_STEP_VALUE_H
#define PROJECT_STEP_VALUE_H

#include "logic/checkpoint.h"
#include "project_step.h"


#include <iostream>
#include <set>

using namespace std ;

class Project_step_value : public A_project
{
public:
     using iterator = Project_step::iterator ;

private:
    Project_step adapter;
    A_project_view* view = nullptr ;

public:
    Project_step_value(QString name, int priority);
    ~Project_step_value() ;

    void validate_step() ;
    bool is_finish() const override ;
    int getPercent() const override ;
    A_project_view* widget() override ;
    void add_Checkpoint(QDate new_date, QString new_comment,int value ) ;
    void add_Checkpoint(Checkpoint* c) ;
    void remove_Checkpoint(Checkpoint* c) ;
    Checkpoint* getCurrent() ;
    set<Checkpoint* , checkpointCmp> get_checkpoint()  ;

    iterator begin(){ return adapter.begin() ;}
    iterator end(){ return adapter.end() ; }
};

#endif // PROJECT_STEP_VALUE_H
