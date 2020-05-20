#include <iostream>

#include <neo3-cpp-core/Core.hpp>
#include <neo3-cpp-core/SmartContract/Contract.hpp>
#include <neo3-cpp-core/SmartContract/InteropService.Crypto.hpp>
#include <neo3-cpp-vm/OpCode.hpp>
#include <neo3-cpp-vm/ScriptBuilder.hpp>

//using namespace std;

using namespace Neo::VM;
using namespace Neo::SmartContract;
using namespace Neo::Cryptography::ECC;

int
main()
{
   OpCode op = OpCode::CLEARITEMS;
   std::cout << op << std::endl;

   ScriptBuilder sb;

   vbyte vx_32(32, 0);
   vbyte vy_32(32, 0);

   ECPoint ecp{ vx_32, vy_32, ECCurve::Secp256r1 };
   vbyte script = Contract::CreateSignatureRedeemScript(ecp);

   std::cout << "Finished successfully" << std::endl;
   return 0;
}