#include "movie.h"
using namespace std;
#include "util.h"
#include <sstream>

Movie::Movie(string name, double price, int qty, string genre, string rating) :
    Product("movie", name, price, qty)
{
  genre_ = genre;
  rating_ = rating;
}

Movie::~Movie()
{
}

set<string> Movie::keywords() const {
  
  set<string> result;

  set<string> names = parseStringToWords(getName());
  result = setUnion(result, names);

  result.insert(convToLower(genre_));

  //result.insert(convToLower(rating_));

  return result;
}

string Movie::displayString() const {

  stringstream ss;
  ss << getName() << "\n";
  ss << "Genre: " << genre_ << " Rating: " << rating_ << "\n";
  ss << getPrice() << " " << getQty() << " left.";
  return ss.str();
}

void Movie::dump(ostream& os) const {
  Product::dump(os);
  os << genre_ << "\n";
  os << rating_ << "\n";
}
