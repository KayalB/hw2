#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const std::string cName, const std::string cCategory, double cPrice, 
int cQty, const std::string cSize, const std::string cBrand) :
    Product(cCategory, cName, cPrice, cQty), cBrand_(cBrand), cSize_(cSize)
{

}

Clothing::~Clothing()
{

}

set<string> Clothing::keywords() const
{
  set<string> retSet;

  set<string> nameSet = parseStringToWords(name_);
  set<string> brandSet = parseStringToWords(cBrand_);

  retSet = setUnion(nameSet, brandSet);

  return retSet;
}

string Clothing::displayString() const
{
  string retStr;

  retStr += (name_);
  retStr += ("\n");
  retStr += ("Size: ");
  retStr += (cSize_);
  retStr += (" Brand: ");
  retStr += (cBrand_);
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
void Clothing::dump(std::ostream& os) const
{
  os << category_ << endl;
  os << name_ << endl;
  os << price_ << endl;
  os << qty_ << endl;
  os << cSize_ << endl;
  os << cBrand_ << endl;
}