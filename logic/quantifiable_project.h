#ifndef QUANTIFIABLE_PROJECT_H
#define QUANTIFIABLE_PROJECT_H

#include "a_project.h"
#include "checkpoint.h"

#include <iostream>
#include <set>

class Quantifiable_project : public A_project
{
private:
    int status ; //the number of items done
    int total_value ; // the total number of item
    set<Checkpoint*, checkpointCmp> checkpoints; // sorted set

    using iterator = set<Checkpoint*, checkpointCmp>::iterator ;
    iterator current ;
public:
    Quantifiable_project(int total_value, int status );
    ~Quantifiable_project() ;
    bool is_finish() const override ;
    void validate_step() override ;

    void addCheckPoint(Checkpoint* c) ;
    void addCheckPoint(QDate d , int value ) ;
    void remove_checkpoint(Checkpoint* c) ;

    //getters and setters
    int getStatus() const;
    void setStatus(int newStatus);

    int getTotal_value() const;
    void setTotal_value(int newTotal_value);

    Checkpoint *getCurrent() ;
    void setCurrent(Checkpoint *newCurrent);

    iterator begin() const { return checkpoints.begin() ; }
    iterator end() const { return checkpoints.end(); }
};

#endif // QUANTIFIABLE_PROJECT_H
