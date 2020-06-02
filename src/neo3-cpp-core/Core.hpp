#pragma once

// CORE: must compile into all supported platforms (js included)
//
// just a bunch of stuff
// ====================

#include "neopt-common/system/types.h"

using vbyte = neopt::vbyte;

#include "ProtocolSettings.hpp"

// --------------------------------
// load ECC "internal" classes
//
#include "Cryptography/Cryptography.hpp"
//
#include "SmartContract/Contract.hpp"
#include "SmartContract/scHelper.hpp"

#include "Wallets/Wallet.hpp"

#include "Wallets/wHelper.hpp"

#include "Wallets/NEP6/NEP6Wallet.hpp"

//
//
//
//
// ------------------------
//
//
//
// more specific

/////#include "SmartContract/Contract.hpp"

//
//#include<vector>

// not in namespace... for now!
//using vbyte = std::vector<unsigned char>;

namespace neo3core {

class X
{
};

} // namespace neo3core
