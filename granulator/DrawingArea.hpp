#pragma once

#include <QWidget>
#include <QRect>

class QMouseEvent;

namespace Granulation {
namespace Panel {

class GranulatorInterface;

class DrawingArea : public QWidget {
    Q_OBJECT
public:
    explicit DrawingArea(QWidget *parent = 0);

signals:
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
};

}
}
