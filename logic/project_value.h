#ifndef PROJECT_VALUE_H
#define PROJECT_VALUE_H

#include "view/a_project_view.h"


class Project_value : public A_project
{
private:
    int total_value ;
    int status ;
    A_project_view* view = nullptr ;

public:
    Project_value( QString name, int priority,int total_value, int status) ;
    ~Project_value() ;

    bool is_finish() const override ;
    int getPercent() const override ;
    A_project_view* widget() override ;

    int getTotal_value() const;
    void setTotal_value(int newTotal_value);
    int getStatus() const;
    void setStatus(int newStatus) ;
};

#endif // PROJECT_VALUE_H
