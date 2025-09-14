#include "main_window.hpp"
#include "../CLASSI_FILE/Container.hpp"
#include "../CLASSI_FILE/File_Generico.hpp"
#include "../CLASSI_FILE/File_Libro.hpp"
#include "../CLASSI_FILE/File_Film.hpp"
#include "../CLASSI_FILE/File_Serie.hpp"
#include "../CLASSI_FILE/finder.hpp"
#include "../JSON_CONTROL/ToJson.hpp"
#include "../visitor/MostraVisitor.hpp"
#include "../visitor/mostra_helper.hpp"
#include "../visitor/ModificaVisitor.hpp"
#include "../CLASSI_FILE/File_Episodio.hpp"
#include "../JSON_CONTROL/FromJson.hpp"
#include "add_episodio_widget.hpp"
#include "left_side.hpp"
#include "right_side.hpp"
#include "linea_verticale.hpp"
#include "add_file_widget.hpp"
#include "upper_bar.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QApplication>
#include <QPushButton>
#include <QIcon>
#include <QString>
#include <iostream>
#include <QMessageBox>
#include <QFileDialog>
#include <QShortcut>
#include <QTimer>
 
MainWindow::MainWindow(Biblioteca* biblioteca, QWidget *parent) : QMainWindow(parent), biblioteca(biblioteca), lista(biblioteca->getArchivio()){

    setWindowTitle("Biblioteca");
    setMinimumSize(800, 600);

    stackedWidget = new QStackedWidget(this);
    
    principale = new QWidget(this);
    aggiuntaLibro = new AddFileWidget(biblioteca, 0, this);  
    aggiuntaFilm = new AddFileWidget(biblioteca, 1, this);    
    aggiuntaSerie = new AddFileWidget(biblioteca, 2, this);  

    leftSide = new LeftSide(biblioteca);
    rightSide = new RightSide(lista);
    linea = new LineaVerticale(this);

    linea->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    QHBoxLayout *layoutPrincipale = new QHBoxLayout(principale);
    layoutPrincipale->setContentsMargins(0, 0, 0, 0);
    layoutPrincipale->setSpacing(0);

    layoutPrincipale->addWidget(leftSide);
    layoutPrincipale->addWidget(linea);
    layoutPrincipale->addWidget(rightSide);

    principale->setLayout(layoutPrincipale);

    stackedWidget->addWidget(principale);
    stackedWidget->addWidget(aggiuntaLibro);
    stackedWidget->addWidget(aggiuntaFilm);
    stackedWidget->addWidget(aggiuntaSerie);

    setCentralWidget(stackedWidget);

    preferito_si = new QIcon(":/IMMAGINI/preferito_si.png");
    preferito_no = new QIcon(":/IMMAGINI/preferito_no.png");   

    connect(leftSide, &LeftSide::addFileSignal, this, &MainWindow::showAddFileWidget);
    connect(leftSide, &LeftSide::importaBiblioteca, this, &MainWindow::importaBiblioteca);
    connect(leftSide, &LeftSide::importaFile, this, &MainWindow::importaFile);
    connect(leftSide, &LeftSide::salvaBiblioteca, this, &MainWindow::salvaBiblioteca);
    
    connect(aggiuntaLibro, &AddFileWidget::FileAggiunto, this, [this](){this->biblioteca->isSaved = false;});

    connect(aggiuntaLibro, &AddFileWidget::FileAggiunto, this, &MainWindow::showMainWindow);
    connect(aggiuntaLibro, &AddFileWidget::FileAnnullato, this, &MainWindow::showMainWindow);
    connect(aggiuntaFilm, &AddFileWidget::FileAggiunto, this, &MainWindow::showMainWindow);
    connect(aggiuntaFilm, &AddFileWidget::FileAnnullato, this, &MainWindow::showMainWindow);
    connect(aggiuntaSerie, &AddFileWidget::FileAggiunto, this, &MainWindow::showMainWindow);
    connect(aggiuntaSerie, &AddFileWidget::FileAnnullato, this, &MainWindow::showMainWindow);
    
    connect(rightSide, &RightSide::File_Clicked, this, &MainWindow::mostraWindow);
    connect(rightSide, &RightSide::elimina, this, &MainWindow::elimina);
    connect(rightSide, &RightSide::modifica, this, &MainWindow::modifica);
    connect(rightSide, &RightSide::salva, this, &MainWindow::salva);
    connect(rightSide, &RightSide::preferito, this, &MainWindow::preferito);

    connect(rightSide, &RightSide::sortNome, this, [this, biblioteca](){ biblioteca->sort_nome(); showMainWindow(); });
    connect(rightSide, &RightSide::sortData, this, [this, biblioteca](){ biblioteca->sort_anno(); showMainWindow(); });

    connect(this, &MainWindow::file_Eliminato, this, &MainWindow::showMainWindow);

    connect(rightSide, &RightSide::showPreferiti, this, [this](){
        this->p = true; 
        rightSide->showpreferiti();
    });
    
    connect(rightSide, &RightSide::showGenerale, this, [this, biblioteca](){
        this->p = false;
        switch (tipoFiles)
        {
            case 0:
                rightSide->setLista(biblioteca->getArchivio());
                break;
            case 1:
                rightSide->setLista(biblioteca->getLibri());
                break;
            case 2:
                rightSide->setLista(biblioteca->getFilm());
                break;
            case 3:
                rightSide->setLista(biblioteca->getSerie());
                break;
            default:
                break;
        }
    });

    connect(rightSide, &RightSide::layoutChanged, this, &MainWindow::showMainWindow);

    connect(rightSide, &RightSide::testoCercato, this, &MainWindow::cercazioneFiles);

    connect(leftSide, &LeftSide::listaCambiataInTutto, this, [this](){
            if(tipoFiles != 0){
                tipoFiles = 0;
                showMainWindow();
                }
            });
    connect(leftSide, &LeftSide::listaCambiataInLibri, this, [this](){
            if(tipoFiles != 1){
                tipoFiles = 1;
                showMainWindow();
                }
            });
    connect(leftSide, &LeftSide::listaCambiataInFilm, this, [this](){
            if(tipoFiles != 2){
                tipoFiles = 2;
                showMainWindow();
                }
            });
    connect(leftSide, &LeftSide::listaCambiataInSerie, this, [this](){
            if(tipoFiles != 3){
                tipoFiles = 3;
                showMainWindow();
                }
            });
}

