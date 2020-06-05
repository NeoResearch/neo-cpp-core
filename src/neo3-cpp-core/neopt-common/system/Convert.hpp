#pragma once

#include <vector>

// library from ReneNyffenegger (zlib license)
#include <cpp-base64/base64.hpp>

#include "types.h"

namespace neopt {

class Convert
{
public:
   static neopt::vbyte FromBase64String(std::string sinput)
   {
      std::string sout = ReneNyffenegger::base64_decode(sinput);
      neopt::vbyte vout((unsigned char*)sout.c_str(), ((unsigned char*)sout.c_str()) + sout.length());
      return vout;
   }

   static std::string ToBase64String(neopt::vbyte vinput)
   {
      std::string sinput((char*)vinput.data(), vinput.size());
      return ReneNyffenegger::base64_encode(sinput);
   }

   static std::string ToBase64String(std::string sinput)
   {
      return ReneNyffenegger::base64_encode(sinput);
   }
};

} // namespace neopt
