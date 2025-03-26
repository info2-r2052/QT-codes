#ifndef QLEDLABEL_H
#define QLEDLABEL_H

//Fuente:
//https://forum.qt.io/topic/101648/how-to-create-simply-virtual-led-indicator/6

#include <QLabel>

class QLedLabel : public QLabel
{
    Q_OBJECT
public:
    explicit QLedLabel(QWidget *parent = 0);

    enum State{
        LED_GREEN_ON,
        LED_RED_ON,
        LED_GRAY,
        LED_BLUE_ON,
        LED_RED_GRAYED,
        LED_GREEN_GRAYED,
        LED_BLUE_GRAYED
    };


signals:

public slots:
    void setState(State state);
    void setState(bool state);
    void setColour(qint8 colour);

};

#endif // QLEDLABEL_H
