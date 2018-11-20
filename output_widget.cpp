#include <QtMath>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>

#include "interpreter.hpp"
#include "output_widget.hpp"
#include "semantic_error.hpp"
#include "startup_config.hpp"

enum ps_state { SUCCESS,
    PARSE_ERROR,
    EXCEPTION };

struct ps_res {
    QString str;
    Expression exp;
};

void find_center(QGraphicsItem * i)
{
    i->setTransformOriginPoint(i->boundingRect().center());
    i->setPos(0, 0);
}

std::pair<enum ps_state, struct ps_res> eval_ps(QString const & str)
{
    std::istringstream is(str.toStdString());
    std::ostringstream os;
    std::ostringstream eos;
    Interpreter interp;

    std::ifstream setupifs(STARTUP_FILE);

    if (!interp.parseStream(setupifs)) {
        eos << "Invalid Startup Program. Could not parse." << std::endl;
        struct ps_res r;
        r.str = QString::fromStdString(eos.str());
        return std::make_pair(PARSE_ERROR, r);
    }
    try {
        Expression exp = interp.evaluate();
    } catch (SemanticError const & ex) {
        struct ps_res r;
        r.str = QString::fromStdString(ex.what());
        return std::make_pair(EXCEPTION, r);
    }

    if (!interp.parseStream(is)) {
        eos << "Error: Invalid Expression. Could not parse." << std::endl;
        struct ps_res r;
        r.str = QString::fromStdString(eos.str());
        return std::make_pair(PARSE_ERROR, r);
    }
    try {
        Expression exp = interp.evaluate();
        os << exp << std::endl;
        struct ps_res r;
        r.exp = exp;
        return std::make_pair(SUCCESS, r);
    } catch (SemanticError const & ex) {
        struct ps_res r;
        r.str = QString::fromStdString(ex.what());
        return std::make_pair(EXCEPTION, r);
    }
}

OutputWidget::OutputWidget(QWidget * parent)
    : QWidget(parent)
    , layout(new QVBoxLayout(this))
    , scene(new QGraphicsScene(this))
    , view(new QGraphicsView(scene, this))
{
    layout->addWidget(view);
    setLayout(layout);
    setObjectName("output");
}

void OutputWidget::resizeEvent(QResizeEvent *)
{
    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

void OutputWidget::eval_plotscript(QString const & str)
{
    scene->clear();
    auto res = eval_ps(str);
    switch (res.first) {
    case PARSE_ERROR:
    case EXCEPTION:
        plot_text(res.second.str);
        break;
    case SUCCESS:
        eval_exp(res.second.exp);
        break;
    }
    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

void OutputWidget::eval_exp(Expression const & exp)
{
    if (exp.isLambda()) {
    } else if (exp.is("point")) {
        plot_pointexp(exp);
    } else if (exp.is("line")) {
        plot_lineexp(exp);
    } else if (exp.is("text")) {
        plot_textexp(exp);
    } else if (exp.isList()) {
        plot_listexp(exp);
    } else if (exp.isNone() || exp.isHeadNumber() || exp.isHeadComplex()
        || exp.isHeadSymbol() || exp.isHeadString()) {
        plot_textexp(exp);
    } else {
        plot_text("ERROR: Unknown Datatype found in OutputWidget::eval_exp");
    }
}

void OutputWidget::plot_text(QString const & str)
{
    auto t = scene->addText(str, QFont("Courier", 1));
    find_center(t);
}

void OutputWidget::plot_textexp(Expression const & exp)
{
    std::ostringstream os;
    os << exp;
    auto s = QString::fromStdString(os.str());
    if (exp.is("text")) {
        auto start = s.indexOf('"') + 1;
        auto off = s.lastIndexOf('"') - start;
        s = s.mid(start, off);
    }
    auto t = scene->addText(s, QFont("Courier", 1));
    find_center(t);
    if (exp.pmap.find("position") != exp.pmap.cend()) {
        t->setPos(find_point(exp.pmap.find("position")->second));
    }
    if (exp.pmap.find("text-rotation") != exp.pmap.cend()) {
        auto e = exp.pmap.find("text-rotation")->second;
        if (e.isHeadNumber()) {
            t->setRotation(qRadiansToDegrees(e.head().asNumber()));
        }
    }
    if (exp.pmap.find("text-scale") != exp.pmap.cend()) {
        auto e = exp.pmap.find("text-scale")->second;
        if (e.isHeadNumber() && (e.head().asNumber() >= 0)) {
            t->setScale(e.head().asNumber());
        }
    }
}

void OutputWidget::plot_listexp(Expression const & exp)
{
    for (auto it = exp.tailConstBegin(); it != exp.tailConstEnd(); ++it) {
        eval_exp(*it);
    }
}

void OutputWidget::plot_lineexp(Expression const & exp)
{
    qreal thick = exp.pmap.find("thickness")->second.head().asNumber();
    if (thick < 0) {
        plot_text("ERROR: thickness must be positive.");
    }
    auto p1 = find_point(exp.m_tail[0]);
    auto p2 = find_point(exp.m_tail[1]);
    scene->addLine(QLineF(p1, p2), QPen(QBrush(Qt::black), thick));
}

void OutputWidget::plot_pointexp(Expression const & exp)
{
    auto prop_sz = exp.pmap.find("size")->second.head();
    if ((prop_sz.asNumber() < 0) || (prop_sz.isComplex())) {
        plot_text("ERROR: size must be positive.");
    }
    qreal sz = prop_sz.asNumber();
    auto p = find_point(exp);
    auto i = scene->addEllipse(
        0, 0, sz, sz, QPen(Qt::black), QBrush(Qt::black));
    find_center(i);
    i->setPos(p);
}

QPointF OutputWidget::find_point(Expression const & exp)
{
    auto x = exp.m_tail[0].head().asNumber();
    auto y = exp.m_tail[1].head().asNumber();
    return { x, y };
}
