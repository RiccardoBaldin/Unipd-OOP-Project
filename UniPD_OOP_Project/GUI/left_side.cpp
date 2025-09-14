#include "left_side.hpp"
#include "tree.hpp"
#include "../CLASSI_FILE/Container.hpp"
#include "../CLASSI_FILE/File_Generico.hpp"
#include "../JSON_CONTROL/ToJson.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QIcon>
#include <QTreeWidget>
#include <QPushButton>
#include <QComboBox>
#include <QShortcut>
#include <QKeySequence>


LeftSide::LeftSide(Biblioteca* biblioteca, QWidget *parent) : QWidget(parent), biblioteca(biblioteca) {
    setFixedWidth(220);

    QLabel *logoLabel = new QLabel(this);
    logoLabel->setPixmap(QPixmap(":/IMMAGINI/LOGO.png"));
    logoLabel->setAlignment(Qt::AlignCenter);
    logoLabel->setFixedHeight(100);
    

    tree = new Tree(biblioteca, this);
    creaFile = new QComboBox(this);
    creaFile->setStyleSheet("font-weight: bold;");
    
    creaFile->addItem("Crea un nuovo file");
    creaFile->addItem("Crea un nuovo libro");
    creaFile->addItem("Crea un nuovo film");
    creaFile->addItem("Crea una nuova serie TV");

    importaB = new QPushButton("+ biblioteca +");
    importaB->setStyleSheet("font-weight: bold;");   
    importaF = new QPushButton("+ file +"); 
    importaF->setStyleSheet("font-weight: bold;");   


    QHBoxLayout *importazioni = new QHBoxLayout();
    importazioni->addWidget(importaB);
    importazioni->addWidget(importaF);

    salva = new QPushButton("Salva la biblioteca");
    salva->setStyleSheet("font-weight: bold;");   


    QShortcut* shortcutNuovo = new QShortcut(QKeySequence("Ctrl+N"), this);
    QShortcut* shortcutSalva = new QShortcut(QKeySequence("Ctrl+S"), this);
    QShortcut* shortcutImporta = new QShortcut(QKeySequence("Ctrl+O"), this);
    connect(shortcutNuovo, &QShortcut::activated, creaFile, &QComboBox::showPopup);
    connect(shortcutSalva, &QShortcut::activated, this, &LeftSide::salvaBiblioteca);
    connect(shortcutImporta, &QShortcut::activated, this, &LeftSide::importaBiblioteca);
    
    connect(creaFile, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &LeftSide::onComboBoxIndexChanged);
    connect(tree, &Tree::updateTreeSignal, this, &LeftSide::updateTree);

    connect(tree, &QTreeWidget::itemClicked, this, [this](QTreeWidgetItem *item){
        if (!item) return;
        QString text = item->text(0).toLower();
        if (text == "i miei libri"){
            emit listaCambiataInLibri();
        } else if (text == "i miei film") {
            emit listaCambiataInFilm();
        } else if (text == "le mie serie") {
            emit listaCambiataInSerie();
        } else if (text == "la mia libreria") {
            emit listaCambiataInTutto();
        }
    });

    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(logoLabel);
    layout->addWidget(tree);
    layout->addWidget(creaFile);
    layout->addLayout(importazioni);
    layout->addWidget(salva);

    setLayout(layout);

    connect(importaB, &QPushButton::clicked, this, &LeftSide::importaBiblioteca);
    connect(importaF, &QPushButton::clicked, this, &LeftSide::importaFile);
    connect(salva, &QPushButton::clicked, this, &LeftSide::salvaBiblioteca);

}

void LeftSide::updateTree() {
    tree->updateTree();
    
}

void LeftSide::resetComboBox(){
    creaFile->setCurrentIndex(0);
}

void LeftSide::onComboBoxIndexChanged(int index) {
    if (index == 0) return;
    emit addFileSignal(index-1);
    resetComboBox();
}
