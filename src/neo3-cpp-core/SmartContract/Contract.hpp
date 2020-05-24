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



namespace Neo {
//
namespace SmartContract {
//
class Contract
{
   /*
public:
   byte[] Script;

public:
   ContractParameterType[] ParameterList;

private:
   string _address;

public:
   string Address
   {
      get
      {
         if (_address == null) {
            _address = ScriptHash.ToAddress();
         }
         return _address;
      }
   }

private:
   UInt160 _scriptHash;

public:
   virtual UInt160 ScriptHash
   {
      get
      {
         if (_scriptHash == null) {
            _scriptHash = Script.ToScriptHash();
         }
         return _scriptHash;
      }
   }

public:
   static Contract Create(ContractParameterType[] parameterList, byte[] redeemScript)
   {
      return new Contract{
         Script = redeemScript,
         ParameterList = parameterList
      };
   }

   /// <summary>
   /// Construct special Contract with empty Script, will get the Script with scriptHash from blockchain when doing the Verify
   /// verification = snapshot.Contracts.TryGet(hashes[i])?.Script;
   /// </summary>
public:
   static Contract Create(UInt160 scriptHash, params ContractParameterType[] parameterList)
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
   static std::string API_CreateSignatureRedeemScript(std::string jsonECPoint)
   {
      auto ecp = ECPoint::API_FromJsonStr(jsonECPoint);
      vbyte v = CreateSignatureRedeemScript(ecp);
      return neopt::vhelper::ToHexString(v);
   }
};
//
} // namespace SmartContract
//
} // namespace Neo