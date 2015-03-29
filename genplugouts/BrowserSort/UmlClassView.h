#ifndef _UMLCLASSVIEW_H
#define _UMLCLASSVIEW_H


#include "UmlBaseClassView.h"


// This class manages 'class view'
//
// You can modify it as you want (except the constructor)
class UmlClassView : public UmlBaseClassView
{
public:
    virtual void sort();

    UmlClassView(void * id, const QByteArray & n) : UmlBaseClassView(id, n) {};

    virtual int orderWeight();

};

#endif
