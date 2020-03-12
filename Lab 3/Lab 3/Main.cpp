#include <IOstream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct retStruct{
	int largest;
	int smallest;
	int denominator; // nämnare
	int numerator; // täljare
};

retStruct mergeSort(int* list, int size) {
	int leftIndex = 0, rightIndex = size / 2;
	retStruct ret{ 0,0,0,0 };
	retStruct leftSolution;
	retStruct rightSolution;

	if (size > 3) {
		retStruct leftSolution = mergeSort(list, size / 2); // cuts list into chunks of two // left side of list
		retStruct rightSolution = mergeSort(list + size / 2, size - size / 2); // cuts list into chunks of two // right side of list

		// set correct index for right side since it starts from the middle
		rightSolution.denominator += size / 2;
		rightSolution.numerator += size / 2;
		rightSolution.largest += size / 2;
		rightSolution.smallest += size / 2;

		// calculate where best solution is
		double leftQuota = list[leftSolution.numerator] / (double)list[leftSolution.denominator];
		double rightQuota = list[rightSolution.numerator] / (double)list[rightSolution.denominator];
		double midQuota =  list[rightSolution.largest] / (double)list[leftSolution.smallest];

		// set corret denominators and numerators
		if (leftQuota < rightQuota && rightQuota > midQuota) {
			ret.denominator = rightSolution.denominator;
			ret.numerator = rightSolution.numerator;
		}
		else if (leftQuota < midQuota && midQuota> rightQuota) {
			ret.denominator = leftSolution.smallest;
			ret.numerator = rightSolution.largest;
		}
		else {
			ret.denominator = leftSolution.denominator;
			ret.numerator = leftSolution.numerator;
		}
		ret.largest = (list[leftSolution.largest] < list[rightSolution.largest]) ? rightSolution.largest : leftSolution.largest;
		ret.smallest = (list[leftSolution.smallest] > list[rightSolution.smallest]) ? rightSolution.smallest : leftSolution.smallest;
		return ret;
	}
	else if(size <= 2) { // if list is 2 in size
		ret.largest = (list[1] > list[0]) ? 1 : 0;
		ret.smallest = (list[0] < list[1]) ? 0 : 1;
		ret.denominator = 0;
		ret.numerator = 1;
		return ret;
	}
	else { // if list is 3 in size
		ret.largest = (list[1] > list[0]) ? 1 : 0; // find largest number
		ret.largest = (list[ret.largest] < list[2]) ? 2 : ret.largest;

		ret.smallest = (list[0] < list[1]) ? 0 : 1; // find smallest number
		ret.smallest = (list[ret.smallest] < list[2]) ? ret.smallest : 2;

		if (list[1] > list[2]) { // find denominator and numerator
			ret.denominator = 0;
			ret.numerator = 1;
		}
		else if (list[0] < list[1]) {
			ret.denominator = 0;
			ret.numerator = 2;
		}
		else{
			ret.denominator = 1;
			ret.numerator = 2;
		}
		return ret;
	}
}

void main() {
	srand(time(0));
	int sizeOfList;
	cout << "Enter any positive number: ";
	cin >> sizeOfList;
	cout << endl;


	int* list = new int[sizeOfList]; // fill array with random numbers
	for (int i = 0; i < sizeOfList; i++) {
		list[i] = rand()% sizeOfList+1;
		cout << list[i] << " , ";
	}

	retStruct ret = mergeSort(list, sizeOfList);

	cout << endl << "Numerator index: " << ret.numerator << endl << "Denominator index: " << ret.denominator << endl << "Largest number: " << list[ret.largest] << endl << "Smallest number: " << list[ret.smallest];
}