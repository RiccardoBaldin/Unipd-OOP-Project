#include "Container.hpp"
#include "File_Generico.hpp"
#include "File_Libro.hpp"
#include "File_Film.hpp"
#include "File_Serie.hpp"
#include "visitor/FileVisitor.hpp"
#include <algorithm>
#include <typeinfo>


Biblioteca::~Biblioteca(){
    if (principale)for(auto x : archivio) delete x;
}

std::vector<File_Generico*> Biblioteca::getArchivio() const{
    return archivio;
}


void Biblioteca::addFile(File_Generico* file){
    if (!check(file)) {
        delete file;
        return;
    }
    archivio.push_back(file);
    if(isSaved) isSaved = false;
}



void Biblioteca::killFile(File_Generico* file){
    for(auto it = archivio.begin(); it != archivio.end(); ++it){
        if(*it == file){
            archivio.erase(it);
            delete file;
            return;
        }
    }
}

void Biblioteca::clear(){
    if(principale){
        for (auto file : archivio) {
            delete file;
        }
    }
    archivio.clear();
}

void Biblioteca::sort_nome() {
    if(archivio.empty()) return;
    std::sort(archivio.begin(), archivio.end(), [](File_Generico* a, File_Generico* b) {
        return a->GetNome() < b->GetNome();
    });
}

void Biblioteca::sort_anno() {
    if(archivio.empty()) return;
    std::sort(archivio.begin(), archivio.end(), [](File_Generico* a, File_Generico* b) {
        return a->GetAnno() < b->GetAnno();
    });
}


std::vector<File_Generico*> Biblioteca::getLibri() const{
    std::vector<File_Generico*> libri;
    for(auto it : archivio){
        if(dynamic_cast<File_Libro*>(it)){
            libri.push_back(it);
        }
    }
    return libri;
}

std::vector<File_Generico*> Biblioteca::getFilm() const{
    std::vector<File_Generico*> film;
    for(auto it : archivio){
        if(dynamic_cast<File_Film*>(it)){
            film.push_back(it);
        }
    }
    return film;
}

std::vector<File_Generico*> Biblioteca::getSerie() const{
    std::vector<File_Generico*> serie;
    for(auto it : archivio){
        if(dynamic_cast<File_Serie*>(it)){
            serie.push_back(it);
        }
    }
    return serie;
}


std::vector<File_Generico*> Biblioteca::getLibriPrefe() const{
    std::vector<File_Generico*> libri;
    for(auto it : archivio){
        if(dynamic_cast<File_Libro*>(it) && it->IsPreferito()){
            libri.push_back(it);
        }
    }
    return libri;
}

std::vector<File_Generico*> Biblioteca::getFilmPrefe() const{
    std::vector<File_Generico*> film;
    for(auto it : archivio){
        if(dynamic_cast<File_Film*>(it) && it->IsPreferito()){
            film.push_back(it);
        }
    }
    return film;
}

std::vector<File_Generico*> Biblioteca::getSeriePrefe() const{
    std::vector<File_Generico*> serie;
    for(auto it : archivio){
        if(dynamic_cast<File_Serie*>(it) && it->IsPreferito()){
            serie.push_back(it);
        }
    }
    return serie;
}

std::vector<File_Generico*> Biblioteca::preferiti() const{
    std::vector<File_Generico*> preferiti;
    for(auto it : archivio){
        if(it->IsPreferito()){
            preferiti.push_back(it);
        }
    }
    return preferiti;
}

bool Biblioteca::check(const File_Generico* a, const File_Generico* exclude) const {
    for (auto cit : archivio) {
        if (cit == exclude) continue;
        if (typeid(*cit) == typeid(*a) &&
            cit->GetNome() == a->GetNome() && 
            cit->GetAnno() == a->GetAnno() && 
            cit->GetAutore() == a->GetAutore()) {
            return false;
        }
    }
    return true;
}

void Biblioteca::Accept(FileVisitor& v) {
    v.Visit(*this);
}

Biblioteca& Biblioteca::operator=(const std::vector<File_Generico*>& files){
    clear();
    for(auto f : files){
        archivio.push_back(f);
    }
    return *this;
}