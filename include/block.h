#pragma once
#include <transaction.h>
#include <vector>
#include <picosha2/picosha2.h>

using namespace std;

class Block{
    private:
        int index;
        int64_t timestamp;
        vector<Transaction> transactions;
        string previousHash;
        string Hash;
        int nonce;

    string calcCurrentHash();
    public:
    Block(int newIndex, string& prevHash, vector<Transaction>& transactions);

    std::string getHash() const { return Hash; }
    std::string getPreviousHash() const { return previousHash; }
    int getIndex() const { return index; }

    void mineBlock(uint32_t difficulty);
};