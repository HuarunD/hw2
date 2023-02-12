#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)// possible error here
{
  set<std::string> temp;
	//int count = 0;
  while (!rawWords.empty()) {
		rawWords = trim(rawWords);
    for (unsigned int i = 0; i < rawWords.size(); i++) {
      if (rawWords[i] < 65 || (rawWords[i] > 90 && rawWords[i] < 97) || rawWords[i]>122|| i == rawWords.size()-1) {
        string temp1;
				if(i == rawWords.size()-1){
					temp1  = rawWords.substr(0);
				}
				else{
					temp1 = rawWords.substr(0, i);
				}
        if(temp1.size()>=2){
					temp.insert(temp1);
				}
				rawWords = rawWords.substr(i+1,rawWords.size()); 
				break;
      }

    }
  }
  return temp;
   
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

// int main() {

//     string s = "Data Abstraction & Problem Solving with C++";
//     std::set<std::string>temp = parseStringToWords(s);
//     std::set<string>::iterator it;
//     for(it = temp.begin();it!=temp.end();++it){
//         std::cout<<*it<<endl;
//     }
//     return 0;
// }