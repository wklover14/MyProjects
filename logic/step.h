#ifndef STEP_H
#define STEP_H

#include <QDate>

class Step
{
public:
    Step(QDate d, QString comment = "");
    virtual ~Step() ;
    const QDate &getDate() const;
    void setDate(const QDate &newDate);

    bool getIs_done() const;
    void setIs_done(bool newIs_done);

    const QString &getComment() const;
    void setComment(const QString &newComment);

protected :
    QDate date ;
    bool is_done ;
    QString comment ;
};

struct StepCmp{
    bool operator()(Step* a, Step* b) const{
        return a->getDate() < b->getDate() ;
    }
};

#endif // STEP_H
