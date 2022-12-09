#ifndef CUSTOM_EVENTS_H
#define CUSTOM_EVENTS_H
#include <QEvent>
#include <QColor>
#pragma once

class colorChanged : public QEvent
{
public:
    colorChanged(QColor u_color);
    const static int type;
    QColor color;
};

#endif // CUSTOM_EVENTS_H