void MainWindow::cercazioneFiles(const QString& t){

    rightSide->resetUpperBar();

    std::string testo = t.toStdString();

    switch (tipoFiles)
    {
    case 0:
        rightSide->setLista(finder(biblioteca->getArchivio(), testo,
                                   [](File_Generico* f){ return f->GetNome(); }));
        break;
    case 1:
        rightSide->setLista(finder(biblioteca->getLibri(), testo,
                                   [](File_Generico* f){ return f->GetNome(); }));
        break;
    case 2:
        rightSide->setLista(finder(biblioteca->getFilm(), testo,
                                   [](File_Generico* f){ return f->GetNome(); }));
        break;
    case 3:
        rightSide->setLista(finder(biblioteca->getSerie(), testo,
                                   [](File_Generico* f){ return f->GetNome(); }));
        break;
    default:
        break;
    }
}


void MainWindow::modifica(File_Generico* file){

    QWidget *modifica = new QWidget();
    QHBoxLayout *sotto = new QHBoxLayout();
    
    QPushButton *annulla = new QPushButton("Annulla");
    QShortcut* escShortcut = new QShortcut(QKeySequence(Qt::Key_Escape), modifica);
    connect(escShortcut, &QShortcut::activated, this, [annulla](){
        annulla->click();
    });
    QPushButton *conferma = new QPushButton("Conferma");
    QShortcut* confShortcut = new QShortcut(QKeySequence(Qt::Key_Return), modifica);
    connect(confShortcut, &QShortcut::activated, this, [conferma](){
        conferma->click();
    });

    sotto->addWidget(annulla, 0, Qt::AlignLeft);
    sotto->addWidget(conferma, 0, Qt::AlignRight);

    ModificaVisitor *visitor = new ModificaVisitor();
    file->Accept(*visitor);
    QVBoxLayout* intero = new QVBoxLayout();
    intero->addWidget(visitor->GetWidget());
    intero->addLayout(sotto);
    modifica->setLayout(intero);
    
    stackedWidget->addWidget(modifica);
    stackedWidget->setCurrentWidget(modifica);

    connect(annulla, &QPushButton::clicked, this, [this, modifica, file, visitor]() {
        stackedWidget->removeWidget(modifica);
        modifica->deleteLater();
        rightSide->updateLayout(biblioteca->getArchivio());
        leftSide->updateTree();
        delete visitor;

        if(auto e = dynamic_cast<File_Episodio*>(file)){
            mostraEpisodio(e);  
        } else {
            mostraWindow(file);
        }
    });

    connect(conferma, &QPushButton::clicked, this, [this, file, visitor, modifica]() {
        if (visitor->confermaModifiche(file, biblioteca)) {
            stackedWidget->removeWidget(modifica);
            modifica->deleteLater();
            rightSide->updateLayout(biblioteca->getArchivio());
            leftSide->updateTree();
            biblioteca->isSaved = false;
            
            if(auto e = dynamic_cast<File_Episodio*>(file)){
                mostraEpisodio(e);
            } else {
                mostraWindow(file);
            }
            delete visitor;
        }
    });



}


