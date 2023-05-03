// Assignment: ASU CSE310 HW#3 Fall 2022
// Name: Race Musgrave
// ASU ID: 1215151093
// ASU Email Address: ramusgra@asu.edu
// Description: this is the header file to assis assignment 3
// it contains methods to create, access and manimulate a maxHeap object
//********************************************************
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//Each Car will have a unique vin
struct Car
{
	string model, make;
	int vin;        //Vehicle Identification Number
	double price;
};

//class MaxHeap represents a max heap that contains Car objects. The underline data structure
//is a one dimensional array of Cars.
class MaxHeap
{
    private:
    struct Car* carArr;	//an array of Cars
    int capacity, size;

	public:
    MaxHeap(int capacity);
    ~MaxHeap();

	Car* getCarArr();
	int getSize();
    void decSize();
	int getCapacity();
	int isFound(int aVin);
	bool heapIncreaseVIN(int index, Car oneCarWithNewVIN);
	bool heapInsert(int vin, string model, string make, double price);
	void heapify(int index);
	Car getHeapMax();
	void extractHeapMax();
	int leftChild(int parentIndex);
	int rightChild(int parentIndex);
	int parent(int childIndex);
	void printHeap();
};

//Constructor to dynamically allocate memory for a heap with the specified capacity
MaxHeap::MaxHeap(int capacity){
 	carArr =  new Car[capacity];
    this->capacity = capacity;
    size = 0;
}

//Destructor
//Before termination, the destructor is called to free the associated memory occupied by the heap.
//and prints the number of nodes deleted by it.
MaxHeap::~MaxHeap(){                //this probably needs work
	delete[] carArr;
    carArr = NULL;
	cout << "\nThe number of deleted cars is: " << size << endl;
}

// simply returns the array of Cars
Car* MaxHeap::getCarArr(){
    return carArr;
}

// returns the size of the maxHeap
int MaxHeap::getSize(){
    return size;
}

// decreases the size of the max heap by 1
void MaxHeap::decSize(){
    if(size > 0){
        size--;
    }
}

// returns the total capacity of the max heap
int MaxHeap::getCapacity(){
    return capacity;
}

//returns the index that a given vin is found, and -1 if not found
int MaxHeap::isFound(int aVin){
    for(int i = 0; i < size; i++){
        if(carArr[i].vin == aVin){
            return i;
        }
    }
    return -1;
}

//****************************************************
//increase the Car's VIN located at the specific index
bool MaxHeap::heapIncreaseVIN(int index, Car oneCarWithNewVIN){
	if (carArr[index].vin > oneCarWithNewVIN.vin){
        cout << "\nIncrease VIN error: index out of range" << endl;
        return false;
    }

    carArr[index].vin = oneCarWithNewVIN.vin ;                                   //make the car at index's vin = to the vin in the new Car
    
    while(index > 0 && carArr[parent(index)].vin < carArr[index].vin){          //this while loop swaps the child node into the parent node
        Car temp = carArr[index];                                               //until the child's vin is smaller than its parent's vin.
        carArr[index] = carArr[parent(index)];
        carArr[parent(index)] = temp;
        index = parent(index);
    }
    return true;
}

//inserts a new Car object into the heap and then moves it into the correct position
bool MaxHeap::heapInsert(int vin, string model, string make, double price){
    //if the size = the capacity, the capacity needs to be doubled
    if(size == capacity){
        cout << "\nReach the capacity limit, double the capacity now.\n";
        capacity = capacity * 2;
        struct Car* temp;
        temp = new Car[capacity];
        for(int i = 0; i < getSize(); i++){
            temp[i] = carArr[i];
        }
        delete[] carArr;
        carArr = temp;
        cout << "\nThe new capacity now is " << getCapacity() << "\n";
    }
    //from here the new object is created and added
    Car newCar;
    Car newVin;
    newVin.vin = vin;
    newCar.vin = -10000;
    newCar.model = model;
    newCar.make = make;
    newCar.price = price;
    size++;
    carArr[size-1] = newCar;
    bool success = heapIncreaseVIN(size-1,newVin);
    if (success == true) return true;
    return false;
}

//takes an index and creates a max heap from that position down the tree
void MaxHeap::heapify(int index){
    int largest;
    int lChild = leftChild(index);
    int rChild = rightChild(index);
    //if left child is greater than parent, we set it to largest
    if(lChild < getSize() && carArr[lChild].vin > carArr[index].vin){
        largest = lChild;
    }
    else largest = index;
    //if right child is greater than largest, we set it to largest
    if(rChild < getSize() && carArr[rChild].vin > carArr[largest].vin){
        largest = rChild;
    }
    //if parent is smaller than either child, call heapify to have it fixed
    if(largest != index){
        Car temp = carArr[index];
        carArr[index] = carArr[largest];
        carArr[largest] = temp;
        heapify(largest);
    }
}

//returns the car array associated with the object
Car MaxHeap::getHeapMax(){
    return carArr[0];
}

//removed the first element in the array by replacing it with the last and then moving it into the correct position
void MaxHeap::extractHeapMax(){
    if(size < 1){
        cout << "Heap underflow\n";
    }
    else{
        carArr[0] = carArr[getSize()-1];
        decSize();
        heapify(0);
    }
}

//returns the left child from a given index
int MaxHeap::leftChild(int PI){
    if(PI == 0){
        return 1;
    }
    return PI * 2 + 1;
}

//returns the right child from a given index
int MaxHeap::rightChild(int PI){
    if(PI == 0){
        return 2;
    }
    return PI * 2 + 2;
}

//returns the parent of a given child index
int MaxHeap::parent(int CI){
    if(CI % 2 == 1){
        CI++;
    }
    return CI / 2 - 1;
}

//prints a standardized out for all elements in the heap
void MaxHeap::printHeap(){
    if (size < 1){
        cout << "\nEmpty heap, no elements\n";
    }
    else{
        cout << "\nHeap capacity = " << capacity << "\n";
        cout << "\nHeap size = " << size << "\n\n";
    }
    for(int i = 0; i < size; i++){
        Car oneCar = carArr[i];
        cout << left;
        cout << setw(8) << oneCar.vin
             << setw(12) << oneCar.model
             << setw(12) << oneCar.make
             << setw(8) << fixed << setprecision(2) << oneCar.price << endl;
    }
}
