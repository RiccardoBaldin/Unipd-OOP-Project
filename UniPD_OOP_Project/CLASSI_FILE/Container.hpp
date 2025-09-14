#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <iostream>
#include <vector>


class File_Generico;
#include "../visitor/FileVisitor.hpp"

class Biblioteca{
    private:
        std::vector<File_Generico*> archivio;
        bool principale = true;

    public:

        Biblioteca() = default;
        ~Biblioteca();

        bool isSaved = true;

        std::vector<File_Generico*> getArchivio() const;
        std::vector<File_Generico*> preferiti() const;
        
        void addFile(File_Generico*);
        void killFile(File_Generico*);
        
        void clear();
        bool check(const File_Generico*, const File_Generico* = nullptr) const;

        Biblioteca& operator=(const std::vector<File_Generico*>&);

        std::vector<File_Generico*> getLibri() const;
        std::vector<File_Generico*> getFilm() const;
        std::vector<File_Generico*> getSerie() const;

        std::vector<File_Generico*> getLibriPrefe() const;
        std::vector<File_Generico*> getFilmPrefe() const;
        std::vector<File_Generico*> getSeriePrefe() const;
        
        void sort_nome();
        void sort_anno();


        void Accept(FileVisitor& visitor);
};

#endif // CONTAINER_HPP