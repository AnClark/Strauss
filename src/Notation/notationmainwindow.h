#ifndef NOTATIONMAINWINDOW_H
#define NOTATIONMAINWINDOW_H

#include <QObject>
#include <QWidget>
#include <src/mastertrack.h>
#include <src/trackmidi.h>
#include <src/notation/notationview.h>
#include <QVBoxLayout>
class NotationMainWindow : public QWidget
{
    Q_OBJECT
public:
    NotationMainWindow(MasterTrack * master);
    void addInstrument(TrackMidi *track);
    void addMeasure();
private:
    NotationView * notationView;
    QVBoxLayout *mainVLayout;
    MasterTrack * masterTrack;
};

#endif // NOTATIONMAINWINDOW_H
