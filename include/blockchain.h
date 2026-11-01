#pragma once
#include "block.h"
#include <vector>
#include "transaction.h"
#include <leveldb/db.h>

class BlockChain
{
private:
    vector<Block> blocks;
    uint32_t difficulty = 3;

public:
    BlockChain();
    BlockChain(bool isEmpty);
    BlockChain(Block& block);

    void createBlock(vector<Transaction> transactions, leveldb::DB *db);
    void addBlock(Block& block);
    Block *getLatestBlock() { return &blocks[getLatestIndex()]; };
    void printBlockChain();
    int getLatestIndex()
    {
        return blocks.size() - 1;
    }
    Block *getBlockAtIndex(int index);
    bool isChainValid();
};