#include "TypeMapping.h"


TypeMapping::TypeMapping (QWidget *parent) : QWidget(parent), ui (new Ui::TypeMappingForm)
{
    ui->setupUi (this);


    // NOT WORKING
    _model = new QStandardItemModel (8, 2, this);
    ui->tableView->setModel(_model);

    _model->setHeaderData(0, Qt::Horizontal, "File Type");
    _model->setHeaderData(1, Qt::Horizontal, "Glyph");

    Properties_S properties;
    for (int row = 0; row < 8; row++)
    {
        QModelIndex index = _model->index( row, 0, QModelIndex ());
        _model->setData (index, enumToQString ( static_cast <FileType_E> (row) ) );

        index = _model->index( row, 1, QModelIndex ());
        ui->tableView->setIndexWidget (index, new GlyphView ());
        _model->setData (index, properties );
    }

    //tableView->setIndexWidget(tableView->model()->index(0, 1), new QPushButton);

    // NOT WORKING - End

}


TypeMapping::~TypeMapping()
{

}


void TypeMapping::setProperty ( const QMap <FileType_E, Properties_S> &typemap)
{
    //

}


void TypeMapping::_updateProperty()
{
    Properties_S properties;

    properties = Properties_S ( ui->view_1->getPriProperty(), ui->view_1->getSecProperty(), ui->view_1->getAnProperty() );
     _typeMap.insert (txt , properties);
    properties = Properties_S ( ui->view_2->getPriProperty(), ui->view_2->getSecProperty(), ui->view_2->getAnProperty() );
    _typeMap.insert (html , properties);
    properties = Properties_S ( ui->view_3->getPriProperty(), ui->view_3->getSecProperty(), ui->view_3->getAnProperty() );
    _typeMap.insert (xml , properties);
    properties = Properties_S ( ui->view_3->getPriProperty(), ui->view_3->getSecProperty(), ui->view_3->getAnProperty() );
    _typeMap.insert (pdf , properties);
    properties = Properties_S ( ui->view_5->getPriProperty(), ui->view_5->getSecProperty(), ui->view_5->getAnProperty() );
    _typeMap.insert (tex , properties);
    properties = Properties_S ( ui->view_6->getPriProperty(), ui->view_6->getSecProperty(), ui->view_6->getAnProperty() );
    _typeMap.insert (cpp , properties);
    properties = Properties_S ( ui->view_7->getPriProperty(), ui->view_7->getSecProperty(), ui->view_7->getAnProperty() );
    _typeMap.insert (hpp , properties);
    properties = Properties_S ( ui->view_8->getPriProperty(), ui->view_8->getSecProperty(), ui->view_8->getAnProperty() );
    _typeMap.insert (other , properties);
}

QMap <FileType_E, Properties_S> TypeMapping::getProperty ()
{
    _updateProperty();
    return _typeMap;
}
