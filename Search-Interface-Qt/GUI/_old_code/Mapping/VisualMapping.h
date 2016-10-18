#ifndef VISUALMAPPING_H
#define VISUALMAPPING_H

#include <QDialog>
#include "ui_VisualMapping.h"

class VisualMapping : public QDialog
{
    Q_OBJECT

private:
    Ui::VisualMapping *ui;

    QMap<VisAttr_E, FileAttr_E> _channelMap;
    QMap <FileType_E, Properties_S> _typeMap;

    void _updateProperty ();

    QColor _getPrimaryColor (const FileAttr_E &, const File_S &);
    QColor _getSecondaryColor (const FileAttr_E &, const File_S &);
    QSizeF _getSecondarySize (const FileAttr_E &, const File_S &);
    QString _getSecondaryShape (const FileAttr_E &, const File_S &);
    Animation _getAnProperty (const FileAttr_E &, const File_S &);

signals:
    void VisualMapping_Signal ();

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
    void on_applyButton_clicked();

public:
    explicit VisualMapping (QWidget *parent = 0);

    PrimaryProperty_S getPriProperty (const File_S &);
    Secondary getSecProperty (const File_S &);
    Animation getAnProperty (const File_S &);

};

#endif // VISUALMAPPING_H
