
#include "UmlActivityPin.h"
#include "FileOut.h"
//Added by qt3to4:
#include "misc/mystr.h"

void UmlActivityPin::write(FileOut & out)
{
    WrapperStr s = name();
    const char * k;
    const char * K;

    if (direction() == InputDirection) {
        switch (parent()->kind()) {
        case anOpaqueAction:
            k = "inputValue";
            break;

        case aSendObjectAction:
            k = ((s == "target") || (s == "request"))
                ? ((const char *) s)
                : "argument";
            break;

        case anUnmarshallAction:
            k = (s == "object") ? "object" : "input";
            break;

        case aSendSignalAction:
        case aCallOperationAction:
            k = (s == "target") ? "target" : "argument";
            break;

        case aCallBehaviorAction:
            k = "argument";
            break;

        case anAddVariableValueAction:
            k = (s == "insertAt") ? "insertAt" : "value";
            break;

        case aRemoveVariableValueAction:
            k = (s == "removeAt") ? "removeAt" : "value";
            break;

        case aBroadcastSignalAction:
            k = "argument";
            break;

        case aWriteVariableValueAction:
            k = "value";
            break;

        case aDestroyObjectAction:
            k = "target";
            break;

        case aTestIdentityAction:
            k = (s == "first") ? "first" : "second";
            break;

        case aReplyAction:
            k = (s == "returnInformation") ? "returnInformation" : "replyValue";
            break;

        case aReduceAction:
            k = "collection";
            break;

        case aRaiseExceptionAction:
            k = "exception";
            break;

        default:
            k = "input"; // !
        }

        K = "Input";
    }
    else {
        switch (parent()->kind()) {
        case anOpaqueAction:
            k = "outputValue";
            break;

        case aValueSpecificationAction:
        case anUnmarshallAction:
        case anAcceptEventAction:
        case aCallOperationAction:
        case aCallBehaviorAction:
        case aReadVariableValueAction:
        case aCreateObjectAction:
        case aTestIdentityAction:
        case aReduceAction:
            k = "result";
            break;

        case anAcceptCallAction:
            k = (s == "returnInformation") ? "returnInformation" : "result";
            break;

        default:
            k = "output"; // !
        }

        K = "Output";
    }

    out.indent();
    out << '<' << k << " xmi:type=\"uml:" << K << "Pin\" name=\"";
    out.quote((const char *)name()); //[jasa] ambiguous call
    out << '"';
    out.id(this);
    write_flags(out);

    if (isControlType())
        out << " isControlType=\"true\"";

    write_ordering(out);
    write_selection(out);
    write_in_state(out);
    out << ">\n";

    out.indent(+1);

    write_description_properties(out);
    write_multiplicity(out, multiplicity(), this);
    UmlItem::write_type(out, type());

    const QVector<UmlItem*> ch = children();
    unsigned n = ch.size();

    for (unsigned i = 0; i != n; i += 1)
        ch[i]->write(out);

    write_incoming_flows(out);

    out.indent(-1);

    out.indent();
    out << "</" << k << ">\n";

    unload();
}

