#include "slidingpuzzle2drenderer.h"
#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLShaderProgram>
#include <QFile>
#include <QVector>
#include <QVector3D>
#include <QOpenGLFunctions_4_3_Core>
#include <QtGui/qopengl.h>

#include "slidingpuzzleutility.h"
#include "vertex.h"

SlidingPuzzle2DRenderer::SlidingPuzzle2DRenderer(QObject *parent) : QObject(parent)
{
    initializeOpenGLFunctions();

    prog = new QOpenGLShaderProgram();
    vertSource = SlidingPuzzleUtility::GetTextFromFile(":/sliding2d.vert");
    fragSource = SlidingPuzzleUtility::GetTextFromFile(":/sliding2d.frag");
    prog->addShaderFromSourceCode(QOpenGLShader::Vertex, vertSource.c_str());
    prog->addShaderFromSourceCode(QOpenGLShader::Fragment, fragSource.c_str());

    prog->link();

    texture = new QOpenGLTexture(QImage(QString(":/test_cat.png")).mirrored());

    instancePosAttr = prog->attributeLocation("instancePos");
    vertexPosAttr = prog->attributeLocation("position");
    vertexClrAttr = prog->attributeLocation("color");
    vertexUvAttr = prog->attributeLocation("uvCoords");
    modelMatrixAttr = prog->uniformLocation("modelMatrix");
    viewProjMatrixAttr = prog->uniformLocation("viewProjMatrix");

//    qDebug() << "Instance Pos Attr: " << instancePosAttr;
//    qDebug() << "Vertex Pos Attr: " << vertexPosAttr;
//    qDebug() << "Vertex Clr Attr: " << vertexClrAttr;
//    qDebug() << "Vertex UV Attr: " << vertexUvAttr;
//    qDebug() << "Model Matrix Attr: " << modelMatrixAttr;
//    qDebug() << "View Proj Attr: " << viewProjMatrixAttr;

    funcs = nullptr;
//    funcs = (QOpenGLFunctions_4_3_Core*)QOpenGLContext::currentContext()->versionFunctions();
//    if (funcs == nullptr)
//    {
//        qDebug() << "Funcs do not exist.";
//        return;
//    }

    vertices.append(Vertex(QVector3D(-.5, -.5, 0),
                           QVector4D(0, 1.0, 0, 1.0),
                           QVector2D(0, 0)));

    vertices.append(Vertex(QVector3D(.5, -.5, 0),
                           QVector4D(1.0, 0, 0, 1.0),
                           QVector2D(1, 0)));

    vertices.append(Vertex(QVector3D(.5, .5, 0),
                           QVector4D(1.0, 0, 1.0, 1.0),
                           QVector2D(1, 1)));

    vertices.append(Vertex(QVector3D(-.5, .5, 0),
                           QVector4D(0, 0, 1.0, 1.0),
                           QVector2D(0, 1)));

    indicies.append(0);
    indicies.append(1);
    indicies.append(2);

    indicies.append(0);
    indicies.append(2);
    indicies.append(3);


}

void SlidingPuzzle2DRenderer::setViewportSize(const QSize &size)
{
    viewportSize = size;
    projectionMat.setToIdentity();
    projectionMat.perspective(45, (float) size.width()/size.height(), .01, 10);
}

void SlidingPuzzle2DRenderer::setWindow(QQuickWindow *window)
{
    qDebug() << "Window Set";
    this->window = window;
    funcs = (QOpenGLFunctions_4_3_Core*)QOpenGLContext::currentContext()->versionFunctions();

    prog->bind();
    vao.create();
    vao.bind();
    prog->enableAttributeArray(instancePosAttr);
    funcs->glVertexAttribDivisor(instancePosAttr, 1);
    prog->enableAttributeArray(vertexPosAttr);
    prog->enableAttributeArray(vertexClrAttr);
    prog->enableAttributeArray(vertexUvAttr);

    vertexBuffer = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vertexBuffer.create();
    vertexBuffer.bind();
    vertexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vertexBuffer.allocate(vertices.constData(), sizeof(Vertex) * vertices.size());

    indexBuffer = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    indexBuffer.create();
    indexBuffer.bind();
    indexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    indexBuffer.allocate(indicies.constData(), sizeof(int)*indicies.size());

    prog->setAttributeBuffer(vertexPosAttr, GL_FLOAT, 0, 3, sizeof(Vertex));
    prog->setAttributeBuffer(vertexClrAttr, GL_FLOAT, sizeof(QVector3D), 4, sizeof(Vertex));
    prog->setAttributeBuffer(vertexUvAttr, GL_FLOAT, sizeof(QVector3D) + sizeof(QVector4D), 2, sizeof(Vertex));

    positionBuffer = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    positionBuffer.create();
    positionBuffer.bind();

    puzzleSize = 2;
    float fsize = (float)puzzleSize;
    for (int i=0; i<puzzleSize; i++)
    {
        for (int j=0; j<puzzleSize; j++)
        {
            auto pos = QVector3D(i+1, j+1, 0);
            positions.append(pos);
//            qDebug() << "Position: " << pos;
        }
    }
    positionBuffer.allocate(positions.constData(), sizeof(QVector3D) * positions.size());
    prog->setAttributeBuffer(instancePosAttr, GL_FLOAT, 0, 3);

    cameraMat.setToIdentity();
    cameraMat.translate(-1-(1/fsize), -1-(1/fsize), -3);

    modelMat.scale(2/fsize);
}

SlidingPuzzle2DRenderer::~SlidingPuzzle2DRenderer()
{
    delete prog;
}

void SlidingPuzzle2DRenderer::paint()
{
    if (funcs == nullptr)
    {
        qDebug() << "Funcs do not exist. Will not draw.";
        return;
    }

    prog->setUniformValue(viewProjMatrixAttr, projectionMat * cameraMat);
    prog->setUniformValue(modelMatrixAttr, modelMat);

    prog->setUniformValue("size", puzzleSize);
    prog->setUniformValue("texture", 0);
    texture->bind();

    glViewport(0, 0, viewportSize.width(), viewportSize.height());

    glDisable(GL_DEPTH_TEST);

    glClearColor(.5, .5, .5, 1);
//    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);

    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    funcs->glDrawElementsInstanced(GL_TRIANGLES,
                                   indicies.size(),
                                   GL_UNSIGNED_INT,
                                   0,
                                   positions.size());

    // Clean up
    prog->disableAttributeArray(instancePosAttr);
    prog->disableAttributeArray(vertexPosAttr);
    prog->disableAttributeArray(vertexClrAttr);
    prog->disableAttributeArray(vertexUvAttr);
    prog->release();
    positionBuffer.release();
    vertexBuffer.release();
    indexBuffer.release();
    vao.release();

    window->resetOpenGLState();
}
