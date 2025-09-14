#ifndef FILE_VIDEO_HPP
#define FILE_VIDEO_HPP

#include <iostream>
#include "File_Generico.hpp"



class File_Video : public File_Generico{

    protected:
        unsigned int durata;
        std::string casa_di_produzione;
        std::string regista;

    public:
        File_Video(const std::string& = "", const std::string& = "",
                   const std::string& = "", unsigned int = 0, unsigned int = 0, 
                   const std::string& = "", const std::string& = "");

        unsigned int GetDurata() const;
        std::string GetCasaDiProduzione() const;
        std::string GetRegista() const;

        void SetDurata(unsigned int);
        void SetCasaDiProduzione(const std::string&);
        void SetRegista(const std::string&);

        virtual File_Video* clone() const = 0;
};


#endif // FILE_VIDEO_HPP