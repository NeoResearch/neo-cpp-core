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

#include <neo3-cpp-core/Cryptography/Crypto.hpp>

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

   ECFieldElement X{ BigInteger{ "92417421609284060097852441734141491128266387380656748836951019715045385777354", 10 }, *ECCurve::Secp256r1 };
   ECFieldElement Y{ BigInteger{ "81306213973968698003399946097148256829885864908442466985789085263601870844340", 10 }, *ECCurve::Secp256r1 };
   //  Address: NSh6STZ6K4jUVDNZHwYSLc4ViuEm9Q1JtU
   //  PublicKey: 02cc52682ea36700b93dce82823fd88647f6056af36cce2f6ee14c572277ef30ca
   // scripthash: 0x0eec9e10f6491c39f3e8dbc8af7186282487594a
   // L1TKE6hbWSMaBESkZJ3PPbQHkHN8DdSRa7F82konNAf3ejhgMpD9

   ECPoint ecp{ X, Y, *ECCurve::Secp256r1 };
   std::cout << "point (JSON): " << ECPoint::API_ToJsonStr(ecp) << std::endl;

   ECPoint G = ECCurve::Secp256r1->G; // allowed copy on 'ucref' type.. beware slicing!
   std::cout << "G:" << G.ToString() << std::endl;

   Test test{ G };

   vbyte vscript = Contract::CreateSignatureRedeemScript(ecp);

   std::cout << "vscript: " << vhelper::ToHexString(vscript) << std::endl;
   std::cout << "vscript: ";
   for (auto i : vscript)
      std::cout << ((unsigned int)i) << " ";
   std::cout << std::endl;

   UInt160 script_hash = Neo::SmartContract::scHelper::ToScriptHash(vscript);
   std::cout << "ScriptHash:" << std::endl;
   std::cout << script_hash.ToString() <<std::endl;

   const Neo::ProtocolSettings ps;
   std::cout << "Base58:" << std::endl;
   string address = Neo::Wallets::wHelper::ToAddress(ps, script_hash);
   std::cout << address << std::endl;

   std::cout << "ScriptHash back from Base58:" << std::endl;
   UInt160 script_hash_2 = Neo::Wallets::wHelper::ToScriptHash(address);
   std::cout << script_hash_2.ToString() << std::endl;

   std::cout << "Encode from Base58:" << std::endl;
   std::cout << Neo::Cryptography::Base58::Encode(script_hash.ToArray()) << std::endl;

   //

   std::cout
     << "Finished successfully" << std::endl;
   return 0;
}
