// Copyright (c) 2018-2019 SIN developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <infinitynodeman.h>
#include <util.h> //fMasterNode variable

CInfinitynodeMan infnodeman;

CInfinitynodeMan::CInfinitynodeMan()
: cs(),
  mapInfinitynodes(),
  nLastScanHeight(0)
{}

void CInfinitynodeMan::Clear()
{
    LOCK(cs);
    mapInfinitynodes.clear();
    nLastScanHeight = 0;
}

bool CInfinitynodeMan::Add(CInfinitynode &inf)
{
    LOCK(cs);
    if (Has(inf.vinBurnFund.prevout)) return false;
    mapInfinitynodes[inf.vinBurnFund.prevout] = inf;
    return true;
}

CInfinitynode* CInfinitynodeMan::Find(const COutPoint &outpoint)
{
    LOCK(cs);
    auto it = mapInfinitynodes.find(outpoint);
    return it == mapInfinitynodes.end() ? NULL : &(it->second);
}

bool CInfinitynodeMan::Get(const COutPoint& outpoint, CInfinitynode& infinitynodeRet)
{
    // Theses mutexes are recursive so double locking by the same thread is safe.
    LOCK(cs);
    auto it = mapInfinitynodes.find(outpoint);
    if (it == mapInfinitynodes.end()) {
        return false;
    }

    infinitynodeRet = it->second;
    return true;
}

bool CInfinitynodeMan::Has(const COutPoint& outpoint)
{
    LOCK(cs);
    return mapInfinitynodes.find(outpoint) != mapInfinitynodes.end();
}

void CInfinitynodeMan::UpdatedBlockTip(const CBlockIndex *pindex)
{
    nCachedBlockHeight = pindex->nHeight;
    if(fMasterNode) {
        // normal wallet does not need to update this every block, doing update on rpc call should be enough
        /* SIN::TODO - update last paid for all infinitynode */
        //UpdateLastPaid(pindex);
    }
}

void CInfinitynodeMan::CheckAndRemove(CConnman& connman)
{
    LOCK(cs);
    if (nCachedBlockHeight > nLastScanHeight)
    {
        LogPrint(BCLog::INFINITYNODE, "CInfinitynodeMan::CheckAndRemove -- block height %d and lastScan %d\n", 
                   nCachedBlockHeight, nLastScanHeight);
        nLastScanHeight = nCachedBlockHeight;
    }
}

void buildInfinitynodeList()
{
}
