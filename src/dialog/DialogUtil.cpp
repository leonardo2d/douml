// *************************************************************************
//
// Copyright 2004-2010 Bruno PAGES  .
// Copyright 2012-2013 Nikolai Marchenko.
// Copyright 2012-2013 Leonardo Guilherme.
//
// This file is part of the DOUML Uml Toolkit.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License Version 3.0 as published by
// the Free Software Foundation and appearing in the file LICENSE.GPL included in the
//  packaging of this file.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License Version 3.0 for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//
// e-mail : doumleditor@gmail.com
// home   : http://sourceforge.net/projects/douml
//
// *************************************************************************









#include <stdlib.h>
#include <stdio.h>

#include <qlabel.h>
#include <QTextStream>
#include <qfontmetrics.h>
//#include <q3popupmenu.h>
//#include <tabdialog.h>
#include <qapplication.h>
#include <QWidget>

//Added by qt3to4:
//
#include "BrowserClass.h"
#include "ClassData.h"

#include "DialogUtil.h"
#include "BodyDialog.h"
#include "BrowserView.h"
#include "DialogTimer.h"
#include "UmlCanvas.h"
#include "KeyValueTable.h"
#include "GenerationSettings.h"
#include "strutil.h"
#include "mu.h"
#include "UmlDesktop.h"
#include "translate.h"
#include "menufactory.h"
#include <QProcess>
static QString DoumlEditor;

SmallPushButton::SmallPushButton(const QString & text, QWidget * parent)
    : QPushButton(text, parent)
{
}

QSize SmallPushButton::sizeHint() const
{
    QFontMetrics fm = fontMetrics();
    QSize sz = fm.size(Qt::TextShowMnemonic, text());

    return QSize(sz.width() + sz.width() / 8 + 4,
                 sz.height() + sz.height() / 8 + 4);
}

MultiLineEdit::MultiLineEdit(QWidget * w, const char * name)
    : QPlainTextEdit(name,w)
{
    //QTextEdit::setTextFormat(Qt::PlainText);
}

// setText() redefinition
void MultiLineEdit::setText(const QString & s)
{
    QPlainTextEdit::setPlainText(s.toUtf8());
}

QString MultiLineEdit::theText() const
{
    // no fromUnicode
    return QPlainTextEdit::toPlainText();
}

void MultiLineEdit::setTheText(const QString & s)
{
    // no toUnicode
    QPlainTextEdit::setPlainText(s);
}

// text() redefinition
QString MultiLineEdit::text() const
{
    QString t = QPlainTextEdit::toPlainText();

    return QString::fromUtf8(t.toUtf8());
}

QString MultiLineEdit::trimmedText() const
{
        return QString::fromUtf8(toPlainText().trimmed().toUtf8());
}

LineEdit::LineEdit(QWidget * w)
    : QLineEdit(w)
{
}

LineEdit::LineEdit(const QString & s, QWidget * parent, const char * name)
    : QLineEdit(s, parent/*, name*/)
{
    setWindowTitle(name);
}

// setText() redefinition
void LineEdit::setText(const QString & s)
{
    QLineEdit::setText(toUnicode(s.toLatin1().constData()));
}

// text() redefinition
QString LineEdit::text() const
{
    QString t = QLineEdit::text();

    return fromUnicode(t);
}

void LineEdit::setTheText(const QString & s)
{
    // no toUnicode
    QLineEdit::setText(s);
}

QString LineEdit::theText() const
{
    // no fromUnicode
    return QLineEdit::text();
}
//

