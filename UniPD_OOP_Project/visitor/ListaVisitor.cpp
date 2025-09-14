#include "ListaVisitor.hpp"
#include "../CLASSI_FILE/File_Generico.hpp"
#include "../CLASSI_FILE/File_Film.hpp"
#include "../CLASSI_FILE/File_Episodio.hpp"
#include "../CLASSI_FILE/File_Serie.hpp"
#include "../CLASSI_FILE/File_Libro.hpp"

#include <QLabel>
#include <QPixmap>
#include <QIcon>
#include <QHBoxLayout>

void ListaVisitor::Visit(File_Generico& file) {
    layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    label = new QLabel();
    label->setAlignment(Qt::AlignLeft);
    layout->addWidget(label);

    QLabel* nome = new QLabel(QString::fromStdString(file.GetNome()));
    nome->setAlignment(Qt::AlignCenter);
    nome->setStyleSheet("color: black;");
    
    layout->addWidget(nome);
    layout->addStretch();

}

void ListaVisitor::Visit(File_Video&) {}

void ListaVisitor::Visit(File_Film& film) {
    Visit(static_cast<File_Generico&>(film));
    
    icona = new QIcon(":/IMMAGINI/film_nero.png");
    
    label->setPixmap(icona->pixmap(35, 35));

}

void ListaVisitor::Visit(File_Episodio& episodio) {
    Visit(static_cast<File_Generico&>(episodio));
    
    icona = new QIcon(":/IMMAGINI/episodio_nero.png");
    
    label->setPixmap(icona->pixmap(35, 35));

}

void ListaVisitor::Visit(File_Serie& serie) {
    Visit(static_cast<File_Generico&>(serie));
    
    icona = new QIcon(":/IMMAGINI/serie_nero.png");
    
    label->setPixmap(icona->pixmap(35, 35));

}

void ListaVisitor::Visit(File_Libro& libro) {
    Visit(static_cast<File_Generico&>(libro));
    
    icona = new QIcon(":/IMMAGINI/libro_nero.png");
    
    label->setPixmap(icona->pixmap(35, 35));

}

QHBoxLayout* ListaVisitor::GetLayout() const {
    return layout;
}

void ListaVisitor::Visit(Biblioteca&) {}
