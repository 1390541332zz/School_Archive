#ifndef PLOTSCRIPT_QTTEST_HELPERS_H
#define PLOTSCRIPT_QTTEST_HELPERS_H

struct NotebookApp_expose {
    NotebookApp * na;
    InputWidget * iw;
    OutputWidget * ow;

private:
    NotebookApp app{};

public:
    NotebookApp_expose()
    {
        na = &app;
        iw = na->findChild<InputWidget *>("input");
        ow = na->findChild<OutputWidget *>("output");
    }
    ~NotebookApp_expose() = default;
};

/* 
findLines - find lines in a scene contained within a bounding box 
            with a small margin
 */
int findLines(QGraphicsScene * scene, QRectF bbox, qreal margin)
{

    QPainterPath selectPath;

    QMarginsF margins(margin, margin, margin, margin);
    selectPath.addRect(bbox.marginsAdded(margins));
    scene->setSelectionArea(selectPath, Qt::ContainsItemShape);

    int numlines(0);
    foreach (auto item, scene->selectedItems()) {
        if (item->type() == QGraphicsLineItem::Type) {
            numlines += 1;
        }
    }

    return numlines;
}

/* 
findPoints - find points in a scene contained within a specified rectangle
 */
int findPoints(QGraphicsScene * scene, QPointF center, qreal radius)
{

    QPainterPath selectPath;
    selectPath.addRect(QRectF(center.x() - radius, center.y() - radius, 2 * radius, 2 * radius));
    scene->setSelectionArea(selectPath, Qt::ContainsItemShape);

    int numpoints(0);
    foreach (auto item, scene->selectedItems()) {
        if (item->type() == QGraphicsEllipseItem::Type) {
            numpoints += 1;
        }
    }

    return numpoints;
}

/* 
findText - find text in a scene centered at a specified point with a given 
           rotation and string contents  
 */
int findText(QGraphicsScene * scene, QPointF center, qreal rotation, QString contents)
{

    int numtext(0);
    foreach (auto item, scene->items(center)) {
        if (item->type() == QGraphicsTextItem::Type) {
            QGraphicsTextItem * text = static_cast<QGraphicsTextItem *>(item);
            if ((text->toPlainText() == contents) && (text->rotation() == rotation) && (text->pos() + text->boundingRect().center() == center)) {
                numtext += 1;
            }
        }
    }

    return numtext;
}

/* 
intersectsLine - find lines in a scene that intersect a specified rectangle
 */
int intersectsLine(QGraphicsScene * scene, QPointF center, qreal radius)
{

    QPainterPath selectPath;
    selectPath.addRect(QRectF(center.x() - radius, center.y() - radius, 2 * radius, 2 * radius));
    scene->setSelectionArea(selectPath, Qt::IntersectsItemShape);

    int numlines(0);
    foreach (auto item, scene->selectedItems()) {
        if (item->type() == QGraphicsLineItem::Type) {
            numlines += 1;
        }
    }

    return numlines;
}

#endif /* PLOTSCRIPT_QTTEST_HELPERS_H */
