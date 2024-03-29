#ifndef PROJECT_STEP_VALUE_H
#define PROJECT_STEP_VALUE_H

#include "logic/checkpoint.h"
#include "project_step.h"


#include <iostream>
#include <set>

using namespace std ;

class Project_step_value : public Project_step
{
public:
     using iterator = Project_step::iterator ;

private:
    int id_project_step_value = - 1 ;
    A_project_view* view = nullptr ;
    QString message;

public:
    Project_step_value(QString name, int priority);
    Project_step_value(int id_project_step_value,int id_project_step, QString name, int priority, QDate begin, QDate end,
                 QString comment, QString description ,
                 int id_project, int id_category ) ;
    ~Project_step_value() ;

    void validate_step() ;
    bool is_finish() const override ;
    int getPercent() const override ;
    A_project_view* widget() override ;
    void add_Checkpoint(QDate new_date, QString new_comment,int value ) ;
    void add_Checkpoint(Checkpoint* c) ;
    void remove_Checkpoint(Checkpoint* c) ;
    void update_checkpoint(Checkpoint* c) ;
    bool check_add_checkpoint(Checkpoint* c) ;
    Checkpoint* getCurrent() ;
    set<Checkpoint* , checkpointCmp> get_checkpoint()  ;

    iterator begin(){ return Project_step::begin() ;}
    iterator end(){ return Project_step::end() ; }
    int getId_project_step_value() const;
    void setId_project_step_value(int newId_project_step_value);
};

#endif // PROJECT_STEP_VALUE_H
