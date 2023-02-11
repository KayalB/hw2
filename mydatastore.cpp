#include "mydatastore.h"
#include <string>
#include <iostream>
#include <set>
#include <map>
#include <fstream>
#include <iomanip>
#include <algorithm>
using namespace std;




MyDataStore::MyDataStore()
{

}

MyDataStore::~MyDataStore()
{
  for(map<string, User*>::iterator it = users_.begin(); it != users_.end(); it++){
    delete it->second;
  }
  for(set<Product*>::iterator it = products_.begin(); it != products_.end(); it++){
    delete *it;
  }
}

void MyDataStore::dump(ostream& ofile)
{
  ofile << "<products>" << endl;
  for(set<Product*>::iterator it = products_.begin(); it != products_.end(); it++){
    (*it)->dump(ofile);
  }
  ofile << "</products>" << endl;
  ofile << "<users>" << endl;
  for(map<string, User*>::iterator it = users_.begin(); it != users_.end(); it++){
    (it)->second->dump(ofile);
  }
  ofile << "</users>" << endl;

}

/**
* Adds a product to the data store
*/
void MyDataStore::addProduct(Product* p){
  products_.insert(p);
  
  // If keyWordMapping_ has nothing added yet
  // if(keyWordMapping_.begin() == keyWordMapping_.end()){

  // For every keyword in Product p
  set<string> productKeywords = p->keywords();
  for(set<string>::iterator it = productKeywords.begin(); it != productKeywords.end(); it++){

    // If that keyword has a match in keyWordMapping_
    if(keyWordMapping_.find(*it) != keyWordMapping_.end()){
      keyWordMapping_[*it].insert(p);
    }
    else{
      set<Product*> addToKeyMapping;
      addToKeyMapping.insert(p);
      keyWordMapping_.insert(make_pair(*it, addToKeyMapping));
    }
  }
}

/**
* Adds a user to the data store
*/
void MyDataStore::addUser(User* u){
  users_.insert(make_pair(u->getName(), u));
}

/**
* Performs a search of products whose keywords match the given "terms"
*  type 0 = AND search (intersection of results for each term) while
*  type 1 = OR search (union of results for each term)
*/
vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){

  // vector<Product*> retVect;

  // // // hasBeenAdded basically checks whether or not anything is ther and helps prevent using garbage value in eachWordVect
  // vector<int> hasBeenAdded;
  // for(int i = 0; i < int(terms.size()); i++){
  //   hasBeenAdded.push_back(0);
  // }


  // for(int i = 0; i < int(terms.size()); i++){
  //   if(keyWordMapping_.find(terms[i]) != keyWordMapping_.end()){
      
  //     eachWordVect[i].insert(keyWordMapping_[terms[i]]);
  //       hasBeenAdded[i] = 1;
  //   }
  // }

  int totalMatches = 0;

  vector<set<Product*>> eachWordVect;
  for(vector<string>::iterator it = terms.begin(); it != terms.end(); it++){
    if(keyWordMapping_.find(*it) != keyWordMapping_.end()){
      eachWordVect.push_back(keyWordMapping_[*it]);
      totalMatches++;
    }
  }

  // for(map<Product*, set<string>>::iterator it = products_.begin(); it != products_.end(); it++){
  //   // Need to think of ways to avoid garbage values for eachWordVect
  //   for(int i = 0; i < int(terms.size()); i++){
  //     //If the term is somehwere in the set of keywords
  //     if(it->second.find(terms[i]) != it->second.end()){
  //       eachWordVect[i].insert(it->first);
  //       hasBeenAdded[i] = 1;
  //     }
  //   }
  // }

  set<Product*> finalReturn; 

  bool thereWasAMatch = false; 

  // Sets finalReturn equal to something so we are not doing intersections with NULL
  for(int i = 0; i < totalMatches; i++){
      finalReturn = eachWordVect[i];
      thereWasAMatch = true; 
  }

  // If there werent any hits, then return an empty vect
  if(!thereWasAMatch){
    vector<Product*> emptyVect; 
    return emptyVect;
  }


  for(int i = 0; i < totalMatches; i++){
    if(type == 1){
      finalReturn = setUnion(finalReturn, eachWordVect[i]);
    }
    else{
      finalReturn = setIntersection(finalReturn, eachWordVect[i]);
    }
  }

  vector<Product*> returnVector(finalReturn.begin(), finalReturn.end());

  return returnVector;


}




void MyDataStore::addToCart(Product* hit, std::string name)
{
  users_[name]->cart_.push_back(hit);


}

void MyDataStore::viewCart(std::string name)
{
  // std::map<std::string, User*> users_;
  User* temp = users_[name];
  int resultNo = 1;

  for(deque<Product*>::iterator it = temp->cart_.begin(); it != temp->cart_.end(); ++it) {
    cout << "Hit " << setw(3) << resultNo << endl;
    cout << (*it)->displayString() << endl;
    cout << endl;
    resultNo++;
  }
}

void MyDataStore::buyCart(std::string name)
{
  // for(map<string, User*>::iterator it = users_.begin(); )
  while(!users_[name]->cart_.empty()){
    Product* tempProduct = users_[name]->cart_.front();
    if(tempProduct->getQty() >= 1 && users_[name]->getBalance() >= tempProduct->getPrice()){
      tempProduct->subtractQty(1);
      users_[name]->deductAmount(tempProduct->getPrice());
      users_[name]->cart_.pop_front();
    }
    else{
      break;
    }
  }

}

bool MyDataStore::checkIfUserExists(std::string name)
{

  if(users_.find(name) != users_.end()){
    return true;
  }
  return false;

}




/**
* Reproduce the database file from the current Products and User values
*/
// void MyDataStore::dump(std::ostream& ofile);