#ifndef MOUSE_HANDLER_HPP
#define MOUSE_HANDLER_HPP

#include <QWidget>

class File_Generico;
class QMouseEvent;
class QPoint;
class QAction;

class mouseMenu : public QWidget{
    Q_OBJECT

public:
    explicit mouseMenu(File_Generico* file, QWidget* parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:
    File_Generico* file;

    QAction* ELIMINA;
    QAction* MODIFICA;
    QAction* APRI;
    QAction* ADD_PREFE;
    QAction* REM_PREFE;
    QAction* SALVA;

    void showTendina(const QPoint&);

signals:
    void selezionato(File_Generico*);

    void managePreferiti(File_Generico*);
    void modifica(File_Generico*);
    void elimina(File_Generico*);
    void salva(File_Generico*);
};


#endif //MOUSE_HANDLER_HPP