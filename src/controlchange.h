#ifndef CONTROLCHANGEVIEW_H
#define CONTROLCHANGEVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWidget>
#include <QPainter>
#include <QStackedLayout>
#include <QMouseEvent>
#include <QDebug>
class TrackMidi;
class ControlChangeContainer;
class ControlChangeOverlay;

class ControlChange : public QFrame{
    Q_OBJECT

public:
    ControlChange(ControlChangeContainer *container);
    void switchOverlay(int index, TrackMidi *track);
    void addOverlay(int index);
    int currentIndex = 0;
    QGraphicsView *backgroundView;
    TrackMidi* midiTrack(){ return _midiTrack;}
    bool eventFilter(QObject *target, QEvent *event);
protected:
    void showEvent(QShowEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    TrackMidi *_midiTrack;
    QStackedLayout *stackedLayout;
    ControlChangeContainer *_container;
    ControlChangeOverlay *_overlay;
    std::map<int,std::unique_ptr<ControlChangeOverlay>> _overlays;
};

#endif // CONTROLCHANGEVIEW_H
