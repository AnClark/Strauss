#include "notationview.h"

NotationView::NotationView(MasterTrack *master) :masterTrack(master)
{
    setMinimumSize(2000,900);
    scene = new QGraphicsScene;
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    // scene->setSceneRect(0,0,10,1000);
    setScene(scene);

    for(int i = 0; i < defaultMeaures; ++i)
    {
        //   AddMeasure(i);

    }
}

NotationPage *NotationView::AddPage(int index)
{
    NotationPage *page = new NotationPage(this);
    auto proxy = scene->addWidget(page);
    proxy->setX(index * 1200);
    qDebug() << scene->sceneRect();
    pages.append(page);

    fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
    return page;
}

void NotationView::AddInstrument(TrackMidi *track)
{
    instruments.push_back(track);
    foreach(auto & page , pages)
    {
        page->addStave();
    }

    if(pages.size() == 0)
    {
        auto page = AddPage(0);
        page->addStave();

    }

}

void NotationView::AddMeasure(int index)
{
    Measure *measure = new Measure;
    measures.append(measure);
    int mes = 1200 / measure->prefferedMeasureWidth;
    measure->width = mes;
    // assignMeasureToPage();

    foreach(auto& page, pages)
    {
        qDebug() << page->unusedMeasures();
        if(page->unusedMeasures() > 0)
        {
            page->assignMeasure(measure);
            return;
        }
    }
}

int NotationView::numInstruments()
{
    return instruments.size();
}

void NotationView::assignMeasureToPage()
{
    for(int i = 0; i < defaultMeaures; ++i)
    {
        AddMeasure(i);
    }
}

void NotationView::wheelEvent(QWheelEvent *event)
{
    if(event->modifiers().testFlag(Qt::ControlModifier))
    {
        const QPointF p0scene = mapToScene(event->pos());

        qreal factor = std::pow(1.1,event->angleDelta().y() /120);
        scale(factor, factor);

        const QPointF p1mouse = mapFromScene(p0scene);
        const QPointF move = p1mouse - event->pos(); // The move
        horizontalScrollBar()->setValue(move.x() + horizontalScrollBar()->value());
        verticalScrollBar()->setValue(move.y() + verticalScrollBar()->value());
    }
    else
    {

        verticalScrollBar()->setValue(verticalScrollBar()->value() - event->angleDelta().y() /120*14);
    }
}
