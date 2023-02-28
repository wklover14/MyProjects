#ifndef PROJECTEXCEPTION_H
#define PROJECTEXCEPTION_H

#include <QString>
#include <QException>

class ProjectException : public QException {
    QString message ;

public :
    ProjectException(QString new_message = "Error") : QException(), message(new_message) {
    }
    ~ProjectException() {} ;
    QString get_message() const { return message ; }
    void raise() const override { throw *this; }
    ProjectException* clone() const override { return new ProjectException(*this); }
};

#endif // PROJECTEXCEPTION_H
