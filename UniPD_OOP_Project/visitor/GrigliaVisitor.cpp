#include "GrigliaVisitor.hpp"
#include "../CLASSI_FILE/File_Generico.hpp"
#include "../CLASSI_FILE/File_Film.hpp"
#include "../CLASSI_FILE/File_Episodio.hpp"
#include "../CLASSI_FILE/File_Serie.hpp"
#include "../CLASSI_FILE/File_Libro.hpp"

#include <QLabel>
#include <QIcon>
#include <QVBoxLayout>

void GrigliaVisitor::Visit(File_Generico& file) {
    if(!layout){    
        layout = new QVBoxLayout();
        label = new QLabel();
        label->setAlignment(Qt::AlignCenter);
        layout->addWidget(label);

        nome = new QLabel();
        nome->setAlignment(Qt::AlignLeft);
        nome->setStyleSheet("color: black;");
        layout->addWidget(nome);
    }
    nome->setText(QString::fromStdString(file.GetNome()));
    label->clear();
}

void GrigliaVisitor::Visit(File_Video&){}

void GrigliaVisitor::Visit(File_Film& film) {
    Visit(static_cast<File_Generico&>(film));
    label->setPixmap(QIcon(":/IMMAGINI/film_nero.png").pixmap(65,65));
}


void GrigliaVisitor::Visit(File_Episodio&) {}


void GrigliaVisitor::Visit(File_Serie& serie) {
    Visit(static_cast<File_Generico&>(serie));
    
    label->setPixmap(QIcon(":/IMMAGINI/serie_nero.png").pixmap(65,65));
}


void GrigliaVisitor::Visit(File_Libro& libro) {
    Visit(static_cast<File_Generico&>(libro));
    label->setPixmap(QIcon(":/IMMAGINI/libro_nero.png").pixmap(65,65));
}


QVBoxLayout* GrigliaVisitor::GetLayout() const {
    return layout;
}

void GrigliaVisitor::Visit(Biblioteca&){}