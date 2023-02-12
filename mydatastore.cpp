#include "mydatastore.h"
#include "util.h"

MyDatastore::MyDatastore()
{
}

MyDatastore::~MyDatastore()
{
	for(unsigned int i=0;i<user_list.size();i++){
		delete user_list[i];
	}
		for(unsigned int i=0;i<product_list.size();i++){
		delete product_list[i];
	}
}

void MyDatastore::addProduct(Product* p)
{
	product_list.push_back(p);
	std::set<std::string>temp = p->keywords();
	//int count = 0;
	for (std::set<std::string>::iterator it2 = temp.begin(); it2 != temp.end(); ++it2) {
		std::map<std::string, std::set<Product*>> ::iterator it = products_.find(convToLower(*it2));
		//std :: cout << "Inserted" <<count << std::endl;
		//count ++;
		if (it != products_.end()) {
			it->second.insert(p);
		}
		else {
			std::set<Product*> related;
			related.insert(p);
			products_.insert(std::make_pair(convToLower(*it2), related));
		}
	}
}

void MyDatastore::addUser(User* u)
{
	user_list.push_back(u);
	users_.insert(std::make_pair(u->getName(), u));
	std::vector<Product*> myCart;
	carts_.insert(std::make_pair(u->getName(), myCart));

}

std::vector<Product*> MyDatastore::search(std::vector<std::string>& terms, int type)
{
	std::vector<Product*> search_result;
	std::set<Product*> set_result;
	std::set<Product*> keyword; 
	if(type == 0){
		for (unsigned int i = 0; i < terms.size(); i++) {
			if(products_.find(terms[i])!=products_.end()){
				if(i == 0){
					set_result = products_[terms[i]];
				}
				else{
					set_result = setIntersection(set_result, products_[terms[i]]);
				}			
			}
		}
	}
	else if(type == 1){
		for (unsigned int i = 0; i < terms.size(); i++) {
			if(products_.find(terms[i])!=products_.end()){
				if(i == 0){
					set_result = products_[terms[i]];
				}
					set_result = setUnion(set_result, products_[terms[i]]);
			}

		}
	}
	for(std::set<Product*>::iterator it=set_result.begin();it != set_result.end();++it){
		search_result.push_back(*it);
	}
	return search_result;
}
void MyDatastore::addCart(std::string userName,unsigned int index, std::vector<Product*> hits_)
{
	if(users_.find(userName)==users_.end()||index>hits_.size()){
		std::cout << "Invalid request" << std::endl;
	}	
	else{
		std::map<std::string, std::vector<Product*>> :: iterator it = carts_.find(userName);
		it->second.push_back(hits_[index-1]);		
	}
}

void MyDatastore::viewCart(std::string userName)
{
	if(users_.find(userName)==users_.end()){
		std::cout << "Invalid username" << std::endl;
	}	
	else{
			std::map<std::string, std::vector<Product*>> :: iterator it = carts_.find(userName);
			for(unsigned int i = 0; i < it->second.size(); i++){
				std:: cout << "Item " << i+1 << std::endl;
				std:: cout << it->second[i]->displayString() << std::endl;
			}
		
	}
}

void MyDatastore::buyCart(std::string userName)
{
	if(users_.find(userName)==users_.end()){
		std::cout << "Invalid username" << std::endl;
	}	

	else{
			std::map<std::string, std::vector<Product*>> :: iterator it = carts_.find(userName);
			User* me = users_.find(userName)->second;
			std::vector<Product*> afterpurchase;
			for (unsigned int i = 0; i < it->second.size(); i++){
				int price = it->second[i]->getPrice();
				if(me->getBalance()>price && it->second[i]->getQty()!=0){
					me->deductAmount(price);
					it->second[i]->subtractQty(1);
				}
				else{
					afterpurchase.push_back(it->second[i]);
				}
			}	
			it->second = afterpurchase;	
	}
}

void MyDatastore::dump(std::ostream& ofile)
{
	ofile << "<products>" << std::endl;
	for (unsigned int i = 0; i < product_list.size(); i++) {
		product_list[i]->dump(ofile);
	}
	ofile << "</products>" << std::endl;
	ofile << "<users>" << std::endl;
	for (unsigned int i = 0; i < user_list.size(); i++) {
		user_list[i]->dump(ofile);		
	}
	ofile << "</users>" << std::endl;

}
