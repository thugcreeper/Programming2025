#include <iostream>

using namespace std;


const int NUMBER_OF_REFERENCES = 20; // 12
const int FRAMES = 3;

void show(char memory[FRAMES]) {
    for (int i = 0; i < FRAMES; i++) {
        cout << memory[i];
        if (i < (FRAMES-1)) {
            cout << ", ";
        }
    }
    cout << "\n";
}

int getOldestIndex(int time[FRAMES]) {
    int old = NUMBER_OF_REFERENCES + 1;
    int oldIndex = -1;
    for (int i = 0; i < FRAMES; i++) {
        if (time[i] < old) {
            old = time[i];
            oldIndex = i;
        }
    }
    return oldIndex;
}

int findLongestIndex(int reference[NUMBER_OF_REFERENCES], int page, int from) {
    for (int i = from; i < NUMBER_OF_REFERENCES; i++) {
        if (reference[i] == page) {
            return i;
        }
    }
    return NUMBER_OF_REFERENCES;
}

int getLongestIndex(int reference[NUMBER_OF_REFERENCES], char memory[FRAMES], int from) {
    
    for (int i = 0; i < FRAMES; i++) {
        if (memory[i] == ' ') {
            return i;
        }
    }
    int longestFrame = -1;
    int longestIndex = -1;
    for (int i = 0; i < FRAMES; i++) {
        int page = memory[i] - '0';
        int longestRef = findLongestIndex(reference, page, from);
        if (longestRef == NUMBER_OF_REFERENCES) {
            return i;
        } else {
            if (longestRef > longestIndex) {
                longestIndex = longestRef;
                longestFrame = i;
            }
        }
    }
    return longestFrame;
}

int findLRUIndex(int reference[NUMBER_OF_REFERENCES], int page, int from) {
    for (int i = from; i >= 0; i--) {
        if (reference[i] == page) {
            return i;
        }
    }
    return -1;
}


int getLRUIndex(int reference[NUMBER_OF_REFERENCES], char memory[FRAMES], int from) {
    
    for (int i = 0; i < FRAMES; i++) {
        if (memory[i] == ' ') {
            return i;
        }
    }
    int lruFrame = -1;
    int lruIndex = NUMBER_OF_REFERENCES;
    for (int i = 0; i < FRAMES; i++) {
        int page = memory[i] - '0';
        int lruRef = findLRUIndex(reference, page, from);
        if (lruRef < lruIndex) {
            lruIndex = lruRef;
            lruFrame = i;
        }
    }
    return lruFrame;
}

int found(char memory[FRAMES], int page) {
    char target = '0' + page;
    for (int i = 0; i < FRAMES; i++) {
        if (target == memory[i]) {
            return 1;
        }
    }
    return 0;
}

void LRU(int reference[NUMBER_OF_REFERENCES], char memory[FRAMES]) {
    
    int faults = 0;
    
    for (int time = 1; time <= NUMBER_OF_REFERENCES; time++) {
        
        cout << reference[time-1] << ": ";
        if (found(memory, reference[time-1]) == 1) {
            cout << "\n";
        } else {
            int index = getLRUIndex(reference, memory, time-2);
            memory[index] = '0' + reference[time-1];
            show(memory);
            faults++;
        }
    }
    cout << "Number of Page Faults: " << faults << "\n";
}

void Optimal(int reference[NUMBER_OF_REFERENCES], char memory[FRAMES]) {
    
    int faults = 0;
    
    for (int time = 1; time <= NUMBER_OF_REFERENCES; time++) {
        
        cout << reference[time-1] << ": ";
        if (found(memory, reference[time-1]) == 1) {
            cout << "\n";
        } else {
            int index = getLongestIndex(reference, memory, time);
            memory[index] = '0' + reference[time-1];
            show(memory);
            faults++;
        }
    }
    cout << "Number of Page Faults: " << faults << "\n";
}

void FIFO(int reference[NUMBER_OF_REFERENCES], char memory[FRAMES]) {
    
    int addedTime[FRAMES];
    
    for (int i = 0; i < FRAMES; i++) {
        addedTime[i] = 0;
    }
    
    int faults = 0;
    
    for (int time = 1; time <= NUMBER_OF_REFERENCES; time++) {
        
        cout << reference[time-1] << ": ";
        if (found(memory, reference[time-1]) == 1) {
            cout << "\n";
        } else {
            int index = getOldestIndex(addedTime);
            memory[index] = '0' + reference[time-1];
            addedTime[index] = time;
            show(memory);
            faults++;
        }
    }
    cout << "Number of Page Faults: " << faults << "\n";
}

int main(int argc, const char * argv[]) {
    
    int reference[NUMBER_OF_REFERENCES] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    // int reference[NUMBER_OF_REFERENCES] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    
    char memory[FRAMES];
    for (int i = 0; i < FRAMES; i++) {
        memory[i] = ' ';
    }
    
    // FIFO(reference, memory);
    // Optimal(reference, memory);
    LRU(reference, memory);
    
    return 0;
}


