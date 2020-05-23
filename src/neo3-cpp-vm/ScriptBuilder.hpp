#pragma once

#include <optional>

//using System;
//using System.IO;
//using System.Numerics;
//using System.Text;

#include <neo3-cpp-core/neopt-common/System.hpp>

using neopt::BinaryWriter;
using neopt::BitConverter;
using neopt::MemoryStream;

#include "OpCode.hpp"

namespace Neo {
//
namespace VM {
//
class ScriptBuilder //: IDisposable
{

private:
   //readonly MemoryStream ms = new MemoryStream();
   MemoryStream ms;
   //
   //readonly BinaryWriter writer;
   BinaryWriter writer;

public:
   //int Offset = > (int)ms.Position;
   int Offset()
   {
      //return (int)ms.Position;
      assert(false);
      return -1;
   }

   ScriptBuilder()
   {
      writer = BinaryWriter{ &ms };
   }

   //void Dispose()
   ~ScriptBuilder()
   {
      //writer.Dispose();
      //ms.Dispose();
   }

   // TODO: not sure that zero is the same as null...
   ScriptBuilder& Emit(OpCode op, std::optional<vbyte> arg = std::nullopt)
   {
      writer.Write((neopt::byte)op);
      if (arg)
         writer.Write(*arg);
      return *this;
   }

   /*
   ScriptBuilder EmitCall(int offset)
   {
      if (offset < sbyte.MinValue || offset > sbyte.MaxValue)
         return Emit(OpCode::CALL_L, BitConverter.GetBytes(offset));
      else
         return Emit(OpCode::CALL, new[]{ (byte)offset });
   }

   ScriptBuilder EmitJump(OpCode op, int offset)
   {
      if (op < OpCode::JMP || op > OpCode::JMPLE_L)
         throw new ArgumentOutOfRangeException(nameof(op));
      if ((int)op % 2 == 0 && (offset < sbyte.MinValue || offset > sbyte.MaxValue))
         op += 1;
      if ((int)op % 2 == 0)
         return Emit(op, new[]{ (byte)offset });
      else
         return Emit(op, BitConverter.GetBytes(offset));
   }

   ScriptBuilder EmitPush(BigInteger number)
   {
      if (number >= -1 && number <= 16)
         return Emit(OpCode::PUSH0 + (byte)(int)number);
      byte[] data = number.ToByteArray(isUnsigned
                                       : false, isBigEndian
                                       : false);
      if (data.Length == 1)
         return Emit(OpCode::PUSHINT8, data);
      if (data.Length == 2)
         return Emit(OpCode::PUSHINT16, data);
      if (data.Length <= 4)
         return Emit(OpCode::PUSHINT32, PadRight(data, 4));
      if (data.Length <= 8)
         return Emit(OpCode::PUSHINT64, PadRight(data, 8));
      if (data.Length <= 16)
         return Emit(OpCode::PUSHINT128, PadRight(data, 16));
      if (data.Length <= 32)
         return Emit(OpCode::PUSHINT256, PadRight(data, 32));
      throw new ArgumentOutOfRangeException(nameof(number));
   }

   ScriptBuilder EmitPush(bool data)
   {
      return Emit(data ? OpCode::PUSH1 : OpCode::PUSH0);
   }
*/

   ScriptBuilder& EmitPush(vbyte data)
   {
      //if (data == null)
      //   throw new ArgumentNullException(nameof(data));
      // impossible null here

      if (data.size() < 0x100) {
         Emit(OpCode::PUSHDATA1);
         writer.Write((neopt::byte)data.size());
         writer.Write(data);
      } else if (data.size() < 0x10000) {
         Emit(OpCode::PUSHDATA2);
         writer.Write((neopt::uint16)data.size());
         writer.Write(data);
      } else // if (data.Length < 0x100000000L)
      {
         Emit(OpCode::PUSHDATA4);
         writer.Write((neopt::uint32)data.size()); // TODO: CHECK THIS TYPE!!! (neopt::uint32)
         writer.Write(data);
      }
      return *this;
   }

   /*
   ScriptBuilder EmitPush(string data)
   {
      return EmitPush(Encoding.UTF8.GetBytes(data));
   }

   ScriptBuilder EmitRaw(byte[] arg = null)
   {
      if (arg != null)
         writer.Write(arg);
      return this;
   }
*/

   ScriptBuilder EmitSysCall(neopt::uint32 api)
   {
      std::cout << "WARNING: EmitSysCall api = " << api << std::endl;
      return Emit(OpCode::SYSCALL, BitConverter::GetBytes(api));
   }

   vbyte ToArray()
   {
      writer.Flush();
      return ms.ToArray();
   }

   /*
   static byte[] PadRight(byte[] data, int length)
   {
      if (data.Length >= length)
         return data;
      byte[] buffer = new byte[length];
      Buffer.BlockCopy(data, 0, buffer, 0, data.Length);
      return buffer;
   }
   */
};
//
} // namespace VM
//
} // namespace Neo
