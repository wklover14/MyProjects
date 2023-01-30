#include "date_picker.h"
#include "ui_date_picker.h"

#include <QDialog>
#include <QCalendarWidget>
#include <QPushButton>

Date_picker::Date_picker(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Date_picker)
{
    ui->setupUi(this);
    setAcceptDrops(true) ;
    connect(this, &Date_picker::mousePressEvent, this, &Date_picker::handleClick) ;
}

Date_picker::~Date_picker()
{
    delete ui;
}

void Date_picker::handleClick(QMouseEvent* mouseCliclEvent){
    //create pop up
    QDialog *customDialog = new QDialog();
    customDialog->setWindowTitle("Select your date");

    QVBoxLayout *layout = new QVBoxLayout();

    QCalendarWidget *calendar = new QCalendarWidget();
    layout->addWidget(calendar) ;

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *okButton = new QPushButton("OK");
    QPushButton *cancelButton = new QPushButton("Annuler");
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    layout->addLayout(buttonLayout);

    customDialog->setLayout(layout);
    //set buttons action, we use a lambda function to update automaticaly the new value of the date
    connect(okButton, &QPushButton::released, customDialog,
            [customDialog, this, calendar](){
                this->selectedDate = calendar->selectedDate() ;
                customDialog->close() ;
                //print the new date
                ui->label->setText(selectedDate.toString()) ;
            } ) ;
    connect(cancelButton, &QPushButton::released, customDialog, &QDialog::close ) ;

    customDialog->exec();


}
