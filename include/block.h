#pragma once
#include <transaction.h>
#include <vector>
#include "picosha2/picosha2.h"

using namespace std;

class Block{
    private:
    int index;
    int64_t timestamp;
    vector<Transaction> transactions;
    string previousHash;
    string Hash;
    int nonce;

    public:
    Block(int newIndex, string& prevHash, vector<Transaction>& transactions);
    explicit Block(const std::string& serializedData);

    std::string getHash() const { return Hash; }
    std::string getPreviousHash() const { return previousHash; }
    int getIndex() const { return index; }

    string calcCurrentHash();
    std::string serialize() const;
    void mineBlock(uint32_t difficulty);
};