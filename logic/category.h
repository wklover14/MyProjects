#ifndef CATEGORY_H
#define CATEGORY_H

#include <QString>
#include <iostream>
#include <QWidget>
#include <list>

#include "parameters.h"
#include "a_project.h"

using namespace std ;

//Class Adaptator design pattern
class Category : private list<A_project*>
{
public:
    Category(QString name, QString color = Parameters::colors_name[ COLORS::salmon ]);
    ~Category() {};
    void update_name(QString new_name) ;
    void remove_project(A_project* a) ;
    void add_project(A_project* a) ;
    list<A_project*> get_project() const ;

    QWidget* widget() ;
    void reload() ;

    const QString &getColor() const;
    void setColor(const QString &newColor);

    const QString &getName() const;
    void setName(const QString &newName);

    int getId_category() const;
    void setId_category(int newId_category);

private :
    QString name ;
    QString color ;
    int idmanager ;
    int id_category ;
    QWidget* view = nullptr ;
};

#endif // CATEGORY_H
