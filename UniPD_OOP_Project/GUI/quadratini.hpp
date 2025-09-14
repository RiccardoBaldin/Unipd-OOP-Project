#ifndef QUADRATINI_HPP
#define QUADRATINI_HPP

#include <QWidget>

class File_Generico;

class Quadratini : public QWidget {
    Q_OBJECT

public:
    explicit Quadratini(File_Generico* file, QWidget *parent = nullptr);

private:
    File_Generico* file;

signals:
    void QuadratinoClicked(File_Generico*);
    void QuadratinoModifica(File_Generico*);
    void QuadratinoElimina(File_Generico*);
    void QuadratinoSalva(File_Generico*);
    void QuadratinoPreferito(File_Generico*);
};


#endif // QUADRATINI_HPP