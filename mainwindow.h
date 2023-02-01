#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "date_picker.h"
#include "color_picker.h"
#include "milestone_widget.h"
#include "carrousel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Date_picker d ;
    Color_picker p ;
    Milestone_widget m ;
    Carrousel c ;
};
#endif // MAINWINDOW_H
