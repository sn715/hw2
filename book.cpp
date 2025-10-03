#include "book.h"
using namespace std;

#include "util.h"
#include <sstream>

Book::Book(string name, double price, int qty, string isbn, string author) :
    Product("book", name, price, qty)
{
  isbn_ = isbn;
  author_ = author;
}

Book::~Book()
{
}

//virtual functions
set<string> Book::keywords() const {
  
  set<string> result;

  set<string> names = parseStringToWords(getName());
  result = setUnion(result, names);

  set<string> authors = parseStringToWords(author_);
  result = setUnion(result, authors);

  result.insert(convToLower(isbn_));

  return result;
}

string Book::displayString() const {

  stringstream ss;
  ss << getName() << "\n";
  ss << "Author: " << author_ << " ISBN: " << isbn_ << "\n";
  ss << getPrice() << " " << getQty() << " left.";
  return ss.str();
}

void Book::dump(ostream& os) const {
  Product::dump(os);
  os << isbn_ << "\n";
  os << author_ << "\n";
}

