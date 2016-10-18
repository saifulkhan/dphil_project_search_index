#include <iostream>
#include <cmath>
#include <vector>
#include <FileInfo.h>

#define BETA 0.65

using namespace std;

class ReleVanceFeedback
{
private:
    vector<FileInfoX> m_fileInfoX;
    map<string, int> m_termMap;
    map<string, int> m_typeMap;
    map<string, int> m_sizeMap;

    void computeRelavance();
    int calculateRFI(const int r, const int n, const int sumR, const int sumN);

public:
    ReleVanceFeedback(vector<FileInfoX>& fileInfoX);
    map<string, int> termMap() const {
        return m_termMap;
    }
    map<string, int> typeMap() const {
        return m_typeMap;
    }
    map<string, int> sizeMap() const {
        return m_sizeMap;
    }
};
