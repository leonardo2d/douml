
#include "UmlFragmentCompartment.h"
#include "FileOut.h"
#include "UmlItem.h"
#include "UmlSequenceMessage.h"
//Added by qt3to4:
#include "misc/mystr.h"

void UmlFragmentCompartment::write(FileOut & out, UmlItem * diagram, QList<UmlSequenceMessage *> &msgs)
{
    UmlFragment * fr = fragment();

    while (fr->container() != 0)
        fr = fr->container()->fragment();

    fr->write(out, diagram, msgs);
}

void UmlFragmentCompartment::write(FileOut & out, UmlItem * diagram, QList<UmlSequenceMessage *> &msgs, WrapperStr oper)
{
    QList<UmlSequenceMessage*>::Iterator it = msgs.begin();
    UmlSequenceMessage * m;

    if (!oper.isEmpty()) {
        static int rank = 0;

        out.indent();
        out << "<operand xmi:type=\"uml:InteractionOperand\"";
        out.id_prefix(diagram, "OPERAND", ++rank);
        out << ">\n";

        out.indent(+1);

        if (! texts().isEmpty()) {
            out.indent();
            out << "<guard xmi:type=\"uml:InteractionConstraint\"";
            out.id_prefix(diagram, "GUARD", rank);
            out << ">\n";

            WrapperStr txt = texts()[0];

            txt.stripWhiteSpace();

            if ((txt.at(0) == "[") && (txt.at(txt.length() - 1) == "]"))
                txt = txt.mid(1, txt.length() - 2);

            if (oper == "loop") {
                int index;
                WrapperStr min;
                WrapperStr max;

                if ((index = txt.find(',')) != -1) {
                    min = txt.left(index);
                    max = txt.mid(index + 1);
                }
                else if ((index = txt.find("..")) != -1) {
                    min = txt.left(index);
                    max = txt.mid(index + 2);
                }
                else
                    min = txt;

                if (! min.isEmpty()) {
                    out.indent();
                    out << "\t<minint xmi:type=\"uml:LiteralInteger\"";
                    out.id_prefix(diagram, "MIN", rank);
                    out << " value=\"";
                    out.quote(min);
                    out << "\"/>\n";
                }

                if (! max.isEmpty()) {
                    out.indent();
                    out << "\t<maxint xmi:type=\"uml:LiteralInteger\"";
                    out.id_prefix(diagram, "MAX", rank);
                    out << " value=\"";
                    out.quote(max);
                    out << "\"/>\n";
                }
            }
            else {
                out.indent();
                out << "\t<specification xmi:type=\"uml:OpaqueExpression\"";
                out.id_prefix(diagram, "GUARD_EXPR", rank);
                out << ">\n";
                out.indent();
                out << "\t\t<body>";
                out.quote(txt);
                out << "</body>\n";
                out.indent();
                out << "\t</specification>\n";
            }

            out.indent();
            out << "</guard>\n";
        }
    }

    static int continuation_rank = 0;

    if (!startContinuation().isEmpty()) {
        out.indent();
        out << "<fragment xmi:type=\"uml:Continuation\"";
        out.id_prefix(diagram, "CONTINUATION", ++continuation_rank);
        out << " name=\"";
        out.quote(startContinuation());
        out << "\" setting=\"false\"/>\n";
    }

    while (it != msgs.end()) {
        m = *it;
        UmlFragmentCompartment * fc = m->fragment();

        if (fc == 0)
            // out of fragment
            ++it;
        else {
            // message inside compartment ?
            if (fc != this) {
                do {
                    UmlFragmentCompartment * pfc = fc->fragment()->container();

                    if (pfc == this)
                        // fc is a fragment compartment of a fragment inside this
                        break;

                    fc = pfc;
                }
                while (fc != 0);
            }

            if (fc == 0)
                // not included in compartment or under
                ++it;
            else if (m->fragment() == this)
                // directly in this compartment
                m->write_fragment(out, diagram, msgs);
            else
                // in sub fragment
                fc->fragment()->write(out, diagram, msgs);
        }
    }

    if (!endContinuation().isEmpty()) {
        out.indent();
        out << "<fragment xmi:type=\"uml:Continuation\"";
        out.id_prefix(diagram, "CONTINUATION", ++continuation_rank);
        out << " name=\"";
        out.quote(endContinuation());
        out << "\" setting=\"true\"/>\n";
    }

    if (!oper.isEmpty()) {
        out.indent(-1);
        out.indent();
        out << "</operand>\n";
    }
}

void UmlFragmentCompartment::bypass(QList<UmlSequenceMessage *> &msgs)
{
    QList<UmlSequenceMessage*>::Iterator it = msgs.begin();
    UmlSequenceMessage * m;

    while (it != msgs.end()) {
        m = *it;
        UmlFragmentCompartment * fc = m->fragment();

        if (fc == 0)
            // out of fragment
            ++it;
        else {
            // message inside compartment ?
            if (fc != this) {
                do {
                    UmlFragmentCompartment * pfc = fc->fragment()->container();

                    if (pfc == this)
                        // fc is a fragment compartment of a fragment inside this
                        break;

                    fc = pfc;
                }
                while (fc != 0);
            }

            if (fc == 0)
                // not included in compartment or under
                ++it;
            else
                msgs.removeOne(m);
        }
    }
}