void init_font_menu(QMenu & fontsubm, UmlCanvas * canvas, int index)
{
    int f;

    for (f = 0; f != UmlFontNumber; f += 1) {
        QString s = stringify((UmlFont) f);
        int i = 0;

        while ((i = s.indexOf('_', i)) != -1)
            s.replace(i, 1, " ");
        //fontsubm.insertItem(new MenuFont(s, canvas->get_font((UmlFont) f)),
         //                   index++);
        MenuFactory::addItem(fontsubm,s,index);
        MenuFactory::findAction(fontsubm, index)->setFont(canvas->get_font((UmlFont) f));
        index++;
    }
}
void same_width(QWidget * l1, QWidget * l2)
{
    int w1 = l1->sizeHint().width();
    int w2 = l2->sizeHint().width();

    if (w1 > w2)
        l2-> setFixedWidth(w1);
    else if (w1 != w2)
        l1-> setFixedWidth(w2);
}

void same_width(QWidget * l1, QWidget * l2, QWidget * l3)
{
    int w1, w2;

    w1 = l1->sizeHint().width();

    if ((w2 = l2->sizeHint().width()) > w1)
        w1 = w2;

    if ((w2 = l3->sizeHint().width()) > w1)
        w1 = w2;

    l1-> setFixedWidth(w1);
    l2-> setFixedWidth(w1);
    l3-> setFixedWidth(w1);
}

void same_width(QWidget * l1, QWidget * l2, QWidget * l3, QWidget * l4)
{
    int w1, w2;

    w1 = l1->sizeHint().width();

    if ((w2 = l2->sizeHint().width()) > w1)
        w1 = w2;

    if ((w2 = l3->sizeHint().width()) > w1)
        w1 = w2;

    if ((w2 = l4->sizeHint().width()) > w1)
        w1 = w2;

    l1-> setFixedWidth(w1);
    l2-> setFixedWidth(w1);
    l3-> setFixedWidth(w1);
    l4-> setFixedWidth(w1);
}

void same_width(QWidget * l1, QWidget * l2, QWidget * l3,
                QWidget * l4, QWidget * l5)
{
    int w1, w2;

    w1 = l1->sizeHint().width();

    if ((w2 = l2->sizeHint().width()) > w1)
        w1 = w2;

    if ((w2 = l3->sizeHint().width()) > w1)
        w1 = w2;

    if ((w2 = l4->sizeHint().width()) > w1)
        w1 = w2;

    if ((w2 = l5->sizeHint().width()) > w1)
        w1 = w2;

    l1-> setFixedWidth(w1);
    l2-> setFixedWidth(w1);
    l3-> setFixedWidth(w1);
    l4-> setFixedWidth(w1);
    l5-> setFixedWidth(w1);
}
void edit(const QString & s, QString name, void * id, EditType k,
          TabDialog * d, post_edit pf, QList<BodyDialog *> & edits)
{
    QString ed = DoumlEditor;

    if (!ed.isEmpty() && (pf != 0)) {
        // try to use it
        QString f;
        QString firstProto = "%1_%2_%3.";
        QString secondProto = "%1_%2_%3.txt";
        firstProto = firstProto.arg(name)
                .arg(QString::number((unsigned long) id, 16))
                .arg(QString::number((unsigned long) user_id()));
       secondProto=secondProto.arg(name)
                .arg(QString::number((unsigned long) id, 16))
                .arg(QString::number((unsigned long) user_id()));
        switch (k) {
        case CppEdit:
            firstProto=firstProto.append(GenerationSettings::get_cpp_src_extension());
            f=firstProto;
            break;

        case JavaEdit:
            firstProto=firstProto.append(GenerationSettings::get_java_extension());
            f=firstProto;
            break;

        case PhpEdit:
            firstProto=firstProto.append(GenerationSettings::get_php_extension());
            f=firstProto;
            break;

        case PythonEdit:
            firstProto=firstProto.append(GenerationSettings::get_python_extension());
            f=firstProto;
            break;

        default: // TxTEdit
            f = secondProto;
        }

        for (int index = 0; index != (int) name.length(); index += 1)
            if (!f[index].isLetterOrNumber())
                f.replace(index, 1, "_");

        QString path = BrowserView::get_dir().absoluteFilePath(f);

        FILE * fp = fopen((const char *) path.toLatin1().constData(), "wb");

        if (fp != 0) {
            if (!s.isEmpty())
                fputs((const char *) s.toLatin1().constData(), fp);

            fclose(fp);
            ed.prepend("\"");
            ed.append("\"");

            ed += " \"" + path + "\"";
            //(void) system(ed.toLatin1().constData());
            QProcess::startDetached(ed);


            if (d->hasOkButton() && (pf != 0))
                (new DialogTimer(s, path, d, pf))->start(1000);

            return;
        }
        else
            msg_critical("Error", QObject::tr("Cannot open '%1'").arg(path));
    }
    else if (d->isModal()) {
        BodyDialog * bd = new BodyDialog(s, d, pf, k, name, edits);

        bd->exec();	// will be deleted elsewhere
    }
    else
        (new BodyDialog(s, d, pf, k, name, edits))->show();
}

