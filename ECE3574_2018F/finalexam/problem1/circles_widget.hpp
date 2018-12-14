#ifndef CIRCLES_WIDGET_HPP
#define CIRCLES_WIDGET_HPP

#include <QDoubleSpinBox>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGridLayout>
#include <QLabel>
#include <QPointer>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class CirclesWidget : public QWidget {
    Q_OBJECT
public:
    explicit CirclesWidget(QWidget * parent = nullptr);
    ~CirclesWidget() override = default;

    CirclesWidget(CirclesWidget const &) = delete;
    CirclesWidget & operator=(CirclesWidget const &) = delete;
    CirclesWidget(CirclesWidget &&) = delete;
    CirclesWidget & operator=(CirclesWidget &&) = delete;

private:
    QPointer<QDoubleSpinBox> xw;
    QPointer<QDoubleSpinBox> yw;
    QPointer<QDoubleSpinBox> rw;
    QPointer<QPushButton> draw;
    QPointer<QGraphicsScene> scene;
    QPointer<QGraphicsView> view;
    QPointer<QVBoxLayout> layout;

    void draw_circle();
    void move_item(QGraphicsItem * i, QPointF p);
    void find_center(QGraphicsItem * i);
    void plot_point(QPointF p, qreal sz = 0);
};

#endif /* CIRCLES_WIDGET_HPP */
