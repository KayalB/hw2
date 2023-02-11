#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "util.h"
#include "datastore.h"



class MyDataStore : public DataStore{
    public:
        MyDataStore();
        ~MyDataStore();

        /**
        * Adds a product to the data store
        */
        void addProduct(Product* p);

        /**
        * Adds a user to the data store
        */
        void addUser(User* u);

        /**
        * Performs a search of products whose keywords match the given "terms"
        *  type 0 = AND search (intersection of results for each term) while
        *  type 1 = OR search (union of results for each term)
        */
        std::vector<Product*> search(std::vector<std::string>& terms, int type);

        /**
        * Reproduce the database file from the current Products and User values
        */
        void dump(std::ostream& ofile);

        void addToCart(Product*, std::string name);

        void viewCart(std::string name);

        void buyCart(std::string name);

        bool checkIfUserExists(std::string name);


    private:
        // std::map<Product*, std::set<std::string>> products_;

        std::set<Product*> products_;

        std::map<std::string, User*> users_;
        std::map<std::string, std::set<Product*>> keyWordMapping_;
        // I could theoretically make another map which is of the list of keywords and their names
};

#endif
