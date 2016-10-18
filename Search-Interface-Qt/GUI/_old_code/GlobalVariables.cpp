#include <QtGui>
#include "GlobalVariables.h"

//void popupMsg (const QString &type, const QString &msg)
//{
//    QMessageBox* msgBox 	= new QMessageBox();
//    msgBox->setWindowTitle(type);
//    msgBox->setText(msg);
//    msgBox->setWindowFlags(Qt::WindowStaysOnTopHint);
//    msgBox->show();
//}


QString enumToQString (const FileType_E &value)
{
    switch (value)
    {
    case txt:
        return "txt";
    case html:
        return "html";
    case xml:
        return "xml";
    case pdf:
        return "pdf";
    case tex:
        return "tex";
    case cpp:
        return "cpp";
    case hpp:
        return "hpp";
    case other:
        return "other";
    default:
        Q_ASSERT (false);
    }
}

