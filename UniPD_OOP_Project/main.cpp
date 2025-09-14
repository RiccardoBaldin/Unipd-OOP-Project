#include <QApplication>
#include "CLASSI_FILE/Container.hpp"
#include "CLASSI_FILE/File_Libro.hpp"
#include "CLASSI_FILE/File_Film.hpp"
#include "CLASSI_FILE/File_Serie.hpp"
#include "JSON_CONTROL/ToJson.hpp"
#include "JSON_CONTROL/FromJson.hpp"
#include "GUI/main_window.hpp"

int main(int argc, char *argv[]) {

    Biblioteca* biblioteca = new Biblioteca();

    QApplication app(argc, argv);

    MainWindow finestra(biblioteca);
    finestra.show();

    return app.exec();
}