//
// Created by 黎进 on 2018/8/10.
//

#ifndef DEMO1_SORTALOGRITHMS_H
#define DEMO1_SORTALOGRITHMS_H

#include <iostream>

using namespace std;

namespace SortAlogrithms {

    // select sort
    template <typename T>
    void selectionSort(T arr[], int n){

        for (int i = 0; i < n; i++) {

            int minIndex = i;
            for (int j = i + 1; j < n; j++) {
                if(arr[j] < arr[minIndex])
                    minIndex = j;
            }

            swap(arr[i], arr[minIndex]);
        }
    }

    // insertion sort
    template <typename T>
    void insertionSort(T arr[], int n){
        for (int i = 1; i < n; i++) {
            for( int j = i ; j > 0 && arr[j] < arr[j-1] ; j -- )
                swap( arr[j] , arr[j-1] );
        }
    }

    // insertion sort plus
    template <typename T>
    void insertionSortPlus(T arr[], int n){
        for (int i = 1; i < n; i++) {
            T tempValue = arr[i];
            int j;
            for (j = i; j > 0 && tempValue < arr[j -1]; j--) {
                arr[j] = arr[j -1];
            }
            arr[j] = tempValue;
        }
    }

    // insertion sort, can sort range from left to right
    template <typename T>
    void insertionSortPlus(T arr[], int leftPos, int rightPos){

        if(leftPos > rightPos)
            return;

        for (int i = leftPos; i < rightPos; ++i) {
            T tempValue = arr[i];
            int j;
            for (j = i; j > leftPos && tempValue < arr[j - 1]; j --) {
                arr[j] = arr[j - 1];
            }
            arr[j] = tempValue;
        }
    }

