#include <string>

struct AlphaStrComp {
  bool operator() (const std::string& lhs, const std::string& rhs)
  { // Uses string's built in operator<
    // to do lexicographic (alphabetical) comparison
    return (lhs < rhs);
  }
};

struct LengthStrComp {
  bool operator()(const std::string& lhs, const std::string& rhs)
  { // Compares strings by size;
    // Breaks ties by lexicographic comparison
    return (   (lhs.size() < rhs.size())
            || (lhs.size() == rhs.size() && lhs < rhs));
  }
};

struct NumStrComp{
  bool operator()(const std::string& lhs, const std::string& rhs)
  {
    int lhsVal = 0;
    int rhsVal = 0;
    //get the value of 
    for (size_t i = 0; i < lhs.size();i++){
      if(lhs[i] >= '0' && lhs[i] <= '9'){
        lhsVal += lhs[i] - '0';
      }
      else if (lhs[i] >= 'a' && lhs[i] <= 'z'){
        lhsVal += lhs[i] - 'a' + 10;
      }
      else if (lhs[i] >= 'A' && lhs[i] <= 'Z'){
        lhsVal += lhs[i] - 'A' + 10;
      }
    } 

    for (size_t i = 0; i < rhs.size();i++){
      if(rhs[i] >= '0' && rhs[i] <= '9'){
        rhsVal += rhs[i] - '0';
      }
      else if (rhs[i] >= 'a' && rhs[i] <= 'z'){
        rhsVal += rhs[i] - 'a' + 10;
      }
      else if (rhs[i] >= 'A' && rhs[i] <= 'Z'){
        rhsVal += rhs[i] - 'A' + 10;
      }
    } 
    if (lhsVal != rhsVal){
      return lhsVal < rhsVal;
    }
    else{
      return lhs < rhs;
    }

  }
};

template <class Comparator>
void DoStringCompare(const std::string& s1, const std::string& s2, Comparator comp)
{
  std::cout << comp(s1, s2) << std::endl;  // calls comp.operator()(s1,s2);
}