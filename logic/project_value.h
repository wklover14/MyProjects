#ifndef PROJECT_VALUE_H
#define PROJECT_VALUE_H

#include "a_project.h"


class Project_value : public A_project
{
private:
    int total_value ;
    int status ;

public:
    Project_value( QString name, int priority,int total_value, int status) ;
    ~Project_value() ;

    bool is_finish() const override ;
    int getPercent() const override ;
    QWidget* widget() override ;

    int getTotal_value() const;
    void setTotal_value(int newTotal_value);
    int getStatus() const;
    void setStatus(int newStatus) ;
};

#endif // PROJECT_VALUE_H
