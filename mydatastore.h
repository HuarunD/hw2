#include "datastore.h"
#include <map>

class MyDatastore : public DataStore {
public:
	MyDatastore();
	~MyDatastore();
	void addProduct(Product* p);
	void addUser(User* u);
	std::vector<Product*> search(std::vector<std::string>& terms, int type);
	void addCart(std::string userName, unsigned int index, std::vector<Product*> hits_);
	void viewCart(std::string userName);
	void buyCart(std::string userName);
	void dump(std::ostream& ofile);
private:
	std::map<std::string, std::set<Product*>> products_;
	std::map<std::string, User*>users_;
	std::map<std::string, std::vector<Product*>> carts_;
	std::vector<Product*> product_list;
	std::vector<User*> user_list;
};