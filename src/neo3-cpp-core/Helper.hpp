#pragma once

// ================================
// Neo/Helper.hpp (the main Helper)
// ================================


namespace Neo
{
namespace Helper {

   static vbyte
   HexToBytes(const std::string& hex)
   {
      // TODO: implement (begin 0x)
      //NEOPT_EXCEPTION("Not implemented yet: HexToBytes");
      vbyte bytes(hex.length() / 2);

      for (uint i = 0; i < hex.length(); i += 2) {
         std::string byteString = hex.substr(i, 2);
         neopt::byte b = (neopt::byte)strtol(byteString.c_str(), NULL, 16);
         bytes[i / 2] = b;
      }
      return bytes;
   }

} // namespace Helper
//
} // namespace Neo