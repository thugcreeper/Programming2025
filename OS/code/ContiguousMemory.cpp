#include <iostream>

using namespace std;

const int PARTITIONS = 5;
const int PROCESSES = 4;

void showPartitions(int partitions[PARTITIONS]) {
    cout << "(";
    for (int i = 0; i < PARTITIONS; i++) {
        cout << partitions[i];
        if (i < PARTITIONS-1) {
            cout << ", ";
        } else {
            cout << ")\n";
        }
    }
}

void firstFit(int partitions[PARTITIONS], int processes[PROCESSES]) {
    for (int i = 0; i < PROCESSES; i++) {
        int findflag = 0;
        for (int j = 0; j < PARTITIONS; j++) {
            if (processes[i] <= partitions[j]) {
                cout << processes[i] << " is put in " << partitions[j] << " partition ";
                partitions[j] -= processes[i];
                showPartitions(partitions);
                findflag = 1;
                break;
            }
        }
        if (findflag == 0) {
            cout << processes[i] << " must wait\n";
        }
    }
}

void bestFit(int partitions[PARTITIONS], int processes[PROCESSES]) {
    for (int i = 0; i < PROCESSES; i++) {
        int minRemain = 1000;
        int minRemainIndex = -1;
        for (int j = 0; j < PARTITIONS; j++) {
            if (processes[i] <= partitions[j]) {
                int remain = partitions[j] - processes[i];
                if (remain < minRemain) {
                    minRemain = remain;
                    minRemainIndex = j;
                }
            }
        }
        if (minRemainIndex == -1) {
            cout << processes[i] << " must wait\n";
        } else {
            cout << processes[i] << " is put in " << partitions[minRemainIndex] << " partition ";
            partitions[minRemainIndex] -= processes[i];
            showPartitions(partitions);
        }
    }
}

void worstFit(int partitions[PARTITIONS], int processes[PROCESSES]) {
    for (int i = 0; i < PROCESSES; i++) {
        int largestIndex = -1;
        int largest = 0;
        for (int j = 0; j < PARTITIONS; j++) {
            if (partitions[j] > largest) {
                largest = partitions[j];
                if (processes[i] <= partitions[j]) {
                    largestIndex = j;
                }
            }
        }
        if (largestIndex == -1) {
            cout << processes[i] << " must wait\n";
        } else {
            cout << processes[i] << " is put in " << partitions[largestIndex] << " partition ";
            partitions[largestIndex] -= processes[i];
            showPartitions(partitions);
        }
    }
}


int main(int argc, const char * argv[]) {
    
    int partitions[PARTITIONS] = {120, 500, 230, 320, 600};
    int processes[PROCESSES] = {230, 420, 150, 430};
    
    // cout << "First Fit:\n";
    // firstFit(partitions, processes);
    
    // cout << "Best Fit:\n";
    // bestFit(partitions, processes);
    
    cout << "Worst Fit:\n";
    worstFit(partitions, processes);
    
    return 0;
}
