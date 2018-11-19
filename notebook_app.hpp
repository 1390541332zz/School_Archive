#ifndef PLOTSCRIPT_NOTEBOOK_APP_H
#define PLOTSCRIPT_NOTEBOOK_APP_H

#include <QWidget>
#include <QPointer>
#include <QVBoxLayout>
#include "input_widget.hpp"
#include "output_widget.hpp"

class NotebookApp : public QWidget {
    Q_OBJECT
public:
    NotebookApp(QWidget* parent = nullptr);
    ~NotebookApp();
private:
    QPointer<QVBoxLayout> layout;
    QPointer<InputWidget> iw;
    QPointer<OutputWidget> ow;
};


#endif /* PLOTSCRIPT_NOTEBOOK_APP_H */
