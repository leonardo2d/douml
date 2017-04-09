//Added by qt3to4:
#include <QTextStream>
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

#ifndef SDLOSTFOUNDMSGSUPPORTCANVAS_H
#define SDLOSTFOUNDMSGSUPPORTCANVAS_H

class SdMsgBaseCanvas;

#include "SdMsgSupport.h"

#define LOSTFOUND_SIZE 9

class SdLostFoundMsgSupportCanvas : public SdMsgSupport
{
private:
    SdMsgBaseCanvas * msg;

public:
    SdLostFoundMsgSupportCanvas(UmlCanvas * canvas, int x, int y, int id);
    virtual ~SdLostFoundMsgSupportCanvas();

    virtual void draw(QPainter & p);

    virtual UmlCode typeUmlCode() const;
    virtual void delete_available(BooL &, BooL & out_model) const;
    virtual void delete_it();
    virtual void change_scale();
    virtual void open();
    virtual void menu(const QPoint &);
    virtual QString may_start(UmlCode &) const;
    virtual QString may_connect(UmlCode & l, const DiagramItem * dest) const;
    virtual bool alignable() const;
    virtual bool copyable() const;
    virtual void add(SdMsgBaseCanvas *);
    virtual void remove(SdMsgBaseCanvas *);
    virtual double min_y() const;
    virtual void update_v_to_contain(const QRect re);
    virtual void moveBy(double dx, double dy);
    virtual void set_z(double);
    virtual bool isaDuration() const;
    virtual bool isOverlappingDuration() const;
    virtual void save(QTextStream & st, bool ref, QString & warning) const;
    static SdLostFoundMsgSupportCanvas * read(char *& st, UmlCanvas * canvas, char * k);
protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif
