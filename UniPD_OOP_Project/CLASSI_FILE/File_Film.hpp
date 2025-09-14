#ifndef FILE_FILM_HPP
#define FILE_FILM_HPP

#include <iostream>
#include "File_Video.hpp"

class File_Film : public File_Video{

    private:
        bool oscar;

    public:
        File_Film(const std::string& = "", const std::string& = "", const std::string& = "", unsigned int = 0, unsigned int = 0, const std::string& = "", const std::string& = "", bool = false);
        ~File_Film()override = default;

        bool GetOscar() const;

        void SetOscar(bool);

        //metodo per visite
        void Accept(FileVisitor& visitor) override ;

        File_Film* clone() const override {return new File_Film(*this);}
};



#endif // FILE_FILM_HPP