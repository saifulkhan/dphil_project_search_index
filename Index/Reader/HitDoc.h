#ifndef HITDOC_H_
#define HITDOC_H_

#include <iostream>
#include <cstdint>
#include "stdHeader.h"

class HitDoc
{
private:
    std::int64_t docId;
    int32_t hits;

public:
	HitDoc();
    ~HitDoc();
    std::int64_t getDocId();
    void setDocId(std::int64_t id);
    void setHits(int32_t  hi);
    int32_t getHits();
    bool operator>( const HitDoc  &doc) const;
	bool operator<(const HitDoc &doc) const;
};

#endif /*HITDOC_H_*/
