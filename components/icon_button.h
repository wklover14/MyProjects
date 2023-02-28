#ifndef ICON_BUTTON_H
#define ICON_BUTTON_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
#include <QEvent>
#include <QPropertyAnimation>

#include "parameters.h"

class Icon_button : public QWidget
{
    Q_OBJECT
private:
    QString path ;
    QLabel* label = new QLabel() ;
public:
    Icon_button(QString icon_path = Parameters::path_plus , QWidget* parent = nullptr): QWidget(parent),
        path(icon_path)
    {
        label->setPixmap( QPixmap(path) ) ;
        label->setStyleSheet( Parameters::icon_stylesheet  ) ;
        QVBoxLayout* layout = new QVBoxLayout() ;
        layout->addWidget( label ) ;

        this->setLayout( layout ) ;
        this->setAcceptDrops( true ) ;
    }
    ~Icon_button() {};

signals :
    void released() ;
    void mousePressEvent(QMouseEvent* e) override ;

//animation
protected :
    bool event(QEvent* event) override {
        if( event->type() == QEvent::Enter) {
            QPropertyAnimation *animation = new QPropertyAnimation(this, "size");
            animation->setDuration(200);
            animation->setStartValue(QSize(width(), height()));
            animation->setEndValue(QSize( width() * 1.1 , height() * 1.1 ));
            animation->start(QAbstractAnimation::DeleteWhenStopped);
        } else if ( event->type() == QEvent::Leave ) {
            // Start animation when the mouse leaves the widget
             QPropertyAnimation *animation = new QPropertyAnimation(this, "size");
             animation->setDuration(200);
             animation->setStartValue(QSize(width()*1.1, height() * 1.1 ));
             animation->setEndValue(QSize( width(), height() ));
             animation->start(QAbstractAnimation::DeleteWhenStopped);
        }
        return QWidget::event(event) ;
    }

};

#endif // ICON_BUTTON_H
