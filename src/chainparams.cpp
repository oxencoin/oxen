// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xd4;
        pchMessageStart[1] = 0xf5;
        pchMessageStart[2] = 0xc3;
        pchMessageStart[3] = 0x34;
        vAlertPubKey = ParseHex("04a77fb4bfc0c93aa3fe641725d01bb32e422f73e669ad0d84d6309778761386ef82899e7e2edd2f4fb06955b1a788b677ca5832fbc378533f1c07d62edcddff56");
        nDefaultPort = 8542;
        nRPCPort = 8543;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);


        const char* pszTimestamp = "BTC Block #401729";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1457456114, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1457456114;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 988240077;

        hashGenesisBlock = genesis.GetHash();
		
        assert(hashGenesisBlock == uint256("0x00000792e26cb3815ba656a2c72b3b2660ab93d359524bf119d1b831c9bc87a5"));
        assert(genesis.hashMerkleRoot == uint256("0x16d2e2608c3406d0ea537d65f75fd5dce6d3ef839cd054a9719764c121087db9"));

        vSeeds.push_back(CDNSSeedData("45.32.130.61", "45.32.130.61"));


        base58Prefixes[PUBKEY_ADDRESS] = boost::assign::list_of(115).convert_to_container<std::vector<unsigned char> >();;
        base58Prefixes[SCRIPT_ADDRESS] = boost::assign::list_of(5).convert_to_container<std::vector<unsigned char> >();;
        base58Prefixes[SECRET_KEY] =     boost::assign::list_of(177).convert_to_container<std::vector<unsigned char> >();;
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();;
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();;

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nLastPOWBlock = 90000;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xc3;
        pchMessageStart[1] = 0x4a;
        pchMessageStart[2] = 0x4e;
        pchMessageStart[3] = 0x55;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 8);
        vAlertPubKey = ParseHex("04a353b8a3edc80e1b3821d1239215acd905b8bab79acbc680202080eaebb3546b67aea9e3d2c4ebfba47eaaa7aab15cc3697ba97a77a7a08256cbb1a3ca67191c");
        nDefaultPort = 18542;
        nRPCPort = 18543;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nTime    = 1457456114;
        genesis.nNonce = 1528;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00c8fa68da7cde713246cc808c9dc1b1c51f258aa89ef8395d4adc56f3e65c9a"));

        vFixedSeeds.clear();
        vSeeds.push_back(CDNSSeedData("45.32.130.61", "45.32.130.61"));

        base58Prefixes[PUBKEY_ADDRESS] = boost::assign::list_of(137).convert_to_container<std::vector<unsigned char> >();;
        base58Prefixes[SCRIPT_ADDRESS] = boost::assign::list_of(196).convert_to_container<std::vector<unsigned char> >();;
        base58Prefixes[SECRET_KEY]     = boost::assign::list_of(239).convert_to_container<std::vector<unsigned char> >();;
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();;
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();;

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;




static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;

        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {

    bool fTestNet = GetBoolArg("-testnet", false);



    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
