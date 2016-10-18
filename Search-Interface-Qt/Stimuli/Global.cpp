#include "Global.h"
#include "../Common/Common.h"

using namespace Stimuli;

QString Stimuli::id ("0");

VECTOR Stimuli::getTF (int index)
{
    static QVector <VECTOR > tF;

    if (tF.isEmpty())
    {
        qDebug () << __PRETTY_FUNCTION__ << "Initializing Transfer Functions.";
        tF.resize (TOTAL_TF);

        //
        tF[0] << PAIR (0, 0) << PAIR (0.45, 0) << PAIR (0.4501, 1) << PAIR (0.55, 1) << PAIR (0.5501, 0) << PAIR (1, 0);
        tF[1] << PAIR (0, 0) << PAIR (0.40, 0) << PAIR (0.4001, 1) << PAIR (0.60, 1) << PAIR (0.6001, 0) << PAIR (1, 0);
        tF[2] << PAIR (0, 0) << PAIR (0.35, 0) << PAIR (0.3501, 1) << PAIR (0.65, 1) << PAIR (0.6501, 0) << PAIR (1, 0);
        tF[3] << PAIR (0, 0) << PAIR (0.30, 0) << PAIR (0.3001, 1) << PAIR (0.70, 1) << PAIR (0.7001, 0) << PAIR (1, 0);
        tF[4] << PAIR (0, 0) << PAIR (0.25, 0) << PAIR (0.2501, 1) << PAIR (0.75, 1) << PAIR (0.7501, 0) << PAIR (1, 0);

        //
        tF[5] << PAIR (0, 0) << PAIR (0.25, 0) << PAIR (0.45, 1) << PAIR (0.55, 1) << PAIR (0.75, 0) << PAIR (1, 0);
        tF[6] << PAIR (0, 0) << PAIR (0.20, 0) << PAIR (0.40, 1) << PAIR (0.60, 1) << PAIR (0.80, 0) << PAIR (1, 0);
        tF[7] << PAIR (0, 0) << PAIR (0.15, 0) << PAIR (0.35, 1) << PAIR (0.65, 1) << PAIR (0.85, 0) << PAIR (1, 0);
        tF[8] << PAIR (0, 0) << PAIR (0.10, 0) << PAIR (0.30, 1) << PAIR (0.70, 1) << PAIR (0.90, 0) << PAIR (1, 0);
        tF[9] << PAIR (0, 0) << PAIR (0.05, 0) << PAIR (0.25, 1) << PAIR (0.75, 1) << PAIR (0.95, 0) << PAIR (1, 0);

        //
        tF[10] << PAIR (0, 0) << PAIR (0.20, 0) << PAIR (0.45, 1) << PAIR (0.55, 1) << PAIR (0.80, 0) << PAIR (1, 0);
        tF[11] << PAIR (0, 0) << PAIR (0.15, 0) << PAIR (0.40, 1) << PAIR (0.60, 1) << PAIR (0.85, 0) << PAIR (1, 0);
        tF[12] << PAIR (0, 0) << PAIR (0.10, 0) << PAIR (0.35, 1) << PAIR (0.65, 1) << PAIR (0.90, 0) << PAIR (1, 0);
        tF[13] << PAIR (0, 0) << PAIR (0.05, 0) << PAIR (0.30, 1) << PAIR (0.70, 1) << PAIR (0.95, 0) << PAIR (1, 0);
        tF[14]                << PAIR (0, 0)    << PAIR (0.25, 1) << PAIR (0.75, 1) << PAIR (1, 0);
    }
    qDebug () << __PRETTY_FUNCTION__ << "Returning Transfer Function: " << index;
    return tF[index];
}

