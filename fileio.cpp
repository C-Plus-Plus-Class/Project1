/*
 * fileio.cpp
 *
 *  Created on: Sep 16, 2017
 *      Author: keith
 */

//============================================================================
// Name        : Proj1_410.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
//============================================================================

#include <iostream>
#include "utilities.h"
//defaults
const char* 		SOURCE_FILE = "TestData.txt";
const char* 		BOGUS_FILE = "BOGUS.txt";
const char*		 	RESULTS_FILE = "results.txt";
using namespace std;

int main() {
    int total_points = 100; //assumme success
    int iRet = FAIL;

    //verify return COULD_NOT_OPEN_FILE
    iRet = loadData(BOGUS_FILE);
    if (iRet != COULD_NOT_OPEN_FILE){
        total_points =total_points-10;
        cout<<"-10 failed to return COULD_NOT_OPEN_FILE on bogus file"<<endl;
    }
    else
        cout<<"Success 1"<<endl;

    //load data
    iRet = loadData(SOURCE_FILE);
    if (iRet != SUCCESS){
        total_points =total_points-10;
        cout<<"-10 failed to return SUCCESS on correct file"<<endl;
    }
    else
        cout<<"Success 2"<<endl;


    //get the next one in line
    process_stats myStats = getNext();
    if (myStats.process_number!=1 || myStats.start_time !=100 ||myStats.cpu_time !=110 ){
        total_points =total_points-20;
        cout<<"-20 failed getnext, expected 1,100,110 got "<<std::to_string(myStats.process_number) <<","<<std::to_string(myStats.start_time)<<","<<std::to_string(myStats.cpu_time)<<endl;
    }
    else
        cout<<"Success 3"<<endl;

    //sort the data
    sortData(START_TIME);

    //get the next one in line
    myStats = getNext();
    if (myStats.process_number!=10 || myStats.start_time !=10 ||myStats.cpu_time !=200 ){
        total_points =total_points-20;
        cout<<"-20 failed getnext after sort, expected 10,10,200 got "<<std::to_string(myStats.process_number) <<","<<std::to_string(myStats.start_time)<<","<<std::to_string(myStats.cpu_time)<<endl;
    }
    else
        cout<<"Success 4"<<endl;

    //save remains
    iRet = saveData(RESULTS_FILE);
    if (iRet != SUCCESS){
        total_points =total_points-10;
        cout<<"-10 failed to return SUCCESS when saving data"<<endl;
    }
    else
        cout<<"Success 1"<<endl;

    cout<<"TOTAL POINTS FOR STUDENT = "<<std::to_string(total_points)<<endl;
    return iRet;
}
