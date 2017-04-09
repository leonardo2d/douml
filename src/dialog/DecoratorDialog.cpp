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





#include <qlabel.h>
#include <qlayout.h>
#include <qpushbutton.h>
#include <qcombobox.h>
//Added by qt3to4:
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "DecoratorDialog.h"
#include "UmlDesktop.h"
#include "BrowserClass.h"
#include "translate.h"

QSize DecoratorDialog::previous_size;

static const char * DefaultDecorators[] = {
    "classmethod"
};

DecoratorDialog::DecoratorDialog(QWidget * parent, QString & s, bool visit)
    : QDialog(parent/*, "decorator editor", TRUE*/), value(s)
{
    setWindowTitle(TR("decorator dialog"));

    QVBoxLayout * vbox = new QVBoxLayout(this);

    vbox->setMargin(5);

    // multiline edit

    e = new MultiLineEdit(this);
    e->setText(s);
    vbox->addWidget(e);

    if (! visit) {
        e->setFocus();

        // to choose and add an decorator

        QLabel * label =
            new QLabel(TR("\nTo add an decorator at the cursor position\n"
                          "you may select it in the list and press 'add'\n"
                          "\nSet operation static to add @staticmethod,\n"
                          "set operation abstract to add @abstractmethod\n"),
                       this);
        label->setAlignment(Qt::AlignCenter);
        vbox->addWidget(label);

        QHBoxLayout * hbox = new QHBoxLayout();
        vbox->addLayout(hbox);
        QPushButton * add_button;

        hbox->setMargin(5);
        add_button = new QPushButton(TR("Add "), this);
        hbox->addWidget(add_button);
        connect(add_button, SIGNAL(clicked()), this, SLOT(add_decorator()));

        cb = new QComboBox(this);

        QSizePolicy sp = cb->sizePolicy();

        sp.setHorizontalPolicy(QSizePolicy::Expanding);
        cb->setSizePolicy(sp);
        cb->setAutoCompletion(completion());

        for (int i = 0;
             i != sizeof(DefaultDecorators) / sizeof(*DefaultDecorators);
             i += 1)
            cb->addItem(DefaultDecorators[i]);

        BrowserClass::instances(decorators);

        if (! decorators.isEmpty()) {
            QStringList list;

            decorators.full_names(list);
            cb->addItems(list);
        }

        hbox->addWidget(cb);

        // buttons ok, cancel

        vbox->addWidget(new QLabel("", this));

        hbox = new QHBoxLayout();
        vbox->addLayout(hbox);
        hbox->setMargin(5);
        QPushButton * accept = new QPushButton(TR("&OK"), this);
        QPushButton * cancel = new QPushButton(TR("&Cancel"), this);
        QSize bs(cancel->sizeHint());

        accept->setDefault(TRUE);
        accept->setFixedSize(bs);
        cancel->setFixedSize(bs);

        hbox->addWidget(accept);
        hbox->addWidget(cancel);

        connect(accept, SIGNAL(clicked()), this, SLOT(accept()));
        connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));
    }
    else {
        e->setReadOnly(TRUE);

        // buttons cancel

        vbox->addWidget(new QLabel("", this));

        QHBoxLayout * hbox = new QHBoxLayout();
        vbox->addLayout(hbox);

        hbox->setMargin(5);
        QPushButton * close = new QPushButton(TR("&Close"), this);

        hbox->addWidget(close);

        connect(close, SIGNAL(clicked()), this, SLOT(reject()));
    }

    // not done in polish else the initial size is too small
    UmlDesktop::setsize_center(this, previous_size, 0.3, 0.3);
}

DecoratorDialog::~DecoratorDialog()
{
    previous_size = size();
}

void DecoratorDialog::add_decorator()
{
    const int ndefault =
        sizeof(DefaultDecorators) / sizeof(*DefaultDecorators);
    int added_index = cb->currentIndex();
    QString added;

    if (added_index < ndefault)
        added = DefaultDecorators[added_index];
    else {
        BrowserNode * cl = decorators.at(added_index - ndefault);
        added = cl->get_name();
    }

    e->appendPlainText("@" + added + "\n");
    e->setFocus();
}

void DecoratorDialog::accept()
{
    value = e->text().trimmed();

    if (!value.isEmpty())
        value += '\n';

    QDialog::accept();
}