void MainWindow::preferito(File_Generico* file){
    file->togglePreferito();
    biblioteca->isSaved = false;
    if(!file->IsPreferito() && p) rightSide->showPreferiti();
}

void MainWindow::elimina(File_Generico* file){

    QMessageBox::StandardButton conferma;
    conferma = QMessageBox::question(this,
                                "Conferma eliminazione",
                                "Sei sicuro di voler eliminare questo elemento?",
                                QMessageBox::Yes | QMessageBox::No);

    if (conferma == QMessageBox::No) {
        return;
    }

    if(auto e = dynamic_cast<File_Episodio*>(file)){
        File_Serie* s = e->GetSerieFile();
        s->RimuoviEpisodio(e);
    
        if(currentMostraWidget){
            stackedWidget->removeWidget(currentMostraWidget);
            currentMostraWidget->deleteLater();
            currentMostraWidget = nullptr;
        }
    
        delete e;
        mostraWindow(s);
        
    }else{
        if (currentMostraWidget) {
            stackedWidget->removeWidget(currentMostraWidget);
            currentMostraWidget->deleteLater();
            currentMostraWidget = nullptr;
        }

        biblioteca->killFile(file);
        rightSide->pulisci();
        rightSide->setLista(biblioteca->getArchivio());
        
    	emit file_Eliminato();
    }
    biblioteca->isSaved = false;
}

