#include <iostream>
#include <string>
using namespace std;


// x: input array
// n: length of array
double* prefixAverage1(double* x, int len){
	double* a = new double[len];
	for(int j = 0; j < len; j++){
		double total = 0;
		for(int i = 0; i <= j; i++){
			total += x[i];
		}
		a[j] = total/(j+1);
	}
	return a;
}


// x: input array
// n: length of array
double* prefixAverage2(double* x, int len){
	double* a = new double[len];
	double total = 0;
	for(int j = 0; j < len; j++){
		total += x[j];
		a[j] = total/(j+1);
	}
	return a;
}


// x: input array
// n: length of array
int example1(int* x, int len){
	int total = 0;
	for(int i = 0; i < len; i++){
		total += x[i];
	}
	return total;
}


// x: input array
// n: length of array
int example2(int* x, int len){
	int total = 0;
	for(int i = 0; i < len; i+=2){
		total += x[i];
	}
	return total;
}


// x: input array
// n: length of array
int example3(int* x, int len){
	int total = 0;
	for(int i = 0; i < len; i++){
		for(int k = 0; k <= i; k++){
			total += x[i];
		}
	}
	return total;
}


// x: input array
// n: length of array
int example4(int* x, int len){
	int prefix = 0;
	int total = 0;
	for(int i = 0; i < len; i++){
		prefix += x[i];
		total += prefix;
	}
	return total;
}


// x: input array
// n: length of array
int example5(int* first, int* second, int len){
	int count = 0;
	for(int i = 0; i < len; i++){
		int total = 0;
		for(int j = 0; j < len; j++){
			for(int k = 0; k <= j; k++){
				total += first[k];
			}
		}
		if(second[i] == total){
			count++;
		}
	}
	return count;
}

double* makeArray(){}

int main(int argc, char** argv){
	// depending on argv call one of these functions:
	// p1 for prefixAverage1, p2 for prefixAverage2, e1 for example1
	// e2 for example2, e3 for example3, e4 for example4, e5 for example5
	// $ ./HW3 p1 p1.txt 6
	if (argc != 4) {
		cout << "\tInvalid Arguments\n\tExample; /HW3 p1 p1.txt 6\n";
        exit(1);

	}
	int maxRun = strtol(argv[3], nullptr, 0);
	double* arr = new double[maxRun];
	
	if (argv[1] == "p1"){
		arr = prefixAverage1(arr, maxRun);
	}
	cout << arr;
	return 0;
}
