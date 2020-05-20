#pragma once

#include <assert.h>

// this is highly experimental

#include "types.h" // vbyte

namespace neopt {
//
class MemoryStream
{
public:
   vbyte internal_buffer;

   vbyte ToArray()
   {
      return internal_buffer;
   }
};
//
} // namespace neopt
//
