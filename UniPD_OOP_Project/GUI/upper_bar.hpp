#ifndef UPPER_BAR_HPP
#define UPPER_BAR_HPP

#include <QWidget>

class QPushButton;
class QLineEdit;
class QComboBox;
class QIcon;
class QString;

class UpperBar : public QWidget {
    Q_OBJECT

public:
    explicit UpperBar(QWidget *parent = nullptr);
    void pulisci();
    void reset();

private:

    QComboBox *changeLayout;

    QPushButton *stella;

    QComboBox *sortComboBox;

    QLineEdit *searchBar;

    QIcon* vuota;
    QIcon* piena;

    bool selezionato;

signals:
    void sortNome();
    void sortData();  

    void showGriglia();
    void showLista();

    void showPreferiti();
    void showGenereale();

    void testoCercato(const QString&);
};


#endif // UPPER_BAR_HPP