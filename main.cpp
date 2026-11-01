#include <block.h>
#include <transaction.h>
#include <vector>

using namespace std;

int main(){

    std::vector<Transaction> txList;
    txList.push_back(Transaction("Alice", "Bob", 50.0));

    // 2. Genesis Block setup
    std::string prevHash = "0";
    Block genesisBlock(0, prevHash, txList);
    
    // Mine the genesis block with a difficulty of 3 leading zeros
    genesisBlock.mineBlock(3);

    // 3. Create and mine the next block
    std::string nextPrevHash = genesisBlock.getHash();
    std::vector<Transaction> txList2;
    txList2.push_back(Transaction("Charlie", "Dave", 10.5));
    txList2.push_back(Transaction("niger", "ssss", 103423.5));
    txList2.push_back(Transaction("gay", "Daveewwre", 10122312.3125));

    Block secondBlock(1, nextPrevHash, txList2);
    secondBlock.mineBlock(3);
    
    return 0;
}