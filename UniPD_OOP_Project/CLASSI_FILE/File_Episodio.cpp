#include "File_Episodio.hpp"
#include "File_Serie.hpp"
#include "visitor/FileVisitor.hpp"

File_Episodio::File_Episodio(const std::string& nome, const std::string& autore, const std::string& genere, unsigned int anno, unsigned int durata, const std::string& casa_di_produzione, const std::string& regista, unsigned int numero_stagione, unsigned int numero_episodio, std::string serieTV)
    : File_Video(nome, autore, genere, anno, durata, casa_di_produzione, regista),
    serie(nullptr),
    numero_episodio(numero_episodio),
    numero_stagione(numero_stagione), 
    serieTV(serieTV){
}


//GETTERS

unsigned int File_Episodio::GetNumeroEpisodio() const {
    return numero_episodio;
}

unsigned int File_Episodio::GetNumeroStagione() const {
    return numero_stagione;
}

std::string File_Episodio::GetSerieTV() const {
    return serieTV;
}

File_Serie* File_Episodio::GetSerieFile() const {
    return serie;
}

//SETTERS

void File_Episodio::SetNumeroEpisodio(unsigned int numero_episodio){
    this->numero_episodio = numero_episodio;
    this->serie->AggiornaNumEpisodi();
}

void File_Episodio::SetNumeroStagione(unsigned int numero_stagione){
    this->numero_stagione = numero_stagione;
    this->serie->AggiornaNumStagioni();
}

void File_Episodio::SetAutore(File_Serie* s) {
    this->serie = s;
    this->autore = (s) ? s->GetAutore() : "";
}

void File_Episodio::SetSerieTV(File_Serie* s) {
    this->serie = s;
    this->serieTV = (s) ? s->GetNome() : "";
}

void File_Episodio::SetCasaDiProduzione(File_Serie* s) {
    this->serie = s;
    this->casa_di_produzione = (s) ? s->GetCasaDiProduzione() : "";
}

void File_Episodio::SetGenere(File_Serie* s) {
    this->serie = s;
    this->genere = (s) ? s->GetGenere() : "";
}

void File_Episodio::SetNome(const std::string& nome){
    this->nome = nome;
}

void File_Episodio::SetAutore(const std::string& autore){
    this->autore = autore;
}

void File_Episodio::SetGenere(const std::string& genere){
    this->genere = genere;
}

//METODO PER VISITE

void File_Episodio::Accept(FileVisitor& visitor){
    visitor.Visit(*this);
}