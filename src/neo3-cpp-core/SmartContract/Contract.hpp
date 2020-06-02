#pragma once

#include <neo3-cpp-core/Cryptography/ECC/ECPoint.hpp>
using namespace Neo::Cryptography::ECC;
#include <neo3-cpp-vm/ScriptBuilder.hpp>
using namespace Neo::VM;
//using Neo.Wallets;
//
#include <neo3-cpp-core/neopt-common/System.hpp>
//using System;
//using System.Linq;
//
#include <neo3-cpp-core/SmartContract/InteropService.Crypto.hpp>

#include "ContractParameterType.hpp"

#include <neo3-cpp-core/neopt-common/numbers/UInt160.hpp>

#include <neo3-cpp-core/Wallets/wHelper.hpp>
#include <neo3-cpp-core/SmartContract/scHelper.hpp>


using UInt160 = neopt::UInt160;

namespace Neo {
//
namespace SmartContract {
//
class Contract
{
   template<class X>
   using uptr = std::unique_ptr<X>;
public:
   vbyte Script;

public:
   vector<ContractParameterType> ParameterList;

   Contract(vbyte Script, vector<ContractParameterType> ParameterList)
     : Script{ Script }
     , ParameterList{ ParameterList }
   {
   }

   virtual ~Contract()
   {
   }

private:
   string _address{ "" };

public:
   string Address()
   {
      if (_address == "") {
         _address = Neo::Wallets::wHelper::ToAddress(ScriptHash());
      }
      return _address;
   }

private:
   uptr<UInt160> _scriptHash;

public:
   virtual const UInt160& ScriptHash()
   {
      if (_scriptHash == nullptr) {
         _scriptHash = uptr<UInt160>{ new UInt160{ Neo::SmartContract::scHelper::ToScriptHash(Script) } };
      }
      return *_scriptHash;
   }

public:
   static uptr<Contract> Create(vector<ContractParameterType> parameterList, vbyte redeemScript)
   {
      return uptr<Contract>{
         new Contract{
           redeemScript,
           parameterList }
      };
   }

   /// <summary>
   /// Construct special Contract with empty Script, will get the Script with scriptHash from blockchain when doing the Verify
   /// verification = snapshot.Contracts.TryGet(hashes[i])?.Script;
   /// </summary>
   /*
public:
   static Contract Create(UInt160 scriptHash, vector<ContractParameterType> parameterList)
   {
      return new Contract{
         Script = Array.Empty<byte>(),
         _scriptHash = scriptHash,
         ParameterList = parameterList
      };
   }

public:
   static Contract CreateMultiSigContract(int m, params ECPoint[] publicKeys)
   {
      return new Contract{
         Script = CreateMultiSigRedeemScript(m, publicKeys),
         ParameterList = Enumerable.Repeat(ContractParameterType.Signature, m).ToArray()
      };
   }

public:
   static byte[] CreateMultiSigRedeemScript(int m, params ECPoint[] publicKeys)
   {
      if (!(1 <= m && m <= publicKeys.Length && publicKeys.Length <= 1024))
         throw new ArgumentException();
      using(ScriptBuilder sb = new ScriptBuilder())
      {
         sb.EmitPush(m);
         foreach (ECPoint publicKey in publicKeys.OrderBy(p = > p)) {
            sb.EmitPush(publicKey.EncodePoint(true));
         }
         sb.EmitPush(publicKeys.Length);
         sb.Emit(OpCode::PUSHNULL);
         sb.EmitSysCall(InteropService.Crypto.CheckMultisigWithECDsaSecp256r1);
         return sb.ToArray();
      }
   }

public:
   static Contract CreateSignatureContract(ECPoint publicKey)
   {
      return new Contract{
         Script = CreateSignatureRedeemScript(publicKey),
         ParameterList = new[]{ ContractParameterType.Signature }
      };
   }
*/

public:
   //static byte[] CreateSignatureRedeemScript(ECPoint publicKey)
   static vbyte CreateSignatureRedeemScript(ECPoint& publicKey)
   {
      std::cout << "Running 'CreateSignatureRedeemScript'" << std::endl;
      //using(ScriptBuilder sb = new ScriptBuilder())
      if (ScriptBuilder sb; true) {
         sb.EmitPush(publicKey.EncodePoint(true));
         sb.Emit(OpCode::PUSHNULL);
         sb.EmitSysCall(Neo::SmartContract::InteropService::Crypto::VerifyWithECDsaSecp256r1());
         return sb.ToArray();
      }
   }

   // ===================== EXPORT API METHODS =====================
   // these methods below provide service to APIs, like 'neopt-js'
   // --------------------------------------------------------------

public:
   // returns 'hexstring' and gets 'ECPoint'
   static std::string EXPORT_NEO3API_CreateSignatureRedeemScript(std::string jsonECPoint);
}; // class Contract
//
} // namespace SmartContract
//
} // namespace Neo

std::string
Neo::SmartContract::Contract::EXPORT_NEO3API_CreateSignatureRedeemScript(std::string jsonECPoint)
{
   auto ecp = ECPoint::_NEO3API_FromJsonStr(jsonECPoint);
   vbyte v = CreateSignatureRedeemScript(ecp);
   return neopt::vhelper::ToHexString(v);
}