bool check_edits(QList<BodyDialog *> & edits)
{
    if (edits.isEmpty())
        return TRUE;

    return (msg_critical("Douml",
                         QObject::tr("Sub dialog(s) still opened\n"
                            "If you choose 'Ok' the dialog will be closed\n"
                            "without taking into account it content"),
                         QMessageBox::Ok, QMessageBox::Abort)
            == QMessageBox::Ok);
}

AType the_type(const QString & t, const QStringList & types,
               BrowserNodeList & nodes)
{
    AType result;
    int rank = types.indexOf(t);

    if (rank != -1)
        result.type = ((BrowserClass *) nodes.at(rank));
    else
        result.explicit_type = t;

    return result;
}

QString type(const QString & t, const QStringList & types,
             BrowserNodeList & nodes)
{
    int rank = types.indexOf(t);

    return (rank != -1)
           ? QString(((BrowserClass *) nodes.at(rank))->get_name())
           : t;
}

QString get_cpp_name(const BrowserClass * cl, ShowContextMode mode)
{
    ClassData * d = (ClassData *) cl->get_data();

    if (! d->cpp_is_external())
        return cl->contextual_name(mode);

    QString name = cl->get_name();
    QString s = d->get_cppdecl();
    int index = s.indexOf('\n');

    s = (index == -1) ? s.trimmed()
        : s.left(index).trimmed();

    if ((index = s.indexOf("${name}")) != -1)
        s.replace(index, 7, name);
    else if ((index = s.indexOf("${Name}")) != -1)
        s.replace(index, 7, capitalize(name));
    else if ((index = s.indexOf("${NAME}")) != -1)
        s.replace(index, 7, name.toUpper());
    else if ((index = s.indexOf("${nAME}")) != -1)
        s.replace(index, 7, name.toLower());

    return s;
}

QString get_java_name(const BrowserClass * cl, ShowContextMode mode)
{
    ClassData * d = (ClassData *) cl->get_data();

    if (! d->java_is_external())
        return cl->contextual_name(mode);

    QString name = cl->get_name();
    QString s = d->get_javadecl();
    int index = s.indexOf('\n');

    s = (index == -1) ? s.trimmed()
        : s.left(index).trimmed();

    if ((index = s.indexOf("${name}")) != -1)
        s.replace(index, 7, name);
    else if ((index = s.indexOf("${Name}")) != -1)
        s.replace(index, 7, capitalize(name));
    else if ((index = s.indexOf("${NAME}")) != -1)
        s.replace(index, 7, name.toUpper());
    else if ((index = s.indexOf("${nAME}")) != -1)
        s.replace(index, 7, name.toLower());

    return s;
}

QString get_php_name(const BrowserClass * cl, ShowContextMode mode)
{
    ClassData * d = (ClassData *) cl->get_data();

    if (! d->php_is_external())
        return cl->contextual_name(mode);

    QString name = cl->get_name();
    QString s = d->get_phpdecl();
    int index = s.indexOf('\n');

    s = (index == -1) ? s.trimmed()
        : s.left(index).trimmed();

    if ((index = s.indexOf("${name}")) != -1)
        s.replace(index, 7, name);
    else if ((index = s.indexOf("${Name}")) != -1)
        s.replace(index, 7, capitalize(name));
    else if ((index = s.indexOf("${NAME}")) != -1)
        s.replace(index, 7, name.toUpper());
    else if ((index = s.indexOf("${nAME}")) != -1)
        s.replace(index, 7, name.toLower());

    return s;
}

