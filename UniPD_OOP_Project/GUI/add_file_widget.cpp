#include "add_file_widget.hpp"
#include "../CLASSI_FILE/Container.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QButtonGroup>
#include <QRadioButton>
#include <QMessageBox>
#include <QStringList>
#include <QShowEvent>
#include <QShortcut>
#include "linea_orizzontale.hpp"

#include "../CLASSI_FILE/File_Libro.hpp"
#include "../CLASSI_FILE/File_Generico.hpp"
#include "../CLASSI_FILE/File_Film.hpp"
#include "../CLASSI_FILE/File_Serie.hpp"

AddFileWidget::AddFileWidget(Biblioteca* biblioteca, int index, QWidget *parent) : QWidget(parent), tipo(index), biblioteca(biblioteca){

    layout = new QVBoxLayout(this);

    annulla = new QPushButton("Annulla");
    conferma =  new QPushButton("Conferma");
    annulla->setFixedWidth(100);
    layoutSotto->addWidget(annulla);
    conferma->setFixedWidth(100);
    layoutSotto->addWidget(conferma);

    QLabel *testo = new QLabel("COMPILARE I CAMPI PER AGGIUNGERE UN FILE");
    testo->setAlignment(Qt::AlignCenter);
    testo->setStyleSheet("font-size: 20px; color: red; font-weight: bold;");

    layout->addWidget(testo);
    layout->addWidget(new LineaOrizzontale());
    SceltaTipo();
    layout->addWidget(new LineaOrizzontale());
    layout->addLayout(layoutSotto);

    connect(conferma, &QPushButton::clicked, this, &AddFileWidget::ConfermaAggiunta);
    connect(annulla, &QPushButton::clicked, this, &AddFileWidget::AnnullaAggiunta);

    QShortcut* escShortcut = new QShortcut(QKeySequence(Qt::Key_Escape), this);
    connect(escShortcut, &QShortcut::activated, this, [this]() {
        annulla->click();
    });

    QShortcut* returnShortcut = new QShortcut(QKeySequence(Qt::Key_Return), this);
    connect(returnShortcut, &QShortcut::activated, this, [this]() {
        conferma->click();
    });
}

void AddFileWidget::SceltaTipo() {
    switch(tipo){
        case 0:
            setWindowTitle("Aggiunta Libro");
            AggiungiLibro();
            break;
        case 1:
            setWindowTitle("Aggiunta Film");
            AggiungiFilm();
            break;
        case 2:
            setWindowTitle("Aggiunta Serie");
            AggiungiSerie();
            break;
    }
}


void AddFileWidget::AggiungiLibro(){
    icona->setPixmap(QPixmap(":/IMMAGINI/Libro_Aggiungi.png"));
    icona->setFixedSize(300,300);
    icona->setAlignment(Qt::AlignCenter);


    layoutSx->addRow("Nome", nome);
    layoutSx->addRow("Autore", autore);
    layoutSx->addRow("Genere", genere);
    layoutSx->addRow("Anno", anno);
    anno->setRange(0,2025);
    anno->setValue(0);

    pagine = new QSpinBox();
    pagine->setRange(0,9999);
    pagine->setValue(0);
    editore = new QLineEdit();

    layoutDx->addRow("Pagine", pagine);
    layoutDx->addRow("Editore", editore);

    QHBoxLayout* iconLayout = new QHBoxLayout();
    iconLayout->addStretch();
    iconLayout->addWidget(icona);
    iconLayout->addStretch();
    layout->addLayout(iconLayout);
    layoutBig->addLayout(layoutSx);
    layoutBig->addLayout(layoutDx);
    layout->addLayout(layoutBig);

}

void AddFileWidget::AggiungiFilm(){
    icona->setPixmap(QPixmap(":/IMMAGINI/Film_Aggiungi.png"));
    icona->setFixedSize(300,300);
    icona->setAlignment(Qt::AlignCenter);

    layoutSx->addRow("Nome", nome);
    layoutSx->addRow("Autore", autore);
    layoutSx->addRow("Genere", genere);
    layoutSx->addRow("Anno", anno);
    anno->setRange(0,2025);
    anno->setValue(0);

    durata = new QSpinBox();
    durata->setRange(0,1000);
    durata->setValue(0);
    
    regista = new QLineEdit();
    casa_di_produzione = new QLineEdit();
    oscar = new QCheckBox();

    layoutDx->addRow("durata", durata);
    layoutDx->addRow("regista", regista);  
    layoutDx->addRow("casa produttrice", casa_di_produzione);
    layoutDx->addRow("vincitore di oscar", oscar);

    QHBoxLayout* iconLayout = new QHBoxLayout();
    iconLayout->addStretch();
    iconLayout->addWidget(icona);
    iconLayout->addStretch();
    layout->addLayout(iconLayout);
    layoutBig->addLayout(layoutSx);
    layoutBig->addLayout(layoutDx);
    layout->addLayout(layoutBig);    

}

