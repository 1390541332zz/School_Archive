#include <QTest>

#include <QDoubleSpinBox>
#include <QGraphicsView>
#include <QPushButton>

#include "circles_widget.hpp"

class CirclesWidgetTest : public QObject {
    Q_OBJECT

private slots:

    void initTestCase();

    // put your tests here
    void testCircles();

private:
    CirclesWidget widget;

    QDoubleSpinBox * xWidget;
    QDoubleSpinBox * yWidget;
    QDoubleSpinBox * rWidget;
    QPushButton * pbWidget;
    QGraphicsView * viewWidget;
};

void CirclesWidgetTest::initTestCase()
{

    xWidget = widget.findChild<QDoubleSpinBox *>("centerx");
    QVERIFY2(xWidget, "Could not find X Center Widget");

    yWidget = widget.findChild<QDoubleSpinBox *>("centery");
    QVERIFY2(yWidget, "Could not find Y Center Widget");

    rWidget = widget.findChild<QDoubleSpinBox *>("radius");
    QVERIFY2(rWidget, "Could not find Radius Widget");

    pbWidget = widget.findChild<QPushButton *>("draw");
    QVERIFY2(pbWidget, "Could not find Draw Widget");

    viewWidget = widget.findChild<QGraphicsView *>("view");
    QVERIFY2(viewWidget, "Could not find View Widget");
}

void CirclesWidgetTest::testCircles()
{
    
}

QTEST_MAIN(CirclesWidgetTest)
#include "circles_widget_test.moc"
