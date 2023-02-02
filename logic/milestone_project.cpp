#include "milestone_project.h"

Milestone_project::Milestone_project() : A_project()
{
    current = milestones.begin() ;
    getCurrent() ; //update to the last value
}

Milestone_project::~Milestone_project(){
    for(auto i : milestones){
       delete i  ;
    }
}

void Milestone_project::add_milestone(QDate new_date, QString new_comment ){
    Milestone* m = new Milestone(new_date, new_comment) ;
    milestones.insert(m) ;
}
void Milestone_project::add_milestone(Milestone* m) { //we need to use this method only for Milestone creates with a new
     milestones.insert(m) ;
}

void Milestone_project::remove_milestone(Milestone* m){
    milestones.erase(m) ;
}

Milestone* Milestone_project::getCurrent(){
    for(auto it : milestones){
        if( ! it->getIs_done() ){
            current = milestones.find(it) ;
            break ;
        }
    }
    return *current ;
}

void Milestone_project::validate_step(){
    if( is_finish() ) { return  ; }
    ( *current )->setIs_done(true) ;
    current++ ;
}

bool Milestone_project::is_finish() const {
    iterator last = milestones.end() ;
    last-- ;
    return (*last)->getIs_done()  && last != milestones.begin() ;
}
