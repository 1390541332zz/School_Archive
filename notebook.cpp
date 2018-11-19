#include "notebook_app.hpp"
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    NotebookApp widget;

    widget.show();

    return app.exec();
}
