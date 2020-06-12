#ifndef CONTROLS_H
#define CONTROLS_H

#include<QWidget>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QComboBox>
#include<QPushButton>
#include<QLabel>
#include<QLineEdit>
#include <QObject>

#include "DS/hld.h"
#include "UI/canvas.h"

class Controls : public QWidget
{
public:
    Controls(int n,QString filePath,Canvas * canvas);
    void updateCorresponding(int selectedValue,int optionsArray){
        qInfo() << "selectedValue: " << selectedValue << " in ComboBox: " << optionsArray;
    }

protected:
private:
    QComboBox * optionsAEdge, * optionsBEdge;
    std::vector<int> optionsValues = std::vector<int>(2);
    Canvas * canvas;
    HLD hld;
};

#endif // CONTROLS_H