QString get_python_name(const BrowserClass * cl, ShowContextMode mode)
{
    ClassData * d = (ClassData *) cl->get_data();

    if (! d->python_is_external())
        return cl->contextual_name(mode);

    QString name = cl->get_name();
    QString s = d->get_pythondecl();
    int index = s.indexOf('\n');

    s = (index == -1) ? s.trimmed()
        : s.left(index).trimmed();

    if ((index = s.indexOf("${name}")) != -1)
        s.replace(index, 7, name);
    else if ((index = s.indexOf("${Name}")) != -1)
        s.replace(index, 7, capitalize(name));
    else if ((index = s.indexOf("${NAME}")) != -1)
        s.replace(index, 7, name.toUpper());
    else if ((index = s.indexOf("${nAME}")) != -1)
        s.replace(index, 7, name.toLower());

    return s;
}

QString get_idl_name(const BrowserClass * cl, ShowContextMode mode)
{
    ClassData * d = (ClassData *) cl->get_data();

    if (! d->idl_is_external())
        return cl->contextual_name(mode);

    QString name = cl->get_name();
    QString s = d->get_idldecl();
    int index = s.indexOf('\n');

    s = (index == -1) ? s.trimmed()
        : s.left(index).trimmed();

    if ((index = s.indexOf("${name}")) != -1)
        s.replace(index, 7, name);
    else if ((index = s.indexOf("${Name}")) != -1)
        s.replace(index, 7, capitalize(name));
    else if ((index = s.indexOf("${NAME}")) != -1)
        s.replace(index, 7, name.toUpper());
    else if ((index = s.indexOf("${nAME}")) != -1)
        s.replace(index, 7, name.toLower());

    return s;
}

QString get_cpp_name(const AType t, ShowContextMode mode)
{
    if (t.type != 0)
        return get_cpp_name(t.type, mode);
    else
        return GenerationSettings::cpp_type(t.explicit_type);
}

QString get_java_name(const AType t, ShowContextMode mode)
{
    if (t.type != 0)
        return get_java_name(t.type, mode);
    else
        return GenerationSettings::java_type(t.explicit_type);
}

QString get_php_name(const AType t, ShowContextMode mode)
{
    if (t.type != 0)
        return get_php_name(t.type, mode);
    else
        return t.explicit_type;
}

QString get_python_name(const AType t, ShowContextMode mode)
{
    if (t.type != 0)
        return get_python_name(t.type, mode);
    else
        return t.explicit_type;
}

QString get_idl_name(const AType t, ShowContextMode mode)
{
    if (t.type != 0)
        return get_idl_name(t.type, mode);
    else
        return GenerationSettings::idl_type(t.explicit_type);
}

void manage_alias(const BrowserNode * node,
                  const char *& p, QString & s,
                  KeyValuesTable * kvt)
{
    // p starts by '@'
    const char * pclosed;

    if ((p[1] == '{') && ((pclosed = strchr(p + 2, '}')) != 0)) {
        static char st[256];
        char * key = ((pclosed - p) > 255) ? new char[pclosed - p - 1] : st;
        QString qsvalue;
        int keylen = pclosed - p - 2;

        strncpy(key, p + 2, keylen);
        key[keylen] = 0;

        if ((kvt != 0) && kvt->get_value(key, qsvalue)) {
            // find in dialog, insert the value
            s += qsvalue;
        }
        else {
            const char * value = 0;
            const BrowserNode * nd = (kvt != 0)
                                     ? ((const BrowserNode *) node->parent())
                                     : node;

            while (nd != 0) {
                if ((value = nd->get_value(key)) != 0)
                    break;

                nd = (BrowserNode *) nd->parent();
            }

            if (value != 0)
                // find, insert the value
                s += value;
            else {
                // not find, insert the key
                s += "@{";
                s += key;
                s += "}";
            }
        }

        // bypass the key
        p += keylen + 3;

        if (key != st)
            delete [] key;
    }
    else
        // bypass '@'
        s += *p++;
}


