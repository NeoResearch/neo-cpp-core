#pragma once 

#include <neo3-cpp-core/Cryptography/Cryptography.hpp>
#include <neo3-cpp-core/ProtocolSettings.hpp>

namespace Neo {
//
namespace Wallets {
//
namespace wHelper {

static string
ToAddress(const UInt160& scriptHash)
{
      vbyte data(21);
      data[0] = ProtocolSettings::Default->AddressVersion;//settings.AddressVersion;
      neopt::Buffer::BlockCopy(scriptHash.ToArray(), 0, data, 1, 20);
      return Neo::Cryptography::Base58::Base58CheckEncode(data);
}

static UInt160
ToScriptHash(string address)
{
      vbyte data = Neo::Cryptography::Base58::Base58CheckDecode(address);
      neopt::byte version = {0x35};
      std::cout << "DataSize after Decode is " << data.size() << std::endl;
      if (data.size() != 21)
         NEOPT_EXCEPTION("Data to be converted problem");
      if (data[0] != version ) // TODO fix to static Default from Protocol Settings
         NEOPT_EXCEPTION("Address Version Problem");
      // data.AsSpan(1)
      vbyte dataCut(data.begin()+1,data.end());    
      return UInt160(dataCut);
}

} // namespace wHelper
//
} // namespace Wallet
//
} // namespace Neo
  //

// Wallet Helper: whelper

/*
// system
#include <limits>
#include <sstream>
#include <vector>

// neo core
#include <ProtocolSettings.hpp>
#include <crypto/chelper.hpp>
#include <crypto/ICrypto.h>
#include <numbers/UInt160.hpp>
#include <system/Buffer.hpp>
#include <system/types.h>
#include <system/vhelper.hpp>
#include <wallets/KeyPair.hpp>

namespace neopt {

// wallets helper class
class whelper
{
public:
   static string ToAddress(const ProtocolSettings& settings, const UInt160& scriptHash)
   {
      vbyte data(21);
      data[0] = settings.AddressVersion;
      Buffer::BlockCopy(scriptHash.ToArray(), 0, data, 1, 20);
      return chelper::Base58CheckEncode(data);
   }

   static UInt160 ToScriptHash(const ProtocolSettings& settings, string& address)
   {
      vbyte data = chelper::Base58CheckDecode(address);
      if (data.size() != 21)
         NEOPT_EXCEPTION("Format Exception ToScriptHash");
      if (data[0] != settings.AddressVersion)
         NEOPT_EXCEPTION("Format Exception ToScriptHash");
      return UInt160(vhelper::Skip(data, 1));
   }
};

// TODO: define all operators here that are necessary

}

#endif
*/