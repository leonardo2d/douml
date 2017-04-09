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





#include <qpainter.h>
#include <qcursor.h>
#include <QTextStream>
#include "FragmentSeparatorCanvas.h"
#include "FragmentCanvas.h"
#include "ui/menufactory.h"
#include "myio.h"
#include "translate.h"

#define LIFE_LINE_HEIGHT 7

FragmentSeparatorCanvas::FragmentSeparatorCanvas(UmlCanvas * canvas, FragmentCanvas * f,
        double vp)
    : DiagramCanvas(0, canvas, 0, 0, LIFE_LINE_HEIGHT, 0, -1),
      fragment(f), vpos(vp)
{
    if (canvas->paste())
        // must not be selected else the move done after if wrong
        canvas->unselect(this);
    else
        compute_position();

    show();
}

FragmentSeparatorCanvas::~FragmentSeparatorCanvas()
{
}

void FragmentSeparatorCanvas::delete_it()
{
    fragment->remove_it(this);
    DiagramCanvas::delete_it();
}

void FragmentSeparatorCanvas::compute_position()
{
    double zoom = the_canvas()->zoom();
    double fy = fragment->y();
    double fh = fragment->height();
    double offset = LIFE_LINE_HEIGHT / 2.0 * zoom;
    double new_x = fragment->x();
    double new_y = fy + fh * vpos;

    if (new_y <= fy)
        new_y = fy + 1;
    else if (new_y >= fy + fh - 1)
        new_y = fy + fh - 2;

    setZValue(fragment->zValue() + 1);
    setRect(0,0,fragment->width(), (int)(LIFE_LINE_HEIGHT * zoom));
    QGraphicsRectItem::moveBy(new_x - x(), new_y - offset - y());
}

void FragmentSeparatorCanvas::update()
{
    hide();
    compute_position();
    show();
    canvas()->update();
}

void FragmentSeparatorCanvas::change_scale()
{
    // do nothing, update called by its fragment
}

void FragmentSeparatorCanvas::drawShape(QPainter & p)
{
    p.setBackgroundMode(::Qt::TransparentMode);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setPen(::Qt::DashDotLine/*DashLine*/);

    int m = 0;//(int)(/*fragment->y() + */fragment->height() * vpos);

    p.drawLine((int) /*fragment->x()*/0, m,
               (int) /*fragment->x() + */fragment->width() - 1, m);

    p.setPen(::Qt::SolidLine);


    FILE * fp = svg();

    if (fp != 0)
        fprintf(fp, "<g>\n\t<line stroke=\"black\" stroke-dasharray=\"20,4\" stroke-opacity=\"1\""
                " x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" />\n</g>\n",
                (int) fragment->x(), m,
                (int) fragment->x() + fragment->width() - 1, m);

    if (selected())
        show_mark(p, rect());
}
void FragmentSeparatorCanvas::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    drawShape(*painter);
}
void FragmentSeparatorCanvas::moveBy(double, double dy)
{
    // moved by user
    if (! fragment->selected()) {
        double zoom = the_canvas()->zoom();
        double offset = LIFE_LINE_HEIGHT / 2.0 * zoom;
        float new_y = y() + dy + offset;
        double fy = fragment->y();
        double fh = fragment->height();

        if (new_y <= (fy + 1))
            new_y = fy + 2;
        else if (new_y >= fy + fh - 1)
            new_y = fy + fh - 2;

        vpos = (new_y - fy) / fh;
        QGraphicsRectItem::moveBy(0, new_y - offset - y());
    }
}

UmlCode FragmentSeparatorCanvas::typeUmlCode() const
{
    return UmlFragmentSeparator;
}

void FragmentSeparatorCanvas::delete_available(BooL &, BooL & out_model) const
{
    out_model |= TRUE;
}

DiagramItem::LineDirection FragmentSeparatorCanvas::allowed_direction(UmlCode)
{
    return DiagramItem::Horizontal;
}

QString FragmentSeparatorCanvas::may_start(UmlCode &) const
{
    return QObject::tr("illegal");
}

QString FragmentSeparatorCanvas::may_connect(UmlCode &, const DiagramItem *) const
{
    return  QObject::tr("illegal");
}

void FragmentSeparatorCanvas::connexion(UmlCode, DiagramItem *,
                                        const QPoint &, const QPoint &)
{
    // not allowed
}

void FragmentSeparatorCanvas::open()
{
}

void FragmentSeparatorCanvas::menu(const QPoint &)
{
    QMenu m(0);

    MenuFactory::createTitle(m,  QObject::tr("Separator"));
    m.addSeparator();
    MenuFactory::addItem(m,  QObject::tr("Remove from diagram"), 1);

    QAction* retAction = m.exec(QCursor::pos());
    if(retAction)
    {
    int index = retAction->data().toInt();
    if (index== 1) {
        delete_it();
        package_modified();
    }
    }
}

void FragmentSeparatorCanvas::save(QTextStream & st, bool, QString &) const
{
    nl_indent(st);
    st << "separator " << (int)(vpos * 10000);
}

FragmentSeparatorCanvas *
FragmentSeparatorCanvas::read(char *& st, UmlCanvas * canvas,
                              char * k, FragmentCanvas * f)
{
    if (strcmp(k, "separator"))
        wrong_keyword(k, "separator");

    FragmentSeparatorCanvas * result =
        new FragmentSeparatorCanvas(canvas, f, read_double(st) / 10000);

    result->compute_position();
    result->show();
    return result;
}

void FragmentSeparatorCanvas::history_save(QBuffer & b) const
{
    DiagramCanvas::history_save(b);
    ::save(vpos, b);
    ::save(fragment, b);
}

void FragmentSeparatorCanvas::history_load(QBuffer & b)
{
    DiagramCanvas::history_load(b);
    ::load(vpos, b);
    fragment = (FragmentCanvas *) ::load_item(b);
}
