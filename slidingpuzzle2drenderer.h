#ifndef SLIDINGPUZZLE2DRENDERER_H
#define SLIDINGPUZZLE2DRENDERER_H

#include <QObject>
#include <QQuickWindow>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QtGui/QOpenGLFunctions>
#include <QOpenGLFunctions_4_3_Core>
#include <QOpenGLTexture>
#include <QMatrix>
#include <QVector3D>
#include <QVector>
#include <string>

#include "vertex.h"

class OGLItem;

class SlidingPuzzle2DRenderer : public QObject, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit SlidingPuzzle2DRenderer(OGLItem *parent = 0);

    void setViewportSize(const QSize &size);
    void setWindow(QQuickWindow *window);
    int getClosestCell(int x, int y);
    void resetPuzzle(int size);

    ~SlidingPuzzle2DRenderer();
public slots:
    void paint();

private:
    OGLItem* oglItem;

    QSize viewportSize;
    QOpenGLShaderProgram *prog;
    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer vertexBuffer;
    QOpenGLBuffer indexBuffer;
    QOpenGLBuffer positionBuffer;

    QQuickWindow *window;
    QMatrix4x4 viewProjMatrix;
    QOpenGLFunctions_4_3_Core* funcs;
    QOpenGLTexture* texture;

    QMatrix4x4 projectionMat;
    QMatrix4x4 cameraMat;
    QMatrix4x4 modelMat;
    QVector<Vertex> vertices;
    QVector<int> indicies;
    QVector<QVector3D> positions;

    std::string vertSource;
    std::string fragSource;

    int hiddenInstance;
    int hiddenPosition;
    int puzzleSize;

    int sizeAttr;
    int hiddenInstanceAttr;
    int modelMatrixAttr;
    int viewProjMatrixAttr;
    int instancePosAttr;
    int vertexPosAttr;
    int vertexClrAttr;
    int vertexUvAttr;
};

#endif // SLIDINGPUZZLE2DRENDERER_H
