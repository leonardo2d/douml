
#include "UmlParameter.h"

#include "UmlClass.h"
#include "CppSettings.h"
//Added by qt3to4:
#include <QByteArray>
#include <QString>
QByteArray UmlParameter::cpp(unsigned rank) const
{
    QByteArray s;
    int index;

    if ((type.type != 0) &&
        (CppSettings::classStereotype(type.type->stereotype()) == "enum")) {
        switch (dir) {
        case InputDirection:
            s = CppSettings::enumIn();
            break;

        case OutputDirection:
            s = CppSettings::enumOut();
            break;

        default:
            // can't be return
            s = CppSettings::enumInout();
            break;
        }
    }
    else {
        switch (dir) {
        case InputDirection:
            if (!type.explicit_type.isEmpty())
                s = CppSettings::builtinIn(type.explicit_type);

            if (s.isEmpty())
                s = CppSettings::in();

        case OutputDirection:
            if (!type.explicit_type.isEmpty())
                s = CppSettings::builtinOut(type.explicit_type);

            if (s.isEmpty())
                s = CppSettings::out();

            break;

        default:

            // can't be return
            if (!type.explicit_type.isEmpty())
                s = CppSettings::builtinInout(type.explicit_type);

            if (s.isEmpty())
                s = CppSettings::inout();
        }
    }

    if ((index = s.indexOf("${type}")) != -1) {
        QByteArray t;

        t = QString("${t%1}").arg(rank).toLatin1();
        s.replace(index, 7, t);
    }

    QByteArray p;

    p = QString(" ${p%u}${v%u}").arg(rank).arg( rank).toLatin1();
    return s + p;
}

