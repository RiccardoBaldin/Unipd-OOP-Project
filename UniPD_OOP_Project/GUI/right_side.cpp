#include "right_side.hpp"
#include "upper_bar.hpp"
#include "disposizione_griglia.hpp"
#include "disposizione_linee.hpp"
#include "linea_orizzontale.hpp"
#include "add_file_widget.hpp"

#include "../CLASSI_FILE/File_Generico.hpp"

#include <QVBoxLayout>
#include <QStackedWidget>


RightSide::RightSide(std::vector<File_Generico*> listaFileDaMostrare, QWidget *parent) : QWidget(parent), listaFileDaMostrare(listaFileDaMostrare){
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    upperBar = new UpperBar(this);
    linea = new LineaOrizzontale(this);
    
    stackedWidget = new QStackedWidget(this);
    Griglia = new DisposizioneGriglia(listaFileDaMostrare, this);
    Linee = new DisposizioneLinee(listaFileDaMostrare, this);

    stackedWidget->addWidget(Griglia);
    stackedWidget->addWidget(Linee);

    layout->addWidget(upperBar);
    layout->addWidget(linea);
    layout->addWidget(stackedWidget);

    setMinimumWidth(600);
    setLayout(layout);

    connect(upperBar, &UpperBar::showGriglia, this, [this, listaFileDaMostrare](){updateLayout(listaFileDaMostrare);
        stackedWidget->setCurrentWidget(Griglia);
        emit layoutChanged();
    });
    connect(upperBar, &UpperBar::showLista, this, [this, listaFileDaMostrare](){updateLayout(listaFileDaMostrare);
        stackedWidget->setCurrentWidget(Linee);
        emit layoutChanged();
    });

    connect(upperBar, &UpperBar::showPreferiti, this, &RightSide::showPreferiti);
    connect(upperBar, &UpperBar::showGenereale, this, &RightSide::showGenerale);

    connect(upperBar, &UpperBar::sortNome, this, [this](){ emit sortNome();});
    connect(upperBar, &UpperBar::sortData, this, [this](){ emit sortData();});
    connect(upperBar, &UpperBar::testoCercato, this, &RightSide::testoCercato);

    connect(Linee, &DisposizioneLinee::File_Clicked, this, &RightSide::File_Clicked);
    connect(Linee, &DisposizioneLinee::lista_elimina, this, &RightSide::elimina);
    connect(Linee, &DisposizioneLinee::lista_modifica, this, &RightSide::modifica);
    connect(Linee, &DisposizioneLinee::lista_salva, this, &RightSide::salva);
    connect(Linee, &DisposizioneLinee::lista_preferito, this, &RightSide::preferito);
    
    connect(Griglia, &DisposizioneGriglia::File_Clicked, this, &RightSide::File_Clicked);
    connect(Griglia, &DisposizioneGriglia::griglia_elimina, this, &RightSide::elimina);
    connect(Griglia, &DisposizioneGriglia::griglia_modifica, this, &RightSide::modifica);
    connect(Griglia, &DisposizioneGriglia::griglia_salva, this, &RightSide::salva);
    connect(Griglia, &DisposizioneGriglia::griglia_preferito, this, &RightSide::preferito);

   
}

void RightSide::setLista(std::vector<File_Generico*> l){
    listaFileDaMostrare = l;
    updateLayout(listaFileDaMostrare);            
}

void RightSide::changeLayout(int index) {
    stackedWidget->setCurrentIndex(index);
    updateLayout(listaFileDaMostrare);
}

void RightSide::updateLayout(std::vector<File_Generico*> l) {
    Griglia->updateLayout(l);
    Linee->updateLayout(l);
}

void RightSide::resetUpperBar(){
    upperBar->reset();
}

void RightSide::pulisci(){
    upperBar->pulisci();
}

void RightSide::showpreferiti(){
    std::vector<File_Generico*> prefes;
    for(const auto s : listaFileDaMostrare){
        if(s->IsPreferito()) prefes.push_back(s);
    }
    updateLayout(prefes);
}