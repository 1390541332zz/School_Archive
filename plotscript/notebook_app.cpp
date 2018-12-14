#include "notebook_app.hpp"
#include <QDebug>

NotebookApp::NotebookApp(QWidget * parent)
    : QWidget(parent)
    , layout(new QVBoxLayout(this))
    , button_layout(new QHBoxLayout(this))
    , iw(new InputWidget(this))
    , ow(new OutputWidget(this))
    , start(new QPushButton("Start Kernel", this))
    , stop(new QPushButton("Stop Kernel", this))
    , reset(new QPushButton("Reset Kernel", this))
    , interrupt(new QPushButton("Interrupt", this))
{
    button_layout->addWidget(start);
    button_layout->addWidget(stop);
    button_layout->addWidget(reset);
    button_layout->addWidget(interrupt);
    layout->addLayout(button_layout);
    layout->addWidget(iw);
    layout->addWidget(ow);
    setLayout(layout);
    connect(iw, &InputWidget::scriptEvalUpdate, this,
        [this]() {
            this->ow->eval_plotscript(this->iw->toPlainText());
        });
}
