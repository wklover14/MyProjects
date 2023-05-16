#ifndef ADD_PAGE_H
#define ADD_PAGE_H


#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QScrollBar>

#include "parameters.h"
#include "view/project_picker_view.h"


class Add_project_page : public QWidget
{
    Q_OBJECT
private :
    QLabel* add_page = new QLabel("Add Project");
    Project_picker_view* picker = new Project_picker_view() ;
public :
    Add_project_page(QWidget* parent= nullptr) : QWidget(parent)
    {
        QVBoxLayout* layout = new QVBoxLayout();
        add_page->setStyleSheet( Parameters::title_stylesheet );
        layout->addWidget(add_page);
        layout->addWidget( picker );
        this->setLayout(layout);

        //notify that a project is created
        connect( picker, &Project_picker_view::project_created, this , [this](A_project* a){
            emit project_created(a) ;
        } ) ;
    } ;
    ~Add_project_page(){} ;

signals:
    void project_created(A_project*) ;
};


#endif // ADD_PAGE_H
