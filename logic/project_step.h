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
    int id_project_step  = -1 ;
    set<Step*, StepCmp> steps ;
    iterator current ; //the first unvalidate step
    A_project_view* view = nullptr ;
    QString message = "" ;


public:
    Project_step(QString name, int priority);
    Project_step(int id_project_step, QString name, int priority, QDate begin, QDate end,
                 QString comment, QString description ,
                 int id_project, int id_category ) ;
    virtual ~Project_step()  ;
    bool check_step_add(Step* s) ;
    void add_step(QDate new_date, QString new_comment ) ;
    void add_step(Step* m) ;
    void remove_step(Step* m) ;
    Step* getCurrent() ;

    void validate_step() ;
    void update_step(Step* s) ;
    bool is_finish() const override ;
    int getPercent() const override ;
    A_project_view* widget() override ;
    set<Step*, StepCmp> get_steps() const ;

    iterator begin() {  return steps.begin() ; }
    iterator end() { return steps.end() ; }

    iterator begin() const {  return steps.begin() ; }
    iterator end() const  { return steps.end() ; }

    int getId_project_step() const;
    void setId_project_step(int newId_project_step);
};

#endif // PROJECT_STEP_H
