#ifndef FILE_GENERICO_HPP
#define FILE_GENERICO_HPP

#include <iostream>

#include "../visitor/FileVisitor.hpp"
#include "../visitor/MostraVisitor.hpp"

class File_Generico{

    protected:
        std::string nome;
        std::string autore;
        std::string genere;
        unsigned int anno;
        bool preferito = false;

    public:
        File_Generico(const std::string& = "", const std::string& = "", const std::string& = "", unsigned int = 0);
        File_Generico(const File_Generico&);
        virtual ~File_Generico() = default;
        virtual File_Generico* clone() const = 0;
        File_Generico& operator=(const File_Generico&);

        std::string GetNome() const;
        std::string GetAutore() const;
        std::string GetGenere() const;
        unsigned int GetAnno() const;

        void togglePreferito() {preferito = !preferito;}

        bool IsPreferito() const;

        virtual void SetNome(const std::string&);
        virtual void SetAutore(const std::string&);
        virtual void SetGenere(const std::string&);
        void SetAnno(unsigned int);

        //metodi per accettare le visite
        virtual void Accept(FileVisitor& visitor);
        
};


#endif // FILE_GENERICO_HPP