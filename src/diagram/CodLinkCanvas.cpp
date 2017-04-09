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





#include <qcursor.h>
//#include <q3popupmenu.h>
//Added by qt3to4:
#include <QTextStream>

#include "CodLinkCanvas.h"
#include "ArrowPointCanvas.h"
#include "UmlCanvas.h"
#include "LabelCanvas.h"
#include "CodDirsCanvas.h"
#include "myio.h"
#include "ToolCom.h"
#include "CodAddMsgDialog.h"
#include "CodEditMsgDialog.h"
#include "CodObjCanvas.h"
#include "ColDiagramView.h"
#include "Tool.h"
#include "ui/menufactory.h"
#include "translate.h"

CodLinkCanvas::CodLinkCanvas(UmlCanvas * canvas, DiagramItem * b,
                             DiagramItem * e, int id,
                             float d_start, float d_end)
    : ArrowCanvas(canvas, b, e, UmlLink, id, TRUE, d_start, d_end), dirs(0)
{
    // note : can't be a self relation
}

CodLinkCanvas::~CodLinkCanvas()
{
}

void CodLinkCanvas::delete_it()
{
    if (dirs)
        dirs->delete_it();

    ArrowCanvas::delete_it();
}

void CodLinkCanvas::update_pos()
{
    ArrowCanvas::update_pos();

    if (dirs != 0)
        dirs->update_pos(beginp, endp);
}

void CodLinkCanvas::setVisible(bool yes)
{
    ArrowCanvas::setVisible(yes);

    if (dirs != 0)
        dirs->setVisible(yes);
}

void CodLinkCanvas::moveBy(double dx, double dy)
{
    if (isSelected())
        the_canvas()->unselect(this);

    ArrowCanvas::moveBy(dx, dy);

    if (dirs)
        dirs->update_pos(beginp, endp);
}

void CodLinkCanvas::open()
{
    QPoint dummy;

    menu(dummy);
}

void CodLinkCanvas::menu(const QPoint &)
{
    bool new_dirs;
    CodDirsCanvas * d = find_dirs();
    CodObjCanvas * from;
    CodObjCanvas * to;

    get_start_end(from, to);

    if (d == 0) {
        new_dirs = TRUE;
        (d = dirs = new CodDirsCanvas(the_canvas(), this, 0))->show();
    }
    else
        new_dirs = FALSE;

    QMenu m;
    QMenu geo;

    MenuFactory::createTitle(m, TR("Link"));
    m.addSeparator();
    MenuFactory::addItem(m, TR("add messages to ") + from->get_full_name(), 1);
    MenuFactory::addItem(m, TR("add messages to ") + to->get_full_name(), 2);
    m.addSeparator();
    MenuFactory::addItem(m, TR("Edit its messages"), 3);
    MenuFactory::addItem(m, TR("Edit all the messages"), 4);
    m.addSeparator();
    MenuFactory::addItem(m, TR("Select linked items"), 7);
    m.addSeparator();

    if (!new_dirs) {
        MenuFactory::addItem(m, TR("Edit drawing settings"), 5);
        m.addSeparator();
    }

    if (get_start() != get_end()) {
        init_geometry_menu(geo, 10);
        MenuFactory::insertItem(m, TR("Geometry (Ctrl+l)"), &geo);
        m.addSeparator();
    }

    MenuFactory::addItem(m, TR("Remove from diagram"), 6);

    QAction* retAction = m.exec(QCursor::pos());
    if(retAction)
    {
        int rank = retAction->data().toInt();

        switch (rank) {
        case 1: {
            CodAddMsgDialog dialog(to, from, d,
                                   (ColDiagramView *) the_canvas()->get_view(),
                                   FALSE);

            dialog.raise();

            if (dialog.exec() != QDialog::Accepted)
                return;
        }

            break;

        case 2: {
            CodAddMsgDialog dialog(from, to, d,
                                   (ColDiagramView *) the_canvas()->get_view(),
                                   TRUE);

            dialog.raise();

            if (dialog.exec() != QDialog::Accepted)
                return;
        }
            break;

        case 3:
            CodEditMsgDialog::exec((ColDiagramView *) the_canvas()->get_view(), d->get_msgs());
            return;
        case 4:
            CodEditMsgDialog::exec((ColDiagramView *) the_canvas()->get_view(),
                                   ((ColDiagramView *) the_canvas()->get_view())->get_msgs());
            return;
        case 5:
            if (d->edit_drawing_settings())
                modified();

            return;

        case 6:
            delete_it();
            ((ColDiagramView *) the_canvas()->get_view())->update_msgs();
            break;
        case 7:
            select_associated();
            return;

        default:
            if (rank >= 10) {
                rank -= 10;

                if (rank == RecenterBegin)
                    set_decenter(-1.0, decenter_end);
                else if (rank == RecenterEnd)
                    set_decenter(decenter_begin, -1.0);
                else if (rank != (int) geometry)
                    set_geometry((LineGeometry) rank, TRUE);
                else
                    return;
            }
            else
                return;
        }
    }

    package_modified();

    if (new_dirs && (dirs != 0)) {
        if (dirs->get_msgs().count() == 0) {
            dirs->delete_it();
            dirs = 0;
        }
        else
            dirs->update_pos(beginp, endp);
    }
}


