#include "checkpoint.h"

Checkpoint::Checkpoint(QDate d,QString comment ,int value): Step(d, comment), value(value)
{

}

Checkpoint::~Checkpoint(){

}
//getters only

int Checkpoint::getValue() const
{
    return value;
}

