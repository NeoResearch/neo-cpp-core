#pragma once

// using Neo.Cryptography;
#include <neo3-cpp-core/Cryptography/Cryptography.hpp>
using ECPoint = Neo::Cryptography::ECC::ECPoint;

#include <neo3-cpp-core/Cryptography/cHelper.hpp>

#include <neo3-cpp-core/ExternalCrypto.h>
/*
using Neo.IO;
using Neo.Ledger;
using Neo.Network.P2P.Payloads;
using Neo.Persistence;
using Neo.SmartContract;
using Neo.SmartContract.Native;
using Neo.VM;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Security.Cryptography;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using static Neo.Wallets.Helper;
*/

#include "./WalletAccount.hpp"

#include <neo3-cpp-core/ProtocolSettings.hpp>

namespace Neo {
//
namespace Wallets {
//
class Wallet
{
public:
   Wallet()
   {
   }

   virtual ~Wallet()
   {
   }

public:
   uptr<WalletAccount> CreateAccount()
   {
      vbyte privateKey(32);
      //using (RandomNumberGenerator rng = RandomNumberGenerator.Create())
      {

         privateKey = Neo::Cryptography::cHelper::RandBytes(privateKey.size());
      }
      uptr<WalletAccount> account{ CreateAccount(privateKey) };
      //Array.Clear(privateKey, 0, privateKey.Length);
      return account;
   }

public:
   virtual uptr<WalletAccount> CreateAccount(const vbyte& privateKey) = 0;

   
        public:
         virtual string Name() = 0;

         /*
        public string Path { get; }
        public abstract Version Version { get; }

        public abstract bool ChangePassword(string oldPassword, string newPassword);
        public abstract bool Contains(UInt160 scriptHash);
        public abstract WalletAccount CreateAccount(byte[] privateKey);
        public abstract WalletAccount CreateAccount(Contract contract, KeyPair key = null);
        public abstract WalletAccount CreateAccount(UInt160 scriptHash);
        public abstract bool DeleteAccount(UInt160 scriptHash);
        public abstract WalletAccount GetAccount(UInt160 scriptHash);
        public abstract IEnumerable<WalletAccount> GetAccounts();

        internal Wallet()
        {
        }

        protected Wallet(string path)
        {
            this.Path = path;
        }

        public WalletAccount CreateAccount()
        {
            byte[] privateKey = new byte[32];
            using (RandomNumberGenerator rng = RandomNumberGenerator.Create())
            {
                rng.GetBytes(privateKey);
            }
            WalletAccount account = CreateAccount(privateKey);
            Array.Clear(privateKey, 0, privateKey.Length);
            return account;
        }

        public WalletAccount CreateAccount(Contract contract, byte[] privateKey)
        {
            if (privateKey == null) return CreateAccount(contract);
            return CreateAccount(contract, new KeyPair(privateKey));
        }

        private List<(UInt160 Account, BigInteger Value)> FindPayingAccounts(List<(UInt160 Account, BigInteger Value)> orderedAccounts, BigInteger amount)
        {
            var result = new List<(UInt160 Account, BigInteger Value)>();
            BigInteger sum_balance = orderedAccounts.Select(p => p.Value).Sum();
            if (sum_balance == amount)
            {
                result.AddRange(orderedAccounts);
                orderedAccounts.Clear();
            }
            else
            {
                for (int i = 0; i < orderedAccounts.Count; i++)
                {
                    if (orderedAccounts[i].Value < amount)
                        continue;
                    if (orderedAccounts[i].Value == amount)
                    {
                        result.Add(orderedAccounts[i]);
                        orderedAccounts.RemoveAt(i);
                    }
                    else
                    {
                        result.Add((orderedAccounts[i].Account, amount));
                        orderedAccounts[i] = (orderedAccounts[i].Account, orderedAccounts[i].Value - amount);
                    }
                    break;
                }
                if (result.Count == 0)
                {
                    int i = orderedAccounts.Count - 1;
                    while (orderedAccounts[i].Value <= amount)
                    {
                        result.Add(orderedAccounts[i]);
                        amount -= orderedAccounts[i].Value;
                        orderedAccounts.RemoveAt(i);
                        i--;
                    }
                    for (i = 0; i < orderedAccounts.Count; i++)
                    {
                        if (orderedAccounts[i].Value < amount)
                            continue;
                        if (orderedAccounts[i].Value == amount)
                        {
                            result.Add(orderedAccounts[i]);
                            orderedAccounts.RemoveAt(i);
                        }
                        else
                        {
                            result.Add((orderedAccounts[i].Account, amount));
                            orderedAccounts[i] = (orderedAccounts[i].Account, orderedAccounts[i].Value - amount);
                        }
                        break;
                    }
                }
            }
            return result;
        }

        public WalletAccount GetAccount(ECPoint pubkey)
        {
            return GetAccount(Contract.CreateSignatureRedeemScript(pubkey).ToScriptHash());
        }

        public BigDecimal GetAvailable(UInt160 asset_id)
        {
            UInt160[] accounts = GetAccounts().Where(p => !p.WatchOnly).Select(p => p.ScriptHash).ToArray();
            return GetBalance(asset_id, accounts);
        }

        public BigDecimal GetBalance(UInt160 asset_id, params UInt160[] accounts)
        {
            byte[] script;
            using (ScriptBuilder sb = new ScriptBuilder())
            {
                sb.EmitPush(0);
                foreach (UInt160 account in accounts)
                {
                    sb.EmitAppCall(asset_id, "balanceOf", account);
                    sb.Emit(OpCode.ADD);
                }
                sb.EmitAppCall(asset_id, "decimals");
                script = sb.ToArray();
            }
            using ApplicationEngine engine = ApplicationEngine.Run(script, extraGAS: 20000000L * accounts.Length);
            if (engine.State.HasFlag(VMState.FAULT))
                return new BigDecimal(0, 0);
            byte decimals = (byte)engine.ResultStack.Pop().GetBigInteger();
            BigInteger amount = engine.ResultStack.Pop().GetBigInteger();
            return new BigDecimal(amount, decimals);
        }
*/
        public:
        
