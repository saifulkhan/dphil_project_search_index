#ifndef CONTDISTFACTORY_H
#define CONTDISTFACTORY_H

#include <iostream>
#include <memory>

#include "DiscreteDist.h"
#include "AbstractContDist.h"
#include "Weibull.h"
#include "LogNormal.h"

using namespace std;

enum DistType
{
    audio,
    backup,
    compressed,
    database,
    developer,
    diskimage,
    document,
    executable,
    image,
    misc,
    sys,
    video,
    web
};


class ContDistFactory
{
private:
    static Weibull* m_audioDist;
    static LogNormal* m_backupDist;
    static LogNormal* m_compressedDist;
    static LogNormal* m_databaseDist;
    static LogNormal* m_developerDist;
    static Weibull* m_diskimageDist;
    static LogNormal* m_documentDist;
    static LogNormal* m_executableDist;
    static LogNormal* m_imageDist;
    static LogNormal* m_miscDist;
    static Weibull* m_systemDist;
    static LogNormal* m_videoDist;
    static LogNormal* m_webDist;

    ContDistFactory(); // No need to create object.

public:
    static AbstractContDist* getContDist(const DistType&);
    static void deleteDist();
};

#endif // ContDistFactory_H
