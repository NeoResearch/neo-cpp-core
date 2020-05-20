#pragma once

#include <cstddef>
#include <sstream>

#include <neo3-cpp-core/neopt-common/System.hpp>

namespace Neo {
//
namespace SmartContract {
//
enum class TriggerType : neopt::byte
{
        System = 0x01,
        /// <summary>
        /// The verification trigger indicates that the contract is being invoked as a verification function.
        /// The verification function can accept multiple parameters, and should return a boolean value that indicates the validity of the transaction or block.
        /// The entry point of the contract will be invoked if the contract is triggered by Verification: 
        ///     main(...);
        /// The entry point of the contract must be able to handle this type of invocation.
        /// </summary>
        Verification = 0x20,
        /// <summary>
        /// The application trigger indicates that the contract is being invoked as an application function.
        /// The application function can accept multiple parameters, change the states of the blockchain, and return any type of value.
        /// The contract can have any form of entry point, but we recommend that all contracts should have the following entry point:
        ///     public byte[] main(string operation, params object[] args)
        /// The functions can be invoked by creating an InvocationTransaction.
        /// </summary>
        Application = 0x40,

        All = System | Verification | Application  
};

ostream&
operator<<(ostream& os, const TriggerType& tt)
{
   std::stringstream ss;
   ss << "TriggerType(" << (int)tt << "; 0x" << std::hex << (int)tt << ")";
   os << ss.str();
   return os;
}

} // namespace SmartContract
//
} // namespace Neo