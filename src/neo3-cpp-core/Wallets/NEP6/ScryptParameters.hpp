#pragma once

#include <neo3-cpp-core/Cryptography/Cryptography.hpp>

#include <unique_ref/unique_ref.hpp>

namespace Neo {
//
namespace Wallets {
//
namespace NEP6 {
//
class ScryptParameters
{
public:
   static uref<ScryptParameters> Default;

public:
   const int N, R, P;

public:
   ScryptParameters(int n, int r, int p)
     : N{ n }
     , R{ r }
     , P{ p }
   {
   }

   /*
        public:
         static ScryptParameters FromJson(JObject json)
        {
            return new ScryptParameters((int)json["n"].AsNumber(), (int)json["r"].AsNumber(), (int)json["p"].AsNumber());
        }

        public:
         JObject ToJson()
        {
            JObject json = new JObject();
            json["n"] = N;
            json["r"] = R;
            json["p"] = P;
            return json;
        }
        */

}; // class ScryptParameters
//
uref<ScryptParameters> ScryptParameters::Default{ ScryptParameters{ 16384, 8, 8 } };
//
} // namespace NEP6
//
} // namespace Wallets
//
} // namespace Neo
  //
