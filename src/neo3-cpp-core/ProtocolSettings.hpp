#pragma once

#include <unique_ref/unique_ref.hpp>

namespace Neo {

class ProtocolSettings
{
public:
   neopt::byte AddressVersion = { 0x35 };

   static unique_ref::uref<ProtocolSettings> Default;
};

//
unique_ref::uref<ProtocolSettings> ProtocolSettings::Default =unique_ref::uref<ProtocolSettings>{ ProtocolSettings{} };

} // namespace Neo
