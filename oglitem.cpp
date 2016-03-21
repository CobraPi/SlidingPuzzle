#include "oglitem.h"
#include <QtQuick/QQuickWindow>
#include "slidingpuzzle2drenderer.h"

OGLItem::OGLItem()
{
    sp2DRenderer = nullptr;
    connect(this, &QQuickItem::windowChanged, this, &OGLItem::handleWindowChanged);
}

void OGLItem::handleWindowChanged(QQuickWindow *win)
{
    if (win) {
        connect(win, &QQuickWindow::beforeSynchronizing, this, &OGLItem::sync, Qt::DirectConnection);
        connect(win, &QQuickWindow::sceneGraphInvalidated, this, &OGLItem::cleanup, Qt::DirectConnection);
        win->setClearBeforeRendering(false);
    }
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
        sp2DRenderer = new SlidingPuzzle2DRenderer();
        connect(window(), &QQuickWindow::beforeRendering, sp2DRenderer, &SlidingPuzzle2DRenderer::paint, Qt::DirectConnection);
    }
    sp2DRenderer->setViewportSize(window()->size() * window()->devicePixelRatio());
    sp2DRenderer->setWindow(window());
}
