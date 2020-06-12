#include "controls.h"



Controls::Controls(int n,QString filePath,Canvas * canvas) : hld(filePath),canvas(canvas)
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
    inputLayout->addWidget(new QLabel("A: "));
    inputLayout->addWidget(optionsA);
    inputLayout->addWidget(new QLabel("B: "));
    inputLayout->addWidget(optionsB);
    inputLayout->addWidget(calcButton);
    mainLayout->addLayout(inputLayout);
    auto edgeLayout = new QHBoxLayout();
    edgeLayout->addWidget(new QLabel("A: "));
    optionsAEdge=new QComboBox();
    edgeLayout->addWidget(optionsAEdge);
    edgeLayout->addWidget(new QLabel("B: "));
    optionsBEdge= new QComboBox();
    edgeLayout->addWidget(optionsBEdge);
    edgeLayout->addWidget(new QLabel("Nuevo Costo para la Arista: "));
    auto edgeCostText = new QLineEdit();
    edgeCostText->setFixedWidth(100);
    edgeLayout->addWidget(edgeCostText);
    auto updateEdgeButton = new QPushButton("Actualizar Arista");
    edgeLayout->addWidget(updateEdgeButton);
    connect(optionsAEdge,&QComboBox::currentTextChanged,this,[this](QString value){
        for(int i=0;i<optionsValues[1];i++){
            optionsBEdge->removeItem(0);
        }
        auto newValue = value.toInt();
        auto graph = this->canvas->getGraph();
        for(auto val : graph[newValue]){
            optionsBEdge->addItem(QString::number(val.node));
        }
        optionsValues[1]=graph[newValue].size();
    });
    for(int i=0;i<n;i++){
        optionsAEdge->addItem(QString::number(i));
    }
    optionsValues[0]=n;
    connect(updateEdgeButton,&QPushButton::clicked,[edgeCostText,canvas,this](){
        auto a= optionsAEdge->currentText().toInt(),b=optionsBEdge->currentText().toInt(),w=edgeCostText->text().toInt();
        qInfo() << "before hld update a=" << a << " b=" << b << " w=" << w;
        auto wasSuccessfull=hld.update(a,b,w);
        qInfo() << "after hld udpate\n";
        if(wasSuccessfull){
            qInfo() << "going to update canvas as well";
            canvas->update(a,b,w);
        }
    });
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
    mainLayout->addLayout(edgeLayout);
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
