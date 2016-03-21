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

class SlidingPuzzle2DRenderer : public QObject, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit SlidingPuzzle2DRenderer(QObject *parent = 0);

    void setViewportSize(const QSize &size);
    void setWindow(QQuickWindow *window);

    ~SlidingPuzzle2DRenderer();
public slots:
    void paint();

private:
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

    int puzzleSize;

    int sizeAttr;
    int modelMatrixAttr;
    int viewProjMatrixAttr;
    int instancePosAttr;
    int vertexPosAttr;
    int vertexClrAttr;
    int vertexUvAttr;
};

#endif // SLIDINGPUZZLE2DRENDERER_H
