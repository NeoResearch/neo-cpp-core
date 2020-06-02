#pragma once

#include <neo3-cpp-core/Cryptography/Cryptography.hpp>

#include <neo3-cpp-core/SmartContract/Contract.hpp>

using ContractParameterType = Neo::SmartContract::ContractParameterType;

namespace Neo {
//
namespace Wallets {
//
namespace NEP6 {
//
class NEP6Contract : public Contract
{
public:
   vector<string> ParameterNames;

public:
   bool Deployed;

   NEP6Contract(vbyte Script, vector<ContractParameterType> ParameterList, vector<string> ParameterNames, bool Deployed)
     : Contract{
        Script,
        ParameterList
     }
     , ParameterNames{ ParameterNames }
     , Deployed{ Deployed }
   {
   }

   virtual ~NEP6Contract()
   {
   }

   /*
        public static NEP6Contract FromJson(JObject json)
        {
            if (json == null) return null;
            return new NEP6Contract
            {
                Script = Convert.FromBase64String(json["script"].AsString()),
                ParameterList = ((JArray)json["parameters"]).Select(p => p["type"].TryGetEnum<ContractParameterType>()).ToArray(),
                ParameterNames = ((JArray)json["parameters"]).Select(p => p["name"].AsString()).ToArray(),
                Deployed = json["deployed"].AsBoolean()
            };
        }

        public JObject ToJson()
        {
            JObject contract = new JObject();
            contract["script"] = Convert.ToBase64String(Script);
            contract["parameters"] = new JArray(ParameterList.Zip(ParameterNames, (type, name) =>
            {
                JObject parameter = new JObject();
                parameter["name"] = name;
                parameter["type"] = type;
                return parameter;
            }));
            contract["deployed"] = Deployed;
            return contract;
        }*/

}; // class NEP6Contract
//
} // namespace NEP6
//
} // namespace Wallets
//
} // namespace Neo
  //
