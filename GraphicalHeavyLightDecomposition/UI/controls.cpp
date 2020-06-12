#include "controls.h"



Controls::Controls(int n,QString filePath) : hld(filePath)
{
    qInfo() << "Controls";
    auto mainLayout = new QVBoxLayout();
    setLayout(mainLayout);
    auto inputLayout = new QHBoxLayout();
    auto optionsA = new QComboBox(), optionsB = new QComboBox();
    for(int i=0;i<n;i++){
        auto iQStr = QString::number(i);
        optionsA->addItem(iQStr);
        optionsB->addItem(iQStr);
    }
    auto calcButton = new QPushButton("Calcular Query");
    inputLayout->addWidget(optionsA);
    inputLayout->addWidget(optionsB);
    inputLayout->addWidget(calcButton);
    mainLayout->addLayout(inputLayout);
    auto sumResultLabel=new QLabel("Suma Aristas: ");
    auto maxResultLabel=new QLabel("Maxima Arista: ");
    auto minResultLabel=new QLabel("Minima Arista: ");
    auto gcdResultLabel=new QLabel("Maximo Comun Divisor de Aristas: ");
    auto lcmResultLabel=new QLabel("Minimo Comun Multiplo de Aristas: ");
    mainLayout->addWidget(sumResultLabel);
    mainLayout->addWidget(maxResultLabel);
    mainLayout->addWidget(minResultLabel);
    mainLayout->addWidget(gcdResultLabel);
    mainLayout->addWidget(lcmResultLabel);
    connect(calcButton,&QPushButton::clicked,[optionsA,optionsB,this,sumResultLabel](){
        auto sumQueryResult = this->hld.query(optionsA->currentText().toInt(),optionsB->currentText().toInt(),HLD::sum);
        sumResultLabel->setText("Suma Aristas: "+QString::number(sumQueryResult));
    });
    connect(calcButton,&QPushButton::clicked,[optionsA,optionsB,this,maxResultLabel](){
        auto maxQueryResult = this->hld.query(optionsA->currentText().toInt(),optionsB->currentText().toInt(),HLD::maximum);
        maxResultLabel->setText("Maxima Arista: "+QString::number(maxQueryResult));
    });
    connect(calcButton,&QPushButton::clicked,[optionsA,optionsB,this,minResultLabel](){
        auto minQueryResult = this->hld.query(optionsA->currentText().toInt(),optionsB->currentText().toInt(),HLD::minimum);
        minResultLabel->setText("Minima Arista: "+QString::number(minQueryResult));
    });
    connect(calcButton,&QPushButton::clicked,[optionsA,optionsB,this,gcdResultLabel](){
        auto gcdQueryResult = this->hld.query(optionsA->currentText().toInt(),optionsB->currentText().toInt(),HLD::gcd);
        gcdResultLabel->setText("Maximo Comun Divisor de Aristas: "+QString::number(gcdQueryResult));
    });
    connect(calcButton,&QPushButton::clicked,[optionsA,optionsB,this,lcmResultLabel](){
        auto lcmQueryResult = this->hld.query(optionsA->currentText().toInt(),optionsB->currentText().toInt(),HLD::lcm);
        lcmResultLabel->setText("Minimo Comun Multiplo de Aristas: "+QString::number(lcmQueryResult));
    });
}
