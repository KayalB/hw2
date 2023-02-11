#include "movie.h"
#include "util.h"
using namespace std;

Movie::Movie(const std::string mName, const std::string mCategory, double mPrice, 
int mQty, const std::string mGenre, const std::string mRating) :
    Product(mCategory, mName, mPrice, mQty), mGenre_(mGenre), mRating_(mRating)
{

}

Movie::~Movie()
{

}

set<string> Movie::keywords() const
{
  // Return Author and ISBN
  set<string> retSet;
  set<string> nameSet = parseStringToWords(name_);
  set<string> genreSet = parseStringToWords(mGenre_);

  retSet = setUnion(nameSet, genreSet);

  return retSet;
}

string Movie::displayString() const
{
  string retStr;

  retStr += (name_);
  retStr += ("\n");
  retStr += ("Genre: ");
  retStr += (mGenre_);
  retStr += (" Rating: ");
  retStr += (mRating_);
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
void Movie::dump(std::ostream& os) const
{
  os << category_ << endl;
  os << name_ << endl;
  os << price_ << endl;
  os << qty_ << endl;
  os << mGenre_ << endl;
  os << mRating_ << endl;
}