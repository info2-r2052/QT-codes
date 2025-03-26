#include "qledlabel.h"
#include <QDebug>

static const int SIZE = 20;
static const QString greenSS = QString("color: white;border-radius: %1;background-color: qlineargradient(spread:pad, x1:0.145, y1:0.16, x2:1, y2:1, stop:0 rgba(20, 252, 7, 255), stop:1 rgba(25, 134, 5, 255));").arg(SIZE/2);
static const QString redSS = QString("color: white;border-radius: %1;background-color: qlineargradient(spread:pad, x1:0.145, y1:0.16, x2:0.92, y2:0.988636, stop:0 rgba(255, 12, 12, 255), stop:0.869347 rgba(103, 0, 0, 255));").arg(SIZE/2);
static const QString orangeSS = QString("color: white;border-radius: %1;background-color: qlineargradient(spread:pad, x1:0.232, y1:0.272, x2:0.98, y2:0.959773, stop:0 rgba(255, 113, 4, 255), stop:1 rgba(91, 41, 7, 255))").arg(SIZE/2);
static const QString blueSS = QString("color: white;border-radius: %1;background-color: qlineargradient(spread:pad, x1:0.04, y1:0.0565909, x2:0.799, y2:0.795, stop:0 rgba(203, 220, 255, 255), stop:0.41206 rgba(0, 115, 255, 255), stop:1 rgba(0, 49, 109, 255));").arg(SIZE/2);
static const QString graySS = QString("color: white;border-radius: %1;background-color: qlineargradient(spread:pad, x1:0.232, y1:0.272, x2:0.98, y2:0.959773, stop:0 rgba(128, 128, 128, 255), stop:1 rgba(100, 100, 100, 255))").arg(SIZE/2);
static const QString greenGrayedSS = QString("color: white;border-radius: %1;background-color: qlineargradient(spread:pad, x1:0.145, y1:0.16, x2:1, y2:1, stop:0 rgba(125, 200, 125, 255), stop:1 rgba(100, 175, 100, 255));").arg(SIZE/2);
static const QString redGrayedSS = QString("color: white;border-radius: %1;background-color: qlineargradient(spread:pad, x1:0.145, y1:0.16, x2:1, y2:1, stop:0 rgba(200, 125, 125, 255), stop:1 rgba(175, 100, 100, 255));").arg(SIZE/2);
static const QString blueGrayedSS = QString("color: white;border-radius: %1;background-color: qlineargradient(spread:pad, x1:0.145, y1:0.16, x2:1, y2:1, stop:0 rgba(125, 125, 200, 255), stop:1 rgba(100, 100, 175, 255));").arg(SIZE/2);
QLedLabel::QLedLabel(QWidget *parent) :
    QLabel(parent)
{
    //Set to ok by default
    //setState(StateOkBlue);
    setState(LED_GRAY);
    setFixedSize(SIZE, SIZE);
}

void QLedLabel::setState(State state)
{
    qDebug() << "setState" << state;
    switch(state){
    case LED_GREEN_ON:
        setStyleSheet(greenSS);
        break;
    case LED_GRAY:
        setStyleSheet(graySS);
        break;
    case LED_RED_ON:
        setStyleSheet(redSS);
        break;
    case LED_BLUE_ON:
    default:
        setStyleSheet(blueSS);
        break;
    }
}


void QLedLabel::setState(bool state)
{
    //setState(state ? StateOk : StateError);
    setState(state ? LED_RED_ON : LED_GREEN_ON);


}


void QLedLabel::setColour(qint8 colour){

    qDebug() << "setState" << colour;
    switch(colour){
    case LED_GREEN_ON:
        setStyleSheet(greenSS);
        break;
    case LED_GRAY:
        setStyleSheet(graySS);
        break;
    case LED_RED_ON:
        setStyleSheet(redSS);
        break;
    case LED_RED_GRAYED:
        setStyleSheet(redGrayedSS);
        break;
    case LED_GREEN_GRAYED:
        setStyleSheet(greenGrayedSS);
        break;
    case LED_BLUE_GRAYED:
        setStyleSheet(blueGrayedSS);
        break;
    case LED_BLUE_ON:
    default:
        setStyleSheet(blueSS);
        break;
    }
}
