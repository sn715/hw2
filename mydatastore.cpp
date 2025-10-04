#include "mydatastore.h"
#include <string>
#include <set>
#include <vector>

#include "util.h" //union and intersection functionality
using namespace std;

MyDataStore::MyDataStore() {

}

MyDataStore::~MyDataStore() {
//delete all the products stored and users 

  for (size_t i = 0; i < products_.size(); i++) {
    delete products_[i];
  }

  map<string, User*>::iterator it;

  for (it = users_.begin(); it != users_.end(); ++it) {
    delete it->second; // deletes the value
  }
}

void MyDataStore::addProduct(Product* p) {
  //need to take in a product and add it to the datastore
  products_.push_back(p);

  //add product to keywords 
  set<string> keywords = p->keywords();

  //debug
  cout << "debug: product " << p->getName() << endl;
  cout << "debug: keywords: " << endl;
  for (set<string>::iterator itt = keywords.begin(); itt != keywords.end(); ++itt) {
    cout << *itt;
  }
  cout << endl;

  set<string>::iterator it;
  for (it = keywords.begin(); it != keywords.end(); ++it) {
    //string lower = convToLower(*it);
    keywords_[*it].insert(p);
  }
}

void MyDataStore::addUser(User* u) {
  string lower = convToLower(u->getName());
  users_[lower] = u;
  //users_.insert({u->getName(), u}); // or users_[u->getName()] = u
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {

  //make a set of products
  set<Product*> results;

  if (terms.empty()) {
    return vector<Product*>(); // empty vector
  }

  if (type == 0) {
    //AND

    //take the first term and save it in keywords
    //iterate through the rest of the terms and save the intersection
    //of that term with the rest of keywords

    if(keywords_.find(terms[0]) != keywords_.end()) 
    {
      results = (keywords_[terms[0]]);
    }

    for (size_t i = 1; i < terms.size(); i++) 
    {
      set<Product*> temp;
      if(keywords_.find(terms[i]) != keywords_.end())
      {
        temp = keywords_[terms[i]];
      }
      results = setIntersection(results, temp);
    }
  }
  else if (type == 1) {
    //OR 
    for (size_t i = 0; i < terms.size(); i++) 
    {
      if(keywords_.find(terms[i]) != keywords_.end())
      {
        //set<Product*> temp = keywords_[terms[i]];
        //results = setUnion(results, temp);
        results = setUnion(results, keywords_[terms[i]]);
      }
    }
  }

  //convert set to vector
  vector<Product*> vResults(results.begin(), results.end());
  return vResults;
 
}

void MyDataStore::dump(std::ostream& ofile) {
  //need to implement
  ofile << "<products>" << endl;
  for (size_t i = 0; i < products_.size(); i++) {
    products_[i]->dump(ofile);
  }
  ofile << "</products>" << endl;

  ofile << "<users>" << endl;
  map<string, User*>::iterator it;
  for (it = users_.begin(); it != users_.end(); ++it)
  {
    it->second->dump(ofile);
  }
  ofile << "</users>" << endl;

}

void MyDataStore::addToCart(string username, Product* p) { // input parameter Product* p?
  //check if user exists

  string lower = convToLower(username);

  if(users_.find(lower) == users_.end()) {
    cout << "Invalid request" << endl;
    return;
  }

  carts_[lower].push_back(p);
}

void MyDataStore::viewCart(string username) {
  
  //check for user
  string lower = convToLower(username);

  if(users_.find(lower) == users_.end()) {
  cout << "Invalid username" << endl;
  return;
  }

  vector<Product*>& cart = carts_[lower];

  for (size_t i = 0; i < cart.size(); i++) 
  {
    cout << "Item " << (i + 1) << endl;
    cout << cart[i]->displayString() << endl;
    cout << endl;
  }
}
void MyDataStore::buyCart(string username) {

  /*check for user
  string lower = convToLower(username);

  User* user = users_[lower];
  vector<Product*>& cart = carts_[lower];
  vector<Product*> purchased;

  for (size_t i = 0; i < cart.size(); i++)
  {
    Product* p = cart[i];

    if (p->getQty() > 0) 
    {
      if (user->getBalance() >= p->getPrice()) 
      {
        user->deductAmount(p->getPrice());
        p->subtractQty(1);
        purchased.push_back(p);
      }
    }
  }

  for (size_t i = 0; i < purchased.size(); i++) 
  {
    vector<Product*>::iterator it;
    for(it = cart.begin(); it != cart.end(); ++it)
    {
      if (*it == purchased[i])
      {
        cart.erase(it);
        break;
      }
    }
  }
  */

  string lower = convToLower(username);

  if (users_.find(lower) == users_.end()) {
    cout << "Invalid username" << endl;
    return;
  }

  User* user = users_[lower];
  vector<Product*>& cart = carts_[lower];

  vector<Product*>::iterator it = cart.begin();

  while (it != cart.end()) {
    Product* p = *it;

    if(p->getQty() > 0 && user->getBalance() >= p->getPrice()) {
      user->deductAmount(p->getPrice());
      p->subtractQty(1);
      it = cart.erase(it);
    }
    else {
      ++it;
    }
  }
}
