#include "mouse_handler.hpp"
#include "../CLASSI_FILE/File_Generico.hpp"

#include <QMouseEvent>
#include <QPoint>
#include <QMenu>
#include <QAction>

mouseMenu::mouseMenu(File_Generico* file, QWidget* parent) : QWidget(parent), file(file) {}

void mouseMenu::mousePressEvent(QMouseEvent* event) {
    
    if(event->button() == Qt::LeftButton) emit selezionato(file);

    if(event->button() == Qt::RightButton){
        #if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
            showTendina(event->globalPosition().toPoint());
        #else
            showTendina(event->globalPos());
        #endif
        }
}

void mouseMenu::showTendina(const QPoint& posizione){
    QMenu* tendina = new QMenu();

    ELIMINA = new QAction("Elimina",this);
    MODIFICA = new QAction("Modifica",this);
    APRI = new QAction("Apri",this);
    ADD_PREFE = new QAction("Aggiungi Preferito",this);
    REM_PREFE = new QAction("Rimuvi Preferito",this);
    SALVA = new QAction("Salva",this);

    tendina->addAction(APRI);
    !file->IsPreferito() ? tendina->addAction(ADD_PREFE) : tendina->addAction(REM_PREFE);
    tendina->addAction(MODIFICA);
    tendina->addAction(ELIMINA);
    tendina->addAction(SALVA);
    
    connect(APRI, &QAction::triggered, this, [this]() { emit selezionato(file); } );

    connect(ADD_PREFE, &QAction::triggered, this, [this]() { emit managePreferiti(file); } );

    connect(REM_PREFE, &QAction::triggered, this, [this]() { emit managePreferiti(file); } );

    connect(MODIFICA, &QAction::triggered, this, [this]() { emit modifica(file); } );

    connect(ELIMINA, &QAction::triggered, this, [this]() { emit elimina(file); } );

    connect(SALVA, &QAction::triggered, this, [this]() { emit salva(file); } );

    tendina->exec(posizione);
}