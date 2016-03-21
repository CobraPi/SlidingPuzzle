#include "oglitem.h"
#include <QtQuick/QQuickWindow>
#include "slidingpuzzle2drenderer.h"

OGLItem::OGLItem()
{
    sp2DRenderer = nullptr;
    setFlag(QQuickItem::ItemHasContents, true);
    inputEnabled = false;
    connect(this, &QQuickItem::windowChanged, this, &OGLItem::handleWindowChanged);
}

void OGLItem::endGame()
{
    inputEnabled = false;
    emit gameEnd();
}

void OGLItem::handleWindowChanged(QQuickWindow *win)
{
    if (win) {
        connect(win, &QQuickWindow::beforeSynchronizing, this, &OGLItem::sync, Qt::DirectConnection);
        connect(win, &QQuickWindow::sceneGraphInvalidated, this, &OGLItem::cleanup, Qt::DirectConnection);
        win->setClearBeforeRendering(false);
    }
}

void OGLItem::handleMouseClicked(int x, int y)
{
    if (inputEnabled)
    {
    //    qDebug() << "Mouse Clicked: " << x << ", " << y;
        sp2DRenderer->handleMouseHit(x, y);
    //    qDebug() << "Hit: " << hit;
    }
}

void OGLItem::startGame(int size)
{
    sp2DRenderer->resetPuzzle(size);
    window()->update();
}

void OGLItem::enableInput()
{
    inputEnabled = true;
}

void OGLItem::cleanup()
{
    if (sp2DRenderer) {
        delete sp2DRenderer;
        sp2DRenderer = nullptr;
    }
}

void OGLItem::sync()
{
    if (!sp2DRenderer) {
        sp2DRenderer = new SlidingPuzzle2DRenderer(this);
        connect(window(), &QQuickWindow::beforeRendering, sp2DRenderer, &SlidingPuzzle2DRenderer::paint, Qt::DirectConnection);
    }
    sp2DRenderer->setViewportSize(window()->size() * window()->devicePixelRatio());
    sp2DRenderer->setWindow(window());
}
