#pragma once

#include <cstddef>
#include <sstream>

#include <neo3-cpp-core/neopt-common/System.hpp>

namespace Neo {
//
namespace SmartContract {
//
enum class ContractParameterType : neopt::byte
{
        Signature = 0x00,
        Boolean = 0x01,
        Integer = 0x02,
        Hash160 = 0x03,
        Hash256 = 0x04,
        ByteArray = 0x05,
        PublicKey = 0x06,
        String = 0x07,

        Array = 0x10,
        Map = 0x12,

        InteropInterface = 0xf0,

        Any = 0xfe,
        Void = 0xff       
};

ostream&
operator<<(ostream& os, const ContractParameterType& tt)
{
   std::stringstream ss;
   ss << "ContractParameterType(" << (int)tt << "; 0x" << std::hex << (int)tt << ")";
   os << ss.str();
   return os;
}

} // namespace SmartContract
//
} // namespace Neo