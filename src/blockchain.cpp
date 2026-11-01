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
}

void BlockChain::addBlock(vector<Transaction> transactions)
{
    int thisIndex = getLatestIndex()+1;
    Block* lastBlock = getLatestBlock(); 
    string prevHash = lastBlock->getHash();

    Block newBlock(thisIndex,prevHash,transactions);

    newBlock.mineBlock(difficulty);

    blocks.push_back(newBlock);
}

Block* BlockChain::getBlockAtIndex(int index){
    return &blocks[index];
}

bool BlockChain::isChainValid()
{
    int lastIndex = getLatestIndex();
    
    Block* prevBlock=getBlockAtIndex(0);
    for(int i = 1; i<=lastIndex;i++){
        Block* thisBlock=getBlockAtIndex(i);
        if(prevBlock->calcCurrentHash()!=thisBlock->getPreviousHash() || thisBlock->getIndex() != i){
            return false;
        }
        prevBlock=thisBlock;
    }
    return true;
}