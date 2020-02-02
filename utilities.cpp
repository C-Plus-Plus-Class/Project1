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
        if(count3 ==0){
            outputStream << it->process_number;
        }else if(count3 ==1){
            outputStream << ","<<it->start_time;
        }else if(count3 ==2){
            outputStream << ","<<it->cpu_time;
        }else{
            outputStream<< std::endl;
        }
        count3++;
    }
    return SUCCESS;
}

void sortData(SORT_ORDER mySortOrder){

}

process_stats getNext(){
    process_stats stats = statsList.at(0);
    statsList.erase(statsList.begin());
    return stats;
}

