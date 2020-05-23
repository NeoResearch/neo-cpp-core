#pragma once

#include "BitConverter.hpp"

namespace neopt {

namespace Encoding {

class ASCII
{
public:
   static vbyte GetBytes(std::string s)
   {
      vbyte bytes;
      for (unsigned i = 0; i < s.size(); i++)
         bytes.push_back(s[i]);
      return bytes;
   };

}; // class ASCII
//
} // namespace Encoding
//
} // namespace neopt