void MainWindow::mostraWindow(File_Generico* file){
    
    if (currentMostraWidget) {
        stackedWidget->removeWidget(currentMostraWidget);
        currentMostraWidget->deleteLater();
        currentMostraWidget = nullptr;
    }

    QWidget* mostra = new QWidget();

    MostraVisitorHelper* a = new MostraVisitorHelper(file, mostra);

    QPushButton* indietro = new QPushButton("Indietro");
    QShortcut* escShortcut = new QShortcut(QKeySequence(Qt::Key_Escape), mostra);
    connect(escShortcut, &QShortcut::activated, indietro, &QPushButton::click);
    
    QPushButton* modificaBtn = new QPushButton("Modifica");
    
    QPushButton* salvaBtn = new QPushButton("Salva su disco");
    QShortcut* salvaShortcut = new QShortcut(QKeySequence("Ctrl+S"), mostra);
    connect(salvaShortcut, &QShortcut::activated, salvaBtn, &QPushButton::click);
    
    QPushButton* eliminaBtn = new QPushButton("Elimina");

    QPushButton* toggle_preferito = new QPushButton();
    toggle_preferito->setIcon(file->IsPreferito() ? *preferito_si : *preferito_no);
    toggle_preferito->setIconSize(QSize(24, 24));  
    toggle_preferito->setFixedSize(32, 32);        

    QHBoxLayout* sopra = new QHBoxLayout();
    sopra->addWidget(indietro, 0, Qt::AlignLeft);
    sopra->addWidget(modificaBtn, 0, Qt::AlignCenter);
    sopra->addWidget(salvaBtn, 0, Qt::AlignCenter);
    sopra->addWidget(eliminaBtn, 0, Qt::AlignCenter);
    sopra->addWidget(toggle_preferito, 0, Qt::AlignRight);

    toggle_preferito->setFlat(true);
    toggle_preferito->setStyleSheet("background-color: transparent; border: none;");

    QVBoxLayout* intero = new QVBoxLayout();
    intero->addLayout(sopra);
    intero->addWidget(a);
    mostra->setLayout(intero);

    stackedWidget->addWidget(mostra);
    stackedWidget->setCurrentWidget(mostra);

    currentMostraWidget = mostra;

    File_Serie* s = dynamic_cast<File_Serie*>(file);
    if(s){
        currentSerie = s;
        currentSerieWidget = mostra;
        connect(a, &MostraVisitorHelper::AggiuntaEpisodio, this, &MainWindow::showAddEpisodioWidget);
        QShortcut* addEpisodeShortcut = new QShortcut(QKeySequence("Ctrl+N"), mostra);
        connect(addEpisodeShortcut, &QShortcut::activated, this, &MainWindow::showAddEpisodioWidget);

        connect(a, &MostraVisitorHelper::ImportaEpisodio, this, &MainWindow::importaEpisodio);
        QShortcut* importEpisodeShortcut = new QShortcut(QKeySequence("Ctrl+O"), mostra);
        connect(importEpisodeShortcut, &QShortcut::activated, this, [this]() {
            importaEpisodio(currentSerie);
        });

        connect(a, &MostraVisitorHelper::EpisodioSelezionato, this, &MainWindow::mostraEpisodio);
        connect(a, &MostraVisitorHelper::EpisodioElimina, this, &MainWindow::elimina);
        connect(a, &MostraVisitorHelper::EpisodioModifica, this, &MainWindow::modifica);
        connect(a, &MostraVisitorHelper::EpisodioSalva, this, &MainWindow::salva);
    }

    connect(indietro, &QPushButton::clicked, this, [this, mostra](){
        stackedWidget->removeWidget(mostra);
        mostra->deleteLater();   
        currentMostraWidget = nullptr;
        showMainWindow();
        leftSide->updateTree();
        stackedWidget->setCurrentWidget(principale);
    });

    connect(toggle_preferito, &QPushButton::clicked, [this, file, toggle_preferito]() {
        file->togglePreferito();
        toggle_preferito->setIcon(file->IsPreferito() ? *preferito_si : *preferito_no);
    });

    connect(modificaBtn, &QPushButton::clicked, this, [this, file]() {
    modifica(file);
    });

    connect(salvaBtn, &QPushButton::clicked, this, [this, file]() {
    salva(file);
    });

    connect(eliminaBtn, &QPushButton::clicked, this, [this, file]() {
    elimina(file);
    });
}

void MainWindow::mostraEpisodio(File_Episodio* ep) {
    if (!ep) return;

    if (currentEpisodioWidget) {
        stackedWidget->removeWidget(currentEpisodioWidget);
        currentEpisodioWidget->deleteLater();
        currentEpisodioWidget = nullptr;
    }
    
    QWidget* mostra = new QWidget();

    MostraVisitorHelper* episodio = new MostraVisitorHelper(static_cast<File_Generico*>(ep), mostra);
    if (episodio->parentWidget()) {
    episodio->setParent(nullptr);
    }
    QPushButton* indietro = new QPushButton("Indietro");
    QShortcut* escShortcut = new QShortcut(QKeySequence(Qt::Key_Escape), mostra);
    connect(escShortcut, &QShortcut::activated, indietro, &QPushButton::click);
    
    QPushButton* modificaBtn = new QPushButton("Modifica");

    QPushButton* eliminaBtn = new QPushButton("Elimina");

    QPushButton* toggle_preferito = new QPushButton();
    toggle_preferito->setIcon(ep->IsPreferito() ? *preferito_si : *preferito_no);
    toggle_preferito->setIconSize(QSize(24, 24));  
    toggle_preferito->setFixedSize(32, 32);


    QHBoxLayout* sopra = new QHBoxLayout();
    sopra->addWidget(indietro, 0, Qt::AlignLeft);
    sopra->addWidget(modificaBtn, 0, Qt::AlignCenter);
    sopra->addWidget(eliminaBtn, 0, Qt::AlignCenter);
    sopra->addWidget(toggle_preferito, 0, Qt::AlignRight);

    toggle_preferito->setFlat(true);
    toggle_preferito->setStyleSheet("background-color: transparent; border: none;");

    QVBoxLayout* intero = new QVBoxLayout();
    intero->addLayout(sopra);
    intero->addWidget(episodio);
    mostra->setLayout(intero);

    stackedWidget->addWidget(mostra);
    stackedWidget->setCurrentWidget(mostra);

    currentEpisodioWidget = mostra;

    connect(indietro, &QPushButton::clicked, [this, mostra, ep]() {
        stackedWidget->removeWidget(mostra);
        mostra->deleteLater();
        currentEpisodioWidget = nullptr;
        rightSide->updateLayout(biblioteca->getArchivio());
        leftSide->updateTree();
        mostraWindow(ep->GetSerieFile());
    });

    connect(toggle_preferito, &QPushButton::clicked, [this, ep, toggle_preferito]() {
        ep->togglePreferito();
        toggle_preferito->setIcon(ep->IsPreferito() ? *preferito_si : *preferito_no);
    });

    connect(modificaBtn, &QPushButton::clicked, this, [this, ep]() {
        modifica(ep);
    });

    connect(eliminaBtn, &QPushButton::clicked, this, [this, ep]() {
        elimina(ep);
    });    

}

