#ifndef COLORFUL_CIRCLE_H
#define COLORFUL_CIRCLE_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

#include "parameters.h"


class Colorful_circle : public QWidget
{
    //this class provide a simple circle with a color,
    //you can change the color with the constructor or with a predefine method
    Q_OBJECT
public:
    explicit Colorful_circle(QString new_color =  Parameters::hexa_code_colors[ COLORS::lavender ] ,
                             QWidget* parent = nullptr,
                             int height = Parameters::color_shape_height,
                             int width = Parameters::color_shape_weight
                             ): QWidget(parent), color(new_color) {
        setFixedWidth( width ) ;
        setFixedHeight( height ) ;
        setContentsMargins(0,0,0,0);
    }
    ~Colorful_circle(){}
    void setColor(QString color){
        this->color = QColor::fromString(color) ;
        this->update() ;
    }
    void setColor(QColor color){
        this->color = color ;
        this->update() ;
    }
    const QColor& getColor()const{ return color; }
protected :
    QColor color ;
    void paintEvent(QPaintEvent* event ){
        QPainter painter(this) ;
        painter.setPen(Qt::NoPen) ;
        painter.setBrush( QBrush(color, Qt::SolidPattern) ) ;
        painter.drawEllipse( QPoint( width()/2, height()/2 ), width()/2 , height()/2 ) ;
        if (event == nullptr)//in order to avoid the warning
            qDebug() ;
    }

} ;



#endif // COLORFUL_CIRCLE_H
