#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include "step.h"

class Checkpoint : public Step
{
public:
    Checkpoint(QDate d,QString comment, int value);
    ~Checkpoint();
    int getValue() const;

    QWidget* widget(); //surcharge de cette methode

private :
    int value ;
    QWidget* source ;
};

struct checkpointCmp{
    bool operator()(const Checkpoint* a, const Checkpoint* b) const {
        return a->getDate() < b->getDate() ;
    }
};

#endif // CHECKPOINT_H
