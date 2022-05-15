#include "configreader.h"
#include <QFile>
#include <QDomElement>
#include <QDebug>
void ConfigReader::readConfig(QPoint* &pos1, int &len1, QPoint* &pos2, int &len2,
                              QPoint* &groundPath, int &len3, QPoint* &aerialPath, int &len4,
                              int& beginX, int& beginY, int& endX){
    QFile file(":/config.xml");
    if (!file.open(QFile::ReadOnly))
        return;

    QDomDocument doc;
    if (!doc.setContent(&file)){
        file.close();
        return;
    }
    file.close();

    QDomElement root = doc.documentElement();
    QDomNode node = root.firstChild();
    while (!node.isNull()){
        if (node.isElement()) {
            QDomElement ele = node.toElement(); //转换为元素
            if(ele.attribute("id")=="1"){
                QDomNodeList list = node.childNodes();
                len1 = list.count();
                pos1=new QPoint[len1];
                //遍历子元素
                for (int i = 0; i < len1; i++) {
                    QDomNode childnode = list.at(i);
                    QDomNodeList childnodeList = childnode.childNodes();
                    pos1[i].setX(childnodeList.at(0).toElement().text().toInt());
                    pos1[i].setY(childnodeList.at(1).toElement().text().toInt());
                }
            }
            else if(ele.attribute("id")=="2"){
                QDomNodeList list = node.childNodes();
                len2 = list.count();
                pos2=new QPoint[len2];
                //遍历子元素
                for (int i = 0; i < len2; i++) {
                    QDomNode childnode = list.at(i);
                    QDomNodeList childnodeList = childnode.childNodes();
                    pos2[i].setX(childnodeList.at(0).toElement().text().toInt());
                    pos2[i].setY(childnodeList.at(1).toElement().text().toInt());
                }
            }
            else if(ele.attribute("id")=="ground"){
                QDomNodeList list = node.childNodes();
                len3 = list.count();
                groundPath=new QPoint[len3];
                //遍历子元素
                for (int i = 0; i < len3; i++) {
                    QDomNode childnode = list.at(i);
                    QDomNodeList childnodeList = childnode.childNodes();
                    groundPath[i].setX(childnodeList.at(0).toElement().text().toInt());
                    groundPath[i].setY(childnodeList.at(1).toElement().text().toInt());
                }
            }
            else if(ele.attribute("id")=="aerial"){
                QDomNodeList list = node.childNodes();
                len4 = list.count();
                aerialPath=new QPoint[len4];
                //遍历子元素
                for (int i = 0; i < len4; i++) {
                    QDomNode childnode = list.at(i);
                    QDomNodeList childnodeList = childnode.childNodes();
                    aerialPath[i].setX(childnodeList.at(0).toElement().text().toInt());
                    aerialPath[i].setY(childnodeList.at(1).toElement().text().toInt());
                }
            }
            else if(ele.tagName()=="BEGIN"){
                QDomNodeList list = node.childNodes();
                beginX = list.at(0).toElement().text().toInt();
                beginY = list.at(1).toElement().text().toInt();
            }
            else{
                endX = node.firstChildElement().text().toInt();
            }
        }
        node = node.nextSibling(); //下一个兄弟节点,nextSiblingElement()是下一个兄弟元素，都差不多
    }

}

