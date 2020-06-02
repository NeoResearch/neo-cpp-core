#ifndef JNUMBER_HPP
#define JNUMBER_HPP

// c++ standard part
#include <cmath> // NAN
#include <map>
#include <vector>

// neopt core part
#include "../numbers/UIntBase.hpp"
#include "../system/IComparable.h"
#include "../system/IEquatable.h"
#include "../system/ISerializable.h"
#include "../system/ITextReader.h"
#include "../system/StringReader.hpp"
#include "../system/mhelper.h"
#include "../system/shelper.h"
#include "JObject.hpp"

namespace neopt {

class JNumber final : public JObject
{
private:
   double _d;

public:
   std::string ToString() const
   {
      std::stringstream ss;
      ss << _d;
      return ss.str();
   }

   JNumber(double d)
     : _d{ d }
   {
   }

   JNumber(int d)
     : _d{ (double) d }
   {
   }

   virtual ~JNumber()
   {
   }
};
}

#endif
