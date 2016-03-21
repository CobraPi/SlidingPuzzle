#ifndef OGLITEM_H
#define OGLITEM_H

#include <QQuickItem>
#include <QVariant>
class SlidingPuzzle2DRenderer;

class OGLItem : public QQuickItem
{
    Q_OBJECT
public:
    OGLItem();

    void endGame();

signals:
    void gameEnd();

public slots:
    void sync();
    void cleanup();
    void handleMouseClicked(int x, int y);
    void startGame(int size);

private slots:
    void handleWindowChanged(QQuickWindow *win);

private:
    SlidingPuzzle2DRenderer* sp2DRenderer;
};

#endif // OGLITEM_H
