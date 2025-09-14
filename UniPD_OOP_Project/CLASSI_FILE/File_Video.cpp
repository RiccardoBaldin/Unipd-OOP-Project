#include "File_Video.hpp"

File_Video::File_Video(const std::string& nome, const std::string& autore, const std::string& genere, unsigned int anno, unsigned int durata, const std::string& casa_di_produzione, const std::string& regista) : File_Generico(nome, autore, genere, anno){
    this->durata = durata;
    this->casa_di_produzione = casa_di_produzione;
    this->regista = regista;
}


//GETTERS

unsigned int File_Video::GetDurata() const {
    return durata;
}

std::string File_Video::GetCasaDiProduzione() const {
    return casa_di_produzione;
}

std::string File_Video::GetRegista() const {
    return regista;
}


//SETTERS

void File_Video::SetDurata(unsigned int durata){
    this->durata = durata;
}

void File_Video::SetCasaDiProduzione(const std::string& casa_di_produzione){
    this->casa_di_produzione = casa_di_produzione;
}

void File_Video::SetRegista(const std::string& regista){
    this->regista = regista;
}