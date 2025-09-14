#ifndef LISTAVISITOR_HPP
#define LISTAVISITOR_HPP

#include "FileVisitor.hpp"

class QHBoxLayout;
class QIcon;
class QLabel;

class ListaVisitor : public FileVisitor {
private:
    QHBoxLayout* layout;
    QIcon* icona;
    QLabel* label;

public:

    void Visit(File_Generico& file) override;
    void Visit(File_Video& video) override;
    void Visit(File_Film& film) override;
    void Visit(File_Episodio& episodio) override;
    void Visit(File_Serie& serie) override;
    void Visit(File_Libro& libro) override;
    void Visit(Biblioteca& biblioteca) override;


    QHBoxLayout* GetLayout() const;
};

#endif // LISTAVISITOR_HPP