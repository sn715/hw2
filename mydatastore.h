#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include <map>

#include "datastore.h"
#include "product.h"
#include "user.h"

using namespace std;

class MyDataStore : public DataStore {

public:
  MyDataStore();
  ~MyDataStore();

  void addProduct(Product* p);
  void addUser(User* u);
  std::vector<Product*> search(std::vector<std::string>& terms, int type);
  void dump(std::ostream& ofile);

  void addToCart(string username, Product* p); // input parameter Product* p?
  void viewCart(string username);
  void buyCart(string username);

private:

  vector<Product*> products_;

  //maps for keyword->products
  map<string, set<Product*>> keywords_;

  //map for username->user
  map<string, User*> users_;

  //map for username->cart where cart is a vector of products
  map<string, vector<Product*>> carts_; //string = username

};

#endif
