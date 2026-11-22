
//
// Created by alexei on 25.10.2026.
//

#include "ShapeStorage.h"

#include <QFile>
#include <QTextStream>

void ShapeStorage::add(Shape* shape)
{
    shapes.push_back(shape);
}

int ShapeStorage::getCount() const
{
    return static_cast<int>(shapes.size());
}

Shape* ShapeStorage::getObject(int index) const
{
    return shapes[index];
}

void ShapeStorage::clearSelection()
{
    for (Shape* shape : shapes)
    {
        shape->setSelected(false);
    }
}

ShapeStorage::~ShapeStorage()
{
    for (Shape* shape : shapes)
    {
        delete shape;
    }
}

void ShapeStorage::removeSelected()
{
    size_t i = 0;

    while (i < shapes.size())
    {
        if (shapes[i]->isSelected())
        {
            delete shapes[i];
            shapes.erase(shapes.begin() + i);
        }
        else
        {
            ++i;
        }
    }
}

std::vector<Shape*> ShapeStorage::takeSelected()
{
    std::vector<Shape*> selectedShapes;

    size_t i = 0;

    while (i < shapes.size())
    {
        if (shapes[i]->isSelected())
        {
            selectedShapes.push_back(shapes[i]);
            shapes.erase(shapes.begin() + i);
        }
        else
        {
            ++i;
        }
    }

    return selectedShapes;
}

bool ShapeStorage::saveToFile(
    const QString& fileName
) const
{
    QFile file(fileName);

    if (!file.open(
            QIODevice::WriteOnly |
            QIODevice::Text))
    {
        return false;
    }

    QTextStream out(&file);

    out << shapes.size() << "\n";

    for (Shape* shape : shapes)
    {
        shape->save(out);
    }

    return out.status() == QTextStream::Ok;
}

bool ShapeStorage::loadFromFile(
    const QString& fileName,
    const ShapeFactory& factory,
    const QRect& bounds
)
{
    QFile file(fileName);

    if (!file.open(
            QIODevice::ReadOnly |
            QIODevice::Text))
    {
        return false;
    }

    QTextStream in(&file);

    int objectCount;
    in >> objectCount;

    if (in.status() != QTextStream::Ok ||
        objectCount < 0)
    {
        return false;
    }

    std::vector<Shape*> loadedShapes;

    auto clearLoadedShapes =
        [&loadedShapes]()
        {
            for (Shape* shape : loadedShapes)
            {
                delete shape;
            }

            loadedShapes.clear();
        };

    for (int i = 0; i < objectCount; ++i)
    {
        QString type;
        in >> type;

        if (in.status() != QTextStream::Ok)
        {
            clearLoadedShapes();
            return false;
        }

        Shape* shape =
            factory.create(type);

        if (shape == nullptr)
        {
            clearLoadedShapes();
            return false;
        }

        if (!shape->load(in, factory) ||
            !shape->fitsInBounds(bounds))
        {
            delete shape;
            clearLoadedShapes();
            return false;
        }

        loadedShapes.push_back(shape);
    }

    for (Shape* shape : shapes)
    {
        delete shape;
    }

    shapes.swap(loadedShapes);

    return true;
}
