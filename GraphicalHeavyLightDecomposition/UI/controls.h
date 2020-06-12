#ifndef CONTROLS_H
#define CONTROLS_H

#include<QWidget>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QComboBox>
#include<QPushButton>
#include<QLabel>

#include "DS/hld.h"

class Controls : public QWidget
{
public:
    Controls(int n,QString filePath);
protected:
private:
    HLD hld;
};

#endif // CONTROLS_H
