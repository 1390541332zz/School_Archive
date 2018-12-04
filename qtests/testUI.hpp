#include "qtests/testHelpers.hpp"

void NotebookTest::testInputOutput()
{
    NotebookApp na{};
    auto iw = na.findChild<InputWidget *>("input");
    auto ow = na.findChild<OutputWidget *>("output");

    QVERIFY2(iw, "Could not find InputWidget as child of NotebookApp");
    QVERIFY2(ow, "Could not find OutputWidget as child of NotebookApp");

    auto view = ow->findChild<QGraphicsView *>();
    QVERIFY2(view, "Could not find QGraphicsView as child of OutputWidget");
    auto scene = view->scene();
    QVERIFY2(scene, "Could not find QGraphicsScene as child of QGraphicsView");
}

void NotebookTest::testButtons()
{
}
