#pragma once

#include <neo3-cpp-core/Cryptography/Cryptography.hpp>

#include <unique_ref/unique_ref.hpp>

#include <neo3-cpp-core/IO/Json/JObject.hpp>

namespace Neo {
//
namespace Wallets {
//
namespace NEP6 {
//
class ScryptParameters final
{
public:
   static uref<ScryptParameters> Default;

public:
   int N, R, P;

public:
   ScryptParameters();

   ScryptParameters(int n, int r, int p)
     : N{ n }
     , R{ r }
     , P{ p }
   {
   }

   virtual ~ScryptParameters()
   {
   }

   ScryptParameters& operator=(const ScryptParameters& other)
   {
      if (&other == this)
         return *this;
      this->N = other.N;
      this->R = other.R;
      this->P = other.P;

      return *this;
   }

public:
   static ScryptParameters FromJson(const nlohmann::json& json)  //const neopt::JObject& json)
   {
      return ScryptParameters{
         json["n"].get<int>(), //.AsNumber(),
         json["r"].get<int>(), //.AsNumber(),
         json["p"].get<int>() //.AsNumber()
      };
   }

public:

   nlohmann::json ToJson()
   {
      nlohmann::json json;
      json["n"] = N;
      json["r"] = R; 
      json["p"] = P;
      return json;
   }

/*
   neopt::uptr<neopt::JObject> ToJson()
   {
      neopt::uptr<neopt::JObject> json{ new neopt::JObject() };
      json->pset("n", neopt::uptr<neopt::JObject>{ new neopt::JNumber{ N } });
      json->pset("r", neopt::uptr<neopt::JObject>{ new neopt::JNumber{ R } });
      json->pset("p", neopt::uptr<neopt::JObject>{ new neopt::JNumber{ P } });
      return json;
   }
*/

}; // class ScryptParameters
//
uref<ScryptParameters> ScryptParameters::Default{ ScryptParameters{ 16384, 8, 8 } };
//
ScryptParameters::ScryptParameters()
  : N{ Default->N }
  , R{ Default->R }
  , P{ Default->P }
{
}
//
} // namespace NEP6
//
} // namespace Wallets
//
} // namespace Neo
  //
