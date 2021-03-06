#ifndef NEOPT_SHELPER_H
#define NEOPT_SHELPER_H

// String Helper: shelper

// system
#include <algorithm>
#include <functional>
#include <sstream>
#include <vector>

// neo core
#include "../system/BinaryReader.hpp"
#include "types.h"

using namespace std; // TODO: avoid!

namespace neopt {

// string helper class
class shelper
{
public:
   static bool StartsWith(const string& s, const string& prefix)
   {
      return (s.rfind(prefix, 0) == 0);
   }

   static string Substring(const string& s, int from)
   {
      return s.substr(from);
   }

   static uint16 ParseHexToShort(const string& hex)
   {
      vbyte vb = HexToBytes(hex);
      BinaryReader reader(vb);
      return reader.ReadUInt16();
   }

   static double ParseDouble(const string& sdouble)
   {
      return std::stod(sdouble);
   }

   static vbyte HexToBytes(const string& hex)
   {
      // TODO: implement (begin 0x)
      //NEOPT_EXCEPTION("Not implemented yet: HexToBytes");
      vbyte bytes(hex.length() / 2);

      for (uint32 i = 0; i < hex.length(); i += 2) {
         std::string byteString = hex.substr(i, 2);
         byte b = (byte)strtol(byteString.c_str(), NULL, 16);
         bytes[i / 2] = b;
      }
      return bytes;
   }

   static string ASCIIToHexString(const string& chars)
   {
      stringstream ss;
      for (unsigned i = 0; i < chars.size(); i++)
         ss << std::setfill('0') << std::setw(2) << std::hex << int((byte)chars[i]);
      return ss.str();
   }

   static string TakeWhile(string s, std::function<bool(char)> f)
   {
      std::string str;
      for (unsigned i = 0; i < s.size(); i++)
         if (!f(s[i]))
            return str;
         else {
            char c = s[i];
            str += (c);
         }
      return str;
   }
};

// TODO: define all operators here that are necessary
}

#endif
