#ifndef XMLPROCESSOR_H
#define XMLPROCESSOR_H

#include <QtGui>
#include <QtDebug>
#include <iostream>
#include <fstream>
#include "GlobalVariables.h"

using namespace std;

class OpenSave
{

private:
    const QString _filename;
    unsigned magicnoS;
    ofstream w;
    ifstream r;

    bool _checkMagicno (unsigned, unsigned);
    void _writeProperty (const PrimaryProperty_S &);
    void _writeProperty (const Secondary &);
    void _writeProperty (const Animation &);

    void _readProperty (PrimaryProperty_S &);
    void _readProperty (Secondary &);
    void _readProperty (Animation &);

    public:
        OpenSave (QString);
       ~OpenSave ();


        bool saveSetting (const vector <PrimaryProperty_S> &, const vector <Secondary> &,  const vector <Animation> &);
        bool openSetting (vector <PrimaryProperty_S> &, vector <Secondary> &,  vector <Animation> &);
};

#endif
