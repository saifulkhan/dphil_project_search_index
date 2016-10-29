#include "ContDistFactory.h"

Weibull* ContDistFactory::m_audioDist       = new Weibull(0.63017, 1.4268E+5);
LogNormal* ContDistFactory::m_backupDist    = new LogNormal(11.079, 2.7162);
LogNormal* ContDistFactory::m_compressedDist= new LogNormal(12.623, 3.2318);
LogNormal* ContDistFactory::m_databaseDist  = new LogNormal(9.1686, 1.5931);
LogNormal* ContDistFactory::m_developerDist = new LogNormal(7.9466, 1.2497);
Weibull* ContDistFactory::m_diskimageDist   = new Weibull(0.30197, 2.6857E+5);
LogNormal* ContDistFactory::m_documentDist  = new LogNormal(8.8189, 3.1152);
LogNormal* ContDistFactory::m_executableDist= new LogNormal(11.783, 1.7659);
LogNormal* ContDistFactory::m_imageDist     = new LogNormal(8.527, 2.0204);
LogNormal* ContDistFactory::m_miscDist      = new LogNormal(14.421, 1.2929);
Weibull* ContDistFactory::m_systemDist      = new Weibull(0.54405, 2.5418E+5);
LogNormal* ContDistFactory::m_videoDist     = new LogNormal(15.697, 2.8214);
LogNormal* ContDistFactory::m_webDist       = new LogNormal(8.2418, 1.331);

AbstractContDist* ContDistFactory::getContDist(const DistType& distType)
{
    switch (distType)
    {
    case audio:
        return m_audioDist;
    case backup:
        return m_backupDist;
    case compressed:
        return m_compressedDist;
    case database:
        return m_databaseDist;
    case developer:
        return m_developerDist;
    case diskimage:
        return m_diskimageDist;
    case document:
        return m_documentDist;
    case executable:
        return m_executableDist;
    case image:
        return m_imageDist;
    case misc:
        return m_miscDist;
    case sys:
        return m_systemDist;
    case video:
        return m_videoDist;
    case web:
        return m_webDist;
    }
    throw "Invalid Continuous Distribution type.";
}


void ContDistFactory::deleteDist()
{
    delete m_audioDist;
    delete m_backupDist;
    delete m_compressedDist;
    delete m_databaseDist;
    delete m_developerDist;
    delete m_diskimageDist;
    delete m_documentDist;
    delete m_executableDist;
    delete m_imageDist;
    delete m_miscDist;
    delete m_systemDist;
    delete m_videoDist;
    delete m_webDist;
}
