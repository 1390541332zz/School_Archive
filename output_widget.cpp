#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <QDebug>

#include "output_widget.hpp"
#include "interpreter.hpp"
#include "semantic_error.hpp"
#include "startup_config.hpp"

enum ps_state { SUCCESS, PARSE_ERROR, EXCEPTION };

struct ps_res {
    QString str;
    Expression exp;
};

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
        } else {
            try {
                Expression exp = interp.evaluate();
            } catch (const SemanticError& ex) {
                eos << ex.what() << std::endl;
                struct ps_res r;
                r.str = QString::fromStdString(eos.str());
                return std::make_pair(EXCEPTION, r);
            }
        }
        if (!interp.parseStream(is)) {
            eos << "Invalid Program. Could not parse." << std::endl;
            struct ps_res r;
            r.str = QString::fromStdString(eos.str());
            return std::make_pair(PARSE_ERROR, r);
        } else {
            try {
                Expression exp = interp.evaluate();
                os << exp << std::endl;
                struct ps_res r;
                r.exp = exp;
                return std::make_pair(SUCCESS, r);
            } catch (const SemanticError& ex) {
                eos << ex.what() << std::endl;
                struct ps_res r;
                r.str = QString::fromStdString(eos.str());
                return std::make_pair(EXCEPTION, r);
            }
        }
}

OutputWidget::OutputWidget(QWidget* parent) 
  : QWidget(parent)
  , layout(new QVBoxLayout(this))
  , scene(new QGraphicsScene(this)) 
  , view(new QGraphicsView(scene, this))
{
    layout->addWidget(view);
    setLayout(layout);
    setObjectName("output");
}

OutputWidget::~OutputWidget() {}

void OutputWidget::eval_plotscript(QString const & str) 
{
    scene->clear();
    auto res = eval_ps(str);
    switch (res.first) {
        case PARSE_ERROR:
        case EXCEPTION:
            plot_text(res.second.str);
            return;
        case SUCCESS:
            eval_exp(res.second.exp);
            break;
    }
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
    } else if (  exp.isNone()       || exp.isHeadNumber() || exp.isHeadComplex() 
              || exp.isHeadSymbol() || exp.isHeadString()
              ) 
    {
        plot_textexp(exp);
    } else {
        plot_text("ERROR: Unknown Datatype found in OutputWidget::eval_exp");
    }
}

void OutputWidget::plot_text(QString const & str)
{
    scene->addText(str);
}

void OutputWidget::plot_textexp(Expression const & exp)
{
    std::ostringstream os;
    os << exp;
    qDebug() << QString::fromStdString(os.str());
    auto t = scene->addText(QString::fromStdString(os.str()));
    if (exp.pmap.find("position") != exp.pmap.cend()) {
        t->setPos(find_point(exp.pmap.find("position")->second));
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
        plot_text("ERROR: thick must be positive.");
    }
    auto p1 = find_point(exp.m_tail[0]);
    auto p2 = find_point(exp.m_tail[1]);
    scene->addLine(QLineF(p1, p2), QPen(QBrush(Qt::black), thick));
}

void OutputWidget::plot_pointexp(Expression const & exp)
{
    qreal sz = exp.pmap.find("size")->second.head().asNumber();
    auto p = find_point(exp);
    if (sz < 0) {
        plot_text("ERROR: size must be positive.");
    }
    qreal x = p.x() - sz;
    qreal y = p.y() + sz;
    qreal w = sz;
    qreal h = sz;
    scene->addEllipse(x, y, w, h, QPen(Qt::black), QBrush(Qt::black));
}

QPointF OutputWidget::find_point(Expression const & exp)
{
    auto x = exp.m_tail[0].head().asNumber();
    auto y = exp.m_tail[1].head().asNumber();
    return QPointF(x, y);
}
