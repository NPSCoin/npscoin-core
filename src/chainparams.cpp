// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin Core developers
// Copyright (c) 2014-2017 The Dash Core developers
// Copyright (c) 2018 The NPSCoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"

#include "arith_uint256.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include "chainparamsseeds.h"

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}


/**
 * Build the genesis block. Note that the output of the genesis coinbase cannot
 * be spent as it did not originally exist in the database.
 *
    block.GetHash = 0000026042729d26a60e02509c2aa43f5e9177ff85ed398b1e97a9a409b99e76
    block.merkle = 6f75e031858084b828c4b1b7a39950a509da0c2a92a6e26a29a5c0e5255ec338
    CBlock(hash=b9dd2d85e9124ad36041e8d9cbbe0ca7e7004e30bee9ef8f834d4dff7570043e, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=6f75e031858084b828c4b1b7a39950a509da0c2a92a6e26a29a5c0e5255ec338, nTime=1517437023, nBits=1e0ffff0, nNonce=3196847, vtx=1)
    CTransaction(hash=6f75e03185, ver=1, vin.size=1, vout.size=1, nLockTime=0)
    CTxIn(COutPoint(0000000000000000000000000000000000000000000000000000000000000000, 4294967295), coinbase 04ffff001d0104444573746164616f2033312f30312f3138202d204d5046207065646520636f6e64656e6163616f2064652065782d707265736964656e746520646120506574726f62726173)
    CTxOut(nValue=120.00000000, scriptPubKey=04adba0f34aac0d8fde16fdbb251f9)

    vMerkleTree:  6f75e031858084b828c4b1b7a39950a509da0c2a92a6e26a29a5c0e5255ec338
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "Technological Infrastructure For Masternodes. NPSCoin was born on September 22, 2018.";
    const CScript genesisOutputScript = CScript() << ParseHex("044a288d3c33fdd4df16325b6c6455604282487822f6b583b2b1ab461bcd4beb3ff99abd77af2a5eec906162408f1e19f4ecaf0a9a12317cfef5acec933d562739") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */
