#include "project_value.h"

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

QWidget* Project_value::widget() {
    return nullptr ;
}
