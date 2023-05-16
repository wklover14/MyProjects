#ifndef STAT_PAGE_H
#define STAT_PAGE_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QScrollBar>

#include "parameters.h"

class Stat_page : public QWidget
{
    Q_OBJECT
private :
    QLabel* stats = new QLabel("Stats");
public :
    Stat_page(QWidget* parent= nullptr) : QWidget(parent)
    {
        QHBoxLayout* layout = new QHBoxLayout();

        stats->setStyleSheet( Parameters::title_stylesheet );
        layout->addWidget(stats) ;
        this->setLayout(layout);
    } ;
    ~Stat_page(){} ;
};



#endif // STAT_PAGE_H
