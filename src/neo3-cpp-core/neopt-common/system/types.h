#ifndef NEOPT_TYPES_H
#define NEOPT_TYPES_H

// system includes
#include <limits>
#include <sstream>
#include <vector>
#include <memory> // unique_ptr

// core includes
// ... none

namespace neopt {
// basic types for Neo core

// the simplest chunk of information
// TODO: migrate to C++17 byte type
typedef unsigned char byte; // EVILLLLL
//using byte = std::byte; // DON't know if it's usable inside vector!! avoid it...

//using byte = std::byte;

static_assert(sizeof(byte) == 1);

// half byte: nibble
//typedef byte nibble;
//typedef uint_least8_t nibble;
struct nibble
{
   nibble()
     : v{ 0X0 }
   {
   }

   nibble(byte b)
     : v{ b }
   {
   }

   operator byte() const
   {
      return (byte)v;
   }

   /*
   operator int() const
   {
      return (int)v;
   }
   */

   unsigned char v;
   //unsigned char v : 4; // better not mess with bits and unaligned ints...
};

// signed short int
typedef short int16;

// unsigned short int
typedef unsigned short uint16;

static_assert(sizeof(uint16) == 2);

// signed int
typedef int int32;

// unsigned int
typedef unsigned int uint32;

static_assert(sizeof(uint32) == 4);

// unsigned long
#ifdef EMSCRIPTEN
typedef unsigned long long uint64;
#else
typedef unsigned long long uint64;
#endif

static_assert(sizeof(uint64) == 8);

// unsigned long
typedef unsigned long ulong;

// =================
// array definitions
// -----------------

// byte array definition
typedef std::vector<byte> vbyte;

// nibble array definition
typedef std::vector<nibble> vnibble;

template<class T>
using uptr = std::unique_ptr<T>; // neopt shortcut for unique_ptr


// please follow JSON standard to allow deserialization (JSON.stringify)
// TODO: hex string or array of numbers? must choose one.
// =======================
// CANNOT DEFINE FUNCTIONS HERE!!! ONLY .h things here, PLEASEEEEEEEEEEEEE
/*
std::string
stringify(const vbyte& vb)
{
   std::stringstream ss;
   ss << "[";
   for (int i = 0; i < (int)vb.size(); i++)
      if (i != ((int)vb.size()) - 1) // not last
         ss << (unsigned int)vb[i] << ",";
      else // last
         ss << (unsigned int)vb[i];
   ss << "]";
   return ss.str();
}
*/

#define NEOPT_EXCEPTION(str)                          \
   {                                                  \
      printf("neopt error(%s): %s\n", __func__, str); \
      exit(1);                                        \
   }

class types
{
public:
   template<class T>
   static T MaxValue()
   {
      return std::numeric_limits<T>::max();
   }

   template<class T>
   static T MinValue()
   {
      return std::numeric_limits<T>::min();
   }
};

template<typename T>
struct MakeStatic
{
   // the const guarantees that 'global state' is read-only for static purposes only
   static const T& object()
   {
      static T t;
      return t;
   }
};

/*
// Example static Singleton Class
class MyStaticSingletonClass final
{
  public:
    // const must be added to ensure global state is read-only
    // this is not a standard singleton, and it is much safer
    void hi() const 
    {
    }
  private:
    friend struct MakeStatic<MyStaticSingletonClass>;
};
*/

/*
ostream&
operator<<(ostream& os, const vbyte& v)
{
   os << "vbyte(" << vbyte.size() << "): ";
   for (auto i : v)
      os << i << " ";
   return os;
}
*/

} // namespace neopt

#endif
