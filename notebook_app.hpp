#ifndef PLOTSCRIPT_NOTEBOOK_APP_H
#define PLOTSCRIPT_NOTEBOOK_APP_H

#include "input_widget.hpp"
#include "output_widget.hpp"
#include <QPointer>
#include <QVBoxLayout>
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
    QPointer<InputWidget> iw;
    QPointer<OutputWidget> ow;
};

#endif /* PLOTSCRIPT_NOTEBOOK_APP_H */
