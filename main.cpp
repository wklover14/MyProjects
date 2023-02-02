//#include "mainwindow.h"

//#include <QApplication>

#include "logic/quantifiable_project.h"
#include "logic/checkpoint.h"

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();
    qDebug() << "Hello world " ;
    Quantifiable_project p(100, 0) ;
    Checkpoint c4( QDate(2023,02, 26) , 100 ) ;
    Checkpoint c1( QDate(2023,01, 31) , 10 ) ;
    Checkpoint c2( QDate(2023,02, 3) , 25 ) ;
    Checkpoint c3( QDate(2023,02, 10) , 65 ) ;


    p.addCheckPoint(&c1) ; p.addCheckPoint(&c2) ; p.addCheckPoint(&c3) ;
    p.addCheckPoint(&c4) ;

     qDebug() << "Hello world " ;
    //qDebug() << p.getCurrent()->getDate() ;

    for( auto it : p ){
        qDebug() << it->getDate() << "  " << it->getValue() ;
    }

    return 0 ;
}
