#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

#include <QWidget>

class QRadioButton;

class TrafficLight: public QWidget{
  Q_OBJECT

public:

  TrafficLight(QWidget * parent = nullptr);
  
private:

  QRadioButton * redlight;
  QRadioButton * yellowlight;
  QRadioButton * greenlight;

};



#endif