void manage_alias(const BrowserNode * node,
                  const char *& p, QString & s,
                  HaveKeyValueData * kvt)
{
    // p starts by '@'
    const char * pclosed;

    if ((p[1] == '{') && ((pclosed = strchr(p + 2, '}')) != 0))
    {
        static char st[256];
        char * key = ((pclosed - p) > 255) ? new char[pclosed - p - 1] : st;
        int keylen = pclosed - p - 2;

        strncpy(key, p + 2, keylen);
        key[keylen] = 0;

        if ((kvt != 0))
        {
            // find in dialog, insert the value
            s += QString(kvt->get_value(key));
        }
        else {
            const char * value = 0;
            const BrowserNode * nd = (kvt != 0)
                                     ? ((const BrowserNode *) node->parent())
                                     : node;

            while (nd != 0) {
                if ((value = nd->get_value(key)) != 0)
                    break;

                nd = (BrowserNode *) nd->parent();
            }

            if (value != 0)
                // find, insert the value
                s += value;
            else {
                // not find, insert the key
                s += "@{";
                s += key;
                s += "}";
            }
        }

        // bypass the key
        p += keylen + 3;

        if (key != st)
            delete [] key;
    }
    else
        // bypass '@'
        s += *p++;
}


static int msg_msg(QMessageBox::Icon icon,
                   QString caption, QString text,
                   int button0, int button1, int button2)
{
    QMessageBox mb(caption, text, icon,
                   button0 | QMessageBox::Default,
                   button1,
                   (button2 == 0) ? 0 : button2 | QMessageBox::Escape);

    if (UmlDesktop::fixed())
        UmlDesktop::tocenter(&mb);

    return mb.exec();
}

int msg_warning(QString caption, QString text,
                int button0, int button1, int button2)
{
    if (UmlDesktop::nogui() && (button1 == 0)) {
        printf("warning\n%s\n%s\n", (const char *) caption.toLatin1().constData(), (const char *) text.toLatin1().constData());
        return 0;
    }

    return msg_msg(QMessageBox::Warning, caption, text, button0, button1, button2);
}

int msg_critical(QString caption, QString text,
                 int button0, int button1, int button2)
{
    if (UmlDesktop::nogui() && (button1 == 0)) {
        printf("critical\n%s\n%s\n", (const char *) caption.toLatin1().constData(), (const char *) text.toLatin1().constData());
        return 0;
    }

    return msg_msg(QMessageBox::Critical, caption, text, button0, button1, button2);
}

int msg_information(QString caption, QString text,
                    int button0, int button1, int button2)
{
    if (UmlDesktop::nogui() && (button1 == 0)) {
        printf("information\n%s\n%s\n", (const char *) caption.toLatin1().constData(), (const char *) text.toLatin1().constData());
        return 0;
    }

    return msg_msg(QMessageBox::Information, caption, text, button0, button1, button2);
}
//

QString editor()
{
    return DoumlEditor;
}

void set_editor(QString s)
{
    DoumlEditor = s;
}

//

static bool Completion = TRUE;

void set_completion(bool y)
{
    Completion = y;
}

bool completion()
{
    return Completion;
}

//
static QWidgetList NonModalDialogs;

void open_dialog(QWidget * w)
{
    if(!NonModalDialogs.contains(w))
        NonModalDialogs.append(w);
}


void close_dialog(QWidget * w)
{
    NonModalDialogs.removeOne(w);
}

QWidgetList dialogs()
{
    return NonModalDialogs;
}
