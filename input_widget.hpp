#ifndef PLOTSCRIPT_INPUT_WIDGET_H
#define PLOTSCRIPT_INPUT_WIDGET_H

#include <QPlainTextEdit>
#include <QPointer>
#include <QShortcut>

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
