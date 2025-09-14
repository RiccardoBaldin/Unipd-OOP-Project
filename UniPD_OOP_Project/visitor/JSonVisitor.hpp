#ifndef JSONVISITOR_HPP
#define JSONVISITOR_HPP

#include "FileVisitor.hpp"
#include <QJsonObject>

class JsonVisitor : public FileVisitor {
private:
    QJsonObject jsonResult;

public:

    void Visit (File_Generico& file) override ;
    void Visit(File_Video& video) override;
    void Visit(File_Film& film) override;
    void Visit(File_Episodio& episodio) override;
    void Visit(File_Libro& libro) override;
    void Visit(File_Serie& serie) override;
    void Visit(Biblioteca& biblioteca) override;
    QJsonObject GetJson() const;
};

#endif // JSONVISITOR_HPP