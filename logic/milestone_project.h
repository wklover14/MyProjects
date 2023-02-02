#ifndef MILESTONE_PROJECT_H
#define MILESTONE_PROJECT_H

#include "a_project.h"
#include "milestone.h"

#include <iostream>
#include <set>

using namespace std ;

class Milestone_project : public A_project
{
private :
    set<Milestone*, MilestoneCmp> milestones ;
    using iterator = set<Milestone*, MilestoneCmp >::iterator ;
    iterator current ;

public:
    Milestone_project();
    ~Milestone_project() ;
    void add_milestone(QDate new_date, QString new_comment ) ;
    void add_milestone(Milestone* m) ;
    void remove_milestone(Milestone* m) ;
    Milestone* getCurrent() ;

    void validate_step() override  ;
    bool is_finish() const override ;

    iterator begin() {  return milestones.begin() ; }
    iterator end() { return milestones.end() ; }
};

#endif // MILESTONE_PROJECT_H