void MainWindow::showAddFileWidget(int index){
    switch(index){
        case 0:
            stackedWidget->setCurrentWidget(aggiuntaLibro);
            break;
        case 1:
            stackedWidget->setCurrentWidget(aggiuntaFilm);
            break;
        case 2:
            stackedWidget->setCurrentWidget(aggiuntaSerie);
            break;
        default:
            break;
    }
}

void MainWindow::showAddEpisodioWidget(){
    if(!episodioWidget){
        episodioWidget = new AddEpisodioWidget(currentSerie, this);

        

        connect(episodioWidget, &AddEpisodioWidget::FileAggiunto, this, [this]() {
            stackedWidget->removeWidget(episodioWidget);
            episodioWidget->deleteLater();
            rightSide->updateLayout(biblioteca->getArchivio());
            leftSide->updateTree();
            episodioWidget = nullptr;
            mostraWindow(currentSerie);
        });
        connect(episodioWidget, &AddEpisodioWidget::FileAnnullato, this, [this]() {
            stackedWidget->removeWidget(episodioWidget);
            episodioWidget->deleteLater();
            rightSide->updateLayout(biblioteca->getArchivio());
            leftSide->updateTree();
            episodioWidget = nullptr;
            mostraWindow(currentSerie);
        });
        stackedWidget->addWidget(episodioWidget);
    }else{
        episodioWidget->setSerie(currentSerie);
    }
    stackedWidget->setCurrentWidget(episodioWidget);
}

void MainWindow::DettagliIndietro(){
    stackedWidget->setCurrentWidget(principale);
}

void MainWindow::showMainWindow() {
    stackedWidget->setCurrentWidget(principale);
    switch (tipoFiles)
    {
    case 0:
        rightSide->setLista(biblioteca->getArchivio());
        break;
    case 1:
        rightSide->setLista(biblioteca->getLibri());
        break;
    case 2:
        rightSide->setLista(biblioteca->getFilm());
        break;
    case 3:
        rightSide->setLista(biblioteca->getSerie());
        break;
    default:
        break;
    }
    rightSide->resetUpperBar();
    rightSide->pulisci();
    leftSide->updateTree();
    QWidget *focus = QApplication::focusWidget();
    if(focus) focus->clearFocus();
    principale->setFocus();
}

void MainWindow::importaBiblioteca() {
    if ((biblioteca->getArchivio().size()) && !biblioteca->isSaved) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Salva biblioteca?", "La biblioteca corrente non è salvata. Vuoi salvarla prima di importare una nuova biblioteca?",
                                      QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (reply == QMessageBox::Cancel) return;
        if (reply == QMessageBox::Yes) {
            QString savePath = QFileDialog::getSaveFileName(this, "Salva biblioteca", "", "File JSON (*.json)");
            if (!savePath.isEmpty()) {
                try {
                    saveAsJson(biblioteca, savePath.toStdString());
                } catch (const std::exception& e) {
                    QMessageBox::warning(this, "Errore", QString::fromStdString(e.what()));
                    return;
                }
            } else {
                return;
            }
        }
    }

    QString filePath = QFileDialog::getOpenFileName(this, "Importa biblioteca", "", "File JSON (*.json)");
    if (filePath.isEmpty()) return;

    Biblioteca* nuovaBib = creaBibliotecaDaJson(filePath.toStdString());
    if (!nuovaBib) {
        QMessageBox::warning(this, "Errore", "Impossibile caricare la biblioteca.");
        return;
    }

    biblioteca->clear();

    for (auto f : nuovaBib->getArchivio()) {
        if (f) {
            biblioteca->addFile(f->clone());
        }
    }
    biblioteca->isSaved = true;

    delete nuovaBib;

    rightSide->updateLayout(biblioteca->getArchivio());
    leftSide->updateTree();

    showMainWindow();
}

