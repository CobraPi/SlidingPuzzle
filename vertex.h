#ifndef VERTEX_H
#define VERTEX_H

#include <QVector2D>
#include <QVector3D>
#include <QVector4D>

class Vertex
{
public:
    Vertex();
    Vertex(QVector3D pos, QVector4D clr, QVector2D uv) : position(pos), color(clr), uv(uv) {}

private:
    QVector3D position;
    QVector4D color;
    QVector2D uv;
};

#endif // VERTEX_H
