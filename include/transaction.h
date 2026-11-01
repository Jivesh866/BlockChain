#pragma once
#include <string>
#include <chrono>

class Transaction {
private:
    std::string sender;
    std::string recipient;
    double amount;
    int64_t timestamp;

public:
    Transaction(std::string from, std::string to, double val) {
        sender = from;
        recipient = to;
        amount = val;
        timestamp = std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::system_clock::now().time_since_epoch()
        ).count();
    }

    std::string getSender() const { return sender; }
    std::string getRecipient() const { return recipient; }
    double getAmount() const { return amount; }
    int64_t getTimestamp() const { return timestamp; }

    std::string toString() const {
        return sender + recipient + std::to_string(amount) + std::to_string(timestamp);
    }
};