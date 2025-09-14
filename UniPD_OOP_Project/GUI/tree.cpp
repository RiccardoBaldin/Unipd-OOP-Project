#include "tree.hpp"
#include "../CLASSI_FILE/Container.hpp"
#include "../CLASSI_FILE/File_Libro.hpp"
#include "../CLASSI_FILE/File_Film.hpp"
#include "../CLASSI_FILE/File_Serie.hpp"
#include "../JSON_CONTROL/ToJson.hpp"

Tree::Tree(Biblioteca* biblioteca, QWidget* parent) : QTreeWidget(parent), biblioteca(biblioteca) {

    setHeaderHidden(true);
    setAlternatingRowColors(true);
    setRootIsDecorated(false);

    setColumnWidth(0, 175);

    libreria = new QTreeWidgetItem(this);
    libreria->setText(0, "La mia libreria");
    libreria->setIcon(0, QIcon(":/IMMAGINI/LIBRERIA.png"));

    libri = new QTreeWidgetItem(libreria);
    libri->setText(0, "I miei libri");
    libri->setIcon(0, QIcon(":/IMMAGINI/LIBRO.png"));

    film = new QTreeWidgetItem(libreria);
    film->setText(0, "I miei film");
    film->setIcon(0, QIcon(":/IMMAGINI/FILM.png"));

    serie = new QTreeWidgetItem(libreria);
    serie->setText(0, "Le mie serie");
    serie->setIcon(0, QIcon(":/IMMAGINI/SERIE.png"));

    updateTree();

}



void Tree::populateTree(){
    if(!biblioteca) return;
    biblioteca->sort_nome();
    for(const auto& file : biblioteca->getArchivio()){
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0, QString::fromStdString(file->GetNome()));
        item->setIcon(0, QIcon(":/IMMAGINI/PUNTO.png"));
        if(dynamic_cast<File_Libro*>(file)){
            libri->addChild(item);
        } else if(dynamic_cast<File_Film*>(file)){
            film->addChild(item);
        } else if(dynamic_cast<File_Serie*>(file)){
            serie->addChild(item);
        }
    }
}

void Tree::updateTree(){
    libri->takeChildren();
    film->takeChildren();
    serie->takeChildren();
    populateTree();
}