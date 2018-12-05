#include "qtests/testHelpers.hpp"

void NotebookTest::testPoints()
{
    NotebookApp_expose expose{};
    auto iw = expose.iw;
    auto ow = expose.ow;

    std::string program = R"(
(begin (list
    (set-property "size" 0.1 (make-point  10  10))
    (set-property "size" 0.1 (make-point -10 -10))
    (set-property "size"   5 (make-point   0   0))
    (set-property "size"   5 (make-point  20  20)) ))
)";

    iw->setPlainText(QString::fromStdString(program));
    QTest::keyClick(iw, Qt::Key_Return, Qt::ShiftModifier);

    auto view = ow->findChild<QGraphicsView *>();
    QVERIFY2(view, "Could not find QGraphicsView as child of OutputWidget");

    auto scene = view->scene();

    auto items = scene->items();
    QCOMPARE(items.size(), 4);

    // make them all selectable
    foreach (auto item, items) {
        item->setFlag(QGraphicsItem::ItemIsSelectable);
    }

    QCOMPARE(findPoints(scene, QPointF(0, 0), 2.51), 1);
    QCOMPARE(findPoints(scene, QPointF(-10, -10), 0.11), 1);
    QCOMPARE(findPoints(scene, QPointF(10, 10), 0.11), 1);
    QCOMPARE(findPoints(scene, QPointF(20, 20), 2.51), 1);
}

void NotebookTest::testLines()
{
}

void NotebookTest::testText()
{
}
