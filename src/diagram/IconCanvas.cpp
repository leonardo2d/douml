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
//#include <q3popupmenu.h>
//Added by qt3to4:
#include <QTextStream>
#include <QPixmap>

#include "IconCanvas.h"
#include "UmlCanvas.h"
#include "BrowserDiagram.h"
#include "BasicData.h"
#include "myio.h"
#include "ui/menufactory.h"
#include "translate.h"

IconCanvas::IconCanvas(BrowserNode * bn, UmlCanvas * canvas,
                       int x, int y, int id)
    : DiagramCanvas(0, canvas, x, y, ICON_CANVAS_MIN_SIZE,
                    ICON_CANVAS_MIN_SIZE, id)
{
    browser_node = bn;
    connect(bn->get_data(), SIGNAL(deleted()), this, SLOT(deleted()));

    const QPixmap * px = bn->pixmap(0);
    int wi = px->width();
    int he = px->height();

    DiagramCanvas::resize(wi, he);

    moveBy(-wi / 2, -he / 2);
}

IconCanvas::IconCanvas(UmlCanvas * canvas) : DiagramCanvas(canvas, -1)
{
    // browser_node was deleted
    Undefined.append(this);
}

IconCanvas::~IconCanvas()
{
}

void IconCanvas::deleted()
{
    disconnect(browser_node->get_data(), SIGNAL(deleted()), this, SLOT(deleted()));
    delete_it();
    canvas()->update();
}

void IconCanvas::delete_available(BooL &, BooL & out_model) const
{
    out_model |= TRUE;
}

void IconCanvas::draw(QPainter & p)
{
    if (! visible()) return;

    p.setRenderHint(QPainter::Antialiasing, true);
    QRect r = rect();

    p.setBackgroundMode(::Qt::OpaqueMode);

    p.drawPixmap(r.topLeft(), *(browser_node->pixmap(0)));

    if (selected())
        show_mark(p, r);

    FILE * fp = svg();

    if (fp != 0) {
        fprintf(fp, "<g transform=\"translate(%d,%d)\">\n",
                r.left(), r.top());
        ((BrowserDiagram *) browser_node)->draw_svg();
        fputs("</g>\n", fp);
    }
}
void IconCanvas::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    draw(*painter);
}
void IconCanvas::change_scale()
{
    // defined to not change size
    QGraphicsRectItem::setVisible(FALSE);
    recenter();
    QGraphicsRectItem::setVisible(TRUE);
}

UmlCode IconCanvas::typeUmlCode() const
{
    return UmlIcon;
}

void IconCanvas::open()
{
    if (! browser_node->deletedp())
        browser_node->open(FALSE);
}

void IconCanvas::menu(const QPoint &)
{
    QMenu m(0);

    MenuFactory::createTitle(m, browser_node->get_name() + TR("\nshort cut"));
    m.addSeparator();
    MenuFactory::addItem(m, TR("Upper"), 0);
    MenuFactory::addItem(m, TR("Lower"), 1);
    MenuFactory::addItem(m, TR("Go up"), 6);
    MenuFactory::addItem(m, TR("Go down"), 7);
    m.addSeparator();

    if (! browser_node->deletedp()) {
        MenuFactory::addItem(m, TR("Open"), 2);
        m.addSeparator();
    }

    MenuFactory::addItem(m, TR("Select diagram in browser"), 3);
    MenuFactory::addItem(m, TR("Select linked items"), 4);
    m.addSeparator();
    MenuFactory::addItem(m, TR("Remove from diagram"), 5);

    QAction* retAction = m.exec(QCursor::pos());
    if(retAction)
    {
        switch (retAction->data().toInt()) {
        case 0:
            upper();
            // force son reaffichage
            hide();
            show();
            canvas()->update();
            break;

        case 1:
            lower();
            // force son reaffichage
            hide();
            show();
            canvas()->update();
            break;

        case 6:
            z_up();
            // force son reaffichage
            hide();
            show();
            canvas()->update();
            break;

        case 7:
            z_down();
            // force son reaffichage
            hide();
            show();
            canvas()->update();
            break;

        case 2:
            browser_node->open(FALSE);
            return;

        case 3:
            browser_node->select_in_browser();
            return;

        case 4:
            the_canvas()->unselect_all();
            select_associated();
            return;

        case 5:
            // delete
            delete_it();
            break;

        default:
            return;
        }
    }

    package_modified();
}

void IconCanvas::apply_shortcut(QString s)
{
    if (s == "Select in browser") {
        browser_node->select_in_browser();
        return;
    }
    else if (s == "Edit") {
        browser_node->open(FALSE);
        return;
    }
    else if (s == "Upper")
        upper();
    else if (s == "Lower")
        lower();
    else if (s == "Go up")
        z_up();
    else if (s == "Go down")
        z_down();
    else
        return;

    // force son reaffichage
    hide();
    show();
    canvas()->update();
}

QString IconCanvas::may_start(UmlCode & l) const
{
    return (l == UmlAnchor) ? QString() : TR("illegal");
}

QString IconCanvas::may_connect(UmlCode & l, const DiagramItem * dest) const
{
    return (l == UmlAnchor) ? dest->may_start(l) : TR("illegal");
}

bool IconCanvas::alignable() const
{
    return TRUE;
}

bool IconCanvas::copyable() const
{
    return selected();
}

bool IconCanvas::represents(BrowserNode * bn)
{
    return (bn == browser_node);
}

void IconCanvas::save(QTextStream & st, bool, QString & warning) const
{
    nl_indent(st);
    st << "iconcanvas " << get_ident() << " ";
    browser_node->save(st, TRUE, warning);
    nl_indent(st);
    save_xyz(st, this, "  xyz");
}

IconCanvas * IconCanvas::read(char *& st, UmlCanvas * canvas, char * k)
{
    if (!strcmp(k, "iconcanvas")) {
        int id = read_id(st);
        BrowserNode * bn = BrowserDiagram::read_diagram_ref(st);
        IconCanvas * result = new IconCanvas(bn, canvas, 0, 0, id);

        read_keyword(st, "xyz");
        read_xyz(st, result);
        result->set_center100();
        result->show();

        return result;
    }
    else
        return 0;
}

void IconCanvas::history_hide()
{
    QGraphicsItem::setVisible(FALSE);
    disconnect(browser_node->get_data(), SIGNAL(deleted()), this, SLOT(deleted()));
}

void IconCanvas::history_load(QBuffer & b)
{
    DiagramCanvas::history_load(b);
    connect(browser_node->get_data(), SIGNAL(deleted()), this, SLOT(deleted()));
}
