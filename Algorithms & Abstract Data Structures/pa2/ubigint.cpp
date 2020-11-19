// $Id: ubigint.cpp,v 1.9 2020-07-02 15:38:57-07 - - $

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
   // DEBUGF ('~', this << " -> " << ubig_value);
   int temp = int(that);
   int sum = 0;
   int counter = 10;
   if(temp >= counter)
   {
      // cout << "a" << endl;
      while (temp >= counter)
      {
         ubig_value.push_back(((temp)% counter) - sum);
         sum += temp % counter;
         counter *= 10;
      }
   }
   else
   {
      // cout << "b" << endl;
      ubig_value.push_back(temp);
      // static_cast <unsigned> (ubig_value.at(ubig_value.size()-1));
   }
   cutZeros();
   // cout << *this << endl;
}


// *DONE*
ubigint::ubigint (const string& that)
{
   DEBUGF ('~', "that = \"" << that << "\"");
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
   DEBUGF ('u', *this << "+" << that);
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
   // Note
   if (*this < that) throw domain_error ("ubigint::operator-(a<b)");
   ubigint result;
   udigit_t difference = 0;
   udigit_t borrow = 0;
   // udigit_t ten = 10;
   // udigit_t carry = 0;

   for(size_t i = 0; i < ubig_value.size(); i++){
      if(i >= that.ubig_value.size()){
         difference = ubig_value[i] + borrow;
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
   result.cutZeros();
   return result;
}

// *DONE*
ubigint ubigint::operator* (const ubigint& that) const 
{
   ubigint result;
   ubigint zero {0};
   if(*this == zero || that == zero) return zero;
   result.ubig_value.resize(ubig_value.size() + that.ubig_value.size()); // p <- sigma
   for(auto index = ubig_value.begin(); index != ubig_value.end(); ++index)
   {
      auto C = 0;  // CarryOver
      auto index_distance = distance(ubig_value.begin(),index);
      for(auto idx = that.ubig_value.begin(); idx != that.ubig_value.end();++idx)
      {
         auto idx_distance = distance(that.ubig_value.begin(),idx); 
         auto d = result.ubig_value.at(index_distance+idx_distance) + 
         (ubig_value.at(index_distance) * that.ubig_value.at(idx_distance)) + C; // Current Answer
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

   // cout << "this: " << *this << endl;
   // cout << "big_loop: " << ubig_value.size()-1 << endl;

   for(int big_loop = ubig_value.size()-1; big_loop >= 1; big_loop--)
   {
      int loop = big_loop;
      int first = (ubig_value.at(loop)+0);
      // cout << "first: "<< first << endl;
      int second = (ubig_value.at(loop-1)+0);
      // cout << "second: "<< second << endl;

      if(first % 2 == 0)
      {
         for(int counter = 0; counter < 9; counter++)
         {
            if(second == counter || second == counter + 1)
            {
               result.ubig_value.insert(result.ubig_value.begin(),(counter/2));
               counter = 10;
            }
            counter++;
         }
      }
      else
      {
         // cout << "c2" << endl;
         for(int counter = 0; counter < 9; counter++)
         {
            if(second == counter || second == counter + 1)
            {
               result.ubig_value.insert(result.ubig_value.begin(),(counter/2)+5);
               counter = 10;
            }
            counter++;
         }
      }
   }
   result.cutZeros();
   ubig_value = result.ubig_value;
   // cout << "-FF result = " << result << endl;
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
   // cout << "START" << endl;
   ubigint power_of_2 {1};
   // cout << "END" << endl;
   ubigint quotient {0};
   ubigint remainder {dividend}; // left operand,

   // =========================================================
   // cout << "divisor: "<< divisor << endl;        
   // cout << "power_of_2: " << power_of_2 << endl;
   // divisor.divide_by_2();
   // power_of_2.divide_by_2();
   // cout << "mdivisor: "<< divisor << endl;       
   // cout << "mpower_of_2: " << power_of_2 << endl;
   // =========================================================

   // =========================================================
   // cout << "divisor: " << divisor << endl;  
   // cout << "remainder: " << remainder << endl;   
   // =========================================================

   int check = 0;
   while (divisor < remainder) 
   {
      check++;
      divisor.multiply_by_2();
      power_of_2.multiply_by_2();
      // cout << "while~divisor: " << divisor << endl;
      // cout << "while~power: " << power_of_2 << endl;
      // cout << "while~remainder: " << remainder << endl;     
   }

   // =========================================================
   // cout << "final check: " << check << endl;            
   // cout << "divisor: " << divisor << endl;  
   // cout << "remainder: " << remainder << endl;      
   // cout << "power_of_2: " << power_of_2 << endl << endl << endl; 
   // =========================================================

   int stop = 0;
   while (power_of_2 > zero)
   {

      // if(stop == 2) break;

      cout << ":div " << divisor << endl;
      cout << ":rem " << remainder << endl;

      if (divisor <= remainder) 
      {
         cout << "b:rem " << remainder << endl;
         cout << "b:quo " << quotient << endl;

         remainder = remainder - divisor;
         quotient = quotient + power_of_2;

         // cout << "a:rem " << remainder << endl;
         // cout << "a:quo " << quotient << endl;
      }

      break;

      divisor.divide_by_2();
      power_of_2.divide_by_2();

      // cout << "stop: " << stop << endl;
      // cout << "divisor: "<< divisor << endl;
      // cout << "power_of_2: " << power_of_2 << endl << endl << endl;

      stop++;
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


   cout << "B" << endl;
   int thisSize = ubig_value.size();
   int thatSize = that.ubig_value.size();
   cout << "thisSize: " << ubig_value.size() << ":" << *this << endl;
   cout << "thatSize: " << that.ubig_value.size() << ":" << that << endl; 



   if(thisSize != thatSize) return false;
   for(auto idx = ubig_value.begin(); idx != ubig_value.end(); ++idx)
   {
      cout << "loop" << endl;
      int idx_distance = distance(ubig_value.begin(),idx);

      cout << "ubig_value.at(" << idx_distance << ") is " << ubig_value.at(idx_distance) << endl;
      cout << "that.big_value.at(" << idx_distance << ") is " << that.ubig_value.at(idx_distance) << endl;

      if(ubig_value.at(idx_distance) != that.ubig_value.at(idx_distance)) return false;
   }
   return true;
}

// *DONE*
bool ubigint::operator< (const ubigint& that) const 
{

   cout << "@" << endl;
   cout << "thisSize: " << ubig_value.size() << endl;
   cout << "thatSize: " << that.ubig_value.size() << endl;

   // If vectors are the same size
   if(ubig_value.size() == that.ubig_value.size())
   {
      for(int index = ubig_value.size()-1 ; index >= 0 ; index--)
      {
         // cout << "ubig_value.at(" << index << ") is " << ubig_value.at(index) << endl;
         // cout << "that.big_value.at(" << index << ") is " << that.ubig_value.at(index) << endl;
         // if((ubig_value.at(index)) > (that.ubig_value.at(index)))
         // {
         //    cout << "this > that" << endl;
         //    return false;
         // }

         auto v1 = int(ubig_value.at(index));
         auto v2 = int(that.ubig_value.at(index));
         
         // cout << "(v1) ubig_value.at(" << index << ") is " << v1 << endl;
         // cout << "(v2) that.big_value.at(" << index << ") is " << v2 << endl;

         if(v1 < v2) return true;
         else return false;
      }
   }
   // If vectors are not same size 
   if (ubig_value.size() < that.ubig_value.size()) return true;
   return false;
}

// *DONE* 
ostream& operator<< (ostream& out, const ubigint& that) 
{ 
   // Specific for printing out value for debugging
   for(auto index = that.ubig_value.end(); 
      index != that.ubig_value.begin(); --index)
   {
      auto index_distance = distance(that.ubig_value.end(),index) - 1;
      index_distance += that.ubig_value.size();
      out << that.ubig_value.at(index_distance) + 0;
      int check = distance(that.ubig_value.end(),index) - 1;
      if(check % 69 == 0 && 
         (index != that.ubig_value.end())) out << "\\" << endl;
   }
   return out;
}