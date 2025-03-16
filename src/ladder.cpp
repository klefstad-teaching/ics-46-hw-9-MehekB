#include "ladder.h"

// Error handling function
void error(string word1, string word2, string msg) {
    cout << "Error: " << msg << endl;
    cout << "Word 1: " << word1 << ", Word 2: " << word2 << endl;
}

// Checks if two strings differ by at most `d` characters
bool edit_distance_within(const string& str1, const string& str2, int d) {
    int len1 = str1.size();
    int len2 = str2.size();
    
    // If the difference in lengths is greater than `d`, they can't be within edit distance `d`
    if (abs(len1 - len2) > d) return false;

    // Count the number of differing characters or differing positions
    int diff_count = 0;
    
    // Case 1: Same length - check for differing characters
    if (len1 == len2) {
        for (int i = 0; i < len1; ++i) {
            if (str1[i] != str2[i]) {
                ++diff_count;
            }
        }
    }
    // Case 2: Length difference of 1 - check for insertions/deletions
    else {
        string longer = len1 > len2 ? str1 : str2;
        string shorter = len1 < len2 ? str1 : str2;
        
        for (int i = 0, j = 0; i < longer.size(); ++i) {
            if (j < shorter.size() && longer[i] == shorter[j]) {
                ++j;
            } else {
                ++diff_count;
            }
            
            // If more than `d` differences are found, return false
            if (diff_count > d) return false;
        }
    }

    return diff_count <= d;
}

// Checks if two words are adjacent (i.e., differ by exactly 1 character or insertion/deletion)
bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

// Generates the word ladder using BFS
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    // Edge case: If the begin word is the same as the end word, return an empty ladder
    if (begin_word == end_word) {
        return {};
    }
    
    // Queue to store ladders (each ladder is a vector of words)
    queue<vector<string>> ladder_queue;
    // Initialize the queue with the begin word
    ladder_queue.push({begin_word});
    
    // Set to track visited words (avoid revisiting)
    set<string> visited;
    visited.insert(begin_word);
    
    // Perform BFS
    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        
        // Get the last word in the current ladder
        string last_word = ladder.back();
        
        // Try all possible words in the word list
        for (const string& word : word_list) {
            // Check if the word is adjacent to the last word and hasn't been visited yet
            if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
                // Create a new ladder by adding the current word
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                
                // If we reached the end word, return the current ladder
                if (word == end_word) {
                    return new_ladder;
                }
                
                // Otherwise, enqueue the new ladder and mark the word as visited
                ladder_queue.push(new_ladder);
                visited.insert(word);
            }
        }
    }
    
    // If no ladder is found, return an empty vector
    return {};
}

// Loads words from a file into the word list
void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
}

// Prints the word ladder
void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
    } else {
        for (const string& word : ladder) {
            cout << word << " ";
        }
        cout << endl;
    }
}

// Verifies the word ladder generation
#define my_assert(e) {cout << #e << ((e) ? " passed" : " failed") << endl;}
void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}