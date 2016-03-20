#include "slidingpuzzleutility.h"
#include <QFile>

std::string SlidingPuzzleUtility::GetTextFromFile(const char* filename)
{
    QFile vertSource(filename);
    vertSource.open(QIODevice::ReadOnly);
    return vertSource.readAll().toStdString();
}
