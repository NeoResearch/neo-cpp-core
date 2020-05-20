#include <iostream>

#include <neo3-cpp-core/Core.hpp>
#include <neo3-cpp-core/SmartContract/Contract.hpp>
#include <neo3-cpp-core/SmartContract/InteropService.Crypto.hpp>
#include <neo3-cpp-vm/OpCode.hpp>
#include <neo3-cpp-vm/ScriptBuilder.hpp>

//using namespace std;

using namespace Neo::VM;
using namespace Neo::SmartContract;

int
main()
{
   OpCode op = OpCode::CLEARITEMS;
   std::cout << op << std::endl;

   ScriptBuilder sb;
   ECPoint ecp;
   vbyte script = Contract::CreateSignatureRedeemScript(ecp);

   return 0;
}