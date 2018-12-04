#ifndef PLOTSCRIPT_INPUT_WIDGET_H
#define PLOTSCRIPT_INPUT_WIDGET_H

#include <QPlainTextEdit>
#include <QPointer>
#include <QShortcut>

class InputWidget : public QPlainTextEdit {
    Q_OBJECT
public:
    explicit InputWidget(QWidget * parent = nullptr);
    ~InputWidget() override = default;
    void keyPressEvent(QKeyEvent * e) override;

    InputWidget(InputWidget const &) = delete;
    InputWidget & operator=(InputWidget const &) = delete;
    InputWidget(InputWidget &&) = delete;
    InputWidget & operator=(InputWidget &&) = delete;

private:
    QPointer<QShortcut> evalKey;
signals:
    void scriptEvalUpdate();
};

#endif /* PLOTSCRIPT_INPUT_WIDGET_H */
