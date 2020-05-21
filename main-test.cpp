#include <iostream>

#include <neo3-cpp-core/Core.hpp>
//
#include <neo3-cpp-core/Cryptography/ECC/ECCurve.hpp> // no dependency
//
#include <neo3-cpp-core/Cryptography/ECC/ECPoint.hpp> // depends on ECFieldElement
//
#include <neo3-cpp-core/Cryptography/ECC/ECCurveList.hpp>
//
#include <neo3-cpp-core/Cryptography/ECC/ECCurve.hpp>
#include <neo3-cpp-core/Cryptography/ECC/ECFieldElement.hpp>
#include <neo3-cpp-core/Cryptography/ECC/ECPoint.hpp>
//
#include <neo3-cpp-core/SmartContract/Contract.hpp>
#include <neo3-cpp-core/SmartContract/InteropService.Crypto.hpp>
#include <neo3-cpp-vm/OpCode.hpp>
#include <neo3-cpp-vm/ScriptBuilder.hpp>
//
#include <csbiginteger-cpp/src/csBigIntegerLibClass.hpp>
using BigInteger = csbigintegerlib::BigInteger;

//using namespace std;

using namespace Neo::VM;
using namespace Neo::SmartContract;
using namespace Neo::Cryptography::ECC;

using namespace neopt;

using namespace csbiginteger;

int
main()
{
   OpCode op = OpCode::CLEARITEMS;
   std::cout << op << std::endl;

   BigInteger big(-1);
   std::cout << big.ToString(16) << std::endl;

   //const ECCurve& c = ECCurveList::Secp256r1();

   ScriptBuilder sb;

   vbyte vx_32(32, 8); // little-endian value
   vbyte vy_32(32, 9); // little-endian value

   ECFieldElement X{ BigInteger{ vx_32 }, ECCurveList::Secp256r1() };
   ECFieldElement Y{ BigInteger{ vy_32 }, ECCurveList::Secp256r1() };

   ECPoint ecp{ X, Y, ECCurveList::Secp256r1() };
   vbyte vscript = Contract::CreateSignatureRedeemScript(ecp);

   //std::cout << vscript << std::endl;
   std::cout << "vscript: ";
   for (auto i : vscript)
      std::cout << std::hex << ((unsigned int)i) << " ";
   std::cout << std::endl;

   std::cout
     << "Finished successfully" << std::endl;
   return 0;
}
