#ifndef CLOTHING_H
#define CLOTHING_H

#include "product.h"

#include <string>

using namespace std;

class Clothing : public Product {
public:
    //constructor
    Clothing(string name, double price, int qty, string size, string brand);
    virtual ~Clothing();

    //virtual functions
    set<string> keywords() const;
    string displayString() const;

    void dump(ostream& os) const;

    //string getSize() const;
    //string getBrand() const;

private:

    //book specific variables
    string size_;
    string brand_;
    
};
#endif