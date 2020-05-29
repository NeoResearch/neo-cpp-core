#pragma once

#include <unique_ref/unique_ref.hpp>

template<class X>
using uref = unique_ref::uref<X>;

namespace Neo {

class ProtocolSettings
{
public:
   neopt::byte AddressVersion = { 0x35 };

   static uref<ProtocolSettings> Default;
};

//
uref<ProtocolSettings> ProtocolSettings::Default = uref<ProtocolSettings>{ ProtocolSettings{} };

} // namespace Neo
