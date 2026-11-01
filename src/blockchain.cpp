#include "blockchain.h"
#include "block.h"
#include "transaction.h"
#include <leveldb/db.h>
#include <iostream>

BlockChain::BlockChain()
{
    vector<Transaction> txs;
    txs.emplace_back("admin", "all", 503.23432);
    string genHash = "0";
    Block genesis(0, genHash, txs);

    genesis.mineBlock(difficulty);

    blocks.push_back(genesis);
}

BlockChain::BlockChain(bool isEmpty)
{
    if (isEmpty != true)
    {
        vector<Transaction> txs;
        txs.emplace_back("admin", "all", 503.23432);
        string genHash = "0";
        Block genesis(0, genHash, txs);

        genesis.mineBlock(difficulty);

        blocks.push_back(genesis);
    }
}
BlockChain::BlockChain(Block &block)
{
    blocks.push_back(block);
}

void BlockChain::addBlock(Block &block)
{
    blocks.push_back(block);
}

void BlockChain::createBlock(vector<Transaction> transactions, leveldb::DB *db)
{
    int thisIndex = getLatestIndex() + 1;
    Block *lastBlock = getLatestBlock();
    string prevHash = lastBlock->getHash();

    Block newBlock(thisIndex, prevHash, transactions);

    newBlock.mineBlock(difficulty);
    string key = "height_" + to_string(thisIndex);
    string value = "block_" + newBlock.getHash();

    leveldb::Status writeStatus = db->Put(leveldb::WriteOptions(), key, value);
    if (writeStatus.ok())
    {
        cout << "Successfully wrote key: " << key << "\n";
    }
    else
    {
        cerr << "Failed to write data.\n";
    }

    key = "block_" + newBlock.getHash();
    value = newBlock.serialize();

    writeStatus = db->Put(leveldb::WriteOptions(), key, value);
    if (writeStatus.ok())
    {
        cout << "Successfully wrote key: " << key << "\n";
    }
    else
    {
        cerr << "Failed to write data.\n";
    }

    blocks.push_back(newBlock);
}

Block *BlockChain::getBlockAtIndex(int index)
{
    return &blocks[index];
}

void BlockChain::printBlockChain()
{
    cout << "The length of the chain is :" << blocks.size() <<endl;
    if (blocks.size() != 0)
    {
        for (auto block : blocks)
        {
            cout << block.getHash() << endl;
        }
    }
    else
    {
        cout << "Empty BlockChain";
    }
}

bool BlockChain::isChainValid()

{
    if (blocks.size() == 0)
    {
        return false;
    }
    int lastIndex = getLatestIndex();

    Block *prevBlock = getBlockAtIndex(0);
    for (int i = 1; i <= lastIndex; i++)
    {
        Block *thisBlock = getBlockAtIndex(i);
        if (prevBlock->calcCurrentHash() != thisBlock->getPreviousHash() || thisBlock->getIndex() != i)
        {
            return false;
        }
        prevBlock = thisBlock;
    }
    return true;
}