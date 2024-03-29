#include "project_value.h"
#include "view/project_value_view.h"

int Project_value::getId_project_value() const
{
    return id_project_value;
}

void Project_value::setId_project_value(int newId_project_value)
{
    id_project_value = newId_project_value;
}

Project_value::Project_value(QString name, int priority,int total_value, int status): A_project(name, priority),total_value(total_value),
    status(status)
{

}

Project_value::~Project_value(){

}

bool Project_value::is_finish() const {
    return status == total_value ;
}

int Project_value::getPercent() const
{
    return status * 100 / total_value ;
}

//getters and setters
int Project_value::getTotal_value() const
{
    return total_value;
}

void Project_value::setTotal_value(int newTotal_value)
{
    total_value = newTotal_value;
}

int Project_value::getStatus() const
{
    return status;
}

void Project_value::setStatus(int newStatus)
{
    status = newStatus;
}

A_project_view* Project_value::widget() {
    if( view == nullptr ){
        view = new Project_value_view(this);
    }
    return view ;
}
