#include "notebook_app.hpp"
#include <QDebug>

NotebookApp::NotebookApp(QWidget* parent) 
  : QWidget(parent)
  , layout(new QVBoxLayout(this))
  , iw(new InputWidget(this))
  , ow(new OutputWidget(this))
  , evalKey(new QShortcut(QKeySequence(Qt::SHIFT + Qt::Key_Return), iw))
{
    layout->addWidget(iw);
    layout->addWidget(ow);
    setLayout(layout);

    connect(evalKey, &QShortcut::activated, this,
                [this] () {
                    qDebug() << "fuckkkk";
                    this->ow->eval_plotscript(this->iw->toPlainText());
                }
           );
}

NotebookApp::~NotebookApp() {}
