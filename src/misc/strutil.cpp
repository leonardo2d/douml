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
#include <qtextcodec.h>
//Added by qt3to4:


#include "strutil.h"
#include "misc/codec.h"

bool manage_comment(QString comment, const char *& p,
                    const char *& pp, bool javadoc)
{
    static QString the_comment;

    p += 10;

    if ((pp != 0) || // comment contains ${comment} !
        comment.isEmpty())
        return FALSE;

    const char * co = comment.toLatin1().constData();

    if (javadoc) {
        the_comment = "/**\n * ";

        do {
            the_comment += *co;

            if ((*co++ == '\n') && *co)
                the_comment += " * ";
        }
        while (*co);

        if (*p != '\n')
            the_comment += (co[-1] != '\n') ? "\n */\n" : " */\n";
        else
            the_comment += (co[-1] != '\n') ? "\n */" : " */";
    }
    else {
        the_comment = "//";

        do {
            the_comment += *co;

            if ((*co++ == '\n') && *co)
                the_comment += "//";
        }
        while (*co);

        if (*p != '\n')
            the_comment += '\n';
    }

    pp = p;
    p = the_comment.toLatin1().constData();
    return TRUE;
}

bool manage_description(QString comment, const char *& p, const char *& pp)
{
    static QString the_comment;

    p += 14;

    if ((pp != 0) || // comment contains ${description} !
        comment.isEmpty())
        return FALSE;

    the_comment = comment;

    if (*p != '\n')
        the_comment += '\n';

    pp = p;
    p = the_comment.toLatin1().constData();
    return TRUE;
}

bool manage_python_comment(QString comment, const char *& p,
                           const char *& pp)
{
    static QString the_comment;

    p += 10;

    if ((pp != 0) || // comment contains ${comment} !
        comment.isEmpty())
        return FALSE;

    const char * co = comment.toLatin1().constData();

    the_comment = "#";

    do {
        the_comment += *co;

        if ((*co++ == '\n') && *co)
            the_comment += "#";
    }
    while (*co);

    if (*p != '\n')
        the_comment += '\n';

    pp = p;
    p = the_comment.toLatin1().constData();
    return TRUE;
}

bool manage_python_description(QString comment, const char *& p, const char *& pp)
{
    return manage_description(comment, p, pp);
}

void manage_python_docstring(QString comment, const char *& p, const char *& pp,
                             BooL & indent_needed, QString & indent,
                             QString & saved_indent)
{
    static QString the_comment;

    p += 12;

    the_comment = comment;

    if ((pp != 0) || // comment contains ${description} !
        the_comment.isEmpty())
        return;

    int index = 0;

    while ((index = the_comment.indexOf("\"\"\"", index)) != -1) {
        the_comment.insert(index, "\\");
        index += 2;
    }

    the_comment = "\"\"\"" + the_comment + "\"\"\"\n";

    if (indent_needed) {
        indent_needed = FALSE;
        the_comment = indent + the_comment;
    }

    pp = p;
    p = the_comment.toLatin1().constData();
    saved_indent =  indent;
    indent = "";
}

bool is_char_of_name(char c)
{
    return (((c >= 'a') && (c <= 'z')) ||
            ((c >= 'A') && (c <= 'Z')) ||
            ((c >= '0') && (c <= '9')) ||
            (c == '_'));
}

QString extract_name(QString s)
{
    int index = s.indexOf("${name}");

    if (index == -1)
        // !!
        return QString();

    const char * p = s.toLatin1().constData();

    int start = index;

    while (start > 0 && is_char_of_name(p[start - 1]))
        start -= 1;

    int end = index + 7;

    while (is_char_of_name(p[end]))
        end += 1;

    return s.mid(start, end - start);
}

QString true_name(const QString & name, const QString & decl)
{
    int index;
    QString n;

    n = ((index = name.indexOf(" ")) == -1)
        ? name
        : name.left(index);

    QString s = extract_name(decl);

    return (s.isEmpty()) ? n : s.replace(s.indexOf("${name}"), 7, n);
}

QString capitalize(const QString & s)
{
    return (s.isEmpty())
           ? s
           : s.left(1).toUpper() + s.mid(1);
}

QString quote(QString s)
{
    QString result;
    const char * p = s.toLatin1().constData();

    for (;;) {
        switch (*p) {
        case 0:
            return result;

        case '<':
            result += "&lt;";
            break;

        case '>':
            result += "&gt;";
            break;

        case '&':
            result += "&amp;";
            break;

        default:
            result += *p;
        }

        p += 1;
    }
}


