#include "expression.hpp"
#include "output_widget.hpp"
#include <QDebug>
#include <QtMath>

static qreal const N = 20;
static qreal const A = 3;
static qreal const B = 3;
static qreal const C = 2;
static qreal const D = 2;
static qreal const P = 0.5;
static qreal const thick = 0;
static std::size_t const cont_M   = 50;
static std::size_t const cont_IT  = 10;
static std::size_t const cont_DEG = 175;

void OutputWidget::move_item(QGraphicsItem * i, QPointF p)
{
    i->setPos(i->pos() + p);
}

void OutputWidget::find_center(QGraphicsItem * i)
{
    auto c = i->boundingRect().center();
    i->setTransformOriginPoint(c);
    i->setPos(-(i->mapToScene(c)));
}

QPointF OutputWidget::find_point(Expression const & exp)
{
    auto x = exp.m_tail[0].head().asNumber();
    auto y = exp.m_tail[1].head().asNumber();
    return { x, y };
}

void OutputWidget::plot_text(QString const & str, QPointF pos, qreal rot, qreal scale)
{
    auto font = QFont("Monospace");
    font.setStyleHint(QFont::TypeWriter);
    font.setPointSize(1);
    auto t = scene->addText(str, font);
    find_center(t);
    move_item(t, pos);
    t->setRotation(rot);
    t->setScale(scale);
}

void OutputWidget::plot_point(QPointF p, qreal sz)
{
    auto i = scene->addEllipse(
        (-sz / 2), (-sz / 2), sz, sz, QPen(Qt::NoPen), QBrush(Qt::black));
    find_center(i);
    move_item(i, p);
}

void OutputWidget::plot_line(QPointF p1, QPointF p2, qreal thick)
{
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
    plot_point(p, sz);
}

void OutputWidget::plot_lineexp(Expression const & exp)
{
    qreal thick = exp.pmap.find("thickness")->second.head().asNumber();
    if (thick < 0) {
        plot_text("ERROR: thickness must be positive.");
    }
    auto p1 = find_point(exp.m_tail[0]);
    auto p2 = find_point(exp.m_tail[1]);
    plot_line(p1, p2, thick);
}

void OutputWidget::plot_textexp(Expression const & exp)
{
    std::ostringstream os;
    os << exp;
    auto s = QString::fromStdString(os.str());
    QPointF pos {0, 0};
    qreal rot = 0;
    qreal scale = 1;
    
    if (exp.is("text")) {
        auto start = s.indexOf('"') + 1;
        auto off = s.lastIndexOf('"') - start;
        s = s.mid(start, off);
    }
    if (exp.pmap.find("position") != exp.pmap.cend()) {
        pos = find_point(exp.pmap.find("position")->second);
    }
    if (exp.pmap.find("text-rotation") != exp.pmap.cend()) {
        auto e = exp.pmap.find("text-rotation")->second;
        if (e.isHeadNumber()) {
            rot = qRadiansToDegrees(e.head().asNumber());
        }
    }
    if (exp.pmap.find("text-scale") != exp.pmap.cend()) {
        auto e = exp.pmap.find("text-scale")->second;
        if (e.isHeadNumber() && (e.head().asNumber() >= 0)) {
            scale = e.head().asNumber();
        }
    }
    plot_text(s, pos, rot, scale);
}

void OutputWidget::plot_listexp(Expression const & exp)
{
    for (auto it = exp.tailConstBegin(); it != exp.tailConstEnd(); ++it) {
        eval_exp(*it);
    }
}

void OutputWidget::plot_discrete(Expression const & exp)
{
    using namespace std::placeholders;
    auto opts_it = std::next(exp.tailConstBegin());
    auto opts = (opts_it == exp.tailConstEnd()) ? Expression{} : *opts_it;
    auto & data = *exp.tailConstBegin();
    auto begin = data.tailConstBegin();
    auto end   = data.tailConstEnd();
    std::vector<QPointF> d;
    d.reserve(exp.arg_length());
    std::transform(begin, end, std::back_inserter(d), 
        std::bind(std::mem_fn(&OutputWidget::find_point), this, _1));
    qreal xmin = std::min_element(d.begin(), d.end(), [] (QPointF lhs, QPointF rhs) 
            { return (lhs.rx() < rhs.rx()); })->rx();
    qreal xmax = std::max_element(d.begin(), d.end(), [] (QPointF lhs, QPointF rhs) 
            { return (lhs.rx() < rhs.rx()); })->rx();
    qreal ymin = std::min_element(d.begin(), d.end(), [] (QPointF lhs, QPointF rhs) 
            { return (lhs.ry() < rhs.ry()); })->ry();
    qreal ymax = std::max_element(d.begin(), d.end(), [] (QPointF lhs, QPointF rhs) 
            { return (lhs.ry() < rhs.ry()); })->ry(); 
    qreal scalex = N / (xmax - xmin);
    qreal scaley = N / (ymax - ymin);
    qreal xmiddle = ((xmax - xmin) / 2 + xmin) * scalex;
    qreal ymiddle = ((ymax - ymin) / 2 + ymin) * scaley;
    qDebug() << ymiddle;
    std::for_each(d.begin(), d.end(), [&] (QPointF dp) {
        QPointF p((xmiddle + dp.rx() * scalex), (ymiddle - dp.ry() * scaley));
        plot_point(p, P); 
        plot_line( p, QPointF(p.rx(), ymiddle), thick); 
    });
    plot_layout(opts, xmin, xmax, ymin, ymax);
}

