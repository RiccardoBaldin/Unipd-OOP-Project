#include "MostraVisitor.hpp"

#include "../CLASSI_FILE/File_Generico.hpp"
#include "../CLASSI_FILE/File_Film.hpp"
#include "../CLASSI_FILE/File_Episodio.hpp"
#include "../CLASSI_FILE/File_Serie.hpp"
#include "../CLASSI_FILE/File_Libro.hpp"
#include "../GUI/riga_lista.hpp"

#include <QLabel>
#include <QPixmap>
#include <QTreeWidget>
#include <set>
#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>

void MostraVisitor::Visit(File_Generico& file) {

    delete widget;
    widget = new QWidget();
    layout = new QVBoxLayout(widget);

    sopra = new QHBoxLayout();
    sotto = new QHBoxLayout();
    sottoSx = new QVBoxLayout();
    sottoDx = new QVBoxLayout();

    nome = new QLabel("Nome: <b>" + QString::fromStdString(file.GetNome()) + "</b>");
    autore = new QLabel("Autore: <b>" + QString::fromStdString(file.GetAutore()) + "</b>");
    genere = new QLabel("Genere: <b>" + (file.GetGenere()!="" ? QString::fromStdString(file.GetGenere()) : "<i>SCONOSCIUTO</i>") + "</b>");
    anno = new QLabel("Anno: <b>" + QString::fromStdString(std::to_string(file.GetAnno())) + "</b>");

    sottoSx->addWidget(autore);
    sottoSx->addWidget(genere);
    sottoSx->addWidget(anno);

    sotto->addLayout(sottoSx);

    widgetIcona = new QLabel();
    widgetIcona->setAlignment(Qt::AlignCenter);

    sopra->addWidget(widgetIcona);

    sopra->addWidget(nome);

    layout->addLayout(sopra);
    layout->addLayout(sotto);

}

void MostraVisitor::Visit(File_Video& video) {
    Visit(static_cast<File_Generico&>(video));
    durata = new QLabel("Durata: <b>" + QString::fromStdString(std::to_string(video.GetDurata())) + "</b>");
    regista = new QLabel("Regista: <b>" + (video.GetRegista()!="" ? QString::fromStdString(video.GetRegista()) : "<i>SCONOSCIUTO</i>") + "</b>");
    casa_di_produzione = new QLabel("Casa Produttrice: <b>" + (video.GetCasaDiProduzione()!="" ? QString::fromStdString(video.GetCasaDiProduzione()) : "<i>SCONOSCIUTO</i>") + "</b>");
    
    sottoDx->addWidget(durata);
    sottoDx->addWidget(regista);
    sottoDx->addWidget(casa_di_produzione);

    sotto->addLayout(sottoDx);
}

void MostraVisitor::Visit(File_Film& film) {
    Visit(static_cast<File_Video&>(film));
    icona = new QIcon(":/IMMAGINI/film_nero.png");
    oscar = new QIcon(":/IMMAGINI/Oscar.png");
    widgetIcona->setPixmap(icona->pixmap(200,200));
    if(film.GetOscar()){
        QLabel *widgetOscar = new QLabel();
        widgetOscar->setPixmap(oscar->pixmap(200,200));
        widgetOscar->setAlignment(Qt::AlignCenter);
        sotto->addWidget(widgetOscar);
    };
}

void MostraVisitor::Visit(File_Episodio& episodio) {
    Visit(static_cast<File_Video&>(episodio));
    icona = new QIcon(":/IMMAGINI/episodio_nero.png");
    widgetIcona->setPixmap(icona->pixmap(200,200));

    serie = new QLabel("Serie TV: <b>" + QString::fromStdString(episodio.GetSerieTV()) + "</b>");
    numero_episodio = new QLabel("Episodio Numero: <b>" + QString::fromStdString(std::to_string(episodio.GetNumeroEpisodio())) + "</b>");
    numero_stagione = new QLabel("Stagione Numero: <b>" + QString::fromStdString(std::to_string(episodio.GetNumeroStagione())) + "</b>");

    sottoDx->addWidget(serie);
    sottoDx->addWidget(numero_stagione);
    sottoDx->addWidget(numero_episodio);

    sotto->addLayout(sottoDx);
    
}

