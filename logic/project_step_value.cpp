#include "project_step_value.h"
#include "view/project_step_value_view.h"


int Project_step_value::getId_project_step_value() const
{
    return id_project_step_value;
}

void Project_step_value::setId_project_step_value(int newId_project_step_value)
{
    id_project_step_value = newId_project_step_value;
}

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

bool Project_step_value::check_add_checkpoint(Checkpoint* c){
    bool rs = true ;
    message = "" ;
    //verify if the value and the date are consistent
    for( auto it : Project_step::get_steps() ){
        auto tmp = dynamic_cast<Checkpoint*>(it) ;
        if( (tmp->getDate() > c->getDate() && tmp->getValue() < c->getValue() ) ||
            (tmp->getDate() < c->getDate() && tmp->getValue() > c->getValue() ) )
        {
            rs = false ;
            message += "Checkpoint { " + tmp->getDate().toString() +  " / " + QString::number( tmp->getValue() ) + " } is incompatible" ;
            break ;
        }
    }
    return rs ;
}

void Project_step_value::add_Checkpoint(QDate new_date, QString new_comment,int value ){
    Checkpoint* new_checkpoint = new Checkpoint(new_date, new_comment, value) ;
    if( ! check_add_checkpoint(new_checkpoint) ) {
        throw new ProjectException(message) ;
    }
    Project_step::add_step(new_checkpoint) ;
}

void Project_step_value::add_Checkpoint(Checkpoint* c){
    if( ! check_add_checkpoint(c) ) {
        throw new ProjectException(message) ;
    }
     Project_step::add_step(c) ;
}

void Project_step_value::remove_Checkpoint(Checkpoint* c){
     Project_step::remove_step(c) ;
}

void Project_step_value::update_checkpoint(Checkpoint* c){
     Project_step::update_step( c ) ;
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
