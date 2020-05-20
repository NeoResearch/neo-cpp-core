
#pragma once

//using Neo.Cryptography;
//using System;
//using System.Text;

#include <functional>

#include "ApplicationEngine.hpp"
#include "CallFlags.hpp"
#include "TriggerType.hpp"

namespace Neo {

namespace SmartContract {
class InteropDescriptor
{
public:
   std::string Method;
   std::string getMethod()
   {
      return Method;
   }

public:
   uint Hash;
   uint getHash()
   {
      return Hash;
   }

   //internal
   //const std::function<bool(ApplicationEngine&)>& Handler;
   bool (*Handler)(ApplicationEngine&);
   //const std::function<bool(ApplicationEngine&)>& getHandler()
   //{
   //   return Handler;
   //}

public:
   long FixedPrice;
   long getFixedPrice()
   {
      return FixedPrice;
   }

public:
   TriggerType AllowedTriggers;
   TriggerType getAllowedTriggers()
   {
      return AllowedTriggers;
   }

public:
   CallFlags RequiredCallFlags;
   CallFlags getRequiredCallFlags()
   {
      return RequiredCallFlags;
   }

   //internal
   //InteropDescriptor(std::string method, const std::function<bool(ApplicationEngine&)>& handler, long fixedPrice, TriggerType allowedTriggers, CallFlags requiredCallFlags)
   InteropDescriptor(std::string method, bool (*handler)(ApplicationEngine&), long fixedPrice, TriggerType allowedTriggers, CallFlags requiredCallFlags)
     : Method{ method }
     , Handler{ handler }
     , FixedPrice{ fixedPrice }
     , AllowedTriggers(allowedTriggers)
     , RequiredCallFlags(requiredCallFlags)
   {
      //this.Method = method;
      // TODO --------> ///////this.Hash = BitConverter.ToUInt32(Encoding.ASCII.GetBytes(method).Sha256(), 0);
      //this.Handler = handler;
      //this.FixedPrice = fixedPrice;
      //this.AllowedTriggers = allowedTriggers;
      //this.RequiredCallFlags = requiredCallFlags;
   }

   InteropDescriptor(const InteropDescriptor& other)
     : Method{ other.Method }
     , Handler{ other.Handler }
     , FixedPrice{ other.FixedPrice }
     , AllowedTriggers(other.AllowedTriggers)
     , RequiredCallFlags(other.RequiredCallFlags)
   {
      //this.Method = method;
      // TODO --------> ///////this.Hash = BitConverter.ToUInt32(Encoding.ASCII.GetBytes(method).Sha256(), 0);
      //this.Handler = handler;
      //this.FixedPrice = fixedPrice;
      //this.AllowedTriggers = allowedTriggers;
      //this.RequiredCallFlags = requiredCallFlags;
   }

public:
   //static implicit operator uint(InteropDescriptor descriptor)
   operator uint() const
   {
      return this->Hash;
   }

}; // class InteropDescriptor
//
} // namespace SmartContract
//
} // namespace Neo