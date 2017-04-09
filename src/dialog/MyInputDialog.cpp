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
#include <qlayout.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qpushbutton.h>
#include <qvalidator.h>
#include <qapplication.h>
//Added by qt3to4:
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "MyInputDialog.h"
#include "DialogUtil.h"
#include "UmlDesktop.h"
#include "translate.h"
#include <QLineEdit>
QSize MyInputDialog::previous_size;

MyInputDialog::MyInputDialog(const char * title, const QString & msg,
                             const QString & init)
    : QDialog(0/*, title, TRUE*/)
{
    setWindowTitle(title);
    move(QCursor::pos());

    QVBoxLayout * vbox = new QVBoxLayout(this);
    QHBoxLayout * hbox;

    vbox->setMargin(5);

    hbox = new QHBoxLayout();
    vbox->addLayout(hbox);
    hbox->setMargin(5);
    hbox->addWidget(new QLabel(msg, this));
    le = new LineEdit(init, this);

    hbox->addWidget(le);

    QFontMetrics fm(QApplication::font());

    le->setMinimumWidth(fm.width("AZERTYUIOPQSDFGHJKLMWXCVBN"));

    hbox = new QHBoxLayout();
    vbox->addLayout(hbox);
    hbox->setMargin(5);
    QPushButton * ok = new QPushButton(TR("&OK"), this);
    QPushButton * cancel = new QPushButton(TR("&Cancel"), this);
    QSize bs(cancel->sizeHint());

    ok->setDefault(TRUE);
    ok->setFixedSize(bs);
    cancel->setFixedSize(bs);

    hbox->addWidget(ok);
    hbox->addWidget(cancel);

    connect(ok, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));

    le->setFocus();
}

MyInputDialog::MyInputDialog(const char * title, const QString & msg,
                             const QStringList & list, const QString & init,
                             bool existing)
    : QDialog(0/*, title, TRUE*/), le(0)
{
    setWindowTitle(title);
    move(QCursor::pos());

    QVBoxLayout * vbox = new QVBoxLayout(this);
    QHBoxLayout * hbox;

    vbox->setMargin(5);

    hbox = new QHBoxLayout();
    vbox->addLayout(hbox);
    hbox->setMargin(5);
    hbox->addWidget(new QLabel(msg, this));
    cb = new QComboBox(this);
    cb->setEditable(!existing);

    if (! existing)
        cb->addItem(init);

    cb->addItems(list);

    if (! existing) {
        cb->setCurrentIndex(0);
        cb->setAutoCompletion(completion());
    }

    hbox->addWidget(cb);

    QSizePolicy sp = cb->sizePolicy();

    sp.setHorizontalPolicy(QSizePolicy::Expanding);
    cb->setSizePolicy(sp);

    QFontMetrics fm(QApplication::font());

    cb->setMinimumWidth(fm.width("azertyuiopqsdfghjklm"));

    hbox = new QHBoxLayout();
    vbox->addLayout(hbox);
    hbox->setMargin(5);
    QPushButton * ok = new QPushButton(TR("&OK"), this);
    QPushButton * cancel = new QPushButton(TR("&Cancel"), this);
    QSize bs(cancel->sizeHint());

    ok->setDefault(TRUE);
    ok->setFixedSize(bs);
    cancel->setFixedSize(bs);

    hbox->addWidget(ok);
    hbox->addWidget(cancel);

    connect(ok, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));

    cb->setFocus();
}

void MyInputDialog::polish()
{
    QDialog::ensurePolished();
    UmlDesktop::limitsize_center(this, previous_size, 0.8, 0.8);
}

MyInputDialog::~MyInputDialog()
{
    previous_size = size();
}

void MyInputDialog::accept()
{
    if ((le == 0) || (le->validator() == 0))
        QDialog::accept();
    else {
        QString s = le->text();
        int p = 0;

        if (le->validator()->validate(s, p) == QValidator::Acceptable)
            QDialog::accept();
    }
}

QString MyInputDialog::getText(const char * title, const QString & msg,
                               const QString & init, BooL & ok,
                               const QValidator * v)
{
    MyInputDialog d(title, msg, init);

    if (v != 0)
        d.le->setValidator(v);

    ok = d.exec() == QDialog::Accepted;

    return (ok)
           ? d.le->text()
           : QString();
}

QString MyInputDialog::getText(const char * title, const QString & msg,
                               const QStringList & list, const QString & init,
                               bool existing, BooL & ok)
{
    MyInputDialog d(title, msg, list, init, existing);

    ok = d.exec() == QDialog::Accepted;

    return (ok)
           ? d.cb->currentText()
           : QString();
}
