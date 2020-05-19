#ifndef NEOPT_COMMON_SYSTEM_BITCONVERTER_HPP
#define NEOPT_COMMON_SYSTEM_BITCONVERTER_HPP

// system includes
#include <fstream>
#include <iostream>
#include <vector>

// neopt core part
#include "../system/types.h"
//#include<numbers/nhelper.h>

//using namespace std; // TODO: do not use that in the future... prefer std::vector instead

namespace neopt {

class BitConverter
{
public:
   static vbyte GetBytes(unsigned int x)
   {
      std::cout << "GetBytes(" << x << ")" << std::endl;
      // given int is considered to be in bigendian (must return little-endian)
      // 16385 -> 0x00004001 (big endian) ->  [1, 64, 0, 0] (little endian)
      vbyte vb(4, 9);
      vb[0] = x & 0x000000FF;
      vb[1] = (x >> 8) & 0x000000FF;
      vb[2] = (x >> 16) & 0x000000FF;
      vb[3] = (x >> 24) & 0x000000FF;
      return vb;
   }

   static short ToInt16(vbyte data, int from)
   {
      NEOPT_EXCEPTION("NOT IMPLEMENTED BitConverter::ToInt16");
   }

   static unsigned short ToUInt16(vbyte data, int from)
   {
      NEOPT_EXCEPTION("NOT IMPLEMENTED BitConverter::ToUInt16");
   }

   static int ToInt32(vbyte data, int from)
   {
      NEOPT_EXCEPTION("NOT IMPLEMENTED BitConverter::ToInt32");
   }

   static unsigned ToUInt32(vbyte data, int from)
   {
      NEOPT_EXCEPTION("NOT IMPLEMENTED BitConverter::ToUInt32");
   }
};

} // namespace neopt

#endif // NEOPT_COMMON_SYSTEM_BITCONVERTER_HPP
