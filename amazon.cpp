#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "mydatastore.h"


using namespace std;
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
void displayProducts(vector<Product*>& hits);

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    MyDataStore ds;



    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits;
    bool done = false;
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) {
            if( cmd == "AND") {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 0);
                displayProducts(hits);
            }
            else if ( cmd == "OR" ) {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1);
                displayProducts(hits);
            }
            else if ( cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            }
	          /* Add support for other commands here */
            // TEMPORARY, JUST TO GET MY BEARINGS
            else if ( cmd == "ADD") {
                string username;
                size_t search_hit_number;

                // Might have to check in case it fails
                // If we can sucessfully get in the username and the search hit number
                if(ss >> username && ss >> search_hit_number){
                  if(search_hit_number <= hits.size() && search_hit_number > 0 && ds.checkIfUserExists(username)){
                    for(int i = 0; i < int(username.size()); i++){
                      username[i] = tolower(username[i]);
                    }
                    ds.addToCart(hits[search_hit_number - 1], username);
                    // cout << "Added to Cart!" << endl;
                  }
                  else{
                    cout << "Invalid request" << endl;
                  }
                }
                else{
                  cout << "Invalid request" << endl;
                }
            }



            else if ( cmd == "VIEWCART") {
                string username;

                // Might have to check in case it fails
                // If we can sucessfully get in the username and the search hit number
                if(ss >> username){
                  if(ds.checkIfUserExists(username)){
                    ds.viewCart(username);
                    // cout << "Added to Cart!" << endl;
                  }
                  else{
                    cout << "Invalid username" << endl;
                  }
                }
                else{
                  cout << "Invalid username" << endl;
                }
            }



            else if ( cmd == "BUYCART") {
                string username;

                // Might have to check in case it fails
                // If we can sucessfully get in the username and the search hit number
                if(ss >> username){
                  if(ds.checkIfUserExists(username)){
                    ds.buyCart(username);
                    // cout << "Added to Cart!" << endl;
                  }
                  else{
                    cout << "Invalid username" << endl;
                  }
                }
                else{
                  cout << "Invalid username" << endl;
                }
            }

            



            else {
                cout << "Unknown command" << endl;
            }
        }

    }
    return 0;
}


// for(i=0; i <5; i++) {

//     cout <<  "ishita hacked ur laptop" << endl;
//     cout << "You forgot te endl. I added it for u :)" << endl;
// }

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
    	cout << "No results found!" << endl;
    	return;
    }
    std::sort(hits.begin(), hits.end(), ProdNameSorter());
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}
