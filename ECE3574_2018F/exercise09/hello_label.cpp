#include <QApplication>

#include "label_printer.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  LabelPrinter hello("Hello world!");

  hello.show();
  return app.exec();
}
