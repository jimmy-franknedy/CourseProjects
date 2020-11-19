// $Id: bigint.cpp,v 1.2 2020-01-06 13:39:55-08 - - $

#include <cstdlib>
#include <exception>
#include <stack>
#include <stdexcept>
using namespace std;

#include "bigint.h"
#include "debug.h"
#include "relops.h"

// NEEDS WORK
bigint::bigint (long that): uvalue (that), is_negative (that < 0) 
{
   // DEBUGF ('~', this << " -> " << uvalue)
}

// NEEDS WORK
bigint::bigint (const ubigint& uvalue_, bool is_negative_):
                uvalue(uvalue_), is_negative(is_negative_) 
{

}

// *DONE*
bigint::bigint (const string& that) 
{
   is_negative = that.size() > 0 and that[0] == '_';
   uvalue = ubigint (that.substr (is_negative ? 1 : 0));
}

// *DONE*
bigint bigint::operator+ () const 
{
   return *this;
}

// *DONE*
bigint bigint::operator- () const 
{
   return {uvalue, not is_negative};
}

// Implemented, Not tested
bigint bigint::operator+ (const bigint& that) const 
{
   bigint result;
   if(is_negative == that.is_negative){
      result.uvalue = uvalue + that.uvalue;
      result.is_negative = is_negative;
   }
   else{
      // Compare values
      if(that.uvalue < uvalue){
         result.uvalue = uvalue - that.uvalue;
         result.is_negative = is_negative;
      }
      else{
         result.uvalue = that.uvalue - uvalue;
         result.is_negative = that.is_negative;
      }
   }
   return result;
}


// NEEDS WORK
bigint bigint::operator- (const bigint& that) const 
{
   //ubigint result = uvalue - that.uvalue;
   bigint result;

   if((is_negative && !that.is_negative) || 
      (!is_negative && that.is_negative)){
      result.uvalue = uvalue + that.uvalue;
      result.is_negative = is_negative;
   }
   else{
      if(that.uvalue < uvalue){
         result.uvalue = uvalue - that.uvalue;
         result.is_negative = is_negative;
      }
      else{
         result.uvalue = that.uvalue - uvalue;
         result.is_negative = !is_negative;
      }
   }
   return result;
}

// *DONE*
bigint bigint::operator* (const bigint& that) const 
{
   bigint result;
   result.uvalue = uvalue * that.uvalue;
   result.is_negative = (is_negative == that.is_negative) ? false : true; 
   return result;
}

// *DONE*
bigint bigint::operator/ (const bigint& that) const 
{
   bigint result = uvalue / that.uvalue;
   result.is_negative = (is_negative == 
      that.is_negative) ? false : true; 
   return result;
}

// *DONE*
bigint bigint::operator% (const bigint& that) const 
{
   bigint result = uvalue % that.uvalue;
   return result;
}

// *DONE*
bool bigint::operator== (const bigint& that) const 
{
   if(is_negative != that.is_negative) return false;
   return uvalue == that.uvalue;
}

// *DONE*
bool bigint::operator< (const bigint& that) const 
{
   if (is_negative != that.is_negative) return is_negative;
   return is_negative ? uvalue > that.uvalue
                      : uvalue < that.uvalue;

}
// *DONE* >> seems like its not working..
ostream& operator<< (ostream& out, const bigint& that) 
{
   return out << (that.is_negative ? "-":"") << that.uvalue;
}