#ifndef COLOR_PICKER_H
#define COLOR_PICKER_H

#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>
#include <QVBoxLayout>
#include "Colorful_circle.h"

class Color_picker : public QWidget
{
    Q_OBJECT

public:
    explicit Color_picker(QWidget *parent = nullptr) ;
    ~Color_picker();

private:
    Colorful_circle item ; //what you will see
    QVBoxLayout *layout = new QVBoxLayout();

signals :
    void mousePressEvent(QMouseEvent* e) override ;

private slots:
    //handle click //generate the color selector
    void handleClick(QMouseEvent* mouseClickEvent) ;


};

#endif // COLOR_PICKER_H
