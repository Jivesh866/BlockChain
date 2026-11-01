#include "blockchain.h"
#include "block.h"
#include "transaction.h"

BlockChain::BlockChain(){
    vector<Transaction> txs;
    txs.emplace_back("admin","all",503.23432);
    string genHash="0";
    Block genesis(0,genHash,txs);

    genesis.mineBlock(difficulty);

    blocks.push_back(genesis);
};

void BlockChain::addBlock(vector<Transaction> transactions)
{
    int thisIndex = getLatestIndex()+1;
    Block* lastBlock = getLatestBlock(); 
    string prevHash = lastBlock->getHash();

    Block newBlock(thisIndex,prevHash,transactions);

    newBlock.mineBlock(difficulty);

    blocks.push_back(newBlock);
};


bool BlockChain::isChainValid()
{
    return false;
};