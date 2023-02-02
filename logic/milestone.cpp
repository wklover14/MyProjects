#include "milestone.h"

Milestone::Milestone( QDate new_date, QString new_comment ) : comment(new_comment), date(new_date), is_done(false)
{
}

const QString &Milestone::getComment() const
{
    return comment;
}

void Milestone::setComment(const QString &newComment)
{
    comment = newComment;
}

const QDate &Milestone::getDate() const
{
    return date;
}

bool Milestone::getIs_done() const
{
    return is_done;
}

void Milestone::setIs_done(bool newIs_done)
{
    is_done = newIs_done;
}
