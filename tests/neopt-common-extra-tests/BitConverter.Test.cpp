#include <iostream>
#include <limits> // numeric_limits

//#define CATCH_CONFIG_MAIN // This tells Catch to provide a main()
#include "../thirdparty/catch2/catch.hpp"

// Some instructions for Catch2
// https://github.com/catchorg/Catch2/blob/master/docs/test-cases-and-sections.md

#include <neo3-cpp-core/neopt-common/system/BitConverter.hpp> // 'src' included

using namespace std;
using namespace neopt;

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
