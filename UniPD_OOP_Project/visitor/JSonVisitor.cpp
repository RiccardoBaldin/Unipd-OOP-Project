#include "FileVisitor.hpp"
#include "JSonVisitor.hpp"
#include <QJsonArray>
#include "../CLASSI_FILE/File_Generico.hpp"
#include "../CLASSI_FILE/File_Video.hpp"
#include "../CLASSI_FILE/File_Film.hpp"
#include "../CLASSI_FILE/File_Episodio.hpp"
#include "../CLASSI_FILE/File_Serie.hpp"
#include "../CLASSI_FILE/File_Libro.hpp"
#include "../CLASSI_FILE/Container.hpp"

void JsonVisitor::Visit(File_Generico& file) {
    jsonResult["nome"] = QString::fromStdString(file.GetNome());
    jsonResult["autore"] = QString::fromStdString(file.GetAutore());
    jsonResult["genere"] = QString::fromStdString(file.GetGenere());
    jsonResult["anno"] = static_cast<int>(file.GetAnno());
    jsonResult["preferito"] = file.IsPreferito();
}

void JsonVisitor::Visit(File_Video& video) {
    Visit(static_cast<File_Generico&>(video));
    jsonResult["durata"] = static_cast<int>(video.GetDurata());
    jsonResult["casa_di_produzione"] = QString::fromStdString(video.GetCasaDiProduzione());
    jsonResult["regista"] = QString::fromStdString(video.GetRegista());
    jsonResult["tipo"] = "video";
}

void JsonVisitor::Visit(File_Film& film) {
    Visit(static_cast<File_Video&>(film));
    jsonResult["oscar"] = film.GetOscar();
    jsonResult["tipo"] = "film";
}

void JsonVisitor::Visit(File_Episodio& episodio){
    Visit(static_cast<File_Video&>(episodio));
    jsonResult["numero_stagione"] = static_cast<int>(episodio.GetNumeroStagione());
    jsonResult["numero_episodio"] = static_cast<int>(episodio.GetNumeroEpisodio());
    jsonResult["serie"] = QString::fromStdString(episodio.GetSerieTV());
    jsonResult["tipo"] = "episodio";
} 

void JsonVisitor::Visit(File_Serie& serie) {

    Visit(static_cast<File_Generico&>(serie)); 
    
    jsonResult["numero_stagioni"] = static_cast<int>(serie.GetNumeroStagioni());
    jsonResult["numero_episodi"] = static_cast<int>(serie.GetNumeroEpisodi());
    jsonResult["casa_di_produzione"] = QString::fromStdString(serie.GetCasaDiProduzione()); 
    jsonResult["tipo"] = "serie";

    QJsonArray episodesArray;

    for (auto& episodio : serie.GetEpisodi()) {
        JsonVisitor episodeVisitor;
        episodio->Accept(episodeVisitor);
        episodesArray.append(episodeVisitor.GetJson());
    }

    jsonResult["episodi"] = episodesArray;
}

void JsonVisitor::Visit(File_Libro& libro) {
    Visit(static_cast<File_Generico&>(libro));
    jsonResult["editore"] = QString::fromStdString(libro.GetEditore());
    jsonResult["numero_pagine"] = static_cast<int>(libro.GetPagine());
    jsonResult["tipo"] = "libro";
}


void JsonVisitor::Visit(Biblioteca& biblioteca) {
    QJsonArray filesArray;

    for (auto& filePtr : biblioteca.getArchivio()) {
        if (!filePtr) continue;

        JsonVisitor fileVisitor;
        filePtr->Accept(fileVisitor);
        filesArray.append(fileVisitor.GetJson());
    }

    jsonResult.insert("biblioteca", filesArray);
}



QJsonObject JsonVisitor::GetJson() const {
    return jsonResult;
}