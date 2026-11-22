//
// Created by alexei on 25.10.2026.
//

#ifndef OOP6_SHAPESTORAGE_H
#define OOP6_SHAPESTORAGE_H
#include <vector>
#include "Shape.h"

class ShapeStorage {
private:
    std::vector<Shape *> shapes;

public:
    void add(Shape *shape);

    int getCount() const;
    Shape *getObject(int index) const;

    void clearSelection();
    void removeSelected();
    std::vector<Shape*> takeSelected();
    bool saveToFile(const QString& fileName) const;
    bool loadFromFile(
        const QString& fileName,
        const ShapeFactory& factory,
        const QRect& bounds
    );
    ~ShapeStorage();
};


#endif //OOP6_SHAPESTORAGE_H