    // bubble sort
    template <typename T>
    void bubbleSort(T arr[], int n){

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n - (i + 1); j++) {
                if(arr[j] > arr[j + 1])
                    swap(arr[j], arr[j + 1]);
            }
        }
    }


    /*
     * ---------------------------------------------------------------------------------------------------------------
     * merge sort
     * ---------------------------------------------------------------------------------------------------------------
     */

    //
    template <typename T>
    void __mergeArray(T arr[], int leftPos, int middlePos, int rightPos) {
        int n = rightPos - leftPos + 1;
        int * newArray = new T[n];

        int pos1 = leftPos;
        int pos2 = middlePos + 1;
        for (int i = 0; i < n; i++) {

            if(pos1 > middlePos) {
                newArray[i] = arr[pos2];
                pos2 ++;
            }
            else if(pos2 > rightPos) {
                newArray[i] = arr[pos1];
                pos1 ++;
            }
            else if(arr[pos1] < arr[pos2]) {
                newArray[i] = arr[pos1];
                pos1++;
            }
            else {
                newArray[i] = arr[pos2];
                pos2++;
            }
        }

        for (int j = 0; j < n; j ++) {
            arr[leftPos + j] = newArray[j];
        }
    }

    // merge sort private function
    template <typename T>
    void __mergeSort(T arr[], int leftPos, int rigthPos) {

        //if(leftPos >= rigthPos)
        //   return;

        // use insertion sort when number in range less then 15, the "15" is any other number you like
        if(rigthPos - leftPos <= 15){
            insertionSortPlus(arr, leftPos, rigthPos);
            return;
        }

        //warn!!! dangerous of memory overflow
        int middlePos = (rigthPos + leftPos)/2;

        __mergeSort(arr, leftPos, middlePos);
        __mergeSort(arr, middlePos + 1, rigthPos);

        // merge when left part of array has any items bigger then right part of array
        if(arr[middlePos] > arr[middlePos + 1])
            __mergeArray(arr, leftPos, middlePos, rigthPos);
    }

    // merge sort public function
    template <typename T>
    void mergeSort(T arr[], int n){
        __mergeSort(arr, 0, n-1);
    }

    // merge sort from bottom to up
    template <typename T>
    void mergeSortBottomUp(T arr[], int n){

        for (int size = 1; size <= n; size++) {
            for (int index = 0; index < n - size; index += (size * 2)) {

                if (size <= 15) {
                    insertionSortPlus(arr, index, index + size * 2 - 1);
                } else if (arr[index + size - 1] > arr[index + size]) {
                    // merge array between arr[index, index + size -1] and arr[index + size, index + size * 2 -1]
                    __mergeArray(arr, index, index + size - 1, min(index + size * 2 - 1, n - 1));
                }
            }
        }
    }


    /*
     * ---------------------------------------------------------------------------------------------------------------
     * quick sort
     * ---------------------------------------------------------------------------------------------------------------
     */

    //
    template <typename T>
    int __partition(T arr[], int leftPos, int rightPos){

        swap(arr[leftPos], arr[rand()%(rightPos - leftPos + 1) + leftPos]);
        T tempValue = arr[leftPos];

        // arr[leftPos + 1, partition] < tempValue,  arr[partition + 1, index) >= tempValue

        int partition = leftPos;
        for (int index = leftPos + 1; index <= rightPos; index ++) {
            if(arr[index] < tempValue){
                swap(arr[partition + 1], arr[index]);
                partition++;
            }
        }

        swap(arr[leftPos], arr[partition]);
        return partition;
    }

    // sort arr[leftPos, rightPos]
    template <typename T>
    void __quickSort(T arr[], int leftPos, int rightPos){

        if(leftPos >= rightPos)
            return;

        int partitionIndex = __partition(arr, leftPos, rightPos);
        __quickSort(arr, leftPos, partitionIndex -1);
        __quickSort(arr, partitionIndex + 1, rightPos);
    }

    template <typename T>
    void quickSort(T arr[], int n){

        srand(time(NULL));
        __quickSort(arr, 0, n -1);
    }

    template <typename T>
    int __partitionDoubleRoute(T arr[], int leftPos, int rightPos){

        // random switch left item
        swap(arr[leftPos], arr[rand()%(rightPos - leftPos + 1) + leftPos]);

        T tempValue = arr[leftPos];

        // arr[leftPos + 1, flagLeft) <= tempValue, arr(flagRight, rightPos] >= tempValue
        int flagLeft = leftPos + 1, flagRight = rightPos;
        while(true){
            while(flagLeft <= rightPos && arr[flagLeft] >= tempValue) flagLeft ++;
            while(flagRight >= leftPos + 1 && arr[flagRight] <= tempValue) flagRight --;

            if(flagLeft > flagRight) break;

            swap(arr[flagLeft], arr[flagRight]);
            flagLeft ++;
            flagRight --;
        }

        swap(arr[leftPos], arr[flagRight]);

        return flagRight;
    }

    template <typename T>
    void __quickSortDoubleRoute(T arr[], int leftPos, int rightPos){

        if(leftPos >= rightPos)
            return;

        int partition = __partitionDoubleRoute(arr, leftPos, rightPos);
        __quickSortDoubleRoute(arr, leftPos, partition - 1);
        __quickSortDoubleRoute(arr, partition + 1, rightPos);
    }

    template <typename T>
    void quickSortDoubleRoute(T arr[], int n){
        srand(time(NULL));
        __quickSortDoubleRoute(arr, 0, n-1);
    }


    //--------

    template <typename T>
    void __quickSortTribleRoute(T arr[], int leftPos, int rightPos){

        if(leftPos >= rightPos)
            return;

        // partition
        swap(arr[leftPos], arr[rand()%(rightPos - leftPos + 1) + leftPos]);

        T tempValue = arr[leftPos];

        int flagLeft = leftPos; // arr[leftPos + 1, flagLeft] < tempValue
        int flagRight = rightPos; // arr[flagRight, rightPos] > tempValue
        int index = leftPos + 1; // arr[flagLeft + 1, index) == tempValue

        while (index > rightPos){

            if(arr[index] < tempValue){
                swap(arr[index], arr[flagLeft + 1]);
                flagLeft ++;
                index ++;
            }
            else if(arr[index] > tempValue){
                swap(arr[index], arr[flagRight]);
                flagRight --;
            }
            else{
                index ++;
            }
        }

        swap(arr[leftPos], arr[flagLeft]);

        __quickSortTribleRoute(arr, leftPos, flagLeft - 1);
        __quickSortTribleRoute(arr, flagRight, rightPos);

        return;
    }

    template <typename T>
    void quickSortTribleRoute(T arr[], int n){

        srand(time(NULL));
        __quickSortTribleRoute(arr, 0, n-1);
    }
}

#endif //DEMO1_SORTALOGRITHMS_H
