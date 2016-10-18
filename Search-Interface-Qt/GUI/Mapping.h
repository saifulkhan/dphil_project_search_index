#ifndef MAPPING_H
#define MAPPING_H

#include <QFileInfo>
#include <QVector>
#include <QGraphicsScene>
#include <qmath.h>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <QGraphicsView>
#include <QTableView>

#include <FileInfo.h>
#include <Treemap.h>
#include <NodeTM.h>

#include "ui_Mapping.h"
#include "Glyph.h"
#include "Table.h"


class Mapping  : public QDialog
{
    Q_OBJECT

private:
    Ui::Mapping *ui;
    Treemap *m_treemap;
    QTableView *m_tableView;
    vector <FileInfoX> m_fileInfoVec;
    vector <QRectF> fileCoordinateVec;
    QGraphicsScene* const scene;
    vector <SizeGlyph*> sizeGlyphVec;
    vector <TypeGlyph*> typeGlyphVec;
    vector <DateGlyph*> dateGlyphVec;
    QVector <TimeGlyph*> timeGlyphVec;
    vector <PermissionGlyph*> permissionGlyphVec;
    ColourMap *colourMap;

    void resetCoordinate();
    void mapSize(const FileInfoX&, const QPointF &center);
    qreal sizeScale(qreal size);
    void mapType(const FileInfoX &fileInfo, const QPointF &center );
    QColor getColor(const FileInfoX &fileInfo);
    void mapDate(const FileInfoX &fileInfo, const QPointF &center);
    void mapTime(const FileInfoX &fileInfo, const QPointF &center);
    void mapPermission(const FileInfoX &fileInfo, const QPointF &center);

public:
    explicit Mapping(QGraphicsScene *scene, QDialog *parent = 0 );
    ~Mapping();
    void startMapping(const vector<FileInfoX> &fileInfoVector);
    void clearMapping();
    void notifyClickEvent(const FileInfoX &fileInfo);  // Part of Observer pattern, will get notified for any event

signals:
    void signal_RelavanceFeddback(const FileInfoX&);

private slots:
    void slot_Treemap(bool);
    // clicks
    void on_typeComboBox_currentIndexChanged(int index);
    void on_dateComboBox_currentIndexChanged(int index);
    void on_typeShowCheckBox_stateChanged(int arg1);
    void on_sizeShowCheckBox_stateChanged(int arg1);
    void on_dateShowCheckBox_stateChanged(int arg1);
    void on_timeShowCheckBox_stateChanged(int arg1);
    void on_permissionShowCheckBox_stateChanged(int arg1);
    void on_typeAnCheckBox_stateChanged(int arg1);
    void on_sizeAnCheckBox_stateChanged(int arg1);
    void on_dateAnCheckBox_stateChanged(int arg1);
    void on_timeAnCheckBox_stateChanged(int arg1);
    void on_permissionAnCheckBox_stateChanged(int arg1);
    void on_colormapButton_clicked();
    void on_applyButton_clicked();
    void on_defaultGroupBox_clicked(bool checked);
    void on_customGroupBox_clicked(bool checked);
    void on_opacitySlider_valueChanged(int value);
};

#endif
