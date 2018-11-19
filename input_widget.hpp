#ifndef PLOTSCRIPT_INPUT_WIDGET_H
#define PLOTSCRIPT_INPUT_WIDGET_H

#include <QPointer>
#include <QShortcut>
#include <QPlainTextEdit>

class InputWidget : public QPlainTextEdit {
    Q_OBJECT
public:
    InputWidget(QWidget* parent = nullptr);
    ~InputWidget();
    void keyPressEvent(QKeyEvent* e);
private:
    QPointer<QShortcut> evalKey;
signals:
    void scriptEvalUpdate();
};


#endif /* PLOTSCRIPT_INPUT_WIDGET_H */
