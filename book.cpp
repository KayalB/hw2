#include "book.h"
#include "util.h"
#include <iostream>


using namespace std;

Book::Book(const std::string bName, const std::string bCategory, double bPrice, 
int bQty, const std::string bIsbn, const std::string bAuthor) :
    Product(bCategory, bName, bPrice, bQty), bIsbn_(bIsbn), bAuthor_(bAuthor)
{

}

Book::~Book()
{

}

set<string> Book::keywords() const
{
  // Return Author and ISBN
  set<string> retSet;

  set<string> nameSet = parseStringToWords(name_);
  set<string> authorSet = parseStringToWords(bAuthor_);
  set<string> isbnSet = parseStringToWords(bIsbn_);

  retSet = setUnion(nameSet, authorSet);
  retSet = setUnion(retSet, isbnSet);

  return retSet;
}

string Book::displayString() const
{
  string retStr;

  retStr += (name_);
  retStr += ("\n");
  retStr += ("Author: ");
  retStr += (bAuthor_);
  retStr += (" ISBN: ");
  retStr += (bIsbn_);
  retStr += ("\n");
  retStr += to_string(price_);
  retStr += (" ");
  retStr += to_string(qty_);
  retStr += (" left.");

  // cout << "---------" << endl << endl;
  // cout << retStr << endl << endl;
  // cout << "---------" << endl;
  return retStr;

}
void Book::dump(std::ostream& os) const
{
  os << category_ << endl;
  os << name_ << endl;
  os << price_ << endl;
  os << qty_ << endl;
  os << bIsbn_ << endl;
  os << bAuthor_ << endl;
}