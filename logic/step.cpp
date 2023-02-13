#include "step.h"

Step::Step(QDate d, QString comment): date(d), is_done(false), comment(comment)
{
}

Step::~Step(){

}

const QDate &Step::getDate() const
{
    return date;
}

void Step::setDate(const QDate &newDate)
{
    date = newDate;
}

bool Step::getIs_done() const
{
    return is_done;
}

void Step::setIs_done(bool newIs_done)
{
    is_done = newIs_done;
}

const QString &Step::getComment() const
{
    return comment;
}

void Step::setComment(const QString &newComment)
{
    comment = newComment;
}