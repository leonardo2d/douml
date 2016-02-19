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

#ifndef ACTIVITYOBJECTDATA_H
#define ACTIVITYOBJECTDATA_H

#include <QTextStream>

#include "SimpleData.h"
#include "ObjectData.h"

class ActivityObjectData : public SimpleData, public ObjectData
{
    Q_OBJECT

    friend class ActivityObjectDialog;

public:
    ActivityObjectData();
    ActivityObjectData(ActivityObjectData * model, BrowserNode * bn);

    virtual void do_connect(BrowserClass * c) override;
    virtual void do_disconnect(BrowserClass * c) override;

    void edit(QString what, QStringList & st);

    virtual void send_uml_def(ToolCom * com, BrowserNode * bn,
                              const QString & comment) override;
    virtual void send_cpp_def(ToolCom * com) override;
    virtual void send_java_def(ToolCom * com) override;
    virtual bool tool_cmd(ToolCom * com, const char * args,
                          BrowserNode * bn, const QString & comment) override;

    void save(QTextStream &, QString & warning) const;
    void read(char *& , char *&);

protected slots:
    void on_delete();
};

#endif
