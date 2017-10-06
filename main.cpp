#include <QApplication>

#include "toggle_widget.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  ToggleWidget w;
  
  w.show();
  return app.exec();
}
