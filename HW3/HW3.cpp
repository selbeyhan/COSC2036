#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
using namespace std;

// x: input array
// n: length of array
double *prefixAverage1(double *x, int len)
{
	double *a = new double[len];
	for (int j = 0; j < len; j++)
	{
		double total = 0;
		for (int i = 0; i <= j; i++)
		{
			total += x[i];
		}
		a[j] = total / (j + 1);
	}
	return a;
}

// x: input array
// n: length of array
double *prefixAverage2(double *x, int len)
{
	double *a = new double[len];
	double total = 0;
	for (int j = 0; j < len; j++)
	{
		total += x[j];
		a[j] = total / (j + 1);
	}
	return a;
}

// x: input array
// n: length of array
int example1(int *x, int len)
{
	int total = 0;
	for (int i = 0; i < len; i++)
	{
		total += x[i];
	}
	return total;
}

// x: input array
// n: length of array
int example2(int *x, int len)
{
	int total = 0;
	for (int i = 0; i < len; i += 2)
	{
		total += x[i];
	}
	return total;
}

// x: input array
// n: length of array
int example3(int *x, int len)
{
	int total = 0;
	for (int i = 0; i < len; i++)
	{
		for (int k = 0; k <= i; k++)
		{
			total += x[i];
		}
	}
	return total;
}

// x: input array
// n: length of array
int example4(int *x, int len)
{
	int prefix = 0;
	int total = 0;
	for (int i = 0; i < len; i++)
	{
		prefix += x[i];
		total += prefix;
	}
	return total;
}

// x: input array
// n: length of array
int example5(int *first, int *second, int len)
{
	int count = 0;
	for (int i = 0; i < len; i++)
	{
		int total = 0;
		for (int j = 0; j < len; j++)
		{
			for (int k = 0; k <= j; k++)
			{
				total += first[k];
			}
		}
		if (second[i] == total)
		{
			count++;
		}
	}
	return count;
}

int main(int argc, char **argv)
{
	// depending on argv call one of these functions:
	// p1 for prefixAverage1, p2 for prefixAverage2, e1 for example1
	// e2 for example2, e3 for example3, e4 for example4, e5 for example5
	if (argc != 4)
	{
		cout << "Invalid input, example below\n\t>./HW3 p1 p1.txt 4";
		return -1;
	}

	string algorithm = argv[1];
	string outputFileName = argv[2];
	int upperLimit = strtol(argv[3], nullptr, 0);
	ofstream outFile(outputFileName);
	if (!outFile.is_open())
	{
		cout << "Error Opening the file";
		return -1;
	}

	for (int i = 0; i <= upperLimit; i++)
	{
		int arrSize = pow(10, i);
		int *arr = new int[arrSize]();
		int *arr2 = nullptr;
		if (algorithm == "e5")
		{
			arr2 = new int[arrSize]();
		}

		clock_t startTime = clock();

		if (algorithm == "p1")
		{
			double *dArry = new double[arrSize]();
			double *result = prefixAverage1(dArry, arrSize);
			delete[] dArry;
			delete result;
		}
		else if (algorithm == "p2")
		{
			double *dArry = new double[arrSize]();
			double *result = prefixAverage2(dArry, arrSize);
			delete[] dArry;
			delete result;
		}
		else if (algorithm == "e1")
		{
			example1(arr, arrSize);
		}
		else if (algorithm == "e2")
		{
			example2(arr, arrSize);
		}
		else if (algorithm == "e3")
		{
			example3(arr, arrSize);
		}
		else if (algorithm == "e4")
		{
			example4(arr, arrSize);
		}
		else if (algorithm == "e5")
		{
			example5(arr, arr2, arrSize);
		}
		else
		{
			cout << "Invalid algorithm specified." << endl;
			delete[] arr;
			if (arr2)
			{
				delete[] arr2;
			}
			outFile.close();
			return -1;
		}
		clock_t endTime = clock();
		auto elapsedTime = log10(static_cast<double>(endTime - startTime) * 1000);
		outFile << elapsedTime << endl;
		delete[] arr;
		if (arr2)
		{
			delete[] arr2;
		}
	}

	outFile.close();
	return 0;
}
