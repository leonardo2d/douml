// *************************************************************************
//
// Copyright 2004-2010 Bruno PAGES  .
//
// This file is part of the BOUML Uml Toolkit.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//
// e-mail : bouml@free.fr
// home   : http://bouml.free.fr
//
// *************************************************************************





#include <q3grid.h> 
#include <q3vbox.h>
#include <qlabel.h>
#include <q3combobox.h> 
#include <qcheckbox.h> 
#include <qpushbutton.h> 

#include "TransitionDialog.h"
#include "TransitionData.h"
#include "BrowserTransition.h"
#include "KeyValueTable.h"
#include "UmlWindow.h"
#include "DialogUtil.h"
#include "strutil.h"
#include "UmlDesktop.h"
#include "BodyDialog.h"
#include "GenerationSettings.h"
#include "ProfiledStereotypes.h"
#include "translate.h"

QSize TransitionDialog::previous_size;

TransitionDialog::TransitionDialog(TransitionData * r)
    : Q3TabDialog(0, 0, FALSE, Qt::WDestructiveClose), rel(r) {
  r->browser_node->edit_start();
  
  if (r->browser_node->is_writable()) {
    setOkButton(TR("OK"));
    setCancelButton(TR("Cancel"));
  }
  else {
    setOkButton(QString::null);
    setCancelButton(TR("Close"));
  }

  setCaption(TR("Transition dialog"));
  visit = !hasOkButton();  

  BrowserNode * bn = rel->browser_node;
  
  
  //
  // general tab
  //
  
  QWidget * grid = GridConverter::InitNewGrid(this, 2);
  umltab = grid;
  
  
  
  GridConverter::PlaceWidget(new QLabel(TR("name : ")),grid);
  edname = dynamic_cast<LineEdit*>(GridConverter::PlaceWidget(new LineEdit(bn->get_name()),grid));
  edname->setReadOnly(visit);
    
  GridConverter::PlaceWidget(new QLabel(TR("stereotype : ")),grid);
  edstereotype = new Q3ComboBox(!visit, grid);
  edstereotype->insertItem(toUnicode(rel->get_stereotype()));
  if (!visit) {
    //edstereotype->insertStringList(rel->get_start()->default_stereotypes(type));
    edstereotype->setAutoCompletion(completion());
    edstereotype->insertStringList(ProfiledStereotypes::defaults(UmlTransition));
  }
  edstereotype->setCurrentItem(0);
  QSizePolicy sp = edstereotype->sizePolicy();
  sp.setHorData(QSizePolicy::Expanding);
  edstereotype->setSizePolicy(sp);
  
  if (r->get_start_node() != r->get_end_node())
    internal_cb = 0;
  else {
    GridConverter::PlaceWidget(new QLabel(),grid);
    internal_cb = dynamic_cast<QCheckBox*>(GridConverter::PlaceWidget(new QCheckBox(TR("internal")),grid));
    internal_cb->setChecked(r->internal());
  }
    
  QWidget * vtab = GridConverter::PlaceVertical(grid);
  GridConverter::PlaceWidget(new QLabel(TR("description :")),vtab);
  if (! visit)
    connect(new SmallPushButton(TR("Editor"), vtab), SIGNAL(clicked()),
	    this, SLOT(edit_description()));
  comment = dynamic_cast<MultiLineEdit*>(GridConverter::PlaceWidget(new MultiLineEdit(grid),grid));
  comment->setReadOnly(visit);
  comment->setText(bn->get_comment());
  //comment->setFont(font);
  
  addTab(grid, "Uml");

  // UML / OCL
  init_tab(ocltab, uml, rel->uml, "Ocl", SLOT(edit_uml_trigger()),
	   SLOT(edit_uml_guard()), SLOT(edit_uml_expr()), TRUE);

  // CPP
  init_tab(cpptab, cpp, rel->cpp, "C++", SLOT(edit_cpp_trigger()),
	   SLOT(edit_cpp_guard()), SLOT(edit_cpp_expr()),
	   GenerationSettings::cpp_get_default_defs());

  // Java
  init_tab(javatab, java, rel->java, "Java", SLOT(edit_java_trigger()),
	   SLOT(edit_java_guard()), SLOT(edit_java_expr()),
	   GenerationSettings::java_get_default_defs());
  
  // USER : list key - value
  
  QWidget * grid = GridConverter::InitNewGrid(this, 2);
  
  
  
  kvtable = dynamic_cast<KeyValuesTable*>(GridConverter::PlaceWidget(new KeyValuesTable(bn, grid, visit), grid));
  addTab(grid, TR("Properties"));
  
  //
    
  connect(this, SIGNAL(currentChanged(QWidget *)),
	  this, SLOT(change_tabs(QWidget *)));
  
  open_dialog(this);
}

TransitionDialog::~TransitionDialog() {
  rel->browser_node->edit_end();
  previous_size = size();
  
  while (!edits.isEmpty())
    edits.take(0)->close();
  
  close_dialog(this);
}

void TransitionDialog::change_tabs(QWidget * w) {
  if (!visit) {
    if (w == umltab)
      edname->setFocus();
    else if (w == ocltab)
      uml.edtrigger->setFocus();
    else if (w == cpptab)
      cpp.edtrigger->setFocus();
    else if (w == javatab)
      java.edtrigger->setFocus();
  }
}

