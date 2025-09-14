#ifndef ADD_EPISODIO_WIDGET_HPP
#define ADD_EPISODIO_WIDGET_HPP

#include <QWidget>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>

class File_Serie;

class QPushButton;
class QVBoxLayout;
class QCheckBox;
class QButtonGroup;
class QShowEvent;

class AddEpisodioWidget : public QWidget{
        Q_OBJECT

public:
    explicit AddEpisodioWidget(File_Serie* serie = nullptr, QWidget *parent = nullptr);
    void setSerie(File_Serie*);

private:
    File_Serie *serie;

    QPushButton *conferma;
    QPushButton *annulla;

    QVBoxLayout *layout;
    QHBoxLayout *layoutSotto = new QHBoxLayout();
    QHBoxLayout *layoutBig = new QHBoxLayout();
    QFormLayout *layoutSx = new QFormLayout();
    QFormLayout *layoutDx = new QFormLayout();

    QLabel *icona = new QLabel();

    //attributi episodio
    QLineEdit *nome = new QLineEdit();
    QLabel *autore = new QLabel();
    QLabel *genere = new QLabel();
    QSpinBox *anno = new QSpinBox();
    QSpinBox *durata = new QSpinBox();
    QLineEdit *regista = new QLineEdit();
    QLabel *casa_di_produzione = new QLabel();
    QSpinBox *numero_stagione = new QSpinBox();
    QSpinBox *numero_episodio = new QSpinBox();

    QLabel *nomeSerie = new QLabel();

protected:
    bool NonCampiVuoti();
    void pulisciCampi();

    void showEvent(QShowEvent *event) override;

public slots:
    //void AggiungiEpisodio();

    void ConfermaAggiunta();
    void AnnullaAggiunta();

signals:
    void FileAggiunto();
    void FileAnnullato();

};


#endif //ADD_EPISODIO_WIDGET_HPP