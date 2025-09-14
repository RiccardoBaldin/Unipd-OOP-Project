#include "File_Generico.hpp"

File_Generico::File_Generico(const std::string& nome, const std::string& autore, const std::string& genere, unsigned int anno)
    : nome(nome), autore(autore), genere(genere), anno(anno){}

File_Generico::File_Generico(const File_Generico& other)
    : nome(other.nome),
      autore(other.autore),
      genere(other.genere),
      anno(other.anno),
      preferito(other.preferito) {
   }

File_Generico& File_Generico::operator=(const File_Generico& other) {
    if (this != &other) {
        nome = other.nome;
        autore = other.autore;
        genere = other.genere;
        anno = other.anno;
        preferito = other.preferito;
    }
    return *this;
}

//GETTERS

std::string File_Generico::GetNome() const {
    return nome;
}

std::string File_Generico::GetAutore() const {
    return autore;
}

std::string File_Generico::GetGenere() const {
    return genere;
}

unsigned int File_Generico::GetAnno() const {
    return anno;
}

bool File_Generico::IsPreferito() const {
    return preferito;
}


//SETTERS

void File_Generico::SetNome(const std::string& nome){
    this->nome = nome;
}

void File_Generico::SetAutore(const std::string& autore){
    this->autore = autore;
}

void File_Generico::SetGenere(const std::string& genere){
    this->genere = genere;
}

void File_Generico::SetAnno(unsigned int anno){
    this->anno = anno;
}


void File_Generico::Accept(FileVisitor& visitor){
    visitor.Visit(*this);
}