void MostraVisitor::Visit(File_Libro& libro) {
    Visit(static_cast<File_Generico&>(libro));
    icona = new QIcon(":/IMMAGINI/libro_nero.png");
    widgetIcona->setPixmap(icona->pixmap(200,200));

    pagine = new QLabel("Numero di pagine: <b>" + QString::fromStdString(std::to_string(libro.GetPagine())) + "</b>");
    editore = new QLabel("Editore: <b>" + (libro.GetEditore()!="" ? QString::fromStdString(libro.GetEditore()) : "<i>SCONOSCIUTO</i>") + "</b>");

    sottoDx->addWidget(pagine);
    sottoDx->addWidget(editore);

    sotto->addLayout(sottoDx);
}

void MostraVisitor::Visit(File_Serie& serie) {
    Visit(static_cast<File_Generico&>(serie));
    icona = new QIcon(":/IMMAGINI/serie_nero.png");
    widgetIcona->setPixmap(icona->pixmap(200,200));

    numero_stagioni = new QLabel("Numero di Stagioni: <b>" + QString::fromStdString(std::to_string(serie.GetNumeroStagioni())) + "</b>");
    numero_episodi = new QLabel("Numero di Episodi: <b>" + QString::fromStdString(std::to_string(serie.GetNumeroEpisodi())) + "</b>");
    casa_di_produzione_serie = new QLabel("Casa Produttrice: <b>" + (serie.GetCasaDiProduzione()!="" ? QString::fromStdString(serie.GetCasaDiProduzione()) : "<i>SCONOSCIUTO</i>") + "</b>");
    
    sottoDx->addWidget(numero_stagioni);
    sottoDx->addWidget(numero_episodi);
    sottoDx->addWidget(casa_di_produzione_serie);
    
    sotto->addLayout(sottoDx);

    CreaAlberoEpisodi(serie);

    if (albero_episodi) {
        layout->addWidget(albero_episodi);
    }

}

void MostraVisitor::CreaAlberoEpisodi(const File_Serie& serie){

    auto episodi = serie.GetEpisodi();

    std::set<unsigned int> stagioni;
    for(const auto& cit : episodi){
        stagioni.insert(cit->GetNumeroStagione());
    }

    if(stagioni.size()==0) return;

    albero_episodi = new QTreeWidget();
    albero_episodi->setHeaderLabels({"nº", "Episodio"});
    albero_episodi->setAlternatingRowColors(true);
    albero_episodi->setRootIsDecorated(false);

    for(unsigned int s : stagioni){
        QString N_Stagione = QString("Stagione %1").arg(s);
        QTreeWidgetItem* RamoStagione = new QTreeWidgetItem(albero_episodi);
        RamoStagione->setText(0, N_Stagione);
        for(auto ep : episodi){
            if(ep->GetNumeroStagione() < s) continue;
            if(ep->GetNumeroStagione() > s) break;
            QTreeWidgetItem* item = new QTreeWidgetItem(RamoStagione);
            item->setText(0, QString::number(ep->GetNumeroEpisodio()));
            Riga_Lista* riga = new Riga_Lista(static_cast<File_Generico*>(ep), albero_episodi);
            albero_episodi->setItemWidget(item, 1, riga);
        }
    }
    albero_episodi->expandAll();
}

QWidget* MostraVisitor::GetWidget() const {
    return widget;
}

QTreeWidget* MostraVisitor::GetAlberoEpisodi() const {
    return albero_episodi;
}

void MostraVisitor::Visit(Biblioteca&){}