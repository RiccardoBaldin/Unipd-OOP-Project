#ifndef TOJSON_HPP
#define TOJSON_HPP

#include <fstream>
#include "../visitor/JSonVisitor.hpp"
#include "../CLASSI_FILE/File_Generico.hpp"
#include "../CLASSI_FILE/Container.hpp"

void saveAsJson(File_Generico*, std::string);
void saveAsJson(Biblioteca*, std::string);

#endif //TOJSON_HPP