void OutputWidget::plot_continuous(Expression const & exp)
{
    qDebug() << &exp;
    //using namespace std::placeholders;
    //auto & func    = *exp.tailConstBegin();
    //auto bounds_it = std::next(exp.tailConstBegin());
    //auto & bounds  = *bounds_it;
    //auto opts_it   = std::next(bounds_it);
    //auto opts      = (opts_it == exp.tailConstEnd()) ? Expression{} : *opts_it;
    //
    //qreal xmin = *bounds.tailConstBegin(); 
    //qreal xmax = *std::next(bounds.tailConstBegin()); 

    //std::vector<qreal> in;
    //std::vector<qreal> args;
    //in.reserve(cont_M);

    //for ()

    //eval_fn(func, args);
    //
    //plot_layout(opts, xmin, xmax, ymin, ymax);
}

void OutputWidget::plot_layout(Expression const & exp, qreal xmin, qreal xmax, qreal ymin, qreal ymax)
{
    auto f = [] (Expression const & e, std::string s) {
        return (   e.isList() 
               && (e.arg_length() == 2)
               && (e.tailConstBegin()->head().asSymbol() == s));
    };
    auto begin = exp.tailConstBegin();
    auto end   = exp.tailConstEnd();
    auto title_it = std::find_if(begin, end, [&f] (Expression const & e) { return f(e, "title"); });
    auto ab_it    = std::find_if(begin, end, [&f] (Expression const & e) { return f(e, "abscissa-label"); });
    auto ord_it   = std::find_if(begin, end, [&f] (Expression const & e) { return f(e, "ordinate-label"); });  
    auto scale_it = std::find_if(begin, end, [&f] (Expression const & e) { return f(e, "text-scale"); });  

    QString title = QString::fromStdString((title_it == end) ? "" 
                  : std::next(title_it->tailConstBegin())->head().asSymbol());
    QString ab    = QString::fromStdString((   ab_it == end) ? "" 
                  : std::next(   ab_it->tailConstBegin())->head().asSymbol());
    QString ord   = QString::fromStdString((  ord_it == end) ? "" 
                  : std::next(  ord_it->tailConstBegin())->head().asSymbol());
    qreal scale   = (scale_it == end) ?  1 : std::next(scale_it->tailConstBegin())->head().asNumber();

    qreal scalex = N / (xmax - xmin);
    qreal scaley = N / (ymax - ymin);
    qreal xmiddle = ((xmax - xmin) / 2 + xmin) * scalex;
    qreal ymiddle = ((ymax - ymin) / 2 + ymin) * scaley;

    plot_text(title,                 QPointF((0       ),  -( N/2 + A)),   0, scale);
    plot_text(ab,                    QPointF((0       ),  -(-N/2 - A)),   0, scale);
    plot_text(ord,                   QPointF((-N/2 - B),  -(0       )), -90, scale);
    plot_text(QString::number(xmin), QPointF((-N/2    ),  -(-N/2 - C)),   0, scale);
    plot_text(QString::number(xmax), QPointF(( N/2    ),  -(-N/2 - C)),   0, scale);
    plot_text(QString::number(ymin), QPointF((-N/2 - D),  -(-N/2    )),   0, scale);
    plot_text(QString::number(ymax), QPointF((-N/2 - D),  -( N/2    )),   0, scale);
    plot_line(QPointF(-N/2,  N/2), QPointF( N/2,  N/2), thick); // Bottom
    plot_line(QPointF(-N/2, -N/2), QPointF( N/2, -N/2), thick); // Top
    plot_line(QPointF(-N/2, -N/2), QPointF(-N/2,  N/2), thick); // Left
    plot_line(QPointF( N/2, -N/2), QPointF( N/2,  N/2), thick); // Right
    plot_line(QPointF(-N/2,     ymiddle), QPointF( N/2,     ymiddle), thick); // Ab Axis
    plot_line(QPointF( xmiddle, -N/2),    QPointF( xmiddle, N/2),     thick); // Ord Axis
}

