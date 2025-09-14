#include "ModificaVisitor.hpp"

#include "../CLASSI_FILE/File_Generico.hpp"
#include "../CLASSI_FILE/File_Film.hpp"
#include "../CLASSI_FILE/File_Episodio.hpp"
#include "../CLASSI_FILE/File_Serie.hpp"
#include "../CLASSI_FILE/File_Libro.hpp"
#include "../CLASSI_FILE/Container.hpp"

#include <QLabel>
#include <QPixmap>
#include <QTreeWidget>
#include <QString>
#include <QLineEdit>
#include <QSpinBox>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>

void ModificaVisitor::Visit(File_Generico& file){
    if(widget) delete widget;
    widget = new QWidget();
    layout = new QVBoxLayout(widget);

    sopra = new QHBoxLayout();
    sotto = new QHBoxLayout();
    sottoSx = new QFormLayout();
    sottoDx = new QFormLayout();

    nome = new QLineEdit();
    autore = new QLineEdit();
    genere = new QLineEdit();
    anno = new QSpinBox(); anno->setRange(0,2025); anno->setValue(file.GetAnno());

    nome->setText(QString::fromStdString(file.GetNome()));
    autore->setText(QString::fromStdString(file.GetAutore()));
    genere->setText(QString::fromStdString(file.GetGenere()));


    sottoSx->addRow("Autore", autore);
    sottoSx->addRow("Genere", genere);
    sottoSx->addRow("Anno", anno);

    sotto->addLayout(sottoSx);
    sotto->addLayout(sottoDx);
    widgetIcona = new QLabel();
    widgetIcona->setAlignment(Qt::AlignCenter);

    sopra->addWidget(widgetIcona);

    sopra->addWidget(new QLabel("Nome"));
    sopra->addWidget(nome);

    layout->addLayout(sopra);
    layout->addLayout(sotto); 
    
}

void ModificaVisitor::Visit(File_Video& video){
    Visit(static_cast<File_Generico&>(video));
    durata = new QSpinBox(); durata->setRange(0,1000); durata->setValue(video.GetDurata()); 
    regista = new QLineEdit(); regista->setText(QString::fromStdString(video.GetRegista()));
    casa_di_produzione = new QLineEdit(); casa_di_produzione->setText(QString::fromStdString(video.GetCasaDiProduzione()));

    sottoDx->addRow("Durata",durata);
    sottoDx->addRow("Regista",regista);
    sottoDx->addRow("casa produttrice",casa_di_produzione);
}

void ModificaVisitor::Visit(File_Film& film){
    Visit(static_cast<File_Video&>(film));
    icona = new QIcon(":/IMMAGINI/film_nero.png");
    widgetIcona->setPixmap(icona->pixmap(200,200));
    oscar = new QCheckBox();
    film.GetOscar() ? oscar->setChecked(true) : oscar->setChecked(false);
    sottoDx->addRow("vincitore di oscar", oscar);
}

void ModificaVisitor::Visit(File_Episodio& episodio){
    Visit(static_cast<File_Video&>(episodio));
    icona = new QIcon(":/IMMAGINI/episodio_nero.png");
    widgetIcona->setPixmap(icona->pixmap(200,200));
    serie = new QLineEdit(QString::fromStdString(episodio.GetSerieTV()));
    numero_stagione = new QSpinBox(); numero_stagione->setRange(0,100); numero_stagione->setValue(episodio.GetNumeroStagione()); 
    numero_episodio = new QSpinBox(); numero_episodio->setRange(0,100); numero_episodio->setValue(episodio.GetNumeroEpisodio()); 

    serie->setReadOnly(true);
    autore->setReadOnly(true);
    genere->setReadOnly(true);
    casa_di_produzione->setReadOnly(true);

    sottoDx->addRow("<b>Serie TV</b>",serie);
    sottoDx->addRow("Numero Stagione",numero_stagione);
    sottoDx->addRow("Numero Episodio",numero_episodio);

    QLabel *info = new QLabel("i campi \"autore\", \"genere\", \"casa di produzione\" e \"serie TV\"\n"
                                 "non sono modificabili essendo appartenenti alla serie dell'episodio.\n"
                                 "se si desidera modificarli si torni alla schermata della serie e li si "
                                 "modifichi per tutti gli episodi contemporaneamente.");

    info->setAlignment(Qt::AlignCenter);
    layout->addWidget(info);
}

void ModificaVisitor::Visit(File_Serie& serie){
    Visit(static_cast<File_Generico&>(serie));
    icona = new QIcon(":/IMMAGINI/serie_nero.png");
    widgetIcona->setPixmap(icona->pixmap(200,200));
    casa_di_produzione_serie = new QLineEdit(); casa_di_produzione_serie->setText(QString::fromStdString(serie.GetCasaDiProduzione()));

    sottoDx->addRow("Casa produttrice", casa_di_produzione_serie);
}

