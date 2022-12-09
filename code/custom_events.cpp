#include "custom_events.h"

const int colorChanged::type = QEvent::registerEventType();

colorChanged::colorChanged(QColor u_color):QEvent((Type)(type))
{
    color = u_color;
}
