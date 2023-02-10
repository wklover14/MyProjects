#ifndef A_PROJECT
#define A_PROJECT

#include <iostream>
#include <set>
#include <QString>
#include <QDate>
#include <QFile>
#include <QWidget>

using namespace std ;

class A_project {
public :
    virtual bool is_finish() const = 0 ;
    virtual int getPercent() const = 0 ;
    virtual QWidget* widget() = 0 ; //this method return a unique view on a project, if this view doesn't exist it'll be created

    virtual ~A_project() = default ;
    A_project(QString name, int priority);

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
