#ifndef _UMLBASECOMPONENT_H
#define _UMLBASECOMPONENT_H


#include "UmlItem.h"
#include "anItemKind.h"
#include "misc/mystr.h"

#include "UmlClass.h"	// to avoid destructor problem
class UmlComponent;
class UmlComponentView;
class UmlComponentDiagram;
class UmlClass;

//  Manage the components.
class UmlBaseComponent : public UmlItem
{
public:
    // returns a new component named 's' created under 'parent'
    //
    // In case it cannot be created (the name is already used or
    // invalid, 'parent' cannot contain it etc ...) return 0 in C++
    // and produce a RuntimeException in Java
    static UmlComponent * create(UmlComponentView * parent, const char * s);

    // returns the kind of the item
    virtual anItemKind kind();

    // returns the optional associated diagram
    UmlComponentDiagram * associatedDiagram();

    // sets the associated diagram, arg may be null to unset it
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_AssociatedDiagram(UmlComponentDiagram * d);

    // returns (in Java a copy of) the optional realizing classes
    const QHash<int,UmlClass*> & realizingClasses();

    // returns (in Java a copy of) the optional provided classes
    const QHash<int,UmlClass*> & providedClasses();

    // returns (in Java a copy of) the optional required classes
    const QHash<int,UmlClass*> & requiredClasses();

    // set the realization, provided and required classes lists
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_AssociatedClasses(const QHash<int,UmlClass*> & realizing, const QHash<int,UmlClass*> & provided, const QHash<int,UmlClass*> & required);

    // to unload the object to free memory, it will be reloaded
    // automatically if needed. args unused
    virtual void unload(bool = FALSE, bool = FALSE);


private:
    UmlComponentDiagram * _assoc_diagram;

    QHash<int,UmlClass*> _realizing;

    QHash<int,UmlClass*> _provided;

    QHash<int,UmlClass*> _required;


protected:
    //internal, do NOT use it

    virtual void read_uml_();

    // the constructor, do not call it yourself !!!!!!!!!!
    UmlBaseComponent(void * id, const WrapperStr & n);

};

inline UmlBaseComponent::UmlBaseComponent(void * id, const WrapperStr & n) : UmlItem(id, n)
{
    _assoc_diagram = 0;
}

#endif
