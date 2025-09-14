#include "disposizione_griglia.hpp"

#include "../CLASSI_FILE/Container.hpp"
#include "../CLASSI_FILE/File_Generico.hpp"
#include "../JSON_CONTROL/FromJson.hpp"
#include "quadratini.hpp"

#include <QScrollArea>


DisposizioneGriglia::DisposizioneGriglia(std::vector<File_Generico*> ListaFileDaMostrare, QWidget *parent) : QWidget(parent), ListaFileDaMostrare(ListaFileDaMostrare){
    
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    
    QWidget* container = new QWidget();

    layout = new QGridLayout(container);
    container->setLayout(layout);
    
    scrollArea->setWidget(container);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    mainLayout->addWidget(scrollArea);

    setLayout(mainLayout);

    updateLayout(ListaFileDaMostrare);
}

void DisposizioneGriglia::resizeEvent(QResizeEvent *) {
    updateLayout(ListaFileDaMostrare);
}

void DisposizioneGriglia::updateLayout(std::vector<File_Generico*> l){

    ListaFileDaMostrare = l;

    layout->setHorizontalSpacing(10);
    layout->setVerticalSpacing(10);

    
    int larghezza = width()>150 ? width(): 150;
    int n_colonne = (larghezza / 150);

    int n_elementi = ListaFileDaMostrare.size();
    int n_righe = (n_elementi + n_colonne - 1) / n_colonne;

    QLayoutItem* item;
    while((item = layout->takeAt(0)) != nullptr){
        item->widget()->deleteLater();
        delete item;
    }

    int i = 0;
    for(int r = 0 ; r < n_righe ; ++r){
        for(int c = 0 ; c < n_colonne ; ++c){
            if(i >= n_elementi){
                break;
            }
            Quadratini* quadratino = new Quadratini((ListaFileDaMostrare)[i], this);
            layout->addWidget(quadratino, r, c);
            connect(quadratino, &Quadratini::QuadratinoClicked, this, &DisposizioneGriglia::File_Clicked);
            connect(quadratino, &Quadratini::QuadratinoModifica, this, &DisposizioneGriglia::griglia_modifica);
            connect(quadratino, &Quadratini::QuadratinoElimina, this, &DisposizioneGriglia::griglia_elimina);
            connect(quadratino, &Quadratini::QuadratinoSalva, this, &DisposizioneGriglia::griglia_salva);
            connect(quadratino, &Quadratini::QuadratinoPreferito, this, &DisposizioneGriglia::griglia_preferito);


            ++i;
        }
        layout->setColumnStretch(r, 0);
        layout->setRowStretch(r, 0);
    }
}
