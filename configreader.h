#ifndef CONFIGREADER_H
#define CONFIGREADER_H
#include <QPoint>

class ConfigReader
{
public:
    ConfigReader(){};
    static void readConfig(QPoint* &pos1, int &len1, QPoint* &pos2, int &len2,
                           QPoint* &groundPath, int &len3, QPoint* &aerialPath, int &len4,
                           int& beginX, int& beginY, int& endX);
};

#endif // CONFIGREADER_H
