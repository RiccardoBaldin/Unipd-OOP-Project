#include "File_Film.hpp"
#include "visitor/FileVisitor.hpp"

File_Film::File_Film(const std::string& nome, const std::string& autore, const std::string& genere, unsigned int anno, unsigned int durata, const std::string& casa_di_produzione, const std::string& regista, bool oscar) : File_Video(nome, autore, genere, anno, durata, casa_di_produzione, regista){
    this->oscar = oscar;
}


//GETTERS

bool File_Film::GetOscar() const {
    return oscar;
}


//SETTERS

void File_Film::SetOscar(bool oscar){
    this->oscar = oscar;
}

//METODO PER VISITE

void File_Film::Accept(FileVisitor& visitor){
    visitor.Visit(*this);
}
