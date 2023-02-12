#include <sstream>
#include <iomanip>
#include "clothing.h"
#include "util.h"
using namespace std;
Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand) :
	Product(category, name, price, qty) {
	size_ = size;
	brand_ = brand;
}



Clothing::~Clothing()
{
}

std::set<std::string>Clothing:: keywords() const {
	std::string lines = name_+brand_;
	std::set<std::string>temp = parseStringToWords(lines);
	return temp;

}

std::string Clothing::displayString() const {
	std::string s = name_;
	s += "\nSize: ";
	s += size_; 
	s += " Brand: ";
	s += brand_;
	s += '\n';
	s += std::to_string(price_);
	s += " ";
	s += std::to_string(qty_);
	s+=" left\n";
	return s;
}


void Clothing::dump(std::ostream& os) const {
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}