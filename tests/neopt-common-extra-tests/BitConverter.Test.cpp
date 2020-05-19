#include <iostream>
#include <limits> // numeric_limits

//#define CATCH_CONFIG_MAIN // This tells Catch to provide a main()
#include "../thirdparty/catch2/catch.hpp"

// Some instructions for Catch2
// https://github.com/catchorg/Catch2/blob/master/docs/test-cases-and-sections.md

#include <neo3-cpp-core/neopt-common/system/BitConverter.hpp>    // 'src' included

using namespace std;
using namespace neopt;

TEST_CASE("neopt extra tests - BitConverter 16385")
{
   // example from: https://www.dotnetperls.com/bitconverter
   int value = 16385;
   vbyte v = BitConverter::GetBytes(value);
   std::cout << "PRINTING!" << std::endl;
   for(unsigned i=0; i<v.size(); i++)
      std::cout << (int)v[i] <<std::endl;
   // v = 0x00004001 (big endian)
   // v = [1, 64, 0, 0] (little endian)
   REQUIRE(v[0] == 1);
   REQUIRE(v[1] == 64);
   REQUIRE(v[2] == 0);
   REQUIRE(v[3] == 0);
}
