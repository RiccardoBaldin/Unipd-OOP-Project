#include "upper_bar.hpp"


#include <QHBoxLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QStackedWidget>
#include <QPushButton>
#include <iostream>
#include <QShortcut>

UpperBar::UpperBar(QWidget *parent) : QWidget(parent) {
    QHBoxLayout *layout = new QHBoxLayout(this);
    setMaximumHeight(50);

    searchBar = new QLineEdit(this);
    searchBar->setPlaceholderText("Cerca...");
    searchBar->setMinimumWidth(150);
    searchBar->setMaximumWidth(150);

    searchBar->addAction(QIcon(":/IMMAGINI/lente.png"), QLineEdit::LeadingPosition);

    changeLayout = new QComboBox();
    changeLayout->setMaximumWidth(150);
    changeLayout->setMinimumWidth(150);

    vuota = new QIcon(":/IMMAGINI/stella_vuota.png");
    piena = new QIcon(":/IMMAGINI/stella_piena.png");
    stella = new QPushButton();
    stella->setIcon(*vuota);
    stella->setFlat(true);
    stella->setIconSize(QSize(24, 24));  
    stella->setFixedSize(30, 30);     
    stella->setStyleSheet("background-color: transparent; border: none;");


    sortComboBox = new QComboBox(this);
    sortComboBox->setMaximumWidth(150);
    sortComboBox->setMinimumWidth(150);



    changeLayout->addItem("Griglia");
    changeLayout->addItem("Lista");


    sortComboBox->addItem("ordina per nome");
    sortComboBox->addItem("ordina per data");

    layout->addWidget(searchBar);
    layout->addStretch();
    layout->addWidget(changeLayout);
    layout->addStretch();
    layout->addWidget(sortComboBox);
    layout->addStretch();
    layout->addWidget(stella);

    setLayout(layout);

    connect(changeLayout, QOverload<int>::of(&QComboBox::currentIndexChanged),
        this, [this](){sortComboBox->setCurrentIndex(0);
                        selezionato = false;
                        stella->setIcon(*vuota);
                        if(changeLayout->currentIndex() == 0) emit showGriglia();
                        emit showGenereale();
                        searchBar->clear();
                      }
            );

    connect(changeLayout, QOverload<int>::of(&QComboBox::currentIndexChanged),
        this, [this](){sortComboBox->setCurrentIndex(0);
                        selezionato = false;
                        stella->setIcon(*vuota);
                        if(changeLayout->currentIndex() == 1) emit showLista();
                        emit showGenereale();
                        searchBar->clear();
                      }
            );

    connect(sortComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
        this, [this](){if(sortComboBox->currentIndex() == 0) emit sortNome(); searchBar->clear();});

    connect(sortComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
        this, [this](){if(sortComboBox->currentIndex() == 1) emit sortData(); searchBar->clear();});

    connect(searchBar, &QLineEdit::textChanged, this, &UpperBar::testoCercato);


    QShortcut* cmdF = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_F), this);
    connect(cmdF, &QShortcut::activated, this, [this]() {
        searchBar->setFocus();
        searchBar->selectAll();
    });

    QShortcut* escShortcut = new QShortcut(QKeySequence(Qt::Key_Escape), this);
    connect(escShortcut, &QShortcut::activated, this, [this]() {
        searchBar->clearFocus();
    });

    connect(stella, &QPushButton::clicked, this, [this]() {
        selezionato = !selezionato;
        stella->setIcon(selezionato ? (*piena) : (*vuota));
        if (!selezionato) pulisci();
        emit selezionato ? showPreferiti() : showGenereale();

    });

}

void UpperBar::pulisci(){
    searchBar->clear();
}

void UpperBar::reset(){
    selezionato = false;
    stella->setIcon(*vuota);
    emit showGenereale();
}