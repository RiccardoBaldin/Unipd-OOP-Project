#ifndef DISPOSIZIONE_GRIGLIA_HPP
#define DISPOSIZIONE_GRIGLIA_HPP

#include <QWidget>
#include <QGridLayout>

class Biblioteca;
class QScrollArea;
class File_Generico;

class DisposizioneGriglia : public QWidget {
    Q_OBJECT

public:
    explicit DisposizioneGriglia(std::vector<File_Generico*> ListaFileDaMostrare, QWidget *parent = nullptr);
    void updateLayout(std::vector<File_Generico*>);

protected:
    void resizeEvent(QResizeEvent*) override;

private:
    std::vector<File_Generico*> ListaFileDaMostrare;
    QGridLayout* layout;
    QScrollArea* scrollArea;


signals:
    void File_Clicked(File_Generico*);
    void griglia_modifica(File_Generico*);
    void griglia_elimina(File_Generico*);
    void griglia_salva(File_Generico*);
    void griglia_preferito(File_Generico*);
};


#endif // DISPOSIZIONE_GRIGLIA_HPP