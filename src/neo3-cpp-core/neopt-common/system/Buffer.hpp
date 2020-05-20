#ifndef BUFFER_HPP
#define BUFFER_HPP

// system includes
#include<cstdlib>
#include<stdio.h>
#include<string.h>

// core includes
#include "../system/types.h"

namespace neopt {

class Buffer
{
public:
   // this copy should overwrite data on destination (not append) // TODO: use memcpy over vector data
   static void BlockCopy(const vbyte& src, int srcOffset, vbyte& dst, int dstOffset, int count)
   {
      // memcpy requires 'restricted' src and dst... assert pointers are different!
      assert(src.data() != dst.data());
      // srcOffset: The zero-based byte offset into src

      //NEOPT_EXCEPTION("Not Implemented BlockCopy");
      ::memcpy(dst.data()+dstOffset, src.data(), count);

      std::cout << "WARNING: WE NEED TO TEST BlockCopy()!!!" << std::endl;
   }
};

}

#endif
