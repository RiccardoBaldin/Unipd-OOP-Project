#include "ToJson.hpp"
#include <QJsonDocument>
#include <QCoreApplication>
#include <filesystem>

void saveAsJson(File_Generico* file, std::string filePath) {

    if (std::filesystem::path(filePath).extension() != ".json") {
        filePath += ".json";
    }

    JsonVisitor visitor;
    file->Accept(visitor);
    QJsonObject jsonVisitor = visitor.GetJson();

    std::ofstream file_1(filePath);
    if (!file_1) {
        throw std::runtime_error("Impossibile aprire il file per la scrittura.");
    }
    file_1 << QJsonDocument(jsonVisitor)
               .toJson(QJsonDocument::Indented)
               .toStdString();
    file_1.close();
}

void saveAsJson(Biblioteca* biblioteca, std::string filePath) {

    if (std::filesystem::path(filePath).extension() != ".json") {
        filePath += ".json";
    }

    JsonVisitor visitor;
    biblioteca->Accept(visitor);
    QJsonObject jsonVisitor = visitor.GetJson();

    std::ofstream file_1(filePath);
    if (!file_1) {
        throw std::runtime_error("Impossibile aprire il file per la scrittura.");
    }
    file_1 << QJsonDocument(jsonVisitor)
               .toJson(QJsonDocument::Indented)
               .toStdString();
    file_1.close();
}