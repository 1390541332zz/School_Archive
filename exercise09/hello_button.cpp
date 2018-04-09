#include <QApplication>
#include <QPushButton>

#include "button_printer.h"

int main(int argc, char *argv[]){
  QApplication app(argc, argv);

  QPushButton hello("Hello world!");
  ButtonPrinter printer;

  QObject::connect(&hello, SIGNAL(clicked()), &printer, SLOT(print()));

  hello.show();
  return app.exec();
}

