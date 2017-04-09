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

#ifndef LABELCANVAS_H
#define LABELCANVAS_H

#include <qfont.h>

#include "QGraphicsScene"
//Added by qt3to4:
#include <QTextStream>

#include "DiagramItem.h"
#include "UmlCanvas.h"

#define LABEL_Z 3000
#define OLD_LABEL_Z 1e100

#define isa_label(x) ((x)->type() == RTTI_LABEL)

class LabelCanvas : public QGraphicsSimpleTextItem, public DiagramItem
{
public:
    static const char * Triangle;
    static const char * Zigzag;

protected:
    bool multi_lines_centered;
    int center_x_scale100;
    int center_y_scale100;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
public:
    LabelCanvas(const QString & n, UmlCanvas * canvas, int x, int y,
                bool bold = FALSE, bool italic = FALSE,
                bool underlined = FALSE, bool mlcentered = TRUE);
    virtual ~LabelCanvas();

    virtual void delete_it();

    const QString get_name() const {
        return text();
    };
    virtual QRect rect() const;
    virtual QRect sceneRect() const;

    int width() const {
        return boundingRect().width();
    };
    int height() const {
        return boundingRect().height();
    };
    void set_name(const QString &);

    void set_strikeout(bool yes);
    void set_underlined(bool yes);

    void move_outside(QRect r, double angle);

    virtual void draw(QPainter & p);

    virtual UmlCode typeUmlCode() const;
    virtual int rtti() const;
    void moveBy(double dx, double dy);
    virtual QPoint center() const;
    void recenter();
    void set_center100();
    virtual bool contains(int, int) const;
    virtual void change_scale();
    virtual void open();
    void menu(const QPoint &);
    virtual QString may_start(UmlCode &) const;
    virtual QString may_connect(UmlCode & l, const DiagramItem * dest) const;
    virtual void connexion(UmlCode, DiagramItem *, const QPoint &, const QPoint &);
    virtual double get_z() const;
    virtual void set_z(double z);	// only called by upper() & lower()
    virtual UmlCanvas * the_canvas() const;
    virtual bool isSelected() const;
    virtual void save(QTextStream  & st, bool ref, QString & warning) const;
    static LabelCanvas * read(char *& st, UmlCanvas * canvas, char *);
    virtual void history_save(QBuffer &) const;
    virtual void history_load(QBuffer &);
    virtual void history_hide();

    virtual void check_stereotypeproperties();

    virtual int type() const;
};

#endif
