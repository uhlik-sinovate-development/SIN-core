// Copyright (c) 2018-2019 SIN developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SIN_INFINITYNODEMAN_H
#define SIN_INFINITYNODEMAN_H

#include <infinitynode.h>

using namespace std;

class CInfinitynodeMan;
class CConnman;

extern CInfinitynodeMan infnodeman;

class CInfinitynodeMan
{
public:

private:

    // critical section to protect the inner data structures
    mutable CCriticalSection cs;
    // Keep track of current block height
    int nCachedBlockHeight;

    static const int INF_BEGIN_HEIGHT = 165000;
    static const int INF_BEGIN_REWARD = 200000;

    // map to hole all INFs
    std::map<COutPoint, CInfinitynode> mapInfinitynodes;


public:

    CInfinitynodeMan();

    int64_t nLastScanHeight;//last verification from blockchain
    /// Add an entry
    bool Add(CInfinitynode &mn);
    /// Find an entry
    CInfinitynode* Find(const COutPoint& outpoint);
    /// Clear InfinityNode vector
    void Clear();
    /// Versions of Find that are safe to use from outside the class
    bool Get(const COutPoint& outpoint, CInfinitynode& infinitynodeRet);
    bool Has(const COutPoint& outpoint);

    void buildInfinitynodeList();
    void updateInfinitynodeList(int fromHeight);

    void CheckAndRemove(CConnman& connman);
    void UpdatedBlockTip(const CBlockIndex *pindex);
};
#endif // SIN_INFINITYNODEMAN_H