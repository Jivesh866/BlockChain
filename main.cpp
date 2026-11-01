#include "block.h"
#include "transaction.h"
#include "blockchain.h"
#include <vector>
#include <iostream>
#include <leveldb/db.h>

using namespace std;

int main()
{

    leveldb::DB *db;
    leveldb::Options options;

    options.create_if_missing = true;

    leveldb::Status status = leveldb::DB::Open(options, "./blockchain", &db);

    if (!status.ok())
    {
        std::cerr << "Failed to open LevelDB: " << status.ToString() << std::endl;
        return 1;
    }

    string retrievedValue;
    bool run = true;
    int i = 1;
    BlockChain chain(true);
    while (run)
    {
        string key = "height_" + to_string(i);

        leveldb::Status readStatus = db->Get(leveldb::ReadOptions(), key, &retrievedValue);

        if (readStatus.ok())
        {
            std::cout << "Retrieved value for [" << key << "]: " << retrievedValue << "\n";
            string blockValue;
            leveldb::Status readStatus2 = db->Get(leveldb::ReadOptions(), retrievedValue, &blockValue);
            if (readStatus2.ok())
            {
                Block toAdd(blockValue);
                chain.addBlock(toAdd);
            }
            else if (readStatus.IsNotFound())
            {
                std::cout << "Block not found in database.\n";
                run = false;
            }
            else
            {
                std::cerr << "Error reading data: " << readStatus.ToString() << "\n";
            }
        }
        else if (readStatus.IsNotFound())
        {
            std::cout << "Height not found in database.\n";
            run = false;
        }
        else
        {
            std::cerr << "Error reading data: " << readStatus.ToString() << "\n";
        }
        i++;
    }

    // std::vector<Transaction> txList;
    // txList.push_back(Transaction("Alice", "Bob", 50.0));
    // BlockChain chain;

    // chain.addBlock(txList,db);

    // std::vector<Transaction> txList2;
    // txList2.push_back(Transaction("Charlie", "Dave", 10.5));
    // txList2.push_back(Transaction("niger", "ssss", 103423.5));
    // txList2.push_back(Transaction("gay", "Daveewwre", 10122312.3125));

    // chain.addBlock(txList2,db);

    // cout<<chain.isChainValid();
    delete db;
    chain.printBlockChain();
    cout << "Works? : " << chain.isChainValid() << endl;
    return 0;
}