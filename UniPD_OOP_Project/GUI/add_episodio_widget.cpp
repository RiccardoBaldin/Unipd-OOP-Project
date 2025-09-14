#include "add_episodio_widget.hpp"
#include "../CLASSI_FILE/File_Serie.hpp"
#include "../CLASSI_FILE/File_Episodio.hpp"

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

AddEpisodioWidget::AddEpisodioWidget(File_Serie* serie, QWidget* parent) : QWidget(parent), serie(serie){

    setWindowTitle("Aggiunta Episodio");

    layout = new QVBoxLayout(this);
    
    annulla = new QPushButton("Annulla");
    conferma = new QPushButton("Conferma");

    QShortcut* escShortcut = new QShortcut(QKeySequence(Qt::Key_Escape), this);
    connect(escShortcut, &QShortcut::activated, annulla, &QPushButton::click);

    QShortcut* enterShortcut = new QShortcut(QKeySequence(Qt::Key_Return), this);
    connect(enterShortcut, &QShortcut::activated, conferma, &QPushButton::click);

    annulla->setFixedWidth(100);
    layoutSotto->addWidget(annulla);
    conferma->setFixedWidth(100);
    layoutSotto->addWidget(conferma);

    QLabel *testo = new QLabel("COMPILARE I CAMPI PER AGGIUNGERE L'EPISODIO");
    testo->setAlignment(Qt::AlignCenter);
    testo->setStyleSheet("font-size: 20px; color: red; font-weight: bold;");

    layout->addWidget(testo);
    layout->addWidget(new LineaOrizzontale());
    
    icona->setPixmap(QPixmap(":/IMMAGINI/Episodio_Aggiungi.png"));
    icona->setFixedSize(300,300);
    icona->setAlignment(Qt::AlignCenter);

    nomeSerie->setText(QString::fromStdString(serie->GetNome()));
    layoutSx->addRow("Serie", nomeSerie);
    layoutSx->addRow("Nome", nome);
    autore->setText(QString::fromStdString(serie->GetAutore()));
    layoutSx->addRow("Autore", autore);
    genere->setText(QString::fromStdString(serie->GetGenere()));
    layoutSx->addRow("Genere", genere);
    layoutSx->addRow("Anno", anno);
    anno->setRange(0,2025);
    anno->setValue(0);

    numero_stagione->setRange(0,100);
    numero_stagione->setValue(0);

    numero_episodio->setRange(0,100);
    numero_episodio->setValue(0);

    durata->setRange(0,1000);
    durata->setValue(0);

    layoutDx->addRow("Numero Stagione", numero_stagione);
    layoutDx->addRow("Numero Episodio", numero_episodio);
    layoutDx->addRow("durata", durata);
    layoutDx->addRow("regista", regista);  
    casa_di_produzione->setText(QString::fromStdString(serie->GetCasaDiProduzione()));
    layoutDx->addRow("casa produttrice", casa_di_produzione);

    QHBoxLayout* iconLayout = new QHBoxLayout();
    iconLayout->addStretch();
    iconLayout->addWidget(icona);
    iconLayout->addStretch();
    layout->addLayout(iconLayout);
    layoutBig->addLayout(layoutSx);
    layoutBig->addLayout(layoutDx);
    layout->addLayout(layoutBig);  
    
    layout->addWidget(new LineaOrizzontale());
    layout->addLayout(layoutSotto);

    connect(conferma, &QPushButton::clicked, this, &AddEpisodioWidget::ConfermaAggiunta);
    connect(annulla, &QPushButton::clicked, this, &AddEpisodioWidget::AnnullaAggiunta);

}

void AddEpisodioWidget::ConfermaAggiunta(){
    if(NonCampiVuoti()){
        File_Episodio* episodio = new File_Episodio(nome->text().toStdString(),
                                       autore->text().toStdString(),
                                       genere->text().toStdString(),
                                       anno->value(),
                                       durata->value(),
                                       casa_di_produzione->text().toStdString(),
                                       regista->text().toStdString(),
                                       numero_stagione->value(),
                                       numero_episodio->value(),
                                       serie->GetNome());
        
        if(!serie->check(episodio,nullptr)){
            QMessageBox::warning(this,
                                "Episodio già presente",
                                "Episodio con stesso nome e autore già presente all'interno della Serie");
        }else if(!serie->postolibero(episodio, nullptr)){
            QString messaggio = QString("Esiste già un episodio numero %1 nella stagione %2 all'interno della serie %3")
                                .arg(QString::number(numero_episodio->value()))
                                .arg(QString::number(numero_stagione->value()))
                                .arg(QString::fromStdString(serie->GetNome()));
            QMessageBox::warning(this,
                                "Posto occupato",
                                messaggio);
        }else{
            serie->AggiungiEpisodio(episodio);
            pulisciCampi();
            emit FileAggiunto();
        }
    }
}

void AddEpisodioWidget::AnnullaAggiunta(){
    pulisciCampi();
    emit FileAnnullato();
}

void AddEpisodioWidget::pulisciCampi(){
    nome->clear();
    autore->clear();
    genere->clear();
    anno->clear();
    durata->clear();
    regista->clear();
    casa_di_produzione->clear();
    numero_stagione->clear();
    numero_episodio->clear();
    nomeSerie->clear();
}

bool AddEpisodioWidget::NonCampiVuoti(){
    QStringList mancanti;
    if(nome->text().isEmpty()) mancanti << "Nome" ;
    if(autore->text().isEmpty()) mancanti << "Autore" ;
    if(numero_stagione->value() == 0) mancanti << "numero della stagione";
    if(numero_episodio->value() == 0) mancanti << "numero del episodio";

    if(!mancanti.isEmpty()){
        QMessageBox::warning(this,
                             "Campi Mancanti!",
                             "I seguenti campi non possono essere vuoti:\n" + mancanti.join("\n"));
        return false;
    }

    return true;
}

void AddEpisodioWidget::setSerie(File_Serie* NuovaSerie){
    serie = NuovaSerie;
    if(serie){
        nomeSerie->setText(QString::fromStdString(serie->GetNome()));
        autore->setText(QString::fromStdString(serie->GetAutore()));
        genere->setText(QString::fromStdString(serie->GetGenere()));
        casa_di_produzione->setText(QString::fromStdString(serie->GetCasaDiProduzione()));
    }
}

void AddEpisodioWidget::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);

    if (nome) {
        nome->setFocus();
    }
}