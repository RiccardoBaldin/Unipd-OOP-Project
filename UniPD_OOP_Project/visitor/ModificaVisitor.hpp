#ifndef MODIFICA_VISITOR_HPP
#define MODIFICA_VISITOR_HPP

#include "FileVisitor.hpp"

class QWidget;
class QVBoxLayout;
class QHBoxLayout;
class QFormLayout;
class QLabel;
class QIcon;
class QLineEdit;
class QSpinBox;
class QCheckBox;

class ModificaVisitor : public FileVisitor{

private:

    QWidget* widget = nullptr;

    QVBoxLayout* layout;
    QHBoxLayout* sopra;
    QHBoxLayout* sotto;
    QFormLayout* sottoSx;
    QFormLayout* sottoDx;


    //attributi generali
    QIcon *icona;
    QLabel *widgetIcona;
    QLineEdit *nome;
    QLineEdit *autore;
    QLineEdit *genere;
    QSpinBox *anno;

    //attributi libro
    QSpinBox *pagine;
    QLineEdit *editore;

    //attributi video
    QSpinBox *durata;
    QLineEdit *regista;
    QLineEdit *casa_di_produzione;

    //attributi film
    QCheckBox *oscar;

    //attributi serie
    QLineEdit *casa_di_produzione_serie;

    //attributi episodio
    QLineEdit *serie;
    QSpinBox *numero_stagione;
    QSpinBox *numero_episodio;

public:
    ModificaVisitor() = default;
    ~ModificaVisitor() = default;

    virtual void Visit(File_Generico& file) override;
    virtual void Visit(File_Video& video) override;
    virtual void Visit(File_Film& film) override;
    virtual void Visit(File_Episodio& episodio) override;
    virtual void Visit(File_Serie& serie) override;
    virtual void Visit(File_Libro& libro) override;
    virtual void Visit(Biblioteca& Biblioteca) override;

    QWidget* GetWidget() const ;
    bool confermaModifiche(File_Generico*, Biblioteca*) const;
};

#endif //MODIFICA_VISITOR_HPP