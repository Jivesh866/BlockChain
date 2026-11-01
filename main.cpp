#include "block.h"
#include "transaction.h"
#include "blockchain.h"
#include <vector>
#include <iostream>

using namespace std;

int main(){

    std::vector<Transaction> txList;
    txList.push_back(Transaction("Alice", "Bob", 50.0));
    BlockChain chain;
    cout << chain.getLatestIndex() <<endl;
    cout << chain.getLatestBlock();

    chain.addBlock(txList);

    cout << chain.getLatestIndex() <<endl;
    cout << chain.getLatestBlock();

    std::vector<Transaction> txList2;
    txList2.push_back(Transaction("Charlie", "Dave", 10.5));
    txList2.push_back(Transaction("niger", "ssss", 103423.5));
    txList2.push_back(Transaction("gay", "Daveewwre", 10122312.3125));

    chain.addBlock(txList2);

    cout << chain.getLatestIndex() <<endl;
    cout << chain.getLatestBlock();
    
    return 0;
}