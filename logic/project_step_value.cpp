#include "project_step_value.h"


Project_step_value::Project_step_value(QString name, int priority) : A_project(name, priority),
    adapter(name, priority)
{
}

Project_step_value::~Project_step_value(){

}
void Project_step_value::validate_step(){
    adapter.validate_step() ;
}

bool Project_step_value::is_finish() const {
    return adapter.is_finish() ;
}

int Project_step_value::getPercent() const {
    return adapter.getPercent() ;
}

void Project_step_value::add_Checkpoint(QDate new_date, QString new_comment,int value ){
    Checkpoint* new_checkpoint = new Checkpoint(new_date, new_comment, value) ;
    adapter.add_step(new_checkpoint) ;
}

void Project_step_value::add_Checkpoint(Checkpoint* c){
     adapter.add_step(c) ;
}

void Project_step_value::remove_Checkpoint(Checkpoint* c){
     adapter.remove_step(c) ;
}

Checkpoint* Project_step_value::getCurrent() {
    return dynamic_cast<Checkpoint*>( adapter.getCurrent() ) ; //dowcast, but its not really a downcast
}

set<Checkpoint* , checkpointCmp> Project_step_value::get_checkpoint()  {
    set<Checkpoint* , checkpointCmp> res ;
    for(auto it : adapter){
        res.insert( dynamic_cast<Checkpoint*>(it) ) ;
    }
    return res ;
}

QWidget* Project_step_value::widget() {
    return nullptr ;
}
