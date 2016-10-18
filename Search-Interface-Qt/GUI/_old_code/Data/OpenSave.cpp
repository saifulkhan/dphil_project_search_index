#include "OpenSave.h"

OpenSave :: OpenSave(QString filename): _filename (filename)
{
    magicnoS = 963;
}


OpenSave :: ~OpenSave()
{

}


void OpenSave ::_writeProperty (const PrimaryProperty_S &p)
{
    w.write ( (char *) &p, sizeof(p) );
}

void OpenSave ::_writeProperty (const Secondary &p)
{
    w.write ( (char *) &p, sizeof(p) );
}

void OpenSave ::_writeProperty (const Animation &p)
{
    w.write ( (char *) &p.antype, sizeof(p.antype) );
    w.write ( (char *) &p.start, sizeof(p.start) );
    w.write ( (char *) &p.stop, sizeof(p.stop) );
    w.write ( (char *) &p.duration, sizeof(p.duration) );

    w.write ( (char *) &p.points, sizeof(p.points) );
    Q_ASSERT ( p.points ==  p.tfVector.size() );
    for (int i = 0; i < p.tfVector.size(); i++)
    {
        w.write ( (char*)&p.tfVector[i].first, sizeof(double) );
        w.write ( (char*)&p.tfVector[i].second, sizeof(double) );
    }
}


void OpenSave ::_readProperty (PrimaryProperty_S &p)
{
    r.read ( (char *) &p, sizeof(p) );
}

void OpenSave ::_readProperty (Secondary &p)
{
    r.read ( (char *) &p, sizeof(p) );
}

void OpenSave ::_readProperty (Animation &p)
{
    r.read ( (char *) &p.duration, sizeof(double) );
    r.read ( (char *) &p.points, sizeof(unsigned) );

    for (int i = 0; i < p.points; i++)
    {
        r.read ( (char*)&p.tfVector[i].first, sizeof(double) );
        r.read ( (char*)&p.tfVector[i].second, sizeof(double) );
    }
}


bool OpenSave::saveSetting (const vector <PrimaryProperty_S> &pri, const vector <Secondary> &sec,  const vector <Animation> &an)
{
    ofstream w (_filename.toStdString().c_str(), ios::out | ios::binary);
    if(!w)
    {
        qFatal ("FATAL-ERROR: OpenSave::saveSetting: Cannot open file...");
        return false;
    }
    w.write ( (char *) &magicnoS, sizeof(magicnoS) );
    unsigned size = pri.size();
    w.write ( (char *) &size, sizeof(unsigned) );

    for (int i = 0; i < pri.size(); i++)
    {
        _writeProperty ( pri[i] );
        _writeProperty ( sec[i] );
        _writeProperty ( an[i] );
    }

    w.close();
    return true;
}


bool OpenSave::openSetting (vector <PrimaryProperty_S> &pri, vector <Secondary> &sec,  vector <Animation> &an)
{
    ifstream r (_filename.toStdString().c_str(), ios::in | ios::binary); // ios::in | ios::binary is bin mode.
    if(!r)
    {
      qFatal ("FATAL-ERROR: OpenSave::openSettings: Cannot open file.");
      return false;
    }

    unsigned magicno = 0;
    r.read((char *) &magicno, sizeof(unsigned));
    if (magicno != magicnoS)
    {
        qFatal ("FATAL-ERROR: OpenSave::openSettings: Wrong file format.");
        return false;
    }
    unsigned size;
    r.read((char *) &size, sizeof(unsigned));

    int i = 0;
    pri.clear();
    sec.clear();
    an.clear();

    while (i < size)
    {
        PrimaryProperty_S p;
        Secondary s;
        Animation a;

        _readProperty (p);
        _readProperty (s);
        _readProperty (a);

        pri.push_back(p);
        sec.push_back(s);
        an.push_back(a);
        i++;
    }

    r.close();
    return true;
}