void remove_comments(WrapperStr & s)
{
    remove_comments(s.GetInternalRef());
}

void remove_comments(QString & s)
{
    int index1 = 0;

    while ((index1 = s.indexOf('/', index1)) != -1) {
        int index2;

        switch (((const char *) s.toLatin1().constData())[index1 + 1]) {
        case '/':
            if ((index2 = s.indexOf('\n', index1 + 2)) != -1)
                s.remove(index1, index2 - index1 + 1);
            else
                s.truncate(index1);

            break;

        case '*':
            if ((index2 = s.indexOf("*/", index1 + 2)) != -1)
                s.replace(index1, index2 - index1 + 2, " ");
            else
                s.truncate(index1);

            break;

        default:
            index1 += 1;
        }
    }
}

void remove_python_comments(WrapperStr & s)
{
    int index1 = 0;

    while ((index1 = s.find('#', index1)) != -1) {
        int index2;

        if ((index2 = s.find('\n', index1 + 1)) != -1)
            s.remove(index1, index2 - index1 + 1);
        else
            s.truncate(index1);
    }
}

void remove_python_comments(QString & s)
{
    int index1 = 0;

    while ((index1 = s.indexOf('/', index1)) != -1) {
        int index2;

        if ((index2 = s.indexOf('\n', index1 + 2)) != -1)
            s.remove(index1, index2 - index1 + 1);
        else
            s.truncate(index1);
    }
}

void remove_preprocessor(WrapperStr & s)
{
    remove_preprocessor(s.GetInternalRef());
}

void remove_preprocessor(QString & s)
{
    int index = 0;

    while ((index = s.indexOf('#', index)) != -1) {
        // remove all up to the end of line
        int index2 = index + 1;
        int index3;

        while ((index3 = s.indexOf('\n', index2)) != -1) {
            // manage multi lines #define
            if (((const char *) s.toLatin1().constData())[index3 - 1] != '\\')
                break;
            else
                index2 = index3 + 1;
        }

        // the \n is still here to have a separator
        if (index3 == -1)
            s.truncate(index);
        else
            s.remove(index, index3 - index);
    }
}

QString java_multiplicity(QString m)
{
    QString r;

    if (! m.isEmpty()) {
        if (*m.toLatin1().constData() != '[')
            r += "[]";
        else {
            for (int index = 0; index != m.length(); index += 1) {
                switch (m.at(index).toLatin1()) {
                case '[':
                    r += '[';
                    break;

                case ']':
                    r += ']';

                default:
                    break;
                }
            }
        }
    }

    return r;
}

// remark : v is not empty and doesn't start by spaces
bool need_equal(const char * p, QString v, bool cpp)
{
    QChar v0 = v.at(0);

    if ((v0 == QChar('=')) || (cpp && (v0 == QChar('('))))
        return FALSE;

    for (;;) {
        switch (*--p) {
        case '=':
            return FALSE;

        case ' ' :
        case '\t':
        case '\n':
        case '\r':
            break;

        default:
            return TRUE;
        }
    }
}

// remark : v is not empty and doesn't start by spaces
bool need_equal(const char * p, const char * v, bool cpp)
{
    if ((*v == '=') || (cpp && (*v == '(')))
        return FALSE;

    for (;;) {
        switch (*--p) {
        case '=':
            return FALSE;

        case ' ' :
        case '\t':
        case '\n':
        case '\r':
            break;

        default:
            return TRUE;
        }
    }
}

//

//

static void bypass_spaces(const char *& s)
{
    for (;;) {
        switch (*s) {
        case ' ' :
        case '\t':
        case '\r':
        case '\n':
            s += 1;
            break;

        default:
            return;
        }
    }
}

bool is_referenced(const char * s, int id, const char * kc, const char * kr)
{
    if (s != 0) {
        if (kc != 0) {
            // search a form kc <n> kr id
            int lkc = strlen(kc);
            int lkr = strlen(kr);

            while ((s = strstr(s, kc)) != 0) {
                s += lkc;
                bypass_spaces(s);

                // bypass canvas id
                while ((*s >= '0') && (*s <= '9'))
                    s += 1;

                bypass_spaces(s);

                if (strncmp(s, kr, lkr) == 0) {
                    s += lkr;
                    bypass_spaces(s);

                    if (atoi(s) == id)
                        return TRUE;
                }
            }
        }
        else {
            // search a form  kr id
            int lkr = strlen(kr);

            while ((s = strstr(s, kr)) != 0) {
                s += lkr;
                bypass_spaces(s);

                if (atoi(s) == id)
                    return TRUE;
            }
        }
    }

    return FALSE;
}
