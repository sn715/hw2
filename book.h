#ifndef BOOK_H
#define BOOK_H

#include "product.h"

#include <string>

using namespace std;

class Book : public Product {
public:
    //constructor
    Book(string name, double price, int qty, string isbn, string author);
    virtual ~Book();

    //virtual functions
    set<string> keywords() const;
    string displayString() const;

    void dump(ostream& os) const;

    //string getISBN() const;
    //string getAuthor() const;

private:

    //book specific variables
    string isbn_;
    string author_;
    
};
#endif
