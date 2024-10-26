#include "stdafx.h"

#include "MarkDownEditor/MarkDownEditor.h"
#include "ui_MarkDownEditor.h"

#include <cmark-gfm.h>

MarkDownEditor::MarkDownEditor(QWidget* parent,Qt::WindowFlags flags) :
  QMainWindow(parent,flags),
  ui(new Ui::MarkDownEditor())
{
  ui->setupUi(this);
}

MarkDownEditor::~MarkDownEditor()
{
  if(ui)
  {
    delete ui;
    ui = nullptr;
  }
}

void MarkDownEditor::on_tab_SourceView_textChanged()
{
  QString text_content = ui->tab_SourceView->document()->toPlainText();

  const char* html_string = cmark_markdown_to_html(text_content.toStdString().c_str(),text_content.length(), CMARK_OPT_DEFAULT);

  ui->tab_DisplayView->setHtml(html_string);
}
