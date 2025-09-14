#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QMainWindow>


class LeftSide;
class RightSide;
class Biblioteca;
class File_Generico;
class File_Episodio;
class File_Serie;
class LineaVerticale;
class QStackedWidget;
class AddFileWidget;
class AddEpisodioWidget;
class QIcon;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(Biblioteca* biblioteca ,QWidget *parent = nullptr);
private:

    QStackedWidget *stackedWidget;
    QWidget *principale;
    AddFileWidget *aggiuntaLibro=nullptr;
    AddFileWidget *aggiuntaFilm=nullptr;
    AddFileWidget *aggiuntaSerie=nullptr;
    AddEpisodioWidget* episodioWidget=nullptr;

    File_Serie* currentSerie;
    QWidget* currentSerieWidget;

    QWidget* currentMostraWidget = nullptr;
    QWidget* currentEpisodioWidget = nullptr;

    LeftSide *leftSide;
    RightSide *rightSide;
    Biblioteca *biblioteca;
    LineaVerticale *linea;

    QIcon* preferito_si;
    QIcon* preferito_no;

    std::vector<File_Generico*> lista;

    bool p;
    unsigned int tipoFiles = 0;
    
private slots:
    void showAddFileWidget(int);
    void showAddEpisodioWidget();

    void showMainWindow();
    void DettagliIndietro();

    void mostraWindow(File_Generico*);
    void mostraEpisodio(File_Episodio*);

    void elimina(File_Generico*);
    void modifica(File_Generico*);
    void salva(File_Generico*);
    void preferito(File_Generico*);

    void cercazioneFiles(const QString&);

    void importaBiblioteca();
    void importaFile();
    void importaEpisodio(File_Serie*);

    void salvaBiblioteca();

signals:
    void file_Eliminato();
};


#endif // MAIN_WINDOW_HPP
