// Copyright (c) 2018-2019 SIN developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SIN_INFINITYNODE_H
#define SIN_INFINITYNODE_H

#include <key.h> // for typr int65_t
#include <validation.h>

using namespace std;

class CInfinitynode;
class CConnman;

struct infinitynode_info_t
{
    infinitynode_info_t() = default;
    infinitynode_info_t(infinitynode_info_t const&) = default;

    infinitynode_info_t(int protoVer, int64_t sTime) :
        nProtocolVersion{protoVer}, sigTime{sTime} 
    {}
    infinitynode_info_t(int protoVer, int64_t sTime, COutPoint const& outpointBurnFund):
        nProtocolVersion{protoVer}, sigTime{sTime} , vinBurnFund{outpointBurnFund}
    {}

    int nProtocolVersion = 0;
    int64_t sigTime = 0;
    CTxIn vinBurnFund{};

    int nHeight = -1;
    int nExpireHeight = -1;
    int nLastRewardHeight = -1;
    int nNextRewardHeight = -1;
};

class CInfinitynode : public infinitynode_info_t
{
private:
    // critical section to protect the inner data structures
    mutable CCriticalSection cs;
public:
    enum SinType {
        SINNODE_1 = 1, SINNODE_5 = 5, SINNODE_10 = 10, SINNODE_UNKNOWN = 0
    };

    CInfinitynode();
    CInfinitynode(const CInfinitynode& other);
    CInfinitynode(int nProtocolVersionIn, COutPoint outpointBurnFund);

    CInfinitynode& operator=(CInfinitynode const& from)
    {
        static_cast<infinitynode_info_t&>(*this)=from;
        nHeight = from.nHeight;
        nExpireHeight = from.nExpireHeight;
        nLastRewardHeight = from.nLastRewardHeight;
        nNextRewardHeight = from.nNextRewardHeight;
        return *this;
    }
};

inline bool operator==(const CInfinitynode& a, const CInfinitynode& b)
{
    return a.vinBurnFund == b.vinBurnFund;
}
inline bool operator!=(const CInfinitynode& a, const CInfinitynode& b)
{
    return !(a.vinBurnFund == b.vinBurnFund);
}
#endif // SIN_INFINITYNODE_H