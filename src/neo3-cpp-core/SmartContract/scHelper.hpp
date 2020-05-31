#pragma once

/*
using Neo.Cryptography;
using Neo.Cryptography.ECC;
using Neo.Ledger;
using Neo.Network.P2P.Payloads;
using Neo.Persistence;
using Neo.SmartContract.Manifest;
using Neo.VM;
using Neo.VM.Types;
using System;
using System.Buffers.Binary;
using System.Collections.Generic;
*/

#include <neo3-cpp-core/neopt-common/numbers/UInt160.hpp>
using UInt160 = neopt::UInt160;

#include <neo3-cpp-core/Cryptography/Crypto.hpp>
#include <neo3-cpp-core/Cryptography/cHelper.hpp>

namespace Neo {
//
namespace SmartContract {
//
namespace scHelper {
//
/*
        public static bool IsMultiSigContract(this byte[] script)
        {
            return IsMultiSigContract(script, out _, out _, null);
        }

        public static bool IsMultiSigContract(this byte[] script, out int m, out int n)
        {
            return IsMultiSigContract(script, out m, out n, null);
        }

        public static bool IsMultiSigContract(this byte[] script, out int m, out ECPoint[] points)
        {
            List<ECPoint> list = new List<ECPoint>();
            if (IsMultiSigContract(script, out m, out _, list))
            {
                points = list.ToArray();
                return true;
            }
            else
            {
                points = null;
                return false;
            }
        }

        private static bool IsMultiSigContract(byte[] script, out int m, out int n, List<ECPoint> points)
        {
            m = 0; n = 0;
            int i = 0;
            if (script.Length < 43) return false;
            switch (script[i])
            {
                case (byte)OpCode.PUSHINT8:
                    m = script[++i];
                    ++i;
                    break;
                case (byte)OpCode.PUSHINT16:
                    m = BinaryPrimitives.ReadUInt16LittleEndian(script.AsSpan(++i));
                    i += 2;
                    break;
                case byte b when b >= (byte)OpCode.PUSH1 && b <= (byte)OpCode.PUSH16:
                    m = b - (byte)OpCode.PUSH0;
                    ++i;
                    break;
                default:
                    return false;
            }
            if (m < 1 || m > 1024) return false;
            while (script[i] == (byte)OpCode.PUSHDATA1)
            {
                if (script.Length <= i + 35) return false;
                if (script[++i] != 33) return false;
                points?.Add(ECPoint.DecodePoint(script.AsSpan(i + 1, 33), ECCurve.Secp256r1));
                i += 34;
                ++n;
            }
            if (n < m || n > 1024) return false;
            switch (script[i])
            {
                case (byte)OpCode.PUSHINT8:
                    if (n != script[++i]) return false;
                    ++i;
                    break;
                case (byte)OpCode.PUSHINT16:
                    if (script.Length < i + 3 || n != BinaryPrimitives.ReadUInt16LittleEndian(script.AsSpan(++i))) return false;
                    i += 2;
                    break;
                case byte b when b >= (byte)OpCode.PUSH1 && b <= (byte)OpCode.PUSH16:
                    if (n != b - (byte)OpCode.PUSH0) return false;
                    ++i;
                    break;
                default:
                    return false;
            }
            if (script[i++] != (byte)OpCode.PUSHNULL) return false;
            if (script[i++] != (byte)OpCode.SYSCALL) return false;
            if (script.Length != i + 4) return false;
            if (BitConverter.ToUInt32(script, i) != InteropService.Crypto.CheckMultisigWithECDsaSecp256r1)
                return false;
            return true;
        }

        public static bool IsSignatureContract(this byte[] script)
        {
            if (script.Length != 41) return false;
            if (script[0] != (byte)OpCode.PUSHDATA1
                || script[1] != 33
                || script[35] != (byte)OpCode.PUSHNULL
                || script[36] != (byte)OpCode.SYSCALL
                || BitConverter.ToUInt32(script, 37) != InteropService.Crypto.VerifyWithECDsaSecp256r1)
                return false;
            return true;
        }

        public static bool IsStandardContract(this byte[] script)
        {
            return script.IsSignatureContract() || script.IsMultiSigContract();
        }
*/

UInt160
ToScriptHash(const vbyte& script)
{
   return UInt160(Neo::Cryptography::Crypto::Hash160(script));
}

string
EXPORT_NEO3API_ToScriptHash(string hexstring);

/*
        public static UInt160 ToScriptHash(this ReadOnlySpan<byte> script)
        {
            return new UInt160(Crypto.Hash160(script));
        }

        internal static bool VerifyWitnesses(this IVerifiable verifiable, StoreView snapshot, long gas)
        {
            if (gas < 0) return false;

            UInt160[] hashes;
            try
            {
                hashes = verifiable.GetScriptHashesForVerifying(snapshot);
            }
            catch (InvalidOperationException)
            {
                return false;
            }
            if (hashes.Length != verifiable.Witnesses.Length) return false;
            for (int i = 0; i < hashes.Length; i++)
            {
                int offset;
                byte[] verification = verifiable.Witnesses[i].VerificationScript;
                if (verification.Length == 0)
                {
                    ContractState cs = snapshot.Contracts.TryGet(hashes[i]);
                    if (cs is null) return false;
                    ContractMethodDescriptor md = cs.Manifest.Abi.GetMethod("verify");
                    if (md is null) return false;
                    verification = cs.Script;
                    offset = md.Offset;
                }
                else
                {
                    if (hashes[i] != verifiable.Witnesses[i].ScriptHash) return false;
                    offset = 0;
                }
                using (ApplicationEngine engine = new ApplicationEngine(TriggerType.Verification, verifiable, snapshot, gas))
                {
                    engine.LoadScript(verification, CallFlags.ReadOnly).InstructionPointer = offset;
                    engine.LoadScript(verifiable.Witnesses[i].InvocationScript, CallFlags.None);
                    if (engine.Execute() == VMState.FAULT) return false;
                    if (!engine.ResultStack.TryPop(out StackItem result) || !result.ToBoolean()) return false;
                    gas -= engine.GasConsumed;
                }
            }
            return true;
        }
        */
//
} // namespace scHelper
//
} //namespace SmartContract
//
} //namespace Neo

// =====================
// define API methods

string
Neo::SmartContract::scHelper::EXPORT_NEO3API_ToScriptHash(string hexstring)
{
   vbyte bytes = Helper::HexToBytes(hexstring);
   return ToScriptHash(bytes).ToString();
}