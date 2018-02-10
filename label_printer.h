#ifndef LABEL_PRINTER_H
#define LABEL_PRINTER_H

#include <QLabel>

class LabelPrinter: public QLabel
{
Q_OBJECT
public:

  LabelPrinter(const char * labelstr);

  void keyPressEvent(QKeyEvent *ev);  
};

#endif

