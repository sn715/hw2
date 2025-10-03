#include "clothing.h"
using namespace std;
#include "util.h"
#include <sstream>

Clothing::Clothing(string name, double price, int qty, string size, string brand) :
    Product("clothing", name, price, qty)
{
  size_ = size;
  brand_ = brand;
}

Clothing::~Clothing()
{
}

set<string> Clothing::keywords() const {
  
  set<string> result;

  set<string> names = parseStringToWords(getName());
  result = setUnion(result, names);

  set<string> brands = parseStringToWords(brand_);
  result = setUnion(result, brands);

  result.insert(convToLower(size_));

  return result;
}

string Clothing::displayString() const {

  stringstream ss;
  ss << getName() << "\n";
  ss << "Size: " << size_ << " Brand: " << brand_ << "\n";
  ss << getPrice() << " " << getQty() << " left.";
  return ss.str();
}

void Clothing::dump(ostream& os) const {
  Product::dump(os);
  os << size_ << "\n";
  os << brand_ << "\n";
}
