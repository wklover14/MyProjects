#ifndef A_PROJECT
#define A_PROJECT

#include <iostream>
#include <QString>
#include <QDate>
#include <QFile>

using namespace std ;

class A_project {
public :
    virtual void validate_step() = 0 ;
    virtual bool is_finish() const = 0 ;

    //getters and setters

    const QString &getName() const;
    void setName(const QString &newName);

    const QDate &getBegin_date() const;
    void setBegin_date(const QDate &newBegin_date);

    const QDate &getEnd_date() const;
    void setEnd_date(const QDate &newEnd_date);

    const QString &getComment() const;
    void setComment(const QString &newComment);

    const QString &getDescription() const;
    void setDescription(const QString &newDescription);

    int getPriority() const;
    void setPriority(int newPriority);

protected :
    QString name ;
    QDate begin_date ;
    QDate end_date ;
    QString comment ;
    QString description ;
    list<QFile> documents ;
    int priority ;
};

#endif
