# BlockChain

A simple blockchain implemented in **C++** to explore how blocks, hashing, and chain validation work, with the chain persisted on disk using **LevelDB**.

## Features
- **Blocks and transactions**: each block holds a list of transactions (sender, receiver, amount)
- **SHA-256 hashing** via the header-only [picosha2](https://github.com/okdshin/PicoSHA2) library, with each block linked to the previous block's hash
- **Chain validation**: `isChainValid()` re-checks the links so tampering is detectable
- **Persistence**: blocks are stored in LevelDB and the chain is rebuilt from disk on startup (keyed by block height)

## Project structure
```
BlockChain/
├── include/            # Headers (Block, Transaction, BlockChain)
├── src/                # Implementations
├── tests/              # Tests
├── external/picosha2/  # SHA-256 library
├── main.cpp            # Entry point: loads the chain from LevelDB, prints it, validates it
└── CMakeLists.txt
```

## Getting started

### Prerequisites
- C++ compiler with C++17 support
- CMake 3.10+
- LevelDB (e.g. `sudo apt install libleveldb-dev` on Ubuntu/Debian, `brew install leveldb` on macOS)

### Build and run
```bash
git clone https://github.com/Jivesh866/BlockChain.git
cd BlockChain
mkdir build && cd build
cmake ..
make
./BlockChain        # executable name may differ, check CMakeLists.txt
```

On start, the program opens the `./blockchain` LevelDB directory, loads every stored block, prints the chain, and reports whether it is valid.

## How it works
1. A block is created from a list of transactions plus the previous block's hash.
2. The block's contents are hashed with SHA-256.
3. The block is written to LevelDB under its hash, and a `height_N` key maps each position in the chain to that hash.
4. On startup, blocks are read back by height in order and re-added to the in-memory chain.
5. Validation walks the chain and checks that each block's stored hash and previous-hash link still match.

## Roadmap
- [ ] Proof-of-work mining with adjustable difficulty
- [ ] Transaction signing with public/private keys
- [ ] Simple CLI to add transactions
- [ ] Unit tests for tampering scenarios
- [ ] Peer-to-peer networking

## Author
**Jivesh Bisht**: [GitHub](https://github.com/Jivesh866) · [LinkedIn](https://www.linkedin.com/in/jivesh-bisht-177414423/)
