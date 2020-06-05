#include <iostream>
#include <limits> // numeric_limits

//#define CATCH_CONFIG_MAIN // This tells Catch to provide a main()
#include "../thirdparty/catch2/catch.hpp"

// Some instructions for Catch2
// https://github.com/catchorg/Catch2/blob/master/docs/test-cases-and-sections.md

#include <neo3-cpp-core/Core.hpp>
#include <neo3-cpp-core/neopt-common/system/BitConverter.hpp> // 'src' included
#include <neo3-cpp-core/Helper.hpp> // 'src' included

using vbyte = neopt::vbyte;
using vbyte = neopt::vbyte;
using BitConverter = neopt::BitConverter;
using namespace std;

TEST_CASE("neopt extra tests - BitConverter 16385")
{
   // example from: https://www.dotnetperls.com/bitconverter
   int value = 16385;
   vbyte v = BitConverter::GetBytes(value);
   //std::cout << "PRINTING!" << std::endl;
   //for (unsigned i = 0; i < v.size(); i++)
   //   std::cout << (int)v[i] << std::endl;
   // v = 0x00004001 (big endian)
   // v = [1, 64, 0, 0] (little endian)
   REQUIRE(v[0] == 1);
   REQUIRE(v[1] == 64);
   REQUIRE(v[2] == 0);
   REQUIRE(v[3] == 0);
}

TEST_CASE("neopt extra tests - BitConverter ToUInt32")
{
   vbyte byteArray = {
      15, 0, 0, 0, 0, 16, 0, 255, 3, 0, 0, 202, 154, 59, 255, 255, 255, 255, 127
   };

   REQUIRE(BitConverter::ToUInt32(byteArray, 1) == 0);
   REQUIRE(BitConverter::ToUInt32(byteArray, 0) == 15);
   REQUIRE(BitConverter::ToUInt32(byteArray, 7) == 1023);
   REQUIRE(BitConverter::ToUInt32(byteArray, 3) == 1048576);
   REQUIRE(BitConverter::ToUInt32(byteArray, 10) == 1000000000);
   REQUIRE(BitConverter::ToUInt32(byteArray, 15) == 2147483647);
   REQUIRE(BitConverter::ToUInt32(byteArray, 14) == 4294967295);
}

TEST_CASE("neopt extra tests - Test ToBase64String")
{
   vbyte byteArray = Neo::Helper::HexToBytes("000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F202122232425262728292A2B2C2D2E2F303132333435363738393A3B3C3D3E3F404142434445464748494A4B4C4D4E4F505152535455565758595A5B5C5D5E5F606162636465666768696A6B6C6D6E6F707172737475767778797A7B7C7D7E7F808182838485868788898A8B8C8D8E8F909192939495969798999A9B9C9D9E9FA0A1A2A3A4A5A6A7A8A9AAABACADAEAFB0B1B2B3B4B5B6B7B8B9BABBBCBDBEBFC0C1C2C3C4C5C6C7C8C9CACBCCCDCECFD0D1D2D3D4D5D6D7D8D9DADBDCDDDEDFE0E1E2E3E4E5E6E7E8E9EAEBECEDEEEFF0F1F2F3F4F5F6F7F8F9FAFBFCFDFEFF");
   string convertedBase64 = neopt::Convert::ToBase64String(byteArray);

   REQUIRE(convertedBase64 ==
           "AAECAwQFBgcICQoLDA0ODxAREhMUFRYXGBkaGxwdHh8gISIjJCUmJygpKissLS4vMDEyMzQ1Njc4\
OTo7PD0+P0BBQkNERUZHSElKS0xNTk9QUVJTVFVWV1hZWltcXV5fYGFiY2RlZmdoaWprbG1ub3Bx\
cnN0dXZ3eHl6e3x9fn+AgYKDhIWGh4iJiouMjY6PkJGSk5SVlpeYmZqbnJ2en6ChoqOkpaanqKmq\
q6ytrq+wsbKztLW2t7i5uru8vb6/wMHCw8TFxsfIycrLzM3Oz9DR0tPU1dbX2Nna29zd3t/g4eLj\
5OXm5+jp6uvs7e7v8PHy8/T19vf4+fr7/P3+/w==");

   REQUIRE(byteArray == neopt::Convert::FromBase64String(convertedBase64));
}
