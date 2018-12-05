#include "qtests/testHelpers.hpp"

void NotebookTest::testPoints()
{
    NotebookApp_expose expose{};
    auto iw = expose.iw;
    auto ow = expose.ow;

    std::string program = R"(
(begin (list
    (set-property "size" 0.000001 (make-point   1000000  1000000))
    (set-property "size" 0.000001 (make-point   1000000 -1000000))
    (set-property "size" 0.000001 (make-point  -1000000  1000000))
    (set-property "size" 0.000001 (make-point  -1000000 -1000000))
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
    QCOMPARE(items.size(), 7);

    // make them all selectable
    foreach (auto item, items) {
        item->setFlag(QGraphicsItem::ItemIsSelectable);
        //qDebug().noquote() << item << "\n  b: " << item->boundingRect() <<"r: " << item->sceneBoundingRect() << " o: " << item->pos();
    }

    QCOMPARE(findPoints(scene, QPointF(0, 0), 2.51), 1);
    QCOMPARE(findPoints(scene, QPointF(-10, -10), 0.11), 1);
    QCOMPARE(findPoints(scene, QPointF( 1000000,  1000000), 0.001), 1);
    QCOMPARE(findPoints(scene, QPointF( 1000000, -1000000), 0.001), 1);
    QCOMPARE(findPoints(scene, QPointF(-1000000,  1000000), 0.001), 1);
    QCOMPARE(findPoints(scene, QPointF(-1000000, -1000000), 0.001), 1);
    QCOMPARE(findPoints(scene, QPointF(20, 20), 2.51), 1);
}

void NotebookTest::testLines()
{
    NotebookApp_expose expose{};
    auto iw = expose.iw;
    auto ow = expose.ow;

    std::string program = R"(
(begin (list
    (set-property "thickness" 10 (make-line (make-point 100 100) (make-point 120 100)))
    (make-line (make-point  0   0) (make-point 20   0))
    (make-line (make-point 20   0) (make-point 40   0))
    (make-line (make-point  0  20) (make-point 20  20))
    (make-line (make-point 40 -40) (make-point 60 -40)) ))
)";

    iw->setPlainText(QString::fromStdString(program));
    QTest::keyClick(iw, Qt::Key_Return, Qt::ShiftModifier);

    auto view = ow->findChild<QGraphicsView *>();
    QVERIFY2(view, "Could not find QGraphicsView as child of OutputWidget");

    auto scene = view->scene();

    auto items = scene->items();
    QCOMPARE(items.size(), 5);

    // make them all selectable
    foreach (auto item, items) {
        item->setFlag(QGraphicsItem::ItemIsSelectable);
        //qDebug().noquote() << item << "\n  b: " << item->boundingRect() <<"r: " << item->sceneBoundingRect() << " o: " << item->pos();
    }

    QCOMPARE(findLines(scene, QRectF(0,     0, 20, 0),  1), 1);
    QCOMPARE(findLines(scene, QRectF(20,    0, 20, 0),  1), 1);
    QCOMPARE(findLines(scene, QRectF(0,    20, 20, 0),  1), 1);
    QCOMPARE(findLines(scene, QRectF(40,  -40, 20, 0),  1), 1);
    QCOMPARE(findLines(scene, QRectF(100, 100, 20, 0), 10), 1);
}

void NotebookTest::testText()
{
    NotebookApp_expose expose{};
    auto iw = expose.iw;
    auto ow = expose.ow;

    std::string program = R"(
(begin (list
    (set-property "position" (make-point 100 100) (make-text "pos")) 
    (set-property "text-scale" 2 (set-property "position" (make-point -100 -100) (make-text "scale")))
    (set-property "text-rotation" pi (set-property "position" (make-point -100 100) (make-text "rot")))
    (make-text "yeet") ))
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
        qDebug().noquote() << item << "\n  b: " << item->boundingRect() <<"r: " << item->sceneBoundingRect() << " o: " << item->pos();
    }

    QCOMPARE(findText(scene, QPointF(   0,    0),    0, QString("yeet")), 1);
    QCOMPARE(findText(scene, QPointF( 100,  100),    0, QString("pos")), 1);
    QCOMPARE(findText(scene, QPointF(-100, -100),    0, QString("scale")), 1);
    QCOMPARE(findText(scene, QPointF(-100,  100),  180, QString("rot")), 1);

}
