#ifndef PROJECT_STEP_H
#define PROJECT_STEP_H

#include "a_project.h"
#include "step.h"

#include <iostream>
#include <set>

using namespace std ;

class Project_step_view ;

class Project_step : public A_project
{
public:
     using iterator = set<Step*, StepCmp >::iterator ;
private :
    set<Step*, StepCmp> steps ;
    iterator current ;
    A_project_view* view = nullptr ;

public:
    Project_step(QString name, int priority);
    virtual ~Project_step()  ;
    void add_step(QDate new_date, QString new_comment ) ;
    void add_step(Step* m) ;
    void remove_step(Step* m) ;
    Step* getCurrent() ;

    void validate_step() ;
    bool is_finish() const override ;
    int getPercent() const override ;
    A_project_view* widget() override ;
    set<Step*, StepCmp> get_steps() const ;

    iterator begin() {  return steps.begin() ; }
    iterator end() { return steps.end() ; }
};

#endif // PROJECT_STEP_H
