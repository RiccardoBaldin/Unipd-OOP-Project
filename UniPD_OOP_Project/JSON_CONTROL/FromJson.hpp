#ifndef FROMJSON_HPP
#define FROMJSON_HPP

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QDebug>
#include <string>

class File_Generico;
class Biblioteca;

File_Generico* creaFileDaJsonObject(const QJsonObject&);

Biblioteca* creaBibliotecaDaJsonObject(const QJsonValue&);

QJsonDocument caricaJsonDaFile(const std::string&);

File_Generico* creaFileDaJson(const std::string&);

Biblioteca* creaBibliotecaDaJson(const std::string&);


#endif //FROMJSON_HPP