ArrowPointCanvas * CodLinkCanvas::brk(const QPoint & p)
{
    ArrowPointCanvas * ap =
            new ArrowPointCanvas(the_canvas(), p.x(), p.y());

    ap->setZValue(zValue() + 1);

    CodLinkCanvas * other =
            new CodLinkCanvas(the_canvas(), ap, end, 0, decenter_begin, decenter_end);

    ap->add_line(this);
    end->remove_line(this, TRUE);
    end = ap;

    //update_pos();

    ap->show();
    other->show();

    if (dirs &&
            ((p - beginp).manhattanLength() < (p - endp).manhattanLength())) {
        other->dirs = dirs;
        dirs = 0;
        other->dirs->set_link(other);
        other->dirs->update_pos(other->beginp, other->endp);
    }

    modified();
    other->modified();

    return ap;
}


ArrowCanvas * CodLinkCanvas::join(ArrowCanvas * other, ArrowPointCanvas * ap)
{
    // has already check is join is possible (self relation must have two points)
    CodDirsCanvas * d = (dirs != 0) ? dirs : ((CodLinkCanvas *) other)->dirs;

    CodLinkCanvas * result = (CodLinkCanvas *) ArrowCanvas::join(other, ap);

    // here this may be 'deleted' (delete_it)
    result->dirs = d;	// result cannot be 0 because start != end

    if (d != 0) {
        d->set_link(result);
        d->update_pos(result->beginp, result->endp);
    }

    result->modified();

    return result;
}

void CodLinkCanvas::get_start_end(CodObjCanvas *& from, CodObjCanvas *& to)
{
    CodLinkCanvas * a;

    a = this;

    while (a->begin->typeUmlCode() == UmlArrowPoint)
        a = (CodLinkCanvas *)((ArrowPointCanvas *) a->begin)->get_other(a);

    from = (CodObjCanvas *) a->begin;

    a = this;

    while (a->end->typeUmlCode() == UmlArrowPoint)
        a = (CodLinkCanvas *)((ArrowPointCanvas *) a->end)->get_other(a);

    to = (CodObjCanvas *) a->end;
}

CodDirsCanvas * CodLinkCanvas::find_dirs() const
{
    if (dirs != 0)
        return dirs;

    const CodLinkCanvas * a;

    a = this;

    while (a->begin->typeUmlCode() == UmlArrowPoint) {
        a = (CodLinkCanvas *)((ArrowPointCanvas *) a->begin)->get_other(a);

        if (a->dirs != 0)
            return a->dirs;
    }

    a = this;

    while (a->end->typeUmlCode() == UmlArrowPoint) {
        a = (CodLinkCanvas *)((ArrowPointCanvas *) a->end)->get_other(a);

        if (a->dirs != 0)
            return a->dirs;
    }

    return 0;
}

void CodLinkCanvas::save(QTextStream & st, bool ref, QString & warning) const
{
    if (ref)
        st << "linkcanvas_ref " << get_ident();
    else if (begin->typeUmlCode() != UmlArrowPoint) {
        nl_indent(st);
        st << "linkcanvas " << get_ident();

        if (decenter_begin >= 0)
            // float output/input bugged
            st << " decenter_begin " << ((int)(decenter_begin * 1000));

        if (decenter_end >= 0)
            // float output/input bugged
            st << " decenter_end " << ((int)(decenter_end * 1000));

        indent(+1);
        save_lines(st, TRUE, TRUE, warning);
        indent(-1);

        CodDirsCanvas * d = find_dirs();

        if (d != 0)
            d->save(st, FALSE, warning);
    }
}

CodLinkCanvas * CodLinkCanvas::read(char *& st, UmlCanvas * canvas, char *& k)
{
    if (!strcmp(k, "linkcanvas_ref"))
        return ((CodLinkCanvas *) dict_get(read_id(st), "link canvas", canvas));
    else if (!strcmp(k, "linkcanvas")) {
        int id = read_id(st);

        float dbegin;
        float dend;

        k = read_keyword(st);

        if (! strcmp(k, "decenter_begin")) {
            dbegin = read_double(st) / 1000;
            k = read_keyword(st);
        }
        else
            dbegin = -1;

        if (! strcmp(k, "decenter_end")) {
            dend = read_double(st) / 1000;
            k = read_keyword(st);
        }
        else
            dend = -1;

        unread_keyword(k, st);

        read_keyword(st, "from");
        read_keyword(st, "ref");

        DiagramItem * bi = dict_get(read_id(st), "", canvas);
        CodLinkCanvas * result;

        for (;;) {
            double z = 0;

            if (read_file_format() >= 5) {
                read_keyword(st, "z");
                z = read_double(st);
            }

            read_keyword(st, "to");

            k = read_keyword(st);

            if (!strcmp(k, "ref"))
                break;

            DiagramItem * ap = ArrowPointCanvas::read(st, canvas, k);

            if (ap == 0)
                unknown_keyword(k);

            result = new CodLinkCanvas(canvas, bi, ap, id, dbegin, dend);

            if (read_file_format() >= 5)
                result->setZValue(z);

            result->show();
            bi = ap;

            read_keyword(st, "line");
            id = read_id(st);
        }

        result =
                new CodLinkCanvas(canvas, bi, dict_get(read_id(st), "", canvas),
                                  id, dbegin, dend);
        result->show();

        k = read_keyword(st);

        return result;
    }
    else
        return 0;
}

void CodLinkCanvas::history_save(QBuffer & b) const
{
    ArrowCanvas ::history_save(b);
    // must save dirs because it may change
    // when an arrow point is added/removed
    ::save(dirs, b);
}

void CodLinkCanvas::history_load(QBuffer & b)
{
    ArrowCanvas::history_load(b);
    dirs = (CodDirsCanvas *) load_item(b);
}
