#ifndef MOSTRA_HELPER_HPP
#define MOSTRA_HELPER_HPP

#include "../visitor/MostraVisitor.hpp"

#include <QObject>
#include <QLayout>


class File_Generico;
class File_Episodio;
class File_Serie;
class MostraVisitor;
class QVBoxLayout;
class QTreeWidgetItem;

class MostraVisitorHelper : public QWidget {
    Q_OBJECT

public:
    explicit MostraVisitorHelper(File_Generico* file = nullptr, QWidget* parent = nullptr);
    void update(File_Generico*);

signals:
    void AggiuntaEpisodio();
    void ImportaEpisodio(File_Serie* serie);
    void EpisodioSelezionato(File_Episodio* episodio);
    void EpisodioModifica(File_Episodio* episodio);
    void EpisodioElimina(File_Episodio* episodio);
    void EpisodioSalva(File_Episodio* episodio);

private:
    File_Serie* serie = nullptr;

};

#endif //MOSTRA_HELPER_HPP