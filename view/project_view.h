#ifndef PROJECT_VIEW_H
#define PROJECT_VIEW_H

#include <QWidget>
#include <QLabel>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QPalette>
#include <QMouseEvent>

#include "parameters.h"
#include "logic/a_project.h"

class Project_view : public QWidget
{
    //this class provide a progress bar in a category_view
    Q_OBJECT
private :
    QLabel* label = new QLabel() ;
    QProgressBar* status  = new QProgressBar();
    A_project* source ;

public :
    Project_view(A_project* source,QWidget* parent = nullptr) : QWidget(parent), source(source) {
        label->setText(source->getName());
        status->setMaximum( 100 );
        status->setValue( source->getPercent() );
        status->setMaximumSize( Parameters::carrousel_width, 20 );

        label->setStyleSheet(Parameters::text_stylesheet_2) ;
        status->setTextVisible(false) ;

        QVBoxLayout* layout = new QVBoxLayout();
        layout->addWidget(label);
        layout->addWidget(status );

        this->setAcceptDrops(true);
        this->setLayout(layout);
        this->setMaximumSize( Parameters::carrousel_width, Parameters::item_height ) ;
    }
    ~Project_view(){}

    void reload(){
        label->setText(source->getName());
        status->setValue( source->getPercent() );
        this->update();
    }

    void setColor(QColor c){
        QString st = "QProgressBar::chunk{background-color:"+ c.name() + "};";
        status->setStyleSheet( st );
        reload();
    }
    const A_project* get_project() const { return source ;  }

public slots :
    void update_s(A_project* a) {
        reload() ;
        a->widget(); //avoid warning
    }

signals :
    void mousePressEvent(QMouseEvent* event) override ;
};

#endif // PROJECT_VIEW_H
