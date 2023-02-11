#ifndef CLOTHING_H
#define CLOTHING_H

#include "product.h"
// Kind of Redundant cause already in Product.h, but whatever
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

class Clothing : public Product{
  public:
    Clothing(const std::string cName, const std::string cCategory, double cPrice, 
    int cQty, const std::string cBrand, const std::string cSize);
    ~Clothing();
    std::set<std::string> keywords() const;
    std::string displayString() const;
    void dump(std::ostream& os) const;
  private:
    std::string cBrand_;
    std::string cSize_;
};





#endif
