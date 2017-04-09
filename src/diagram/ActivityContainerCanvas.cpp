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





#include "ActivityContainerCanvas.h"
#include "BrowserNode.h"
#include "ArrowCanvas.h"
#include "PinCanvas.h"
#include "ParameterCanvas.h"
#include "ExpansionNodeCanvas.h"
#include "ArrowPointCanvas.h"

void ActivityContainerCanvas::force_inside(DiagramItem * di, QGraphicsItem * ci,
        BooL & need_sub_upper)
{
    QRect r = rect();
    QRect sr = di->rect();
    int dx = 0;
    int dy = 0;

    if (sr.left() < r.left()) {
        if (sr.right() <= r.right())
            dx = r.left() - sr.left();
    }
    else if (sr.right() > r.right())
        dx = r.right() - sr.right();

    if (sr.top() < r.top()) {
        if (sr.bottom() <= r.bottom())
            dy = r.top() - sr.top();
    }
    else if (sr.bottom() > r.bottom())
        dy = r.bottom() - sr.bottom();

    if ((dx != 0) || (dy != 0))
        ci->moveBy(dx, dy);

    need_sub_upper |= (ci->zValue() <= zValue());
}

// resize this to contain its sub elements
void ActivityContainerCanvas::resize_to_contain(QList<QGraphicsItem*> & all,
        BooL & need_sub_upper)
{
    QList<QGraphicsItem*>::Iterator cit;
    BrowserNode * browser_node = get_bn();
    QRect r = rect();
    int resize_left = 0;
    int resize_right = 0;
    int resize_top = 0;
    int resize_bottom = 0;

    for (cit = all.begin(); cit != all.end(); ++cit) {
        if ((*cit)->isVisible() && !(*cit)->isSelected()) {
            DiagramItem * di = QCanvasItemToDiagramItem(*cit);

            if ((di != 0) &&
                (di->get_bn() != 0) &&
                (((BrowserNode *) di->get_bn())->parent() == browser_node)) {
                // must look at the type because some canvas items have browser_node
                // attr equals to the diagram and the parent of the diagram is the activity
                switch (di->typeUmlCode()) {
                case UmlActivityObject:
                case UmlActivityAction:
                case UmlActivityPartition:
                case UmlExpansionRegion:
                case UmlInterruptibleActivityRegion:
                case InitialAN:
                case FlowFinalAN:
                case ActivityFinalAN:
                case DecisionAN:
                case MergeAN:
                case ForkAN:
                case JoinAN: {
                    QRect di_r = di->rect();
                    int dx = 0;
                    int dy = 0;

                    if (di_r.left() < r.left()) {
                        dx = r.left() - di_r.left();

                        if (dx > resize_left)
                            resize_left = dx;
                    }

                    if (di_r.right() > r.right()) {
                        dx = di_r.right() - r.right();

                        if (dx > resize_right)
                            resize_right = dx;
                    }

                    if (di_r.top() < r.top()) {
                        dy = r.top() - di_r.top();

                        if (dy > resize_top)
                            resize_top = dy;
                    }

                    if (di_r.bottom() > r.bottom()) {
                        dy = di_r.bottom() - r.bottom();

                        if (dy > resize_bottom)
                            resize_bottom = dy;
                    }
                }

                need_sub_upper |= ((*cit)->zValue() <= zValue());
                break;

                default:
                    break;
                }
            }
        }
    }

    int dx = 0;
    int dy = 0;
    int dw = 0;
    int dh = 0;

    if (resize_top != 0) {
        dy = -resize_top;
        dh = resize_top;
    }

    if (resize_bottom != 0)
        dh += resize_bottom;

    if (resize_left != 0) {
        dx = -resize_left;
        dw = resize_left;
    }

    if (resize_right != 0)
        dw += resize_right;

    if ((dx != 0) || (dy != 0)) {
        moveBy(dx, dy);
        moveSelfRelsBy(dx, dy);
    }

    if ((dw != 0) || (dh != 0))
        DiagramCanvas::resize(width() + dw, height() + dh);
}

// update sub nodes position to be inside this
void ActivityContainerCanvas::force_sub_inside(QList<QGraphicsItem*> & all,
        BooL & need_sub_upper)
{
    QList<QGraphicsItem*>::Iterator cit;
    BrowserNode * browser_node = get_bn();

    for (cit = all.begin(); cit != all.end(); ++cit) {
        if ((*cit)->isVisible()/* && !(*cit)->isSelected()*/) {
            DiagramItem * di = QCanvasItemToDiagramItem(*cit);

            if ((di != 0) &&
                (di->get_bn() != 0) &&
                (((BrowserNode *) di->get_bn())->parent() == browser_node)) {
                // must look at the type because some canvas items have browser_node
                // attr equals to the diagram and the parent of the diagram is the activity
                switch (di->typeUmlCode()) {
                case UmlActivityObject:
                case UmlActivityAction:
                case UmlActivityPartition:
                case UmlExpansionRegion:
                case UmlInterruptibleActivityRegion:
                case InitialAN:
                case FlowFinalAN:
                case ActivityFinalAN:
                case DecisionAN:
                case MergeAN:
                case ForkAN:
                case JoinAN:
                    force_inside(di, *cit, need_sub_upper);
                    break;

                default:
                    break;
                }
            }
        }
    }
}

