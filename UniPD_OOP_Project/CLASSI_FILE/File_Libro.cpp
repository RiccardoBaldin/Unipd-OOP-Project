#include "File_Libro.hpp"
#include "visitor/FileVisitor.hpp"

File_Libro::File_Libro(const std::string& nome, const std::string& autore, const std::string& genere, unsigned int anno, unsigned int pagine, const std::string& editore)
            : File_Generico(nome, autore, genere, anno), pagine(pagine), editore(editore){}


//GETTERS

unsigned int File_Libro::GetPagine() const{
    return pagine;
}

std::string File_Libro::GetEditore() const{
    return editore;
}


//SETTERS

void File_Libro::SetPagine(unsigned int pagine){
    this->pagine = pagine;
}

void File_Libro::SetEditore(const std::string& editore){
    this->editore = editore;
}

//METODO PER VISITE

void File_Libro::Accept(FileVisitor& visitor){
    visitor.Visit(*this);
}
