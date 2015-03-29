#ifndef _ASSOCIATION_H
#define _ASSOCIATION_H



#include "aRelationKind.h"
#include <qmap.h>

class FileIn;
class Token;

// an unused role has an empty id
struct Role {
    WrapperStr name;

    WrapperStr id;

    // idref of the type containing it
    WrapperStr idref;

    aRelationKind aggregate;

    bool navigable : 1;

    bool readOnly : 1;

    bool isDerived : 1;

    bool isDerivedUnion : 1;

    bool isOrdered : 1;

    bool isUnique : 1;

    bool isStatic : 1;

    WrapperStr multiplicity;

    WrapperStr visibility;

    WrapperStr comment;

    WrapperStr constraint;

    WrapperStr defaultValue;

    Role() : aggregate(anAssociation), navigable(TRUE), readOnly(FALSE), isStatic(FALSE) {}

    void setMultiplicity(WrapperStr v, bool upper, const char * dflt);

};

class Association
{
public:
    Association() : is_class_association(FALSE) {}

    void import(FileIn & in, Token & token);

    void set_class_association() {
        is_class_association = TRUE;
    }
    // search for the association from its id

    static Association & get(WrapperStr id, WrapperStr s = "");

    static void solveThem();


protected:
    WrapperStr name;

    Role roles[2];

    static QMap<QString, Association> All;

    bool is_class_association;


private:
    void solve(WrapperStr id);

};

#endif
