#include "notebook_app.hpp"
#include <QDebug>

NotebookApp::NotebookApp(QWidget* parent)
    : QWidget(parent)
    , layout(new QVBoxLayout(this))
    , iw(new InputWidget(this))
    , ow(new OutputWidget(this))
{
    layout->addWidget(iw);
    layout->addWidget(ow);
    setLayout(layout);
    connect(iw, &InputWidget::scriptEvalUpdate, this,
        [this]() {
            this->ow->eval_plotscript(this->iw->toPlainText());
        });
}

NotebookApp::~NotebookApp() {}
