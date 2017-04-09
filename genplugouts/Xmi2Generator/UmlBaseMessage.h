#ifndef _UMLBASEMESSAGE_H
#define _UMLBASEMESSAGE_H
#include "../src/misc/mystr.h"
#include <QByteArray>
#include <QHash>



class UmlClassInstanceReference;
class UmlOperation;

// this class manages messages indenpendently of the diagram
class UmlBaseMessage
{
public:
    // return the instance sending the message
    UmlClassInstanceReference * from() const {
        return _from;
    }

    // return the instance receiving the message
    UmlClassInstanceReference * to() const {
        return _to;
    }

    // return the operation or 0/null,
    // exclusive with form()
    UmlOperation * operation() const {
        return _operation;
    }

    // return message as a string, may be empty/null,
    // exclusive with operation()
    const WrapperStr & form() const {
        return _form;
    }


private:
    UmlClassInstanceReference * _from;

    UmlClassInstanceReference * _to;

    UmlOperation * _operation;

    WrapperStr _form;

    // internal, don't call it
    void read_(const QHash<void*, UmlClassInstanceReference*> & instances);

    friend class UmlBaseSequenceMessage;
    friend class UmlBaseCollaborationMessage;
};

#endif
