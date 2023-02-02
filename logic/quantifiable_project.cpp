#include "quantifiable_project.h"

Quantifiable_project::Quantifiable_project(int total_value, int status ): A_project(),status(status), total_value(total_value)
{
    current = checkpoints.begin();
}
Quantifiable_project::~Quantifiable_project(){
    for( auto it : checkpoints ){
        delete it ;
    }
}

bool Quantifiable_project::is_finish() const
{
    return status == total_value ;
}

void Quantifiable_project::validate_step()
{
    //here we update the chekpoint
    (*current)->setIs_donne(true);
    status = (*current)->getValue() ;
    current++ ;
}

void Quantifiable_project::remove_checkpoint(Checkpoint* c){
    checkpoints.erase(c);
}

void Quantifiable_project::addCheckPoint(Checkpoint* c) { //only for the checkpoint create with the new operator
        checkpoints.insert(c) ;
}

void Quantifiable_project::addCheckPoint(QDate d , int value ) {
    Checkpoint* c = new Checkpoint(d, value) ;
    checkpoints.insert(c) ;
}

//getters and setters

int Quantifiable_project::getStatus() const
{
    return status;
}

void Quantifiable_project::setStatus(int newStatus)
{
    status = newStatus;
}

int Quantifiable_project::getTotal_value() const
{
    return total_value;
}

void Quantifiable_project::setTotal_value(int newTotal_value)
{
    total_value = newTotal_value;
}

Checkpoint* Quantifiable_project::getCurrent()
{
    for( auto it : checkpoints ){
        if( ! it->getIs_donne() ){
            current = checkpoints.find(it) ;
            break ;
        }
    }
    return *current ;
}

void Quantifiable_project::setCurrent(Checkpoint *newCurrent)
{
    current = checkpoints.find(newCurrent) ;
}
