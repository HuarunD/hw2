#include <sstream>
#include <iomanip>
#include "movie.h"
#include "util.h"
using namespace std;
Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating) :
	Product(category, name, price, qty) {
	genre_ = genre;
	rating_ = rating;
}



Movie::~Movie()
{
}

std::set<std::string>Movie::keywords() const {
	std::string lines = name_;
	std::set<std::string>temp = parseStringToWords(lines);
	temp.insert(genre_);
	return temp;

}

std::string Movie::displayString() const {
	std::string s = name_;
	s += "\nGenre: ";
	s += genre_; 
	s += " Rating: ";
	s += rating_;
	s += '\n';
	s += std::to_string(price_);
	s += " ";
	s += std::to_string(qty_);
	s+=" left\n";
	return s;
}

void Movie::dump(std::ostream& os) const {
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}

