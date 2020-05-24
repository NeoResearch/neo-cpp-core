#include <iostream>

#include <neo3-cpp-core/Core.hpp>
//
#include <neo3-cpp-core/Cryptography/ECC/ECC.hpp>
#include <neo3-cpp-core/Cryptography/ECC/ECCurve.hpp>
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

class Test
{
public:
   uref<ECPoint> r;
   Test(const ECPoint& c)
     : r{ c }
   {
   }
};

int
main()
{
   BigInteger bigtest{ "0x00FFFFFFFF00000001000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFF", 16 };
   std::cout << "bigtest = " << bigtest.ToString(10) << std::endl;

   OpCode op = OpCode::CLEARITEMS;
   std::cout << op << std::endl;

   BigInteger big(-1);
   std::cout << big.ToString(16) << std::endl;

   //const ECCurve& c = ECCurve::Secp256r1();

   ScriptBuilder sb;

   vbyte vx_32(32, 8); // little-endian value
   vbyte vy_32(32, 9); // little-endian value

   ECFieldElement X{ BigInteger{ "43563478194357645732161043749214420341576583724275881899443933055754116882936" }, *ECCurve::Secp256r1 };
   ECFieldElement Y{ BigInteger{ "6800198406926458502571476951697947402787919362010374841430910815761615021861" }, *ECCurve::Secp256r1 };
   //expected publicKey.EncodePoint(true) { 3, 96, 80, 14, 12, 163, 115, 233, 65, 231, 174, 155, 203, 149, 91, 129, 86, 126, 183, 82, 81, 220, 101, 149, 154, 212, 175, 97, 250, 138, 177, 97, 248, }
   //expected verification { 12, 33, 3, 96, 80, 14, 12, 163, 115, 233, 65, 231, 174, 155, 203, 149, 91, 129, 86, 126, 183, 82, 81, 220, 101, 149, 154, 212, 175, 97, 250, 138, 177, 97, 248, 11, 65, 138, 107, 30, 117, }

   ECPoint ecp{ X, Y, *ECCurve::Secp256r1 };
   std::cout << "point (JSON): " << ecp.ToJsonStr() << std::endl;

   ECPoint G = ECCurve::Secp256r1->G; // allowed copy on 'ucref' type.. beware slicing!
   std::cout << "G:" << G.ToString() << std::endl;

   Test test{ G };

   vbyte vscript = Contract::CreateSignatureRedeemScript(ecp);

   //std::cout << vscript << std::endl;
   std::cout << "vscript: ";
   for (auto i : vscript)
      std::cout << ((unsigned int)i) << " ";
   std::cout << std::endl;

   std::cout
     << "Finished successfully" << std::endl;
   return 0;
}
