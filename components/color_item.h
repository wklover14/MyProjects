#ifndef COLOR_ITEM_H
#define COLOR_ITEM_H

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QHBoxLayout>
#include <QPropertyAnimation>
#include <QFont>

#include "Colorful_circle.h"

class Color_item : public QWidget {
    Q_OBJECT

public:
    // explicit Color_item(QWidget* parent = nullptr) : QWidget(parent){} ;
    explicit Color_item(QString color, QString label, QWidget* parent = nullptr ):QWidget(parent),
        image(color, nullptr)
    {
        text.setText(label) ;
        layout.addWidget(&image) ;
        layout.addWidget(&text) ;
        this->setLayout(&layout) ;
        this->setAcceptDrops(true) ;
        layout.setContentsMargins(0, 0, 0, 0) ; //spacing will be done by their parent
    }
    ~Color_item() {} ;

    void setColor(QString color){ image.setColor(color) ; }
    void setColor(QColor color){ image.setColor(color) ; }
    void setText(QString text){  this->text.setText( text ) ; }
    const QColor& getColor() const { return image.getColor() ;}
    QString getLabel() const { return text.text() ; }

private :
    Colorful_circle image ;
    QLabel text ;
    QHBoxLayout layout ;

signals:
    void mousePressEvent(QMouseEvent* e) override;

//animation
protected :
    bool event(QEvent* event) override {
        if( event->type() == QEvent::Enter){
            //put text in Bold
            QFont font = text.font() ;
            font.setBold(true) ;
            text.setFont(font) ;
            //start animation when the mouse enter
            QPropertyAnimation *animation = new QPropertyAnimation(this, "size");
            animation->setDuration(200);
            animation->setStartValue(QSize(width(), height()));
            animation->setEndValue(QSize( width() * 1.3 , height() * 1.3 ));
            animation->start(QAbstractAnimation::DeleteWhenStopped);

        } else if( event->type() == QEvent::Leave) {
            //Put text non Bold
            QFont font = text.font() ;
            font.setBold(false) ;
            text.setFont(font) ;
            // Start animation when the mouse leaves the widget
             QPropertyAnimation *animation = new QPropertyAnimation(this, "size");
             animation->setDuration(200);
             animation->setStartValue(QSize(width()*1.3, height() * 1.3 ));
             animation->setEndValue(QSize( width(), height() ));
             animation->start(QAbstractAnimation::DeleteWhenStopped);
             text.setStyleSheet("text-decoration : none ; ") ;
        }
        return QWidget::event(event) ;
    }

};

#endif // COLOR_ITEM_H