void TransitionDialog::polish() {
  Q3TabDialog::polish();
  UmlDesktop::limitsize_center(this, previous_size, 0.8, 0.8);
}

void TransitionDialog::init_tab(QWidget *& tab, TransDialog & d, TransDef & td,
				const char * lbl, const char * sl_trigger,
				const char * sl_guard, const char * sl_expr,
				bool enabled) {
  QWidget * grid = GridConverter::InitNewGrid(this, 2);
  QWidget * vtab;

  tab = grid;
  
  
  
  vtab = GridConverter::PlaceVertical(grid);
  GridConverter::PlaceWidget(new QLabel(TR("trigger : ")),vtab);
  if (! visit)
    connect(new SmallPushButton(TR("Editor"), vtab), SIGNAL(clicked()),
	    this, sl_trigger);
  d.edtrigger = dynamic_cast<MultiLineEdit*>(GridConverter::PlaceWidget(new MultiLineEdit(grid),grid));

  QFont font = d.edtrigger->font();

  if (! hasCodec())
    font.setFamily("Courier");
  font.setFixedPitch(TRUE);
  d.edtrigger->setFont(font);
  d.edtrigger->setText(td.trigger);
  if (visit)
    d.edtrigger->setReadOnly(TRUE);
  
  vtab = GridConverter::PlaceVertical(grid);
  GridConverter::PlaceWidget(new QLabel(TR("guard\nconstraint : ")),vtab);
  if (! visit)
    connect(new SmallPushButton(TR("Editor"), vtab), SIGNAL(clicked()),
	    this, sl_guard);
  d.edguard = dynamic_cast<MultiLineEdit*>(GridConverter::PlaceWidget(new MultiLineEdit(grid),grid));
  d.edguard->setFont(font);
  d.edguard->setText(td.guard);
  if (visit)
    d.edguard->setReadOnly(TRUE);
  
  vtab = GridConverter::PlaceVertical(grid);
  GridConverter::PlaceWidget(new QLabel(TR("activity\nexpression : ")),vtab);
  if (! visit)
    connect(new SmallPushButton(TR("Editor"), vtab), SIGNAL(clicked()),
	    this, sl_expr);
  d.edexpr = dynamic_cast<MultiLineEdit*>(GridConverter::PlaceWidget(new MultiLineEdit(grid),grid));
  d.edexpr->setFont(font);
  d.edexpr->setText(td.expr);
  if (visit)
    d.edexpr->setReadOnly(TRUE);
  
  addTab(grid, lbl);
  
  if (! enabled)
    removePage(grid);
}

void TransitionDialog::edit_description() {
  edit(comment->text(), "transition_description", rel, TxtEdit,
       this, (post_edit) post_edit_description, edits);
}

void TransitionDialog::post_edit_description(TransitionDialog * d, QString s)
{
  d->comment->setText(s);
}

#define DEF_EDIT(attr, lang, Lang) \
void TransitionDialog::edit_##lang##_##attr() {	\
  edit(lang.ed##attr->text(), "transition_"#lang"_"#attr, rel, Lang,  \
       this, (post_edit) post_edit_##lang##_##attr, edits);	\
} \
  \
void TransitionDialog::post_edit_##lang##_##attr(TransitionDialog * d, QString s) \
{ \
  d->lang.ed##attr->setText(s); \
}

DEF_EDIT(trigger, uml, TxtEdit)
DEF_EDIT(trigger, cpp, CppEdit)
DEF_EDIT(trigger, java, JavaEdit)

DEF_EDIT(guard, uml, TxtEdit)
DEF_EDIT(guard, cpp, CppEdit)
DEF_EDIT(guard, java, JavaEdit)

DEF_EDIT(expr, uml, TxtEdit)
DEF_EDIT(expr, cpp, CppEdit)
DEF_EDIT(expr, java, JavaEdit)

void TransitionDialog::accept() {
  if (!check_edits(edits) || !kvtable->check_unique())
    return;
    
  BrowserNode * bn = rel->browser_node;
  QString s;
  
  s = edname->text().stripWhiteSpace();
  if (s.isEmpty())
    s = "<transition>";
  
  if ((s != bn->get_name()) &&
      ((BrowserNode *) bn->parent())->wrong_child_name(s, UmlTransition,
						       bn->allow_spaces(),
						       bn->allow_empty()))
    msg_critical(TR("Error"), s + TR("\n\nillegal name or already used"));
  else {  
    bn->set_name(s);
    
    bool newst = rel->set_stereotype(fromUnicode(edstereotype->currentText().stripWhiteSpace()));
    
    if (internal_cb != 0)
      rel->set_internal(internal_cb->isChecked());
    
    uml.accept(rel->uml);  
    cpp.accept(rel->cpp);  
    java.accept(rel->java);    
    
    bn->set_comment(comment->text());
    UmlWindow::update_comment_if_needed(bn);
    
    kvtable->update(bn);
    
    ProfiledStereotypes::modified(bn, newst);
    
    bn->modified();
    bn->package_modified();
    rel->modified();
    
    Q3TabDialog::accept();
  }
}

void TransDialog::accept(TransDef & td) {
  td.trigger = edtrigger->text();
  td.guard = edguard->text();
  td.expr = edexpr->text();
}
