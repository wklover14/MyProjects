#ifndef DOCUMENTS_H
#define DOCUMENTS_H

#include <QString>
#include <QFile>

class Documents
{
public:
    Documents();
private :
    QString name ;
    QFile doc ;
};

#endif // DOCUMENTS_H
