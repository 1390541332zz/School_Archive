#include "circles_widget.hpp"

CirclesWidget::CirclesWidget(QWidget * parent)
    : QWidget(parent)
    , xw(new QDoubleSpinBox(this))
    , yw(new QDoubleSpinBox(this))
    , rw(new QDoubleSpinBox(this))
    , draw(new QPushButton("draw", this))
    , scene(new QGraphicsScene(this))
    , view(new QGraphicsView(scene, this))
    , layout(new QVBoxLayout(this))
{
    xw->setRange(-10., 10.);
    xw->setSingleStep(0.1);

    yw->setRange(-10., 10.);
    yw->setSingleStep(0.1);

    rw->setRange(0.1, 10.);
    rw->setSingleStep(0.1);

    xw->setObjectName("centerx");
    yw->setObjectName("centery");
    rw->setObjectName("radius");
    draw->setObjectName("draw");
    view->setObjectName("view");

    QPointer<QGridLayout> gl(new QGridLayout(this));

    gl->addWidget((new QLabel("x:")), 0, 0);
    gl->addWidget(xw, 0, 1);
    gl->addWidget((new QLabel("y:")), 1, 0);
    gl->addWidget(yw, 1, 1);
    gl->addWidget((new QLabel("radius:")), 0, 3);
    gl->addWidget(yw, 0, 4);
    gl->addWidget(draw, 1, 3, 1, 2, Qt::AlignCenter);

    layout->addLayout(gl);
    layout->addWidget(view);
    setLayout(layout);

    connect(draw, &QPushButton::clicked, this,
        [this]() {
            this->draw_circle();
        });
}

void CirclesWidget::draw_circle()
{
    scene->clear();
    plot_point(QPointF{ xw->value(), yw->value() }, rw->value());
}

void CirclesWidget::move_item(QGraphicsItem * i, QPointF p)
{
    i->setPos(i->pos() + p);
}

void CirclesWidget::find_center(QGraphicsItem * i)
{
    auto c = i->boundingRect().center();
    i->setTransformOriginPoint(c);
    i->setPos(-(i->mapToScene(c)));
}
void CirclesWidget::plot_point(QPointF p, qreal sz)
{
    auto i = scene->addEllipse(
        (-sz / 2), (-sz / 2), sz, sz, QPen(Qt::NoPen), QBrush(Qt::black));
    find_center(i);
    move_item(i, p);
}
