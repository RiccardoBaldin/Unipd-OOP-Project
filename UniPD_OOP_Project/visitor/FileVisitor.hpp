
#ifndef FILEVISITOR_HPP
#define FILEVISITOR_HPP

class File_Generico;
class File_Video;
class File_Film;
class File_Episodio;
class File_Serie;
class File_Libro;
class Biblioteca;

class FileVisitor{
    public:

        virtual ~FileVisitor() = default;
        virtual void Visit(File_Generico& file) = 0;
        virtual void Visit(File_Video& video) = 0;
        virtual void Visit(File_Film& film) = 0;
        virtual void Visit(File_Episodio& episodio) = 0;
        virtual void Visit(File_Serie& serie) = 0;
        virtual void Visit(File_Libro& libro) = 0;
        virtual void Visit(Biblioteca& biblioteca) = 0;
};


#endif // FILEVISITOR_HPP