void AddFileWidget::AggiungiSerie(){
    icona->setPixmap(QPixmap(":/IMMAGINI/Serie_Aggiungi.png"));
    icona->setFixedSize(300,300);
    icona->setAlignment(Qt::AlignCenter);

    layoutSx->addRow("Nome", nome);
    layoutSx->addRow("Autore", autore);
    layoutSx->addRow("Genere", genere);
    layoutSx->addRow("Anno", anno);
    anno->setRange(0,2025);
    anno->setValue(0);

    casa_di_produzione_serie = new QLineEdit();

    layoutDx->addRow("casa produttrice", casa_di_produzione_serie);


    QHBoxLayout* iconLayout = new QHBoxLayout();
    iconLayout->addStretch();
    iconLayout->addWidget(icona);
    iconLayout->addStretch();
    layout->addLayout(iconLayout);
    layoutBig->addLayout(layoutSx);
    layoutBig->addLayout(layoutDx);
    layout->addLayout(layoutBig);    

}

void AddFileWidget::ConfermaAggiunta(){
    if(NonCampiVuoti()){
        switch(tipo){
            case 0:{
                    File_Libro* libro = new File_Libro(nome->text().toStdString(),
                                       autore->text().toStdString(),
                                       genere->text().toStdString(),
                                       anno->value(),
                                       pagine->value(),
                                       editore->text().toStdString());
                    if(biblioteca->check(libro,nullptr)){
                        biblioteca->addFile(libro);
                        pulisciCampi();
                        emit FileAggiunto();
                    }else{
                        QMessageBox::warning(this,
                                            "Articolo già presente",
                                            "Articolo già presente nella biblioteca digitale");
                        delete libro;
                    }
                    break;
            }case 1:{    
                    File_Film* film = new File_Film(nome->text().toStdString(),
                                       autore->text().toStdString(),
                                       genere->text().toStdString(),
                                       anno->value(),
                                       durata->value(),
                                       casa_di_produzione->text().toStdString(),
                                       regista->text().toStdString(),
                                       oscar->isChecked());
                    if(biblioteca->check(film,nullptr)){
                        biblioteca->addFile(film);
                        pulisciCampi();
                        emit FileAggiunto();
                    }else{
                        QMessageBox::warning(this,
                                            "Articolo già presente",
                                            "Articolo già presente nella biblioteca digitale");
                        delete film;
                    }
                    break;
            }case 2:{    
                    File_Serie* serie = new File_Serie(nome->text().toStdString(),
                                       autore->text().toStdString(),
                                       genere->text().toStdString(),
                                       anno->value(),
                                       0,
                                       0,
                                       casa_di_produzione_serie->text().toStdString());
                    if(biblioteca->check(serie,nullptr)){
                        biblioteca->addFile(serie);
                        pulisciCampi();
                        emit FileAggiunto();
                    }else{
                        QMessageBox::warning(this,
                                            "Articolo già presente",
                                            "Articolo già presente nella biblioteca digitale");
                        delete serie;
                    }
                    break;
            }
        }
    }
}

void AddFileWidget::AnnullaAggiunta(){
    pulisciCampi();
    emit FileAnnullato();
}

void AddFileWidget::pulisciCampi() {
    nome->clear();
    autore->clear();
    genere->clear();
    anno->clear();
    switch(tipo){
        case 0:
            pagine->clear();
            editore->clear();
            break;
        case 1:
            durata->clear();
            regista->clear();
            casa_di_produzione->clear();
            oscar->setChecked(false);
            break;
        case 2:
            casa_di_produzione_serie->clear();
            break;
    }


}

bool AddFileWidget::NonCampiVuoti(){
    QStringList mancanti;
    if(nome->text().isEmpty()) mancanti << "Nome" ;
    if(autore->text().isEmpty()) mancanti << "Autore" ;

    if(!mancanti.isEmpty()){
        QMessageBox::warning(this,
                             "Campi Mancanti!",
                             "I seguenti campi non possono essere vuoti:\n" + mancanti.join("\n"));
        return false;
    }

    return true;
}

void AddFileWidget::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);

    if (nome) {
        nome->setFocus();
    }
}