#include "picosha2/picosha2.h"
#include "block.h"
#include <iostream>
#include <sstream>
#include <chrono>

using namespace std;
// Private Implementations

// Public Implementations

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

Block::Block(int newIndex, string &prevHash, vector<Transaction> &transactions)
{
    this->index = newIndex;
    this->previousHash = prevHash;
    this->timestamp = std::chrono::duration_cast<std::chrono::seconds>(
                          std::chrono::system_clock::now().time_since_epoch())
                          .count();

    this->nonce = 0;
};

void Block::mineBlock(uint32_t difficulty)
{
    std::string target(difficulty, '0');

    cout << "Mining block " << index << "...\n";

    do
    {
        nonce++;
        Hash = calcCurrentHash();
    } while (Hash.substr(0, difficulty) != target);

    std::cout << "Block Mined Successfully! Nonce: " << nonce << "\n";
    std::cout << "Hash: " << Hash << "\n\n";
}

std::string Block::serialize() const
{
    std::stringstream ss;

    ss << index << "|"
       << timestamp << "|"
       << previousHash << "|"
       << Hash << "|"
       << nonce << "|";

    ss << transactions.size() << "|";

    for (const auto &tx : transactions)
    {
        ss << tx.getSender() << "|"
           << tx.getRecipient() << "|"
           << tx.getAmount() << "|"
           << tx.getTimestamp() << "|";
    }

    return ss.str();
}


Block::Block(const std::string& serializedData) {
    std::stringstream ss(serializedData);
    std::string segment;

    std::getline(ss, segment, '|');
    index = std::stoi(segment);

    std::getline(ss, segment, '|');
    timestamp = std::stoll(segment);

    std::getline(ss, previousHash, '|');
    std::getline(ss, Hash, '|');

    std::getline(ss, segment, '|');
    nonce = std::stoi(segment);
    std::getline(ss, segment, '|');
    size_t txCount = std::stoul(segment);

    transactions.clear();

    for (size_t i = 0; i < txCount; ++i) {
        std::string sender, recipient;
        double amount;
        int64_t txTimestamp;

        std::getline(ss, sender, '|');
        std::getline(ss, recipient, '|');

        std::getline(ss, segment, '|');
        amount = std::stod(segment);

        std::getline(ss, segment, '|');
        txTimestamp = std::stoll(segment);
        Transaction tx(sender, recipient, amount);
        transactions.push_back(tx);
    }
}