         static std::optional<vbyte> GetPrivateKeyFromNEP2(string nep2, string passphrase, int N = 16384, int r = 8, int p = 8)
        {
           std::cout << "GetPrivateKeyFromNEP2 NOT IMPLEMENTED!" << std::endl;
           /*
            if (nep2 == null) throw new ArgumentNullException(nameof(nep2));
            if (passphrase == null) throw new ArgumentNullException(nameof(passphrase));
            byte[] data = nep2.Base58CheckDecode();
            if (data.Length != 39 || data[0] != 0x01 || data[1] != 0x42 || data[2] != 0xe0)
                throw new FormatException();
            byte[] addresshash = new byte[4];
            Buffer.BlockCopy(data, 3, addresshash, 0, 4);
            byte[] datapassphrase = Encoding.UTF8.GetBytes(passphrase);
            byte[] derivedkey = SCrypt.DeriveKey(datapassphrase, addresshash, N, r, p, 64);
            Array.Clear(datapassphrase, 0, datapassphrase.Length);
            byte[] derivedhalf1 = derivedkey[..32];
            byte[] derivedhalf2 = derivedkey[32..];
            Array.Clear(derivedkey, 0, derivedkey.Length);
            byte[] encryptedkey = new byte[32];
            Buffer.BlockCopy(data, 7, encryptedkey, 0, 32);
            Array.Clear(data, 0, data.Length);
            byte[] prikey = XOR(encryptedkey.AES256Decrypt(derivedhalf2), derivedhalf1);
            Array.Clear(derivedhalf1, 0, derivedhalf1.Length);
            Array.Clear(derivedhalf2, 0, derivedhalf2.Length);
            ECPoint pubkey = Cryptography.ECC.ECCurve.Secp256r1.G * prikey;
            UInt160 script_hash = Contract.CreateSignatureRedeemScript(pubkey).ToScriptHash();
            string address = script_hash.ToAddress();
            if (!Encoding.ASCII.GetBytes(address).Sha256().Sha256().AsSpan(0, 4).SequenceEqual(addresshash))
                throw new FormatException();
            return prikey;
            */
           return vbyte{};
        }
/*
        public static byte[] GetPrivateKeyFromWIF(string wif)
        {
            if (wif == null) throw new ArgumentNullException();
            byte[] data = wif.Base58CheckDecode();
            if (data.Length != 34 || data[0] != 0x80 || data[33] != 0x01)
                throw new FormatException();
            byte[] privateKey = new byte[32];
            Buffer.BlockCopy(data, 1, privateKey, 0, privateKey.Length);
            Array.Clear(data, 0, data.Length);
            return privateKey;
        }

        public virtual WalletAccount Import(X509Certificate2 cert)
        {
            byte[] privateKey;
            using (ECDsa ecdsa = cert.GetECDsaPrivateKey())
            {
                privateKey = ecdsa.ExportParameters(true).D;
            }
            WalletAccount account = CreateAccount(privateKey);
            Array.Clear(privateKey, 0, privateKey.Length);
            return account;
        }

        public virtual WalletAccount Import(string wif)
        {
            byte[] privateKey = GetPrivateKeyFromWIF(wif);
            WalletAccount account = CreateAccount(privateKey);
            Array.Clear(privateKey, 0, privateKey.Length);
            return account;
        }

        public virtual WalletAccount Import(string nep2, string passphrase, int N = 16384, int r = 8, int p = 8)
        {
            byte[] privateKey = GetPrivateKeyFromNEP2(nep2, passphrase, N, r, p);
            WalletAccount account = CreateAccount(privateKey);
            Array.Clear(privateKey, 0, privateKey.Length);
            return account;
        }

        public Transaction MakeTransaction(TransferOutput[] outputs, UInt160 from = null)
        {
            UInt160[] accounts;
            if (from is null)
            {
                accounts = GetAccounts().Where(p => !p.Lock && !p.WatchOnly).Select(p => p.ScriptHash).ToArray();
            }
            else
            {
                if (!Contains(from))
                    throw new ArgumentException($"The address {from.ToString()} was not found in the wallet");
                accounts = new[] { from };
            }
            using (SnapshotView snapshot = Blockchain.Singleton.GetSnapshot())
            {
                HashSet<UInt160> cosignerList = new HashSet<UInt160>();
                byte[] script;
                List<(UInt160 Account, BigInteger Value)> balances_gas = null;
                using (ScriptBuilder sb = new ScriptBuilder())
                {
                    foreach (var (assetId, group, sum) in outputs.GroupBy(p => p.AssetId, (k, g) => (k, g, g.Select(p => p.Value.Value).Sum())))
                    {
                        var balances = new List<(UInt160 Account, BigInteger Value)>();
                        foreach (UInt160 account in accounts)
                            using (ScriptBuilder sb2 = new ScriptBuilder())
                            {
                                sb2.EmitAppCall(assetId, "balanceOf", account);
                                using (ApplicationEngine engine = ApplicationEngine.Run(sb2.ToArray(), snapshot, testMode: true))
                                {
                                    if (engine.State.HasFlag(VMState.FAULT))
                                        throw new InvalidOperationException($"Execution for {assetId.ToString()}.balanceOf('{account.ToString()}' fault");
                                    BigInteger value = engine.ResultStack.Pop().GetBigInteger();
                                    if (value.Sign > 0) balances.Add((account, value));
                                }
                            }
                        BigInteger sum_balance = balances.Select(p => p.Value).Sum();
                        if (sum_balance < sum)
                            throw new InvalidOperationException($"It does not have enough balance, expected: {sum.ToString()} found: {sum_balance.ToString()}");
                        foreach (TransferOutput output in group)
                        {
                            balances = balances.OrderBy(p => p.Value).ToList();
                            var balances_used = FindPayingAccounts(balances, output.Value.Value);
                            cosignerList.UnionWith(balances_used.Select(p => p.Account));
                            foreach (var (account, value) in balances_used)
                            {
                                sb.EmitAppCall(output.AssetId, "transfer", account, output.ScriptHash, value);
                                sb.Emit(OpCode.ASSERT);
                            }
                        }
                        if (assetId.Equals(NativeContract.GAS.Hash))
                            balances_gas = balances;
                    }
                    script = sb.ToArray();
                }
                if (balances_gas is null)
                    balances_gas = accounts.Select(p => (Account: p, Value: NativeContract.GAS.BalanceOf(snapshot, p))).Where(p => p.Value.Sign > 0).ToList();

                var cosigners = cosignerList.Select(p =>
                         new Cosigner()
                         {
                             // default access for transfers should be valid only for first invocation
                             Scopes = WitnessScope.CalledByEntry,
                             Account = new UInt160(p.ToArray())
                         }).ToArray();

                return MakeTransaction(snapshot, script, cosigners, balances_gas);
            }
        }

        public Transaction MakeTransaction(byte[] script, UInt160 sender = null, TransactionAttribute[] attributes = null)
        {
            UInt160[] accounts;
            if (sender is null)
            {
                accounts = GetAccounts().Where(p => !p.Lock && !p.WatchOnly).Select(p => p.ScriptHash).ToArray();
            }
            else
            {
                if (!Contains(sender))
                    throw new ArgumentException($"The address {sender.ToString()} was not found in the wallet");
                accounts = new[] { sender };
            }
            using (SnapshotView snapshot = Blockchain.Singleton.GetSnapshot())
            {
                var balances_gas = accounts.Select(p => (Account: p, Value: NativeContract.GAS.BalanceOf(snapshot, p))).Where(p => p.Value.Sign > 0).ToList();
                return MakeTransaction(snapshot, script, attributes ?? new TransactionAttribute[0], balances_gas);
            }
        }

        private Transaction MakeTransaction(StoreView snapshot, byte[] script, TransactionAttribute[] attributes, List<(UInt160 Account, BigInteger Value)> balances_gas)
        {
            Random rand = new Random();
            foreach (var (account, value) in balances_gas)
            {
                Transaction tx = new Transaction
                {
                    Version = 0,
                    Nonce = (uint)rand.Next(),
                    Script = script,
                    Sender = account,
                    ValidUntilBlock = snapshot.Height + Transaction.MaxValidUntilBlockIncrement,
                    Attributes = attributes,
                };

                // will try to execute 'transfer' script to check if it works
                using (ApplicationEngine engine = ApplicationEngine.Run(script, snapshot.Clone(), tx, testMode: true))
                {
                    if (engine.State.HasFlag(VMState.FAULT))
                        throw new InvalidOperationException($"Failed execution for '{script.ToHexString()}'");
                    tx.SystemFee = Math.Max(engine.GasConsumed - ApplicationEngine.GasFree, 0);
                }

                UInt160[] hashes = tx.GetScriptHashesForVerifying(snapshot);

                // base size for transaction: includes const_header + attributes + script + hashes
                int size = Transaction.HeaderSize + tx.Attributes.GetVarSize() + script.GetVarSize() + IO.Helper.GetVarSize(hashes.Length);

                foreach (UInt160 hash in hashes)
                {
                    byte[] witness_script = GetAccount(hash)?.Contract?.Script ?? snapshot.Contracts.TryGet(hash)?.Script;
                    if (witness_script is null) continue;
                    tx.NetworkFee += CalculateNetworkFee(witness_script, ref size);
                }
                tx.NetworkFee += size * NativeContract.Policy.GetFeePerByte(snapshot);
                if (value >= tx.SystemFee + tx.NetworkFee) return tx;
            }
            throw new InvalidOperationException("Insufficient GAS");
        }

        public static long CalculateNetworkFee(byte[] witness_script, ref int size)
        {
            long networkFee = 0;

            if (witness_script.IsSignatureContract())
            {
                size += 67 + witness_script.GetVarSize();
                networkFee += ApplicationEngine.OpCodePrices[OpCode.PUSHDATA1] + ApplicationEngine.OpCodePrices[OpCode.PUSHDATA1] + ApplicationEngine.OpCodePrices[OpCode.PUSHNULL] + InteropService.Crypto.VerifyWithECDsaSecp256r1.FixedPrice;
            }
            else if (witness_script.IsMultiSigContract(out int m, out int n))
            {
                int size_inv = 66 * m;
                size += IO.Helper.GetVarSize(size_inv) + size_inv + witness_script.GetVarSize();
                networkFee += ApplicationEngine.OpCodePrices[OpCode.PUSHDATA1] * m;
                using (ScriptBuilder sb = new ScriptBuilder())
                    networkFee += ApplicationEngine.OpCodePrices[(OpCode)sb.EmitPush(m).ToArray()[0]];
                networkFee += ApplicationEngine.OpCodePrices[OpCode.PUSHDATA1] * n;
                using (ScriptBuilder sb = new ScriptBuilder())
                    networkFee += ApplicationEngine.OpCodePrices[(OpCode)sb.EmitPush(n).ToArray()[0]];
                networkFee += ApplicationEngine.OpCodePrices[OpCode.PUSHNULL] + InteropService.Crypto.VerifyWithECDsaSecp256r1.FixedPrice * n;
            }
            else
            {
                //We can support more contract types in the future.
            }

            return networkFee;
        }

        public bool Sign(ContractParametersContext context)
        {
            bool fSuccess = false;
            foreach (UInt160 scriptHash in context.ScriptHashes)
            {
                WalletAccount account = GetAccount(scriptHash);
                if (account is null) continue;

                // Try to sign self-contained multiSig

                Contract multiSigContract = account.Contract;

                if (multiSigContract != null &&
                    multiSigContract.Script.IsMultiSigContract(out int m, out ECPoint[] points))
                {
                    foreach (var point in points)
                    {
                        account = GetAccount(point);
                        if (account?.HasKey != true) continue;
                        KeyPair key = account.GetKey();
                        byte[] signature = context.Verifiable.Sign(key);
                        fSuccess |= context.AddSignature(multiSigContract, key.PublicKey, signature);
                        if (fSuccess) m--;
                        if (context.Completed || m <= 0) break;
                    }
                }
                else
                {
                    // Try to sign with regular accounts

                    if (account.HasKey)
                    {
                        KeyPair key = account.GetKey();
                        byte[] signature = context.Verifiable.Sign(key);
                        fSuccess |= context.AddSignature(account.Contract, key.PublicKey, signature);
                    }
                }
            }
            return fSuccess;
        }

        public abstract bool VerifyPassword(string password);
    }
    */

}; // class Wallet
//
} // namespace Wallets
//
} // namespace Neo
  //
