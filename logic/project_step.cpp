#include "project_step.h"
#include "view/project_step_view.h"

Project_step::Project_step(QString name, int priority) : A_project(name, priority)
{
    current = steps.begin() ;
    getCurrent() ; //update to the last value
}

Project_step::~Project_step(){
    for(auto i : steps){
       delete i  ;
    }
}

void Project_step::add_step(QDate new_date, QString new_comment ){
    Step* m = new Step(new_date, new_comment) ;
    steps.insert(m) ;
}
void Project_step::add_step(Step* m) { //we need to use this method only for Milestone creates with a new
     steps.insert(m) ;
}

void Project_step::remove_step(Step* m){
    steps.erase(m) ;
}

set<Step*, StepCmp> Project_step::get_steps() const {
    return steps ;
}

Step* Project_step::getCurrent(){
    for(auto it : steps){
        if( ! it->getIs_done() ){
            current = steps.find(it) ;
            break ;
        }
    }
    return *current ;
}

void Project_step::validate_step(){
    if( is_finish() ) { return  ; }
    ( *current )->setIs_done(true) ;
    current++ ;
}

bool Project_step::is_finish() const {
    iterator last = steps.end() ;
    last-- ;
    return (*last)->getIs_done()  && last != steps.begin() ;
}

int Project_step::getPercent() const {
    int total = steps.size() ;
    int status = 0 ;
    for( auto it : steps ){
        if( it->getIs_done() )
            status++;
    }

    return total != 0 ? status * 100 / total : 0 ;
}

QWidget* Project_step::widget() {
    if( view == nullptr )
        view = new Project_step_view(this) ;
    return view ;
}

