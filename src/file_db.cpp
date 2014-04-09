#include "eater/file_db.hpp"
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

namespace Eater
{
    bool FileDB::open(const std::string &file)
    {
        struct stat buffer;

        int r = stat(file.c_str(), &buffer);

        if (r == -1) {
            this->file = file;
            return true;
        }

        this->file = file;

        std::ifstream is;
        is.open(file);

        if (!is.is_open()) {
            LOGG_LN("File is not open...");

            return false;
        }

        int number = 0;
        is >> number;

        for(;number != 0; number--) {
            FoodItem it;

            is >> it;

            std::cout << it << std::endl;
            food_items.push_back(it);
        }

        return true;
    }

    bool FileDB::close()
    {
        if (file == "") {
            return false;
        }

        std::ofstream os;
        os.open(file, std::ios::out | std::ios::trunc);

        if (!os.is_open()) {
            LOGG(E_RED("Error: "));
            LOGG("Faild to open file: ");
            LOGG_LN(file);

            return false;
        }

        os << food_items.size() << std::endl;

        for (auto it = food_items.begin(); it != food_items.end(); it++) {
            os << *it << std::endl;
        }

        os.close();

        return true;
    }

    bool FileDB::exists(const FoodItem &it) const
    {
        for (auto i = food_items.begin(); i != food_items.end(); i++) {
            if (it.id() == i->id()) {
                return true;
            }
        }

        return false;
    }

    bool FileDB::add(FoodItem &it)
    {
        if (it.id() != -1) {
            return false;
        }

        if (food_items.empty()) {
            it.id(1);

            food_items.push_back(it);

            return true;
        }

        auto tmp = food_items.back();
        it.id(tmp.id() + 1);

        food_items.push_back(it);

        return true;
    }

    bool FileDB::find(id_t id, FoodItem &it) const
    {
        for (auto i = food_items.begin(); i != food_items.end(); i++) {
            if (id == i->id()) {
                it = *i;

                return true;
            }
        }

        return false;
    }
} /* Eater */ 
