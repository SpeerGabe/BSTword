# BST Word Frequency Tool
 
A binary search tree implementation in C++ that maps words to their occurrence counts. Supports insertion, deletion, search, in-order traversal, file I/O, and `operator[]` for map-style access.
 
Built as part of CSCI 325 (Data Structures) at UT Martin and extended with real corpus analysis.
 
---
 
## Features
 
- **Full BST operations** — insert, search, delete (with inorder-successor replacement for two-child nodes), min, max
- **Word frequency counting** — reads any `.txt` file, strips punctuation, lowercases, and tallies every word
- **File I/O** — load a corpus, save sorted results
- **`operator[]` overloads** — both const (read) and non-const (read/write with auto-insert)
- **Const-correct** — read-only methods are marked `const` throughout
---
 
## Build
 
```bash
make
```
 
Requires g++ with C++17. To clean up object files and the binary:
 
```bash
make clean
```
 
---
 
## Usage
 
```bash
./driver
```
 
An interactive menu lets you:
 
| Option | Action |
|--------|--------|
| 1 | Manually set a word and count |
| 2 | Look up a word's count |
| 3 | Print all entries in alphabetical order |
| 4 | Save results to a file |
| 5 | Find the alphabetically first word |
| 6 | Find the alphabetically last word |
| 7 | Remove a word |
| 8 | Read and count all words from a `.txt` file |
 
**Example — counting words in a file:**
 
```
Choice: 8
Enter filename to read (.txt extension optional): sherlock
Done. Use option 3 to print or 4 to save results.
 
Choice: 2
Enter word: holmes
"holmes" appears 445 time(s).
```
 
---
 
## Sample Output — The Adventures of Sherlock Holmes
 
Run against the full text of *The Adventures of Sherlock Holmes* (107,533 words, Project Gutenberg). Top 20 most frequent **non-stop words**:
 
| Rank | Word | Count |
|------|------|-------|
| 1 | holmes | 445 |
| 2 | should | 212 |
| 3 | time | 149 |
| 4 | door | 139 |
| 5 | room | 133 |
| 6 | here | 128 |
| 7 | face | 128 |
| 8 | might | 126 |
| 9 | just | 125 |
| 10 | matter | 123 |
| 11 | way | 115 |
| 12 | heard | 113 |
| 13 | yes | 112 |
| 14 | hand | 112 |
| 15 | house | 110 |
 
Results saved in alphabetical order via in-order BST traversal — no sorting step needed.
 
---
 
## Implementation Notes
 
**Deletion** uses the standard inorder-successor strategy: when removing a node with two children, it is replaced by the smallest value in its right subtree, then that successor is deleted recursively.
 
**`operator[]` (non-const)** inserts a node with count 0 if the key is not present, then returns a reference to its data — matching the behavior of `std::map`. The earlier version of this code had a bug where a manually-allocated node was created alongside the insert call, causing a memory leak and a dangling reference. That is fixed here.
 
**Punctuation handling** strips all punctuation except apostrophes so contractions like *don't* and *it's* are preserved as single tokens.
 
**Error handling** — `readFromFile` returns a boolean so the driver can distinguish a failed open from a successful read. Passing a nonexistent file prints an error and returns to the menu rather than silently reporting success.
 
---
 
## Files
 
```
.
├── BST.h / BST.cpp      — BST class
├── Node.h / Node.cpp    — Node class
├── driver.cpp           — Interactive CLI
├── Makefile
├── sherlock.txt         — Sample corpus (Project Gutenberg)
└── poem.txt             — Smaller sample corpus
```
