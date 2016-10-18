#include "HitDoc.h"

HitDoc::HitDoc()
{
}


HitDoc::~HitDoc()
{
}

int64_t HitDoc::getDocId()
{
    return docId;
}


void HitDoc::setDocId(int64_t id)
{
    docId = id;
}


void HitDoc::setHits(int32_t  hi)
{
    hits = hi;
}


int32_t HitDoc::getHits()
{
    return hits;
}


bool HitDoc::operator> (const HitDoc &doc) const
{
    return docId < doc.docId;
}

bool HitDoc::operator<( const HitDoc &doc) const
{
    return docId > doc.docId;
}

