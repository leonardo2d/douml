#ifndef _UMLCLASSINSTANCE_H
#define _UMLCLASSINSTANCE_H


#include "UmlBaseClassInstance.h"


class UmlClassInstance : public UmlBaseClassInstance
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlClassInstance(void * id, const QByteArray & s) : UmlBaseClassInstance(id, s) {
    }

};

#endif
