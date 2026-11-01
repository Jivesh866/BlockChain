#pragma once
#include "block.h"
#include <vector>
#include "transaction.h"

class BlockChain
{
private:\
    vector<Block> blocks;
    uint32_t difficulty = 3;

public:
    BlockChain();
    void addBlock(vector<Transaction> transactions);
    Block* getLatestBlock() { return &blocks[getLatestIndex()] ; };
    int getLatestIndex() { 
        return blocks.size() - 1; 
    }
    Block* getBlockAtIndex(int index);
    bool isChainValid();
};