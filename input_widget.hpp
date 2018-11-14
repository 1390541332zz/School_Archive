#ifndef PLOTSCRIPT_INPUT_WIDGET_H
#define PLOTSCRIPT_INPUT_WIDGET_H

#include <QPlainTextEdit>


class InputWidget : public QPlainTextEdit {
    Q_OBJECT
public:
    InputWidget(QWidget* parent = nullptr);
    ~InputWidget();
private:

};


#endif /* PLOTSCRIPT_INPUT_WIDGET_H */
