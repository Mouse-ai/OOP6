#include "Group.h"

Group::Group()
    : Shape(0, 0)
{
}

Group::~Group()
{
    for (Shape* shape : children)
    {
        delete shape;
    }
}

void Group::add(Shape* shape)
{
    if (shape != nullptr)
    {
        shape->setSelected(false);
        children.push_back(shape);
    }
}
QRect Group::boundingRect() const
{
    if (children.empty())
    {
        return QRect();
    }

    QRect result = children[0]->boundingRect();

    for (int i = 1; i < children.size(); ++i)
    {
        result = result.united(children[i]->boundingRect());
    }

    return result;
}
void Group::draw(QPainter& painter) const
{
    for (Shape* shape : children)
    {
        shape->draw(painter);
    }

    if (selected)
    {
        painter.save();

        QPen pen(Qt::red);
        pen.setWidth(2);
        pen.setStyle(Qt::DashLine);

        painter.setPen(pen);
        painter.drawRect(boundingRect());

        painter.restore();
    }
}
bool Group::contains(int pointX, int pointY) const
{
    return boundingRect().contains(pointX, pointY);
}
void Group::move(int dx, int dy, const QRect& bounds)
{
    QRect newRect = boundingRect().translated(dx, dy);

    if (!bounds.contains(newRect))
    {
        return;
    }

    for (Shape* shape : children)
    {
        shape->move(dx, dy, bounds);
    }
}
bool Group::canResize(int delta) const
{
    return false;
}

void Group::changeSize(int delta)
{
}