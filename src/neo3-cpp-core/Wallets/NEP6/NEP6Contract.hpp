#pragma once 

#include <neo3-cpp-core/Cryptography/Cryptography.hpp>

namespace Neo {
//
namespace Wallets {
//
namespace NEP6 {
//
class NEP6Contract : Contract
{
        public:
        vector<string> ParameterNames;
        public:
         bool Deployed;

        private:
         void AddAccount(NEP6Account account, bool is_import)
        {
            lock (accounts)
            {
                if (accounts.TryGetValue(account.ScriptHash, out NEP6Account account_old))
                {
                    account.Label = account_old.Label;
                    account.IsDefault = account_old.IsDefault;
                    account.Lock = account_old.Lock;
                    if (account.Contract == null)
                    {
                        account.Contract = account_old.Contract;
                    }
                    else
                    {
                        NEP6Contract contract_old = (NEP6Contract)account_old.Contract;
                        if (contract_old != null)
                        {
                            NEP6Contract contract = (NEP6Contract)account.Contract;
                            contract.ParameterNames = contract_old.ParameterNames;
                            contract.Deployed = contract_old.Deployed;
                        }
                    }
                    account.Extra = account_old.Extra;
                }
                accounts[account.ScriptHash] = account;
            }
        }

} // class Wallet
//
} // namespace NEP6
//
} // namespace Wallet
//
} // namespace Neo
  //

