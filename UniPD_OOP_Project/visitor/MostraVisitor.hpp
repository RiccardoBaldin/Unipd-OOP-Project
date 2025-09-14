#ifndef MOSTRAVISITOR_HPP
#define MOSTRAVISITOR_HPP

#include "FileVisitor.hpp"
#include <QWidget>


class QTreeWidget;
class QLabel;
class QVBoxLayout;
class QHBoxLayout;
class QIcon;
class File_Generico;
class File_Video;
class File_Film;
class File_Episodio;
class File_Serie;
class File_Libro;

class MostraVisitor : public FileVisitor {
private:

    QWidget* widget = nullptr;

    QVBoxLayout* layout;
    QHBoxLayout* sopra;
    QHBoxLayout* sotto;
    QVBoxLayout* sottoSx;
    QVBoxLayout* sottoDx;


    //attributi generali
    QIcon *icona;
    QLabel *widgetIcona;
    QLabel *nome;
    QLabel *autore;
    QLabel *genere;
    QLabel *anno;

    //attributi libro
    QLabel *pagine;
    QLabel *editore;

    //attributi video
    QLabel *durata;
    QLabel *regista;
    QLabel *casa_di_produzione;

    //attributi film
    QIcon *oscar;

    //attributi serie
    QLabel *numero_stagioni;
    QLabel *numero_episodi;
    QLabel *casa_di_produzione_serie;
    QTreeWidget *albero_episodi = nullptr;

    //attributi episodio
    QLabel *serie;
    QLabel *numero_stagione;
    QLabel *numero_episodio;

    void CreaAlberoEpisodi(const File_Serie& serie);

public:

    MostraVisitor() = default;
    ~MostraVisitor() = default;

    virtual void Visit(File_Generico& file) override;
    virtual void Visit(File_Video& video) override;
    virtual void Visit(File_Film& film) override;
    virtual void Visit(File_Episodio& episodio) override;
    virtual void Visit(File_Serie& serie) override;
    virtual void Visit(File_Libro& libro) override;
    virtual void Visit(Biblioteca& biblioteca) override;

    QWidget* GetWidget() const ;
    QTreeWidget* GetAlberoEpisodi() const ;
};

#endif // MOSTRAVISITOR_HPP