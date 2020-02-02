//
// Created by allan on 2/1/20.
//

#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
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
        process_stats stats;
        std::stringstream ss(line);
        string number;int ct = 0;
        while(std::getline(ss,number,',')){
            if(ct == 0){
                stats.process_number=std::stoi(number);
            }else if(ct == 1){
                stats.start_time=std::stoi(number);
            }else{
                stats.cpu_time=std::stoi(number);
            }
            ct++;
        }
        statsList.push_back(stats);
    }
    inputStream.close();
    return SUCCESS;
}

int saveData(const char* filename){
    ofstream outputStream;
    outputStream.open(filename);
    if(!outputStream.is_open()||outputStream.fail()) {
        outputStream.close();
        outputStream.close();
        return COULD_NOT_OPEN_FILE;
    }
    int count3 = 0;
    for(vector<process_stats>::iterator it = statsList.begin();it!=statsList.end();it++){
        outputStream << it->process_number;
        outputStream << ","<<it->start_time;
        outputStream << ","<<it->cpu_time;
        outputStream << std::endl;
    }
    return SUCCESS;
}

//sort methods
bool sortByProcessNumber(const process_stats &a, const process_stats &b)
{
    return a.process_number<b.process_number;
}
bool sortByStartTime(const process_stats &a, const process_stats &b)
{
    return a.start_time<b.start_time;
}
bool sortByCPUTime(const process_stats &a, const process_stats &b)
{
    return a.cpu_time<b.cpu_time;
}

void sortData(SORT_ORDER mySortOrder){
    if(mySortOrder==PROCESS_NUMBER){
        std::sort(statsList.begin(), statsList.end(), sortByProcessNumber);
    }else if(mySortOrder==START_TIME){
        std::sort(statsList.begin(), statsList.end(), sortByStartTime);
    }else if(mySortOrder==CPU_TIME){
        std::sort(statsList.begin(), statsList.end(), sortByCPUTime);
    }
}

process_stats getNext(){
    process_stats stats = statsList.at(0);
    statsList.erase(statsList.begin());
    return stats;
}

