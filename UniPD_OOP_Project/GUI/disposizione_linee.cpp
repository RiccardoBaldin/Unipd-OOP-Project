#include "disposizione_linee.hpp"

#include "../CLASSI_FILE/Container.hpp"
#include "../CLASSI_FILE/File_Generico.hpp"
#include "riga_lista.hpp"

#include <QListWidget>
#include <QVBoxLayout>

DisposizioneLinee::DisposizioneLinee(std::vector<File_Generico*> ListaFileDaMostrare, QWidget *parent) : QWidget(parent), ListaFileDaMostrare(ListaFileDaMostrare){
   
   QVBoxLayout* mainLayout = new QVBoxLayout(this);

    listWidget = new QListWidget(this);
    listWidget->setAlternatingRowColors(true);
    listWidget->setStyleSheet("QListWidget::item { border-bottom: 1px solid green; }");

    mainLayout->addWidget(listWidget);

    setLayout(mainLayout);

    updateLayout(ListaFileDaMostrare);
}

void DisposizioneLinee::updateLayout(std::vector<File_Generico*> l) {
    listWidget->clear();
    ListaFileDaMostrare = l;
    for(auto file : ListaFileDaMostrare){
        if (!file) continue;
        Riga_Lista* riga = new Riga_Lista(file, this);
        QListWidgetItem* item = new QListWidgetItem();
        item->setSizeHint(riga->sizeHint());
        listWidget->addItem(item);
        listWidget->setItemWidget(item, riga);

        connect(riga, &Riga_Lista::RigaClicked, this, &DisposizioneLinee::File_Clicked);
        connect(riga, &Riga_Lista::RigaModifica, this, &DisposizioneLinee::lista_modifica);
        connect(riga, &Riga_Lista::RigaElimina, this, &DisposizioneLinee::lista_elimina);
        connect(riga, &Riga_Lista::RigaSalva, this, &DisposizioneLinee::lista_salva);
        connect(riga, &Riga_Lista::RigaPreferito, this, &DisposizioneLinee::lista_preferito);
    }

}