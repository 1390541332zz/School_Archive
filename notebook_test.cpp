#include "notebook_app.hpp"
#include <QTest>

class NotebookTest : public QObject {
    Q_OBJECT

private slots:

    void initTestCase();

    void testInputOutput();
    void testButtons();

    void testPoints();
    void testLines();
    void testText();

    void testDiscretePlotLayout();
    void testContinuousPlotLayout();
};

void NotebookTest::initTestCase()
{
}

#include "qtests/testContinuousPlotLayout.hpp"
#include "qtests/testDiscretePlotLayout.hpp"
#include "qtests/testPrimitiveGraphics.hpp"
#include "qtests/testUI.hpp"

QTEST_MAIN(NotebookTest)
#include "notebook_test.moc"
