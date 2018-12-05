#ifndef PLOTSCRIPT_OUTPUT_WIDGET_H
#define PLOTSCRIPT_OUTPUT_WIDGET_H

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QPointF>
#include <QPointer>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>

class Expression;

class OutputWidget : public QWidget {
    Q_OBJECT
public:
    explicit OutputWidget(QWidget * parent = nullptr);
    ~OutputWidget() override = default;

    void eval_plotscript(QString const & str);

    OutputWidget(OutputWidget const &) = delete;
    OutputWidget & operator=(OutputWidget const &) = delete;
    OutputWidget(OutputWidget &&) = delete;
    OutputWidget & operator=(OutputWidget &&) = delete;

protected:
    void resizeEvent(QResizeEvent * e) override;

private:
    QPointer<QVBoxLayout> layout;
    QPointer<QGraphicsScene> scene;
    QPointer<QGraphicsView> view;

    void find_center(QGraphicsItem * i);
    QPointF find_point(Expression const & exp);

    void eval_exp(Expression const & exp);
    void plot_text(QString const & str);
    void plot_pointexp(Expression const & exp);
    void plot_textexp(Expression const & exp);
    void plot_lineexp(Expression const & exp);
    void plot_listexp(Expression const & exp);

    void plot_layout(Expression const & exp);
    void plot_discrete(Expression const & exp);
    void plot_continuous(Expression const & exp);
};

#endif /* PLOTSCRIPT_OUTPUT_WIDGET_H */
