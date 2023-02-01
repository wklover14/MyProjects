#ifndef DATE_PICKER_H
#define DATE_PICKER_H

#include <QWidget>
#include <QMouseEvent>
#include <QDate>

namespace Ui {
class Date_picker;
}

class Date_picker : public QWidget
{
    Q_OBJECT

public:
    explicit Date_picker(QWidget *parent = nullptr);
    ~Date_picker();

private:
    Ui::Date_picker *ui;
    QDate selectedDate = QDate::currentDate() ;

signals :
    void mousePressEvent(QMouseEvent* e) override ;

private slots:
    //handle click
    void handleClick(QMouseEvent* mouseClickEvent) ;

    //handle POP PUP

};

#endif // DATE_PICKER_H
