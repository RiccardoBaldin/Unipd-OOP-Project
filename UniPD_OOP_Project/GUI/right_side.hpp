#ifndef RIGHT_SIDE_HPP
#define RIGHT_SIDE_HPP

#include <QWidget>

class UpperBar;
class LineaOrizzontale;
class Biblioteca;
class File_Generico;
class QStackedWidget;
class DisposizioneGriglia;
class DisposizioneLinee;

class RightSide : public QWidget {
    Q_OBJECT

public:
    explicit RightSide(std::vector<File_Generico*> listaFileDaMostrare, QWidget *parent = nullptr);
    void updateLayout(std::vector<File_Generico*>);
    void setLista(std::vector<File_Generico*>);
    void resetUpperBar();
    void showpreferiti();
    void pulisci();

private:
    UpperBar *upperBar;
    LineaOrizzontale *linea;
    std::vector<File_Generico*> listaFileDaMostrare;
    QStackedWidget *stackedWidget;
    DisposizioneGriglia *Griglia;
    DisposizioneLinee *Linee;

private slots:
    void changeLayout(int index);

signals:
    void File_Clicked(File_Generico*);
    void modifica(File_Generico*);
    void elimina(File_Generico*);
    void salva(File_Generico*);
    void preferito(File_Generico*);

    void sortNome();
    void sortData();

    void showPreferiti();
    void showGenerale();

    void testoCercato(const QString&);

    void layoutChanged();
        
};

#endif // RIGHT_SIDE_HPP