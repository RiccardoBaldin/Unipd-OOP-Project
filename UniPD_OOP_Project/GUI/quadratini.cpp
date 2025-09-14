#include "quadratini.hpp"
#include "../CLASSI_FILE/File_Generico.hpp"
#include "../visitor/GrigliaVisitor.hpp"
#include "../mouse/mouse_handler.hpp"

#include <QVBoxLayout>

Quadratini::Quadratini(File_Generico* file, QWidget *parent) : QWidget(parent), file(file) {
    

    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);
    setAutoFillBackground(true);


    QPalette pal = palette();
    setPalette(pal);
    setStyleSheet("background: #BEBEBE; border: 2px solid black; border-radius: 5px;");

    GrigliaVisitor *visitor = new GrigliaVisitor();
    file->Accept(*visitor);

    QVBoxLayout *layout= new QVBoxLayout(this);
    layout->setContentsMargins(5,5,5,5);
    layout->setAlignment(Qt::AlignCenter);

    mouseMenu* click = new mouseMenu(file);
    click->setLayout(visitor->GetLayout());

    click->setFixedSize(120,120);

    layout->addWidget(click);

    setLayout(layout);

    connect(click, &mouseMenu::selezionato, this, [this](){ emit QuadratinoClicked(this->file);});
    connect(click, &mouseMenu::managePreferiti, this, [this](){ emit QuadratinoPreferito(this->file);});
    connect(click, &mouseMenu::modifica, this, [this](){ emit QuadratinoModifica(this->file);});
    connect(click, &mouseMenu::elimina, this, [this](){ emit QuadratinoElimina(this->file);});
    connect(click, &mouseMenu::salva, this, [this](){ emit QuadratinoSalva(this->file);});
    
}
