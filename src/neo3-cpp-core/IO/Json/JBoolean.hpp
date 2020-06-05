#ifndef JBOOLEAN_HPP
#define JBOOLEAN_HPP

// c++ standard part
#include <cmath> // NAN
#include <map>
#include <vector>

// neopt core part
#include "JObject.hpp"
#include <neo3-cpp-core/neopt-common/numbers/UIntBase.hpp>
#include <neo3-cpp-core/neopt-common/system/IComparable.h>
#include <neo3-cpp-core/neopt-common/system/IEquatable.h>
#include <neo3-cpp-core/neopt-common/system/ISerializable.h>
#include <neo3-cpp-core/neopt-common/system/ITextReader.h>
#include <neo3-cpp-core/neopt-common/system/StringReader.hpp>
#include <neo3-cpp-core/neopt-common/system/mhelper.h>
#include <neo3-cpp-core/neopt-common/system/shelper.h>

namespace neopt {

class JBoolean final : public JObject
{
private:
   //bool _b;

public:
   JBoolean(bool b)
     //: _b{ b }
   {
   }

   // ToString()
};
}

#endif
