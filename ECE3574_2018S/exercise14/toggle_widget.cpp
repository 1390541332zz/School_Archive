#include "toggle_widget.h"

#include <QPushButton>
#include <QRadioButton>

#include <QLayout>

ToggleWidget::ToggleWidget(){

  QPushButton * pb = new QPushButton("Switch");
  rb = new QRadioButton("Light");

  QObject::connect(pb, SIGNAL(clicked()), rb, SLOT(toggle()));
  
  QHBoxLayout *layout = new QHBoxLayout;
  layout->addWidget(pb);
  layout->addWidget(rb);

  qDebug("Button's parent before setLayout: %p", pb->parent());
  this->setLayout(layout);
  qDebug("Button's parent after setLayout: %p", pb->parent());
}

bool ToggleWidget::isOn(){
  return rb->isChecked();
}
