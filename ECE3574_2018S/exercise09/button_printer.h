#ifndef _BUTTON_PRINTER_H_
#define _BUTTON_PRINTER_H_

#include <QObject>

class ButtonPrinter: public QObject{
  Q_OBJECT

public slots:
   void print();
};

#endif

