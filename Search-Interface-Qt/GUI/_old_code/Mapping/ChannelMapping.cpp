#include "ChannelMapping.h"


ChannelMapping::ChannelMapping (QWidget *parent) : QWidget(parent)
{
    setupUi (this);
}


ChannelMapping::~ChannelMapping()
{

}

QMap<VisAttr_E, FileAttr_E> ChannelMapping::getProperty()
{
    _updateProperty ();
    return _map;
}

void ChannelMapping::setProperty(const QMap<VisAttr_E, FileAttr_E> &)
{
    //
}


void ChannelMapping::_updateProperty ()
{
    _map[PriColor] = static_cast <FileAttr_E> ( pricolorCombobox->currentIndex() );
    _map[SecColor] = static_cast <FileAttr_E> ( seccolorCombobox->currentIndex() );
    _map[SecSize] = static_cast <FileAttr_E> ( secsizeCombobox->currentIndex() );
    _map[SecShape] = static_cast <FileAttr_E> ( secshapeCombobox->currentIndex() );
    _map[SecAn] = static_cast <FileAttr_E> ( anComboBox->currentIndex() );


    // 1. Delete all the "Default" from the list.
    QList <FileAttr_E> list = _map.values();
    QList<FileAttr_E>::iterator itr = list.begin();
    while (itr != list.end())
    {
        if (*itr == Default)
            itr = list.erase (itr);
        else
            ++itr;
    }

    // 2. Check if there are duplicate entries of "Type"/"Size"/"Date"
    for (int i = 0; i < list.size() - 1; i++)
    {
        if (list.at(i) == list.at(i + 1))
        {
            // commented in Qt5, though its not Qt5 related.
            //popupMsg ("ERROR", "Different attribute should not be mapped onto the same visual channel.");

            return;
        }
    }

}


void ChannelMapping::on_pricolorCombobox_currentIndexChanged(int index)
{
    _updateProperty ();
}

void ChannelMapping::on_seccolorCombobox_currentIndexChanged(int index)
{
    _updateProperty ();
}

void ChannelMapping::on_secsizeCombobox_currentIndexChanged(int index)
{
    _updateProperty ();
}

void ChannelMapping::on_secshapeCombobox_currentIndexChanged(int index)
{
    _updateProperty ();
}

void ChannelMapping::on_anComboBox_currentIndexChanged(int index)
{
    _updateProperty ();
}
