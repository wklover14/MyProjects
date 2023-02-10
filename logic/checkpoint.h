#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include "step.h"

class Checkpoint : public Step
{
public:
    Checkpoint(QDate d,QString comment, int value);
    ~Checkpoint();
    int getValue() const;

private :
    int value ;
};

struct checkpointCmp{
    bool operator()(const Checkpoint* a, const Checkpoint* b) const {
        return a->getDate() < b->getDate() ;
    }
};

#endif // CHECKPOINT_H
