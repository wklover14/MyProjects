#include "mainwindow.h"
#include <QApplication>

//#include "logic/milestone_project.h"
//#include "components/menu.h"

int main(int argc, char *argv[])
{
      QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

//    qDebug() << "Hello world " ;
//    Milestone_project p ;
//    qDebug() << "Hello world " ;
//    p.add_milestone( QDate(2023,02, 26) , "Milestone 4" ) ;
//    p.add_milestone( QDate(2023,01, 31) , "Milestone 1" ) ;
//    p.add_milestone( QDate(2023,02, 3) , "Milestone 2"  ) ;
//    p.add_milestone( QDate(2023,02, 10) , "Milestone 3"  ) ;


//    p.add_milestone(&c1) ; p.add_milestone(&c2) ; p.add_milestone(&c3) ;
//    p.add_milestone(&c4) ;

//    qDebug() << "Hello world " ;
//    qDebug() << p.getCurrent()->getDate() ;

//    for( auto it : p ){
//        qDebug() << it->getDate() << "  " << it->getComment() << it->getIs_done() ;
//    }

//    for( int i = 0 ; i < 5 ; i++ )
//    {
//        qDebug() << " step " << i << " state = "<< p.is_finish() ;
//        p.validate_step() ;
//        for( auto it : p ){
//            qDebug() << it->getDate() << "  " << it->getComment() << it->getIs_done() ;
//        }
//    }
//    qDebug() << "end" ;

//    Menu m ;
//    m.show() ;
//    return a.exec() ;
}
