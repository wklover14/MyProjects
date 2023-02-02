#ifndef MILESTONE_H
#define MILESTONE_H

#include <QString>
#include <QDate>

class Milestone
{
public:
    Milestone( QDate new_date, QString new_comment = " ") ;
    const QString &getComment() const;
    void setComment(const QString &newComment);

    const QDate &getDate() const;

    bool getIs_done() const;
    void setIs_done(bool newIs_done);

private :
    QString comment ;
    QDate date ;
    bool is_done ;
};

struct MilestoneCmp {
    bool operator()(const Milestone* a,const Milestone* b ) const {
        return a->getDate() < b->getDate() ;
    }
};

#endif // MILESTONE_H
