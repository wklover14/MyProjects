#include "checkpoint.h"

Checkpoint::Checkpoint(QDate d, int value): date(d), is_donne(false), value(value)
{

}

//getters only

int Checkpoint::getValue() const
{
    return value;
}

bool Checkpoint::getIs_donne() const
{
    return is_donne;
}

const QDate &Checkpoint::getDate() const
{
    return date;
}

void Checkpoint::setIs_donne(bool newIs_donne)
{
    is_donne = newIs_donne;
}
