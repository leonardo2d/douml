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

#ifndef SOCKET_H
#define SOCKET_H

//#include <q3socketdevice.h>
#include <qsocketnotifier.h>
#include <QTcpSocket>
#include <QTcpServer>
class ToolCom;

class Server : /* public QObject, */ public QTcpServer
{
    Q_OBJECT

protected:
    ToolCom * com;
    //QSocketNotifier * notifier;
    bool on_error;

public:
    Server(ToolCom * c);
    Server(ToolCom * c, int s);
    virtual ~Server();

    bool write_block(char * data, unsigned int len);

    qint64 read(char* buff, qint64 len);

protected slots:
    void data_received();
private:
    QTcpSocket *m_socket;
public slots:
    void onNewConnection();
};

#endif
