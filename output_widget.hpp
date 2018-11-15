#ifndef PLOTSCRIPT_OUTPUT_WIDGET_H
#define PLOTSCRIPT_OUTPUT_WIDGET_H

#include <QPointer>
#include <QString>
#include <QWidget>
#include <QPointF>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

class Expression;

class OutputWidget : public QWidget {
    Q_OBJECT
public:
    OutputWidget(QWidget* parent = nullptr);
    ~OutputWidget();

    void eval_plotscript(QString const & str);
protected:
    virtual void resizeEvent(QResizeEvent*);
private:
    QPointer<QVBoxLayout> layout;
    QPointer<QGraphicsScene> scene;
    QPointer<QGraphicsView> view;

    void eval_exp(Expression const & exp);
    void plot_text(QString const & str);
    void plot_textexp(Expression const & exp);
    void plot_listexp(Expression const & exp);
    void plot_lineexp(Expression const & exp);
    void plot_pointexp(Expression const & exp);
    QPointF find_point(Expression const & exp);
};


#endif /* PLOTSCRIPT_OUTPUT_WIDGET_H */
