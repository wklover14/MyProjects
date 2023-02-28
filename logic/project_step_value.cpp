#include "project_step_value.h"
#include "view/project_step_value_view.h"


Project_step_value::Project_step_value(QString name, int priority) : Project_step(name, priority)
{
}

Project_step_value::~Project_step_value(){

}

void Project_step_value::validate_step(){
    Project_step::validate_step() ;
}

bool Project_step_value::is_finish() const {
    return Project_step::is_finish() ;
}

int Project_step_value::getPercent() const {
    return Project_step::getPercent() ;
}

void Project_step_value::add_Checkpoint(QDate new_date, QString new_comment,int value ){
    Checkpoint* new_checkpoint = new Checkpoint(new_date, new_comment, value) ;
    Project_step::add_step(new_checkpoint) ;
}

void Project_step_value::add_Checkpoint(Checkpoint* c){
     Project_step::add_step(c) ;
}

void Project_step_value::remove_Checkpoint(Checkpoint* c){
     Project_step::remove_step(c) ;
}

Checkpoint* Project_step_value::getCurrent() {
    return dynamic_cast<Checkpoint*>( Project_step::getCurrent() ) ; //dowcast, but its not really a downcast
}

set<Checkpoint* , checkpointCmp> Project_step_value::get_checkpoint()  {
    set<Checkpoint* , checkpointCmp> res ;
    for(auto it : Project_step::get_steps()){
        res.insert( dynamic_cast<Checkpoint*>(it) ) ;
    }
    return res ;
}

A_project_view* Project_step_value::widget() {
    if( view == nullptr )
    {
        view = new Project_step_value_view(this) ;
    }
    return view ;
}
