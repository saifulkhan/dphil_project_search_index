#include "RelevanceFeedback.h"

ReleVanceFeedback::ReleVanceFeedback(vector<FileInfoX>& fileInfoX) : m_fileInfoX(fileInfoX)
{
    this->computeRelavance();
}


void ReleVanceFeedback::computeRelavance()
{
    /*
     * Map: <term, <relavant, not-relavant> >
     */
    map<string, pair<unsigned, unsigned>> termMap;
    map<string, pair<unsigned, unsigned>> typeMap;
    map<string, pair<unsigned, unsigned>> sizeMap;
    unsigned totalRelavant = 0;
    unsigned totalIrrelavant = 0;

    /*
     *  Calculate total relavant and non-relavant from the list of documents/results
     *
     */
    for (vector<FileInfoX>::iterator it = m_fileInfoX.begin(); it != m_fileInfoX.end(); ++it) {
        string termx = (*it).m_termx;
        string typex = (*it).m_typex;
        string sizex = tokenise((*it).m_sizex, " ").back();

        /*
         * Calculate the relavant and not relavant.
         */
        if ((*it).m_select) {
            ++termMap[termx].first;
            ++typeMap[typex].first;
            ++sizeMap[sizex].first;
            ++totalRelavant;
        }
        else {
            ++termMap[termx].second;
            ++typeMap[typex].second;
            ++sizeMap[sizex].second;
            ++totalIrrelavant;
        }
    }

    cout << __PRETTY_FUNCTION__ << endl;
    cout << "totalRelavant=" << totalRelavant << ", totalIrrelavant=" << totalIrrelavant << endl;

    /*
     * Aggregate relavant & irrelavant (+ve & -ve)
     */
    map<string, pair<unsigned, unsigned>>::iterator it1;
    for (it1 = termMap.begin(); it1 != termMap.end(); ++it1) {
        cout << it1->first << ": " ;
        int newR = this->calculateRFI(it1->second.first, it1->second.second, totalRelavant, totalIrrelavant);
        m_termMap[it1->first] = newR;
    }

    for (it1 = typeMap.begin(); it1 != typeMap.end(); ++it1) {
        cout << it1->first << ": " ;
        int newR = this->calculateRFI(it1->second.first, it1->second.second, totalRelavant, totalIrrelavant);
        m_typeMap[it1->first] = newR;
    }

    for (it1 = sizeMap.begin(); it1 != sizeMap.end(); ++it1) {
        cout << it1->first << ": " ;
        int newR = this->calculateRFI(it1->second.first, it1->second.second, totalRelavant, totalIrrelavant);
        m_sizeMap[it1->first] = newR;
    }

}


/*
 * RFI:
 * Aggregate relavant & irrelavant (+ve & -ve)
 */
int ReleVanceFeedback::calculateRFI(const int r, const int n, const int totalRelavant, const int totalIrrelavant)
{
    double positive = 0;
    double negative =0;

    if(totalRelavant > 0) {
       positive = BETA * static_cast<double>(r) / static_cast<double>(totalRelavant);
    }
    if (totalIrrelavant > 0) {
        negative = (1 - BETA)  * static_cast<double>(n) / static_cast<double>(totalIrrelavant);
    }

    int newR = round((positive - negative) * 100.00);

    cout << "R=" << r << ", N=" << n << ", R'=" << newR << endl;

    return newR;
}