void ModificaVisitor::Visit(File_Libro& libro){
    Visit(static_cast<File_Generico&>(libro));
    icona = new QIcon(":/IMMAGINI/libro_nero.png");
    widgetIcona->setPixmap(icona->pixmap(200,200));
    pagine = new QSpinBox(); pagine->setRange(0,9999); pagine->setValue(libro.GetPagine());
    editore = new QLineEdit(); editore->setText(QString::fromStdString(libro.GetEditore()));

    sottoDx->addRow("Pagine", pagine);
    sottoDx->addRow("Editore",editore);
}

bool ModificaVisitor::confermaModifiche(File_Generico* file, Biblioteca* b) const {

    if (nome->text().isEmpty() || autore->text().isEmpty()) {
        QMessageBox::warning(widget, "Errore", "nome e/o autore non possono essere lasciati vuoti");
        return false;
    }

    File_Generico *tmp = file->clone();

    tmp->SetNome(nome->text().toStdString());
    tmp->SetAutore(autore->text().toStdString());
    tmp->SetGenere(genere->text().toStdString());
    tmp->SetAnno(anno->value());

    if (auto libro = dynamic_cast<File_Libro*>(tmp)) {
        libro->SetPagine(pagine->value());
        libro->SetEditore(editore->text().toStdString());
    }
    else if (auto film = dynamic_cast<File_Film*>(tmp)) {
        film->SetDurata(durata->value());
        film->SetRegista(regista->text().toStdString());
        film->SetCasaDiProduzione(casa_di_produzione->text().toStdString());
        film->SetOscar(oscar->isChecked());
    }
    else if (auto serie = dynamic_cast<File_Serie*>(tmp)) {
        serie->SetCasaDiProduzione(casa_di_produzione_serie->text().toStdString());
    }
    else if (auto ep = dynamic_cast<File_Episodio*>(tmp)) {
        ep->SetDurata(durata->value());
        ep->SetRegista(regista->text().toStdString());
        ep->SetNumeroStagione(numero_stagione->value());
        ep->SetNumeroEpisodio(numero_episodio->value());

        File_Serie* serie_padre = ep->GetSerieFile();
        if (serie_padre && !serie_padre->postolibero(ep, static_cast<File_Episodio*>(file))) {
            QMessageBox::warning(widget, "Errore",
                "Esiste già un episodio con stesso numero di stagione e numero episodio");
            delete tmp;
            return false;
        }
    }

    if (!b->check(tmp, file)) {
        QMessageBox::warning(widget, "Errore", "Articolo già presente nella biblioteca digitale");
        delete tmp;
        return false;
    }


    if(auto serie = dynamic_cast<File_Serie*>(file)) {
        serie->SetNome(tmp->GetNome());
        serie->SetAutore(tmp->GetAutore());
        serie->SetGenere(tmp->GetGenere());
        serie->SetAnno(tmp->GetAnno());
        serie->SetCasaDiProduzione(dynamic_cast<File_Serie*>(tmp)->GetCasaDiProduzione());
    }
    else if(auto film = dynamic_cast<File_Film*>(file)) {
        film->SetNome(tmp->GetNome());
        film->SetAutore(tmp->GetAutore());
        film->SetGenere(tmp->GetGenere());
        film->SetAnno(tmp->GetAnno());
        film->SetDurata(dynamic_cast<File_Film*>(tmp)->GetDurata());
        film->SetRegista(dynamic_cast<File_Film*>(tmp)->GetRegista());
        film->SetCasaDiProduzione(dynamic_cast<File_Film*>(tmp)->GetCasaDiProduzione());
        film->SetOscar(dynamic_cast<File_Film*>(tmp)->GetOscar());
    }
    else if(auto libro = dynamic_cast<File_Libro*>(file)) {
        libro->SetNome(tmp->GetNome());
        libro->SetAutore(tmp->GetAutore());
        libro->SetGenere(tmp->GetGenere());
        libro->SetAnno(tmp->GetAnno());
        libro->SetPagine(dynamic_cast<File_Libro*>(tmp)->GetPagine());
        libro->SetEditore(dynamic_cast<File_Libro*>(tmp)->GetEditore());
    }
    else if(auto episodio = dynamic_cast<File_Episodio*>(file)) {
        episodio->SetNome(tmp->GetNome());
        episodio->SetAutore(tmp->GetAutore());
        episodio->SetGenere(tmp->GetGenere());
        episodio->SetAnno(tmp->GetAnno());
        episodio->SetDurata(dynamic_cast<File_Episodio*>(tmp)->GetDurata());
        episodio->SetRegista(dynamic_cast<File_Episodio*>(tmp)->GetRegista());
        episodio->SetNumeroStagione(dynamic_cast<File_Episodio*>(tmp)->GetNumeroStagione());
        episodio->SetNumeroEpisodio(dynamic_cast<File_Episodio*>(tmp)->GetNumeroEpisodio());
    }
    delete tmp;
    return true;
}

void ModificaVisitor::Visit(Biblioteca&){}

QWidget* ModificaVisitor::GetWidget() const {
    return widget;
}
