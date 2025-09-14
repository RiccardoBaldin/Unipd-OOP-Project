#ifndef LEFT_SIDE_HPP
#define LEFT_SIDE_HPP

#include <QWidget>

class Biblioteca;
class Tree;
class QComboBox;
class QPushButton;

class LeftSide : public QWidget {
    Q_OBJECT

public:
    explicit LeftSide(Biblioteca *biblioteca = nullptr, QWidget *parent = nullptr);
signals:
    void addFileSignal(int index);

    void importaBiblioteca();
    void importaFile();

    void salvaBiblioteca();
    
    void listaCambiataInLibri();
    void listaCambiataInFilm();
    void listaCambiataInSerie();
    void listaCambiataInTutto();

private slots:
    void onComboBoxIndexChanged(int index);

public slots:
    void updateTree();
    void resetComboBox();

private:
    Biblioteca *biblioteca;
    Tree *tree;
    QComboBox *creaFile;
    QPushButton *importaB;
    QPushButton *importaF;
    QPushButton *salva;
};

#endif // LEFT_SIDE_HPP
