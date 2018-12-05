#include <QDebug>
#include <QString>
#include <fstream>
#include <sstream>

#include "expression.hpp"
#include "output_widget.hpp"
#include "plotscript_eval.hpp"

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

void OutputWidget::resizeEvent(QResizeEvent * e)
{
    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    QWidget::resizeEvent(e);
}

void OutputWidget::eval_plotscript(QString const & str)
{
    scene->clear();
    Expression e{};
    std::istringstream iss(str.toStdString());
    std::ostringstream oss;
    std::ostringstream ess;
    auto res = eval_from_stream_e(e, iss, oss, ess);
    switch (res) {
    case EXIT_SUCCESS:
        qDebug().noquote() << "\n  " << QString::fromStdString(oss.str());
        eval_exp(e);
        break;
    case EXIT_FAILURE:
    default:
        qDebug().noquote() << "\n  " << QString::fromStdString(ess.str());
        plot_text(QString::fromStdString(ess.str()));
        break;
    }
    scene->setSceneRect(scene->itemsBoundingRect());
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
    } else if (exp.is("discrete-plot")) {
        plot_discrete(exp);
    } else if (exp.is("continuous-plot")) {
        plot_continuous(exp);
    } else if (exp.isList()) {
        plot_listexp(exp);
    } else if (exp.isNone() || exp.isHeadNumber() || exp.isHeadComplex()
        || exp.isHeadSymbol() || exp.isHeadString()) {
        plot_textexp(exp);
    } else {
        plot_text("ERROR: Unknown Datatype found in OutputWidget::eval_exp");
    }
}
