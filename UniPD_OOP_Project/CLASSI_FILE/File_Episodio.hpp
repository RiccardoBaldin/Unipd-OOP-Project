#ifndef FILE_EPISODIO_HPP
#define FILE_EPISODIO_HPP

#include <iostream>
#include "File_Video.hpp"

class File_Serie;

class File_Episodio : public File_Video{

    private:
        File_Serie* serie;
        unsigned int numero_episodio;
        unsigned int numero_stagione;
        std::string serieTV;

    public:
        File_Episodio(const std::string& = "", const std::string& = "", const std::string& = "", unsigned int = 0, unsigned int = 0, const std::string& = "", const std::string& = "", unsigned int = 0, unsigned int = 0, std::string = "");
        ~File_Episodio()override = default;
        File_Episodio* clone() const override {return new File_Episodio(*this);}

        unsigned int GetNumeroEpisodio() const;
        unsigned int GetNumeroStagione() const;
        std::string GetSerieTV() const;
        File_Serie* GetSerieFile() const;

        void SetNome(const std::string&) override;
        void SetAutore(const std::string&) override;
        void SetGenere(const std::string&) override;

        void SetNumeroEpisodio(unsigned int);
        void SetNumeroStagione(unsigned int);
        void SetAutore(File_Serie*);
        void SetSerieTV(File_Serie*);
        void SetCasaDiProduzione(File_Serie*);
        void SetGenere(File_Serie*);

        //metodo per visite
        
        void Accept(FileVisitor& visitor) override ;

};

#endif // FILE_EPISODIO_HPP