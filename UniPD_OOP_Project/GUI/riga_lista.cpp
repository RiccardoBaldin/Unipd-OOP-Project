#include "riga_lista.hpp"
#include "../CLASSI_FILE/File_Generico.hpp"
#include "../CLASSI_FILE/File_Episodio.hpp"
#include "../visitor/ListaVisitor.hpp"
#include "../mouse/mouse_handler.hpp" 

#include <QVBoxLayout>

Riga_Lista::Riga_Lista(File_Generico* file, QWidget *parent) : QWidget(parent), file(file) {

    ListaVisitor *visitor = new ListaVisitor();
    file->Accept(*visitor);

    QVBoxLayout *layout = new QVBoxLayout(this);
    mouseMenu* click = new mouseMenu(file);
    click->setLayout(visitor->GetLayout());
    layout->addWidget(click);

    setLayout(layout);

    connect(click, &mouseMenu::selezionato, this, [this](){ emit RigaClicked(this->file);});
    connect(click, &mouseMenu::managePreferiti, this, [this](){ emit RigaPreferito(this->file);});
    connect(click, &mouseMenu::modifica, this, [this](){ emit RigaModifica(this->file);});
    connect(click, &mouseMenu::elimina, this, [this](){ emit RigaElimina(this->file);});
    connect(click, &mouseMenu::salva, this, [this](){ emit RigaSalva(this->file);});
}

File_Episodio* Riga_Lista::getEpisodio() const {
    return dynamic_cast<File_Episodio*>(file);
}