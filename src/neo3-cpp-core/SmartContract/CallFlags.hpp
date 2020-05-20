#pragma once

#include <cstddef>
#include <sstream>

#include <neo3-cpp-core/neopt-common/System.hpp>

namespace Neo {
//
namespace SmartContract {
//
enum class CallFlags : neopt::byte
{
   None = 0,

   AllowStates = 0b00000001,
   AllowModifyStates = 0b00000010,
   AllowCall = 0b00000100,
   AllowNotify = 0b00001000,

   ReadOnly = AllowStates | AllowCall | AllowNotify,
   All = AllowStates | AllowModifyStates | AllowCall | AllowNotify
};

ostream&
operator<<(ostream& os, const CallFlags& cf)
{
   std::stringstream ss;
   ss << "CallFlags(" << (int)cf << "; 0x" << std::hex << (int)cf << ")";
   os << ss.str();
   return os;
}

} // namespace SmartContract
//
} // namespace Neo