#include "a_project.h"

A_project::A_project(QString name, int priority) : name(name),priority(priority){

}

//getters and setters

const QString &A_project::getName() const
{
    return name;
}

void A_project::setName(const QString &newName)
{
    name = newName;
}

const QDate &A_project::getBegin_date() const
{
    return begin_date;
}

void A_project::setBegin_date(const QDate &newBegin_date)
{
    begin_date = newBegin_date;
}

const QDate &A_project::getEnd_date() const
{
    return end_date;
}

void A_project::setEnd_date(const QDate &newEnd_date)
{
    end_date = newEnd_date;
}

const QString &A_project::getComment() const
{
    return comment;
}

void A_project::setComment(const QString &newComment)
{
    comment = newComment;
}

const QString &A_project::getDescription() const
{
    return description;
}

void A_project::setDescription(const QString &newDescription)
{
    description = newDescription;
}

int A_project::getPriority() const
{
    return priority;
}

void A_project::setPriority(int newPriority)
{
    priority = newPriority;
}
