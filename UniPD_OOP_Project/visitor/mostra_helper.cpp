#include "mostra_helper.hpp"

#include "../CLASSI_FILE/File_Generico.hpp"
#include "../CLASSI_FILE/File_Episodio.hpp"
#include "../CLASSI_FILE/File_Serie.hpp"
#include "../GUI/riga_lista.hpp"


#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QTreeWidget>
#include <QLabel>

MostraVisitorHelper::MostraVisitorHelper(File_Generico* file, QWidget *parent)
    : QWidget(parent), serie(nullptr) {
    update(file);
}

void MostraVisitorHelper::update(File_Generico* file) {
    if (!file) return;

    if (layout()) {
        QLayoutItem* child;
        while ((child = layout()->takeAt(0)) != nullptr) {
            if (child->widget()) {
                delete child->widget();
            }
            delete child;
        }
        delete layout();
    }

    serie = dynamic_cast<File_Serie*>(file);

    QVBoxLayout* layout = new QVBoxLayout(this);
    MostraVisitor* visitor = new MostraVisitor();
    file->Accept(*visitor);

    if (serie) {
        QTreeWidget* albero = new QTreeWidget(); 
        albero = visitor->GetAlberoEpisodi();
        if (albero) {
            if (albero->topLevelItemCount() == 0) {
                QLabel* nessunEpisodioLabel = new QLabel("Nessun episodio presente");
                layout->addWidget(nessunEpisodioLabel);
            } else {
                for (int i = 0; i < albero->topLevelItemCount(); ++i) {
                    QTreeWidgetItem* stagione = albero->topLevelItem(i);
                    for (int j = 0; j < stagione->childCount(); ++j) {
                        QTreeWidgetItem* episodio = stagione->child(j);
                        QWidget* widget = albero->itemWidget(episodio, 1);
                        Riga_Lista* riga = qobject_cast<Riga_Lista*>(widget);
                        if (riga) {
                            connect(riga, &Riga_Lista::RigaClicked, this, [this, riga ](){EpisodioSelezionato(riga->getEpisodio());});
                            connect(riga, &Riga_Lista::RigaModifica, this, [this, riga ](){EpisodioModifica(riga->getEpisodio());});
                            connect(riga, &Riga_Lista::RigaElimina, this, [this, riga ](){EpisodioElimina(riga->getEpisodio());});
                            connect(riga, &Riga_Lista::RigaSalva, this, [this, riga ](){EpisodioSalva(riga->getEpisodio());});
                        }
                    }
                }
            }
        }
        QHBoxLayout* sottosopra = new QHBoxLayout();
        QPushButton* BottoneAggiunta = new QPushButton("Aggiungi Episodio");
        connect(BottoneAggiunta, &QPushButton::clicked, this, [this](){ emit AggiuntaEpisodio();});
        sottosopra->addWidget(BottoneAggiunta);
        QPushButton* BottoneImport = new QPushButton("Importa Episodio");
        sottosopra->addWidget(BottoneImport);
        connect(BottoneImport, &QPushButton::clicked, this, [this](){ emit ImportaEpisodio(serie);});
        layout->addLayout(sottosopra);
    }

    QWidget* container = visitor->GetWidget();
    layout->addWidget(container);

    setLayout(layout);
}