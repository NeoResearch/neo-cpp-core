#ifndef JNUMBER_HPP
#define JNUMBER_HPP

// c++ standard part
#include <cmath> // NAN
#include <map>
#include <vector>

// neopt core part
#include <neo3-cpp-core/neopt-common/numbers/UIntBase.hpp>
#include <neo3-cpp-core/neopt-common/system/IComparable.h>
#include <neo3-cpp-core/neopt-common/system/IEquatable.h>
#include <neo3-cpp-core/neopt-common/system/ISerializable.h>
#include <neo3-cpp-core/neopt-common/system/ITextReader.h>
#include <neo3-cpp-core/neopt-common/system/StringReader.hpp>
#include <neo3-cpp-core/neopt-common/system/mhelper.h>
#include <neo3-cpp-core/neopt-common/system/shelper.h>
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
