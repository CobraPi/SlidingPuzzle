#ifndef OGLITEM_H
#define OGLITEM_H

#include <QQuickItem>
class SlidingPuzzle2DRenderer;

class OGLItem : public QQuickItem
{
    Q_OBJECT
public:
    OGLItem();

signals:

public slots:
    void sync();
    void cleanup();

private slots:
    void handleWindowChanged(QQuickWindow *win);

private:
    SlidingPuzzle2DRenderer* sp2DRenderer;
};

#endif // OGLITEM_H
