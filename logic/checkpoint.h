#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include "step.h"

class Checkpoint : public Step
{
public:
    Checkpoint(QDate d,QString comment, int value);
    ~Checkpoint();
    int getValue() const;
    void rollback() override ;

    QWidget* widget() override ; //in order to replace the method inherited from Step

private :
    int value ;
    int id_checkpoint = -1 ;
    QWidget* source = nullptr;
};

struct checkpointCmp{
    bool operator()(const Checkpoint* a, const Checkpoint* b) const {
        return a->getDate() < b->getDate() ;
    }
};

#endif // CHECKPOINT_H