class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 262800; // One year - Note: actual number of blocks per calendar year with DGW v3 is ~262800
        consensus.nMasternodePaymentsStartBlock = 720; // 720 blocks ~ 1 day
        consensus.nMasternodePaymentsIncreaseBlock = 99999999; // NOT USED
        consensus.nMasternodePaymentsIncreasePeriod = 99999999; // NOT USED
        consensus.nInstantSendKeepLock = 24;
        consensus.nBudgetPaymentsStartBlock = 1051200; // 4 years from now, not decided yet
        consensus.nBudgetPaymentsCycleBlocks = 21600; // ~(60*24*30)/2, actual number of blocks per month is 275000 / 12 = 22917
        consensus.nBudgetPaymentsWindowBlocks = 100;
        consensus.nBudgetProposalEstablishingTime = 60*60*24;
        consensus.nSuperblockStartBlock = 1072800; // 4 years and 1 month from now, not decided yet
        consensus.nSuperblockCycle = 21600; // ~(60*24*30)/2, actual number of blocks per month is 275000 / 12 = 22917
        consensus.nGovernanceMinQuorum = 10;
        consensus.nGovernanceFilterElements = 20000;
        consensus.nMasternodeMinimumConfirmations = 15;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = 1;
        consensus.BIP34Hash = uint256S("0x0000047777a943ad3805816e64a490155857dc2d5d41224b235dbdc9d6d2c5b7"); // block #1
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 24 * 60 * 60; // NPSCoin: 1 day
        consensus.nPowTargetSpacing = 2 * 60; // NPSCoin: 2 minutes
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1916; // 95% of 2016
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1537628400; // Sept 22nd, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1544857200; // Dec 15th, 2018

        // Deployment of DIP0001
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nStartTime = 1537628400; // Sept 22nd, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nTimeout = 1544857200; // Dec 15th, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nWindowSize = 4032;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nThreshold = 3226; // 80% of 4032

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x000000000000000000000000000000000000000000000000000000000100001f"); // 15 chainwork

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x000009aa4059143f307a2670a8d2093dff1e1d35d64d55a3e817c23efa43b04e"); // 15 hash

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xd3;
        pchMessageStart[1] = 0xc1;
        pchMessageStart[2] = 0x2a;
        pchMessageStart[3] = 0xda;
        vAlertPubKey = ParseHex("04916f291064ea1599b8a82490d8ed4bb0288af7f92a1a8f5afd4b3dbca6a625107e97023f208f4f26ccc8c172be2914edd8602f89f31017d6ec22337cb3d2d1df");
        nDefaultPort = 9855;
        nMaxTipAge = 6 * 60 * 60; // ~144 blocks behind -> 2 x fork detection time, was 24 * 60 * 60 in bitcoin
        nDelayGetHeadersTime = 24 * 60 * 60;
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(1537628400, 1941285, 0x1e0ffff0, 1, 16 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000b72cc1c26003ab8060e62a8eb98684c275d1cd989a2c9af3f9676a3f621"));
        assert(genesis.hashMerkleRoot == uint256S("0x2a99a8553e97400c92e45dfd3bff779f83ae2f9cf51c7287d2dbd8fa4a2101ab"));

        vSeeds.push_back(CDNSSeedData("seed1.npscoin.io", "seed1.npscoin.io" ));
        vSeeds.push_back(CDNSSeedData("seed2.npscoin.io", "seed2.npscoin.io" ));
        vSeeds.push_back(CDNSSeedData("seed3.npscoin.io", "seed3.npscoin.io" ));

        // NPSCoin addresses start with 'N'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,53);
        // NPSCoin script addresses start with '5' or '6'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,12);
        // NPSCoin private keys
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,181);
        // NPSCoin BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        // NPSCoin BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        // NPSCoin BIP44 coin type is '5'
        nExtCoinType = 5;

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        nPoolMaxTransactions = 3;
        nFulfilledRequestExpireTime = 60*60; // fulfilled requests expire in 1 hour
        strSporkPubKey = "046a90132630a8f7c6c65e029d1a721882df13c30c4f6f4a70c9f3123ce6c1afa4aa5ab23fe62cfc551c1155cba2c78d78207bc3ca33c57c7e542d84ddb0852643";

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            (  0, uint256S("0x00000b72cc1c26003ab8060e62a8eb98684c275d1cd989a2c9af3f9676a3f621"))
            (  1, uint256S("0x0000047777a943ad3805816e64a490155857dc2d5d41224b235dbdc9d6d2c5b7"))
            (  5, uint256S("0x00000fc575143cab481d8f8d6373bfecbf2346b7fafefa998e82193ea1513a79"))
            ( 10, uint256S("0x00000f848c751fc4f82ce6a70aa7b284c914394497133960767d3941367dc92e"))
            ( 15, uint256S("0x000009aa4059143f307a2670a8d2093dff1e1d35d64d55a3e817c23efa43b04e")),
            1537629502, // * UNIX timestamp of last checkpoint block
            16,    // * total number of transactions between genesis and last checkpoint
                        //   (the tx=... number in the SetBestChain debug.log lines)
            3000        // * estimated number of transactions per day after checkpoint
        };

        // Founder Address
        strFounderAddress = "NXvE1dQrhP5fDwiLniX1DihEQWMyk9cvfT";
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 64800; // 3 months
        consensus.nMasternodePaymentsStartBlock = 120; // not true, but it's ok as long as it's less then nMasternodePaymentsIncreaseBlock
        consensus.nMasternodePaymentsIncreaseBlock = 99999999; // NOT USED
        consensus.nMasternodePaymentsIncreasePeriod = 99999999; // NOT USED
        consensus.nInstantSendKeepLock = 6;
        consensus.nBudgetPaymentsStartBlock = 1051200;
        consensus.nBudgetPaymentsCycleBlocks = 50;
        consensus.nBudgetPaymentsWindowBlocks = 10;
        consensus.nBudgetProposalEstablishingTime = 60*20;
        consensus.nSuperblockStartBlock = 1072800; // NOTE: Should satisfy nSuperblockStartBlock > nBudgetPeymentsStartBlock
        consensus.nSuperblockCycle = 24; // Superblocks can be issued hourly on testnet
        consensus.nGovernanceMinQuorum = 1;
        consensus.nGovernanceFilterElements = 500;
        consensus.nMasternodeMinimumConfirmations = 1;
        consensus.nMajorityEnforceBlockUpgrade = 51;
        consensus.nMajorityRejectBlockOutdated = 75;
        consensus.nMajorityWindow = 100;
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256S("0x00000b16ae2f29669c91460e5b5f6f2e9d4228afa1169e54f3df2ff48158c578");
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 24 * 60 * 60; // NPSCoin: 1 day
        consensus.nPowTargetSpacing = 2 * 60; // NPSCoin: 2 minutes
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1512; // 75% for testchains
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1537452900; // Sept 20th, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1544857200; // Dec 15th, 2018

        // Deployment of DIP0001
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nStartTime = 1537452900; // Sept 20th, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nTimeout = 1544857200; // Dec 15th, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nWindowSize = 100;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nThreshold = 50; // 50% of 100

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0"); //

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x0"); //

        pchMessageStart[0] = 0xf5;
        pchMessageStart[1] = 0x82;
        pchMessageStart[2] = 0xac;
        pchMessageStart[3] = 0xd2;
        vAlertPubKey = ParseHex("04b85a1b23efb8a18a406590f99febf2d4c78215b4184bc3e0c63f4bcb0970055bf5cc825dde6ac53c785ee2c9f1f2460bb97448be9619f676720492fcb0f47e80");
        nDefaultPort = 19855;
        nMaxTipAge = 0x7fffffff; // allow mining on top of old blocks for testnet
        nDelayGetHeadersTime = 24 * 60 * 60;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1537452900, 4639, 0x1e0ffff0, 1, 16 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000b16ae2f29669c91460e5b5f6f2e9d4228afa1169e54f3df2ff48158c578"));
        assert(genesis.hashMerkleRoot == uint256S("0x2a99a8553e97400c92e45dfd3bff779f83ae2f9cf51c7287d2dbd8fa4a2101ab"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("testnet-seed.npscoin.io", "testnet-seed.npscoin.io" ));

        // Testnet NPSCoin addresses start with 'n'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,112); // c
        // Testnet NPSCoin script addresses start with '5' or '6'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,12); // s
        // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,240);
        // Testnet NPSCoin BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Testnet NPSCoin BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        // Testnet NPSCoin BIP44 coin type is '1' (All coin's testnet default)
        nExtCoinType = 1;

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 3;
        nFulfilledRequestExpireTime = 5*60; // fulfilled requests expire in 5 minutes
        strSporkPubKey = "04f6906a6bae28442d91c92f614364d93c65ac0b01dbd89659128f346fb4dc9ef4054077a404acd1cb8c6be74bb6ecb212c848d9cc08eee16919ce0881e850eeee";

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            (   0, uint256S("0x00000b16ae2f29669c91460e5b5f6f2e9d4228afa1169e54f3df2ff48158c578")),
            1537452900, // * UNIX timestamp of last checkpoint block
            1,       // * total number of transactions between genesis and last checkpoint
                        //   (the tx=... number in the SetBestChain debug.log lines)
            0.01         // * estimated number of transactions per day after checkpoint
        };

        // Founder Address
        strFounderAddress = "n7ja8wiFruqRGbXJqqbUNSHwp884t6RUZk";
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 20;
        consensus.nMasternodePaymentsStartBlock = 60;
        consensus.nMasternodePaymentsIncreaseBlock = 99999999; // NOT USED
        consensus.nMasternodePaymentsIncreasePeriod = 99999999; // NOT USED
        consensus.nInstantSendKeepLock = 6;
        consensus.nBudgetPaymentsStartBlock = 1051200;
        consensus.nBudgetPaymentsCycleBlocks = 50;
        consensus.nBudgetPaymentsWindowBlocks = 10;
        consensus.nBudgetProposalEstablishingTime = 60*20;
        consensus.nSuperblockStartBlock = 1072800;
        consensus.nSuperblockCycle = 10;
        consensus.nGovernanceMinQuorum = 1;
        consensus.nGovernanceFilterElements = 100;
        consensus.nMasternodeMinimumConfirmations = 1;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = -1; // BIP34 has not necessarily activated on regtest
        consensus.BIP34Hash = uint256();
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 24 * 60 * 60; // NPSCoin: 1 day
        consensus.nPowTargetSpacing = 2 * 60; // NPSCoin: 2 minutes
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_DIP0001].nTimeout = 999999999999ULL;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0xc3;
        pchMessageStart[1] = 0x7b;
        pchMessageStart[2] = 0xc9;
        pchMessageStart[3] = 0xea;
        nMaxTipAge = 6 * 60 * 60; // ~144 blocks behind -> 2 x fork detection time, was 24 * 60 * 60 in bitcoin
        nDelayGetHeadersTime = 0; // never delay GETHEADERS in regtests
        nDefaultPort = 29855;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1537428490, 0, 0x207fffff, 1, 16 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x1d1426e15dffce0c064cabb5227013b3a200feb0416114ff5cf8600f0a95ad43"));
        assert(genesis.hashMerkleRoot == uint256S("0x2a99a8553e97400c92e45dfd3bff779f83ae2f9cf51c7287d2dbd8fa4a2101ab"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        nFulfilledRequestExpireTime = 5*60; // fulfilled requests expire in 5 minutes

        checkpointData = (CCheckpointData){
            boost::assign::map_list_of
            ( 0, uint256S("0x00")),
            0,
            0,
            0
        };

        // Regtest NPSCoin addresses start with 'n'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,112);
        // Regtest NPSCoin script addresses start with '5' or '6'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,12);
        // Regtest private keys start with '9' or 'c' (Bitcoin defaults)
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,240);
        // Regtest NPSCoin BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Regtest NPSCoin BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        // Regtest NPSCoin BIP44 coin type is '1' (All coin's testnet default)
        nExtCoinType = 1;

        // Founder Address
        strFounderAddress = "n7ja8wiFruqRGbXJqqbUNSHwp884t6RUZk";
   }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
            return mainParams;
    else if (chain == CBaseChainParams::TESTNET)
            return testNetParams;
    else if (chain == CBaseChainParams::REGTEST)
            return regTestParams;
    else
        throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}
