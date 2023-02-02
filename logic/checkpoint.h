#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include <QDate>

class Checkpoint
{
public:
    Checkpoint(QDate d, int value);

    void setDate(const QDate &newDate);

    int getValue() const;

    bool getIs_donne() const;

    const QDate &getDate() const;

    void setIs_donne(bool newIs_donne);

private :
    QDate date ;
    bool is_donne ;
    int value ;
};

struct checkpointCmp{
    bool operator()(const Checkpoint* a, const Checkpoint* b) const {
        return a->getDate() < b->getDate() ;
    }
};

#endif // CHECKPOINT_H
