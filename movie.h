#ifndef MOVIE_H
#define MOVIE_H

#include "product.h"

#include <string>

using namespace std;

class Movie : public Product {
public:
    //constructor
    Movie(string name, double price, int qty, string genre, string rating);
    virtual ~Movie();

    //virtual functions
    set<string> keywords() const;
    string displayString() const;

    void dump(ostream& os) const;

private:

    //book specific variables
    string genre_;
    string rating_;
    
};
#endif
