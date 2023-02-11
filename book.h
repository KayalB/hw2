#ifndef BOOK_H
#define BOOK_H

#include "product.h"
// Kind of Redundant cause already in Product.h, but whatever
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

class Book : public Product{
  public:
    Book(const std::string bName, const std::string bCategory, double bPrice, 
    int bQty, const std::string bIsbn, const std::string bAuthor);
    ~Book();
    std::set<std::string> keywords() const;
    std::string displayString() const;
    void dump(std::ostream& os) const;
  private:
    std::string bIsbn_;
    std::string bAuthor_;
};





#endif
