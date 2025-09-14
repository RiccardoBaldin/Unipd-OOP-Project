#include "FromJson.hpp"

#include "../CLASSI_FILE/Container.hpp"
#include "../CLASSI_FILE/File_Generico.hpp"
#include "../CLASSI_FILE/File_Video.hpp"
#include "../CLASSI_FILE/File_Episodio.hpp"
#include "../CLASSI_FILE/File_Film.hpp"
#include "../CLASSI_FILE/File_Serie.hpp"
#include "../CLASSI_FILE/File_Libro.hpp"

File_Generico* creaFileDaJsonObject(const QJsonObject& obj) {
    std::string tipo = obj["tipo"].toString().toStdString();
    std::string nome = obj["nome"].toString().toStdString();
    std::string autore = obj["autore"].toString().toStdString();
    std::string genere = obj["genere"].toString().toStdString();
    unsigned int anno = obj["anno"].toInt();
    bool preferito = obj["preferito"].toBool();

    if (tipo == "episodio") {
        unsigned int durata = obj["durata"].toInt();
        std::string casa_di_produzione = obj["casa_di_produzione"].toString().toStdString();
        std::string regista = obj["regista"].toString().toStdString();
        unsigned int numero_stagione = obj["numero_stagione"].toInt();
        unsigned int numero_episodio = obj["numero_episodio"].toInt();
        std::string serieTV = obj["serie"].toString().toStdString();
        File_Episodio* episodio = new File_Episodio(nome, autore, genere, anno, durata, casa_di_produzione, regista, numero_stagione, numero_episodio, serieTV);
        if(preferito) episodio->togglePreferito();
        return episodio;

    }
    if (tipo == "film") {
        unsigned int durata = obj["durata"].toInt();
        std::string casa_di_produzione = obj["casa_di_produzione"].toString().toStdString();
        std::string regista = obj["regista"].toString().toStdString();
        bool oscar = obj["oscar"].toBool();
        File_Film* film = new File_Film(nome, autore, genere, anno, durata, casa_di_produzione, regista, oscar);
        if(preferito) film->togglePreferito();
        return film;

    }
    if (tipo == "libro") {
        unsigned int pagine = obj["numero_pagine"].toInt();
        std::string editore = obj["editore"].toString().toStdString();
        File_Libro* libro = new File_Libro(nome, autore, genere, anno, pagine, editore);
        if(preferito) libro->togglePreferito();
        return libro;

    }
    if (tipo == "serie") {
        unsigned int numero_stagioni = obj["numero_stagioni"].toInt();
        unsigned int numero_episodi = obj["numero_episodi"].toInt();
        std::string casa = obj["casa_di_produzione"].toString().toStdString();
        File_Serie* serie = new File_Serie(nome, autore, genere, anno, numero_stagioni, numero_episodi, casa);
        if(preferito) serie->togglePreferito();

        if (obj.contains("episodi") && obj["episodi"].isArray()) {
            QJsonArray episodiArray = obj["episodi"].toArray();
            for (const auto& e : episodiArray) {
                QJsonObject epObj = e.toObject();
                std::string epNome = epObj["nome"].toString().toStdString();
                unsigned int durata = epObj["durata"].toInt();
                std::string regista = epObj["regista"].toString().toStdString();
                unsigned int numero_stagione = epObj["numero_stagione"].toInt();
                unsigned int numero_episodio = epObj["numero_episodio"].toInt();
                bool epPreferito = epObj["preferito"].toBool();
                
                File_Episodio* ep = new File_Episodio(
                    epNome, autore, genere, anno, durata, "",
                    regista, numero_stagione, numero_episodio, nome
                );
                if(epPreferito) ep->togglePreferito();
                serie->AggiungiEpisodio(ep);
            }
        }
        return serie;
    }
    return nullptr;
}

Biblioteca* creaBibliotecaDaJson(const std::string& path) {
    QJsonDocument doc = caricaJsonDaFile(path);
    if (doc.isNull()) return nullptr;

    QJsonArray archivio;
    if (doc.isArray()) {
        archivio = doc.array();
    } else if (doc.isObject() && doc.object().contains("biblioteca")) {
        archivio = doc.object()["biblioteca"].toArray();
    } else {
        qWarning() << "JSON non contiene una biblioteca valida";
        return nullptr;
    }

    Biblioteca* biblioteca = new Biblioteca();
    for (const auto& a : archivio) {
        if (a.isObject()) {
            File_Generico* file = creaFileDaJsonObject(a.toObject());
            if (file && biblioteca->check(file)) {
                biblioteca->addFile(file);
            } else {
                delete file; // evitare memory leak
            }
        }
    }

    return biblioteca;
}

QJsonDocument caricaJsonDaFile(const std::string& path) {
    QFile file(QString::fromStdString(path));
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Impossibile aprire il file:" << QString::fromStdString(path);
        return QJsonDocument();
    }
    QByteArray data = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "Errore parsing JSON:" << parseError.errorString();
        return QJsonDocument();
    }
    return doc;
}

File_Generico* creaFileDaJson(const std::string& path) {
    QJsonDocument doc = caricaJsonDaFile(path);
    if (!doc.isObject()) {
        qWarning() << "Il JSON non è un oggetto valido per un singolo file.";
        return nullptr;
    }
    return creaFileDaJsonObject(doc.object());
}
