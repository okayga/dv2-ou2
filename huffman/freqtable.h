// A frequency table to construct the trie by calculating
// each UTF-8 characters frequency in a text.
struct freqtable {
    int freq;
    char symbol;
}

freqtable *frequencyCount(const char *filename);

void freqtableKill(freqtable *ft)