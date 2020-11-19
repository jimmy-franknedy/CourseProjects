// $Id: ubigint.cpp,v 1.9 2020-07-02 15:38:57-07 - - $
// Edward Garcia
// Jimmy Franknedy


#include <cctype>
#include <cstdlib>
#include <exception>
#include <stack>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <sstream>

using namespace std;
#include "ubigint.h"
#include "debug.h"

ubigint::ubigint (unsigned long that)
{
   for (char digit: to_string(that))
   {
      ubig_value.insert(ubig_value.begin(),digit-'0');
   }
   cutZeros();
}


// *DONE*
ubigint::ubigint (const string& that)
{
   // DEBUGF ('~', "that = \"" << that << "\"");
   for (char digit: that) 
   {
      if (not isdigit (digit)) 
      {
         throw invalid_argument ("ubigint::ubigint(" + that + ")");
      }
      ubig_value.insert(ubig_value.begin(),digit-'0');
   }
   cutZeros();
}

// TEST PASSED
ubigint ubigint::operator+ (const ubigint& that) const 
{
   // DEBUGF ('u', *this << "+" << that);
   ubigint result;
   udigit_t sum = 0;
   udigit_t remndr = 0;
   udigit_t carry = 0;
   if(ubig_value.size() > that.ubig_value.size()
      || ubig_value.size() == that.ubig_value.size()){
      for (size_t i = 0; i < ubig_value.size(); i++){
         if(i >= that.ubig_value.size()){
            sum = ubig_value[i] + 0 + carry;
         }
         else
            sum = ubig_value[i] + that.ubig_value[i] + carry;
         if(sum > 9){
            carry = sum/10;
            remndr = sum%10;
            result.ubig_value.push_back(remndr);
         }
         else{
            result.ubig_value.push_back(sum);
            carry = 0;
         }
         if(i == ubig_value.size() - 1 && carry > 0)
            result.ubig_value.push_back(carry);
      }
   }
   else{
      for (size_t i = 0; i < that.ubig_value.size(); i++){
         if(i >= ubig_value.size()){
            sum = that.ubig_value[i] + 0 + carry;
         }
         else
            sum = that.ubig_value[i] + ubig_value[i] + carry;
         if(sum > 9){
            carry = sum/10;
            remndr = sum%10;
            result.ubig_value.push_back(remndr);
         }
         else{
            result.ubig_value.push_back(sum);
            carry = 0;
         }
         if(i == that.ubig_value.size() - 1 && carry > 0)
            result.ubig_value.push_back(carry);
      }
   }
   DEBUGF ('u', result);
   result.cutZeros();
   return result;
}

// IMPLEMENTED NOT TESTED THOUGH
ubigint ubigint::operator- (const ubigint& that) const 
{
   if (*this < that) throw domain_error ("ubigint::operator-(a<b)");
   ubigint result;
   udigit_t difference = 0;
   udigit_t borrow = 0;

   for(size_t i = 0; i < ubig_value.size(); i++){
      if(i >= that.ubig_value.size()){
         difference = ubig_value[i] + borrow;
         borrow = 0;
      }
      else{
         if(ubig_value[i] < that.ubig_value[i]){
            difference = ubig_value[i] + 10 
            - that.ubig_value[i] + borrow;
            borrow = -1;
         }
         else{
            difference = ubig_value[i] - that.ubig_value[i] + borrow;
            borrow = 0;
         }
      }
      result.ubig_value.push_back(difference);
   }
   // Trim 0s
   result.cutZeros();
   return result;
}

// *DONE*
ubigint ubigint::operator* (const ubigint& that) const 
{
   ubigint result;
   ubigint zero {0};
   if(*this == zero || that == zero) return zero;
   result.ubig_value.resize(ubig_value.size()+that.ubig_value.size());
   for(auto index = ubig_value.begin(); index != ubig_value.end();
   ++index)
   {
      auto C = 0;  // CarryOver
      auto index_distance = distance(ubig_value.begin(),index);
      for(auto idx= that.ubig_value.begin();idx!=that.ubig_value.end();
      ++idx)
      {
         auto idx_distance = distance(that.ubig_value.begin(),idx); 
         auto d = result.ubig_value.at(index_distance+idx_distance) + 
         (ubig_value.at(index_distance)
         *that.ubig_value.at(idx_distance)) + C;
         result.ubig_value.at(index_distance+idx_distance) = d % 10;
         C = floor(d/10);
      }
      result.ubig_value.at(index_distance+that.ubig_value.size()) = C;
   }
   result.cutZeros();
   return result;
}

