#ifndef TEXT_PICKER_H
#define TEXT_PICKER_H

#include <QLabel>
#include <QWidget>
#include <QInputDialog>
#include <QMouseEvent>
#include "parameters.h"

class Text_picker : public QLabel
{
    Q_OBJECT
private :
    QString title ;
    QString message ;

public :
    Text_picker(QWidget* parent=nullptr): QLabel(parent)
    {
        title = "New name" ;
        message = "Enter the new name" ;
        this->setAcceptDrops(true);
        this->setStyleSheet(Parameters::text_stylesheet_1) ;
        connect(this, &Text_picker::mouseDoubleClickEvent, this , &Text_picker::handle_double_click ) ;
    }
    Text_picker(QString new_title, QString new_message, QWidget* parent=nullptr): QLabel(parent), title(new_title), message(new_message)
    {
        this->setAcceptDrops(true);
        this->setStyleSheet(Parameters::text_stylesheet_1) ;
        connect(this, &Text_picker::mouseDoubleClickEvent, this , &Text_picker::handle_double_click ) ;
    }

    ~Text_picker(){} ;

    const QString &getTitle() const;
    void setTitle(const QString &newTitle);

    const QString &getMessage() const;
    void setMessage(const QString &newMessage);

private slots:
    void handle_double_click(QMouseEvent* event){
        bool ok = true ;
        QString rs = QInputDialog::getText(nullptr, title ,message ,
                                           QLineEdit::Normal, QString(QLabel::text()) , &ok  ) ;
        if(ok){
            QLabel::setText(rs) ;
            emit value_changed(rs) ;
        }
        event->isBeginEvent() ; //in order to avoid warnings
    }

signals :
    void mouseDoubleClickEvent(QMouseEvent* event) ;
    void mousePressEvent(QMouseEvent* event) ;
    void value_changed(QString);
};

inline const QString &Text_picker::getMessage() const
{
    return message;
}

inline void Text_picker::setMessage(const QString &newMessage)
{
    message = newMessage;
}

inline const QString &Text_picker::getTitle() const
{
    return title;
}

inline void Text_picker::setTitle(const QString &newTitle)
{
    title = newTitle;
}

#endif // TEXT_PICKER_H
