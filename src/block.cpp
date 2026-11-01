#include "picosha2/picosha2.h"
#include "block.h"
#include <iostream>
#include <sstream>
#include <chrono>

using namespace std;
// Private Implementations

string Block::calcCurrentHash()
{
    std::stringstream ss;
    string data = "";
    for (auto transaction : this->transactions)
    {
        data += transaction.toString();
    }
    ss << index << previousHash << timestamp << data << nonce;
    std::string record = ss.str();

    vector<unsigned char> hash(picosha2::k_digest_size);

    picosha2::hash256(record.begin(), record.end(), hash.begin(), hash.end());

    std::string hex_str = picosha2::bytes_to_hex_string(hash.begin(), hash.end());

    return hex_str;
}

// Public Implementations

Block::Block(int newIndex, string &prevHash, vector<Transaction> &transactions)
{
    this->index = newIndex;
    this->previousHash = prevHash;
    this->timestamp = std::chrono::duration_cast<std::chrono::seconds>(
                          std::chrono::system_clock::now().time_since_epoch())
                          .count();

    this->nonce=0;
    
};

void Block::mineBlock(uint32_t difficulty) {
        std::string target(difficulty, '0');

        cout << "Mining block " << index << "...\n";

        do {
            nonce++;
            Hash = calcCurrentHash();
        } while (Hash.substr(0, difficulty) != target);

        std::cout << "Block Mined Successfully! Nonce: " << nonce << "\n";
        std::cout << "Hash: " << Hash << "\n\n";
    }