// update sub nodes to be upper this, recursively
void ActivityContainerCanvas::force_sub_upper(QList<QGraphicsItem*> & all)
{
    QList<QGraphicsItem*>::Iterator cit;
    BrowserNode * browser_node = get_bn();

    for (cit = all.begin(); cit != all.end(); ++cit) {
        if ((*cit)->isVisible()) {
            DiagramItem * di = QCanvasItemToDiagramItem(*cit);

            if ((di != 0) &&
                (di->get_bn() != 0) &&
                (((BrowserNode *) di->get_bn())->parent() == browser_node)) {
                // must look at the type because some canvas items have browser_node
                // attr equals to the diagram and the parent of the diagram is the activity
                switch (di->typeUmlCode()) {
                case UmlActivityObject:
                case UmlActivityAction:
                case UmlActivityPartition:
                case UmlExpansionRegion:
                case UmlInterruptibleActivityRegion:
                case InitialAN:
                case FlowFinalAN:
                case ActivityFinalAN:
                case DecisionAN:
                case MergeAN:
                case ForkAN:
                case JoinAN:
                    if ((*cit)->zValue() <= zValue())
                        ((DiagramCanvas *) di)->upper();

                    {
                        ActivityContainerCanvas * cntr =
                            dynamic_cast<ActivityContainerCanvas *>(di);

                        if (cntr != 0)
                            cntr->force_sub_upper(all);
                    }
                    break;

                default:
                    break;
                }
            }
        }
    }
}

// if elt parent is present, force inside it
bool ActivityContainerCanvas::force_inside(DiagramCanvas * elt, bool part)
{
    // if its parent is present, force inside it
    QList<QGraphicsItem*> all = elt->the_canvas()->items();
    QList<QGraphicsItem*>::Iterator cit;
    BrowserNode * parent = (BrowserNode *) elt->get_bn()->parent();

    for (cit = all.begin(); cit != all.end(); ++cit) {
        if ((*cit)->isVisible()) {
            DiagramItem * di = QCanvasItemToDiagramItem(*cit);

            if ((di != 0) &&
                IsaActivityContainer(di->typeUmlCode(), part) &&
                (((ActivityContainerCanvas *) di)->get_bn() == parent)) {
                BooL under = FALSE;

                ((ActivityContainerCanvas *) di)->force_inside(elt, elt, under);

                if (under)
                    elt->upper();

                return TRUE;
            }
        }
    }

    elt->upper();
    return FALSE;
}

// only for pin & parameter & expansion node
static bool indirectly_selected(DiagramItem * di)
{
    switch (di->typeUmlCode()) {
    case UmlParameter:
        return ((ParameterCanvas *) di)->activity_selected();
    case UmlActivityPin:
        return ((PinCanvas *) di)->action_selected();
    case UmlExpansionNode:
        return ((ExpansionNodeCanvas *) di)->region_selected();
    default:
        return FALSE;

    }
}

void ActivityContainerCanvas::prepare_for_move(bool on_resize)
{
    if (! on_resize) {
        // select all sub nodes
        QList<QGraphicsItem*> all = canvas()->items();
        QList<QGraphicsItem*>::Iterator cit;
        UmlCanvas * canvas = the_canvas();

        for (cit = all.begin(); cit != all.end(); ++cit) {
            if ((*cit)->isVisible() && !(*cit)->isSelected()) {
                DiagramItem * di = QCanvasItemToDiagramItem(*cit);

                if ((di != 0) &&
                    (di->get_bn() != 0) &&
                    (((BrowserNode *) di->get_bn()->parent()) == browser_node)) {
                    // must look at the type because some canvas items have browser_node
                    // attr set to the diagram and the parent of the diagram is the activity
                    switch (di->typeUmlCode()) {
                    case UmlActivityObject:
                    case UmlActivityAction:
                    case UmlActivityPartition:
                    case InitialAN:
                    case FlowFinalAN:
                    case ActivityFinalAN:
                    case DecisionAN:
                    case MergeAN:
                    case ForkAN:
                    case JoinAN:
                    case UmlExpansionRegion:
                    case UmlInterruptibleActivityRegion:
                        canvas->select(*cit);
                        ((DiagramCanvas *) di)->prepare_for_move(on_resize);
                        break;

                    default:
                        break;
                    }
                }
            }
        }

        // select points on lines having the two extremities selected or
        // connecting pin/parameter/expansion node of element selected
        for (cit = all.begin(); cit != all.end(); ++cit) {
            if ((*cit)->isVisible() && !(*cit)->isSelected() && isa_arrow(*cit)) {
                ArrowCanvas * ar = (ArrowCanvas *) *cit;
                DiagramItem * b;
                DiagramItem * e;

                ar->extremities(b, e);

                if (!b->isSelected() || !e->isSelected()) {
                    DiagramItem * start = ar->get_start();
                    DiagramItem * dest = ar->get_end();

                    if ((start->isSelected() || indirectly_selected(start)) &&
                        (dest->isSelected() || indirectly_selected(dest))) {
                        while (b->typeUmlCode() == UmlArrowPoint) {
                            canvas->select((ArrowPointCanvas *) b);
                            ar = ((ArrowPointCanvas *) b)->get_other(ar);
                            ar->extremities(b, e);
                        }

                        ar = (ArrowCanvas *) *cit;
                        ar->extremities(b, e);

                        while (e->typeUmlCode() == UmlArrowPoint) {
                            canvas->select((ArrowPointCanvas *) e);
                            ar = ((ArrowPointCanvas *) e)->get_other(ar);
                            ar->extremities(b, e);
                        }
                    }
                }
            }
        }
    }
}
