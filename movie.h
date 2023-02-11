#ifndef MOVIE_H
#define MOVIE_H

#include "product.h"
// Kind of Redundant cause already in Product.h, but whatever
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

class Movie : public Product{
  public:
    Movie(const std::string mName, const std::string mCategory, double mPrice, 
    int mQty, const std::string mGenre, const std::string mRating);
    ~Movie();
    std::set<std::string> keywords() const;
    std::string displayString() const;
    void dump(std::ostream& os) const;
  private:
    std::string mGenre_;
    std::string mRating_;
};





#endif
