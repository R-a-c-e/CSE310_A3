// Assignment: ASU CSE310 HW#3 Fall 2022
// Name: Race Musgrave
// ASU ID: 1215151093
// ASU Email Address: ramusgra@asu.edu
// Description: This program displays a menu of choices to a user
//              and performs the chosen task. It will keep asking a user to
//              enter the next choice until the choice of 'Q' (Quit) is entered.

#include "MaxHeap.h"

using namespace std;

void printMenu();
void heapSort(MaxHeap* oneMaxHeap);

int main()
{
	char input1 = 'Z';
	int vin, newVIN;
	string model, make;
    double price;
	int capacity, index = -1;   //array capacity and index
	bool success = false;

	//declare any other variables in case you need them
	//----

    Car oneCar;
	Car maxCar;
	Car newCar;
	int check;

	// instantiate an empty Heap
	MaxHeap* heap1 = nullptr;
	printMenu();

	do {
		cout << "\nWhat action would you like to perform?" << endl;
		cin.get(input1);
		input1 = toupper(input1);
		cin.ignore(20, '\n');	//flush the buffer

		// matches one of the cases
		switch (input1)
		{
			case 'C':	//create empty Heap with the relevant capacity
				cout << "\nPlease enter the heap capacity: ";
				cin >> capacity;
				cin.ignore(20, '\n');	//flush the buffer

				heap1 = new MaxHeap(capacity);																		//may be incorrect

				break;

			case 'D':	//delete the heap, call the destructor explicitly
				cout << "\nDelete the heap" << endl;
				heap1->~MaxHeap();
				heap1 = new MaxHeap(5);
				break;

			case 'E':	//Extract the maximum node
                if (heap1 == nullptr){
                    cout << "\nEmpty heap, can NOT extract max" << endl;
				}
                else
                {
					cout << "\nBefore extract heap max operation:\n"; 
                    heap1->printHeap();
					heap1->extractHeapMax();
					cout << "\nAfter extract heap max operation:\n";
					heap1->printHeap();
                }
				break;

			case 'F':	//Find a Car
				cout << "\nEnter the car VIN you want to search: ";
				cin >> vin;
				cin.ignore(20, '\n');	//flush the buffer

				if(heap1->isFound(vin) >= 0){
					cout << "\nCar with VIN: " << vin << " is found\n";
				}
				else{
					cout << "\nCar with VIN: " << vin << " is NOT found\n";
				}
				break;

			case 'I':	//Insert a Car
				cout << "\nEnter the car model: ";
				cin >> model;

				cout << "\nEnter the car make: ";
				cin >> make;

				cout << "\nEnter the car VIN: ";
				cin >> vin;
				cout << "\nEnter the car price: ";
				cin >> price;
				cin.ignore(20, '\n');	//flush the buffer
				//if the vin is found, its a duplicate, otherwise we add it to th heap
				if(heap1->isFound(vin) >= 0){
					cout << "\nDuplicated Car. Not added\n";
				}
				else{
					success = heap1->heapInsert(vin,model,make,price);
					if(success == true){
						cout << "\nCar \"" << model << " " << make << "\" is added\n";
					}
					break;
				}
				
				cout << "\nCar \"" << model << " " << make << "\" is NOT added\n";
				
				break;

			case 'K':	//increase the vin
				cout << "\nEnter the old car VIN you want to increase: ";
				cin >> vin;
				cout << "\nEnter the new car VIN: ";
				cin >> newVIN;
				cin.ignore(20, '\n');	//flush the buffer
				index = heap1->isFound(vin);
				check = heap1->isFound(newVIN);
				if(index < 0){
					cout << "\nThe old VIN you try to increase does not exist\n";
					break;
				}
				if(check >= 0){
					cout << "\nThe new VIN you entered already exist, increase VIN operation failed\n";
					break;
				}
				if(newVIN < vin){
					cout << "\nIncrease VIN error: new vin is smaller than current vin\n";
					break;
				}
				newCar.vin = newVIN;
				cout << "\nBefore increase VIN operation:\n";
				heap1->printHeap();
				success = heap1->heapIncreaseVIN(index,newCar);
				//if success is true, the vin was successfully increased
				if(success == true){
					cout << "\nCar with old VIN: " << vin << " is increased to new VIN: " << newVIN << "\n";
					cout << "\nAfter increase VIN operation: \n";
					heap1->printHeap();
				}
				break;

			case 'M':	//get maximum node
				//if the heap is empty display different message and exit
				if (heap1->getSize() <= 0){
                    cout << "Empty heap, can NOT get max node" << endl;
				}
			    else{
				maxCar = heap1->getHeapMax();
				cout << "\nThe maximum heap node is:\n";
				cout << left;
				cout << setw(8) << maxCar.vin
     				 << setw(12) << maxCar.model
     				 << setw(12) << maxCar.make
     				 << setw(8) << fixed << setprecision(2) << maxCar.price << endl;
				}
				break;

			case 'P':	//Print heap contents

			    if (heap1 == nullptr){
                    cout << "\nEmpty heap, can NOT get max node" << endl;
					break;
				}
				heap1->printHeap();
				break;

			case 'S':	//HeapSort
				cout << "\nHeap sort. Cars will be sorted in increasing order of their VINs" << endl;
				heapSort(heap1);
				break;

			case 'Q':	//Quit
				delete heap1;
				break;

			case '?':	//Display Menu
				printMenu();
				break;

			default:
				cout << "Unknown action\n";
				break;
		}
	} while (input1 != 'Q');
	return 0;
}

//*****************************************************
//Given a max heap, we want to sort it in increasing order according to Car VIN, put the
//sorting result inside another array and print it out
void heapSort(MaxHeap* oneMaxHeap){
	int heapSize = oneMaxHeap->getSize();
	for(int i = oneMaxHeap->getSize()-1; i >= 0; i--){
		Car temp = oneMaxHeap->getCarArr()[0];
		oneMaxHeap->getCarArr()[0] = oneMaxHeap->getCarArr()[i];
		oneMaxHeap->getCarArr()[i] = temp;
		oneMaxHeap->decSize();
		oneMaxHeap->heapify(0);
	}
	for(int i = 0; i < heapSize; i++){
        Car oneCar = oneMaxHeap->getCarArr()[i];
        cout << left;
        cout << setw(8) << oneCar.vin
             << setw(12) << oneCar.model
             << setw(12) << oneCar.make
             << setw(8) << fixed << setprecision(2) << oneCar.price << endl;
    }
}

//**The function displays the menu to a user**
void printMenu(){
	cout << "Choice\t\tAction\n";
	cout << "------\t\t------\n";
	cout << "C\t\tCreate a heap\n";
	cout << "D\t\tDelete the heap\n";
	cout << "E\t\tExtract max node\n";
	cout << "F\t\tFind a Car by VIN\n";
	cout << "I\t\tInsert a Car\n";
	cout << "K\t\tIncrease the VIN\n";
	cout << "M\t\tGet the max node\n";
	cout << "P\t\tPrint the heap\n";
	cout << "S\t\tHeap Sort\n";
	cout << "Q\t\tQuit\n";
	cout << "?\t\tDisplay Help\n\n";
}