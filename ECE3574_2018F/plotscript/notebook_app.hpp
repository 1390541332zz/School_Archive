#ifndef PLOTSCRIPT_NOTEBOOK_APP_H
#define PLOTSCRIPT_NOTEBOOK_APP_H

#include "input_widget.hpp"
#include "output_widget.hpp"
#include <QPointer>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>

class NotebookApp : public QWidget {
    Q_OBJECT
public:
    explicit NotebookApp(QWidget * parent = nullptr);
    ~NotebookApp() override = default;

    NotebookApp(NotebookApp const &) = delete;
    NotebookApp & operator=(NotebookApp const &) = delete;
    NotebookApp(NotebookApp &&) = delete;
    NotebookApp & operator=(NotebookApp &&) = delete;

private:
    QPointer<QVBoxLayout> layout;
    QPointer<QHBoxLayout> button_layout;
    QPointer<InputWidget> iw;
    QPointer<OutputWidget> ow;
    QPointer<QPushButton> start;
    QPointer<QPushButton> stop;
    QPointer<QPushButton> reset;
    QPointer<QPushButton> interrupt;
};

#endif /* PLOTSCRIPT_NOTEBOOK_APP_H */
