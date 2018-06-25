#ifndef IMAGEPROCESS_H
#define IMAGEPROCESS_H

#include <QString>

class ImageProcess
{
protected:
    int encodeImage(QString Qfilename);
    void decodeImage(QString Qfilename);
    bool isBitSet(char ch, int pos);
};

#endif // IMAGEPROCESS_H
