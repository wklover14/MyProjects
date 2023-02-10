#ifndef TEXT_PICKER_H
#define TEXT_PICKER_H

#include <QLabel>
#include <QWidget>
#include <QInputDialog>
#include <QMouseEvent>
#include "parameters.h"

class Text_picker : public QLabel
{
    Q_OBJECT
public :
    Text_picker(QWidget* parent=nullptr): QLabel(parent)
    {
        this->setAcceptDrops(true);
        this->setStyleSheet(Parameters::text_stylesheet_1) ;
        connect(this, &Text_picker::mouseDoubleClickEvent, this , &Text_picker::handle_double_click ) ;
    }
    ~Text_picker(){} ;

private slots:
    void handle_double_click(QMouseEvent* event){
        bool ok = true ;
        QString rs = QInputDialog::getText(nullptr, "Change name" , "Enter the new name" ,
                                           QLineEdit::Normal, QString(QLabel::text()) , &ok  ) ;
        if(ok){
            QLabel::setText(rs) ;
            emit value_changed(rs) ;
        }
        event->isBeginEvent() ; //in order to avoid warnings
    }

signals :
    void mouseDoubleClickEvent(QMouseEvent* event) ;
    void mousePressEvent(QMouseEvent* event) ;
    void value_changed(QString);
};

#endif // TEXT_PICKER_H
