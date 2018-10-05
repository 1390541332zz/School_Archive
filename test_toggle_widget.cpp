#include <QtTest/QtTest>
#include <QtWidgets>
#include <QDebug>

#include "toggle_widget.h"

class TestToggleWidget : public QObject {
  Q_OBJECT

private slots:
    void testRadio();
};

void TestToggleWidget::testRadio()
{
    ToggleWidget* widget = new ToggleWidget();
    QRadioButton * rad = widget->findChild<QRadioButton *>();
    QPushButton * but = widget->findChild<QPushButton *>();
    QVERIFY(but != nullptr);
    QVERIFY(rad != nullptr);
    QVERIFY(!(widget->isOn()));
    QVERIFY(!(rad->isChecked()));
    QTest::mouseClick(but, Qt::LeftButton);
    QVERIFY(widget->isOn());
    QVERIFY(rad->isChecked());
    QTest::mouseClick(but, Qt::LeftButton, Qt::NoModifier, but->rect().center());
    QVERIFY(!(widget->isOn()));
    QVERIFY(!(rad->isChecked()));
    delete widget;
}

QTEST_MAIN(TestToggleWidget)
#include "test_toggle_widget.moc"
