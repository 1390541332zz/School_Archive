#ifndef TOGGLE_WIDGET_H
#define TOGGLE_WIDGET_H

#include <QWidget>

class QRadioButton;

class ToggleWidget: public QWidget{
  Q_OBJECT

public:

  ToggleWidget();

  bool isOn();

private:
  QRadioButton * rb;
};


#endif
