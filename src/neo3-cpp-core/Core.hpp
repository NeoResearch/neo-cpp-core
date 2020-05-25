#pragma once

// CORE: must compile into all supported platforms (js included)
//
// just a bunch of stuff
// ====================

#include "neopt-common/system/types.h"

using vbyte = neopt::vbyte;

// --------------------------------
// load ECC "internal" classes
//
#include "Cryptography/Cryptography.hpp"
//
#include "SmartContract/Contract.hpp"
#include "SmartContract/scHelper.hpp"

#include "Wallet/wHelper.hpp"

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
