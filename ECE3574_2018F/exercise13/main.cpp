#include <QApplication>


#include "traffic_light.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  TrafficLight light;

  // setup the timer and conenction here

  light.show();
  return app.exec();
}

