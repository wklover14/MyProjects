#include "project_step.h"
#include "logic/projectException.h"
#include "view/project_step_view.h"

Project_step::Project_step(int id_project_step, QString name, int priority, QDate begin, QDate end,
                           QString comment, QString description ,
                           int id_project, int id_category ):
                            A_project(name, priority, begin, end,
                            comment, description ,
                            id_project, id_category ),
                            id_project_step(id_project_step)
{

}

int Project_step::getId_project_step() const
{
    return id_project_step;
}

void Project_step::setId_project_step(int newId_project_step)
{
    id_project_step = newId_project_step;
}

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

bool Project_step::check_step_add(Step* s) {
    bool rs = true ;
    message = "" ;
    if( s->getDate() > getEnd_date() || s->getDate() < getBegin_date() ) {
        //error, you can't add step after the end of the project
        message += "You can't add step after the end of the project \n You can't add a step before the begining of the project" ;
        rs = false ;
    }
    return rs ;
}

void Project_step::add_step(QDate new_date, QString new_comment ) {
    Step* m = new Step(new_date, new_comment) ;
    if( !check_step_add(m) ){
        throw new ProjectException(message) ;
    }
    steps.insert(m) ;
}

void Project_step::add_step(Step* m){ //we need to use this method only for Milestone creates with a new
    if( !check_step_add(m) ){
        throw new ProjectException(message) ;
    }
    steps.insert(m) ;
}

void Project_step::remove_step(Step* m){
    steps.erase(m) ;
}

set<Step*, StepCmp> Project_step::get_steps() const {
    return steps ;
}

Step* Project_step::getCurrent(){
    if( steps.empty() ) return nullptr ;

    for(auto it : steps){
        if( ! it->getIs_done() ){
            current = steps.find(it) ;
            break ;
        }
    }
    if( current == steps.end() && current != steps.begin() ) current-- ; //to really have the last element, verify if the carrousel is empty also
    return *current ;
}

void Project_step::validate_step(){
    if( is_finish() ) { return  ; }
    current++ ;
}

void Project_step::update_step(Step* s) {
    //after modifying a step, you need to call this method on his source

    auto tmp = steps.find(s) ;
    getCurrent() ;

    if( tmp == steps.end() ){
        throw new ProjectException(" There is no step !! ") ;
        return ;
    }
    if( s->getDate() > getCurrent()->getDate() ) {
        //You need to validate all the steps which are before
        throw new ProjectException(" You need to validate all the steps which are before !! ") ;
        return ;
    }
    if( ! s->getIs_done() ) {
        //we unvalide all the next steps
        while( tmp != steps.end() ){
            (*tmp)->setIs_done(false) ;
            tmp++;
        }
    }
}

bool Project_step::is_finish() const {
    iterator last = steps.end() ;
    last--;
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

A_project_view* Project_step::widget() {
    if( view == nullptr )
        view = new Project_step_view(this) ;
    return view ;
}

