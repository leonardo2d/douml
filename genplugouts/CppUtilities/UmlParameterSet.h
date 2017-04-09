#ifndef _UMLPARAMETERSET_H
#define _UMLPARAMETERSET_H


#include "UmlBaseParameterSet.h"

#include "UmlActivityItem.h"

class UmlParameterSet : public UmlBaseParameterSet, public UmlActivityItem
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlParameterSet(void * id, const QByteArray & s) : UmlBaseParameterSet(id, s) {
    }

};

#endif