// NEEDS WORK
void ubigint::multiply_by_2() 
{
   ubigint result = *this + *this;
   ubig_value = result.ubig_value;
   cutZeros();
}

// NEEDS WORK
void ubigint::divide_by_2() 
{
   ubigint result;
   ubig_value.push_back(0);
   for(int big_loop = ubig_value.size()-1; big_loop >= 1; big_loop--)
   {
      int loop = big_loop;
      int first = (ubig_value.at(loop));
      int second = (ubig_value.at(loop-1));

      if(first % 2 == 0)
      {
         for(int counter = 0; counter < 9; counter++)
         {
            if(second == counter || second == counter + 1)
            {
               result.ubig_value.insert(result.ubig_value.begin(),
               (counter/2));
               counter = 10;
            }
            counter++;
         }
      }
      else
      {
         for(int counter = 0; counter < 9; counter++)
         {
            if(second == counter || second == counter + 1)
            {
               result.ubig_value.insert(result.ubig_value.begin(),
               (counter/2)+5);
               counter = 10;
            }
            counter++;
         }
      }
   }
   result.cutZeros();
   ubig_value = result.ubig_value;
}

void ubigint::cutZeros()
{
   while(ubig_value.size() > 1 and ubig_value.back() == 0)
   {
      ubig_value.pop_back(); 
   }
}


struct quo_rem { ubigint quotient; ubigint remainder; };
quo_rem udivide (const ubigint& dividend, const ubigint& divisor_) 
{
   // NOTE: udivide is a non-member function.
   ubigint divisor {divisor_};
   ubigint zero {0};
   if (divisor == zero) throw domain_error ("udivide by zero");
   ubigint power_of_2 {1};
   ubigint quotient {0};
   ubigint remainder {dividend}; // left operand,
   while (divisor < remainder) 
   {
      divisor.multiply_by_2();
      power_of_2.multiply_by_2();  
   }

   while (power_of_2 > zero)
   {
      if (divisor <= remainder) 
      {
         remainder = remainder - divisor;
         quotient = quotient + power_of_2;
      }
      divisor.divide_by_2();
      power_of_2.divide_by_2();
   }
   return {.quotient = quotient, .remainder = remainder};
}

// Overloaded Operators

// *DONE*
ubigint ubigint::operator/ (const ubigint& that) const 
{
   return udivide (*this, that).quotient;
}

// *DONE*
ubigint ubigint::operator% (const ubigint& that) const 
{
   return udivide (*this, that).remainder;
}

// *DONE*
bool ubigint::operator== (const ubigint& that) const 
{
   int thisSize = ubig_value.size();
   int thatSize = that.ubig_value.size();
   if(thisSize != thatSize) return false;
   for(auto idx = ubig_value.begin(); idx != ubig_value.end();++idx)
   {
      auto idx_distance = distance(ubig_value.begin(),idx);
      if((ubig_value.at(idx_distance)+'0') != 
         (that.ubig_value.at(idx_distance)+'0')) return false;
   }
   return true;
}

// *DONE*
bool ubigint::operator< (const ubigint& that) const 
{
   if (ubig_value.size() < that.ubig_value.size())
   {
      // cout << "(a)" << endl;
      return true;
   }

   else if(ubig_value.size()==that.ubig_value.size()&&!(*this==that))
   {
      for(int index = ubig_value.size()-1 ; index >= 0 ; index--)
      {
         if(ubig_value.at(index) < that.ubig_value.at(index)) 
             return true;
         else if(ubig_value.at(index) > that.ubig_value.at(index)) 
             return false;
      }
   }
   return false;
}

// *DONE* 
ostream& operator<< (ostream& out, const ubigint& that) 
{ 
   // Specific for printing out value for debugging
   for(auto index = that.ubig_value.end(); 
      index != that.ubig_value.begin(); --index)
   {
      auto index_distance =distance(that.ubig_value.end(),index)-1;
      index_distance += that.ubig_value.size();
      out << that.ubig_value.at(index_distance) + 0;
      int check = distance(that.ubig_value.end(),index) - 1;
      if(check % 69 == 0 && 
         (index != that.ubig_value.end())) out << "\\" << endl;
   }
   return out;
}
