#pragma once

// ================================
// Neo/Helper.hpp (the main Helper)
// ================================

namespace Neo {
//
namespace Helper {
//
// too bad... 'constexpr' only on C++20 (but emscripten doesn't have it yet!)
//

// private
static int
BitLen(int w)
{
   return (w < 1 << 15 ? (w < 1 << 7
                            ? (w < 1 << 3 ? (w < 1 << 1
                                               ? (w < 1 << 0 ? (w < 0 ? 32 : 0) : 1)
                                               : (w < 1 << 2 ? 2 : 3))
                                          : (w < 1 << 5
                                               ? (w < 1 << 4 ? 4 : 5)
                                               : (w < 1 << 6 ? 6 : 7)))
                            : (w < 1 << 11
                                 ? (w < 1 << 9 ? (w < 1 << 8 ? 8 : 9) : (w < 1 << 10 ? 10 : 11))
                                 : (w < 1 << 13 ? (w < 1 << 12 ? 12 : 13) : (w < 1 << 14 ? 14 : 15))))
                       : (w < 1 << 23 ? (w < 1 << 19
                                           ? (w < 1 << 17 ? (w < 1 << 16 ? 16 : 17) : (w < 1 << 18 ? 18 : 19))
                                           : (w < 1 << 21 ? (w < 1 << 20 ? 20 : 21) : (w < 1 << 22 ? 22 : 23)))
                                      : (w < 1 << 27
                                           ? (w < 1 << 25 ? (w < 1 << 24 ? 24 : 25) : (w < 1 << 26 ? 26 : 27))
                                           : (w < 1 << 29 ? (w < 1 << 28 ? 28 : 29) : (w < 1 << 30 ? 30 : 31)))));
};

static int
GetBitLength(const BigInteger& i)
{
   vbyte b = i.ToByteArray();
   return (b.size() - 1) * 8 + BitLen(i.Sign() > 0 ? b[b.size() - 1] : 255 - b[b.size() - 1]);
}

static vbyte
HexToBytes(const std::string& hex)
{
   // TODO: implement (begin 0x)
   //NEOPT_EXCEPTION("Not implemented yet: HexToBytes");
   vbyte bytes(hex.length() / 2);

   for (neopt::uint32 i = 0; i < hex.length(); i += 2) {
      std::string byteString = hex.substr(i, 2);
      neopt::byte b = (neopt::byte)strtol(byteString.c_str(), NULL, 16);
      bytes[i / 2] = b;
   }
   return bytes;
}
//
} // namespace Helper
//
} // namespace Neo