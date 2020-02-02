//
// Created by allan on 2/1/20.
//

#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include "utilities.h"
using namespace std;

vector<process_stats> statsList;
int loadData(const char* filename){
    ifstream inputStream;
    inputStream.open(filename);
    if(!inputStream.is_open()||inputStream.fail()) {
        inputStream.close();
        return COULD_NOT_OPEN_FILE;
    }
    statsList.clear();
    string line;
    while (getline(inputStream, line)) {
        std::stringstream ss(line);
        int processNumber;ss>>processNumber;
        int startTime;ss>>startTime;
        int cpuTime;ss>>cpuTime;
        process_stats stats;
            stats.process_number = processNumber;
            stats.start_time = startTime;
            stats.cpu_time = cpuTime;
        statsList.push_back(stats);
    }
    inputStream.close();
    return SUCCESS;
}

int saveData(const char* filename){
    return FAIL;
}

void sortData(SORT_ORDER mySortOrder){

}

process_stats getNext(){
    process_stats pStats;
        pStats.process_number=0;
        pStats.start_time=0;
        pStats.cpu_time=0;
    return pStats;
}

