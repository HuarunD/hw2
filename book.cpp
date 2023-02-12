#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"
using namespace std;
Book::Book(const std::string category, const std::string name, double price, int qty, const std::string isbn, const std::string author):
	Product(category, name, price, qty) {
	isbn_ = isbn;
	author_ = author;
}



Book::~Book()
{
}

std::set<std::string> Book::keywords() const {
	std::string lines  = name_ + author_;
	std::set<std::string>temp = parseStringToWords(lines);
	temp.insert(isbn_);
	return temp;

}

std::string Book::displayString() const {
	std::string s = name_;
	s += "\nAuthor: ";
	s += author_; 
	s += " ISBN: ";
	s += isbn_;
	s += '\n';
	s += std::to_string(price_); // need for all 
	s += " ";
	s += std::to_string(qty_);
	s+=" left\n";
	return s;
}

void Book::dump(std::ostream& os) const {
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}