void MainWindow::importaFile() {
    QString filePath = QFileDialog::getOpenFileName(
        this, "Importa file", "", "File JSON (*.json)");
    if (filePath.isEmpty()) return;

    File_Generico* nuovoFile = creaFileDaJson(filePath.toStdString());
    if (!nuovoFile || dynamic_cast<File_Episodio*>(nuovoFile)) {
        QMessageBox::warning(this, "Errore", "Impossibile caricare il file.");
        return;
    }



    if (!biblioteca->check(nuovoFile)) {
        std::string tipo;
        if (dynamic_cast<File_Libro*>(nuovoFile)) tipo = "Il libro";
        else if (dynamic_cast<File_Film*>(nuovoFile)) tipo = "Il film";
        else if (dynamic_cast<File_Serie*>(nuovoFile)) tipo = "La serie";
        else tipo = "File";

        QMessageBox::warning(this, "Errore", 
            QString::fromStdString(tipo + " \"" + nuovoFile->GetNome() + "\" è già presente nella biblioteca."));
        delete nuovoFile; 
        return;
    }

    biblioteca->addFile(nuovoFile);

    rightSide->updateLayout(biblioteca->getArchivio());
    leftSide->updateTree();
}

void MainWindow::importaEpisodio(File_Serie* serie){
    QString filePath = QFileDialog::getOpenFileName(
        this, "Importa episodio", "", "File JSON (*.json)");
    if (filePath.isEmpty()) return;

    File_Generico* nuovoEpisodio = creaFileDaJson(filePath.toStdString());
    auto epi = static_cast<File_Episodio*>(nuovoEpisodio);
    if (!nuovoEpisodio || !epi) {
        QMessageBox::warning(this, "Errore", "Impossibile caricare il file.");
        return;
    }

    if (!serie->check(epi, nullptr)){
        QMessageBox::warning(this, "Errore", 
            QString::fromStdString("L'episodio \"" + nuovoEpisodio->GetNome() + "\" è già presente nella biblioteca."));
        delete nuovoEpisodio; 
        return;
    }
    
    if (!serie->postolibero(epi, nullptr)){
        QMessageBox::warning(this, "Errore", 
            QString::fromStdString(
                "La serie \"" + serie->GetNome() +
                "\" contiene già un episodio numero \"" + std::to_string(epi->GetNumeroEpisodio()) +
                "\" nella stagione \"" + std::to_string(epi->GetNumeroStagione()) +
                "\", modificare il file .JSON e riprovare !"
            )
        );    
        delete nuovoEpisodio; 
        return;
    }
        
    serie->AggiungiEpisodio(static_cast<File_Episodio*>(nuovoEpisodio));
    mostraWindow(serie);
}

void MainWindow::salvaBiblioteca() {

    if(biblioteca->getArchivio().size() == 0){
        QMessageBox::warning(this, "Errore", QString::fromStdString("inutile salvare una biblioteca vuota"));
        return;       
    }


    QString filePath = QFileDialog::getSaveFileName(
        this,
        "Salva biblioteca",
        "",
        "File JSON (*.json)"
    );

    if (filePath.isEmpty()) return;

    try {
        saveAsJson(biblioteca, filePath.toStdString());
        biblioteca->isSaved = true;
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Errore", QString::fromStdString(e.what()));
    }
}

void MainWindow::salva(File_Generico* file){
    QString filePath = QFileDialog::getSaveFileName(
        this,
        "Salva file singolo",
        "",
        "File JSON (*.json)"
    );

    if (filePath.isEmpty()) return;

    try {
        saveAsJson(file, filePath.toStdString());
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Errore", QString::fromStdString(e.what()));
    }
}
