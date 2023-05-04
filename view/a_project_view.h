#ifndef A_PROJECT_VIEW_H
#define A_PROJECT_VIEW_H

#include <QWidget>
#include "logic/a_project.h"

//recurssif inlcusion
class A_project ;

class A_project_view : public QWidget
{
    Q_OBJECT
private:

public:
    A_project_view(QWidget* parent=nullptr) : QWidget(parent) {} ;
    virtual ~A_project_view(){};

signals:
    void source_modified(A_project* a) ;
};

#endif // A_PROJECT_VIEW_H
