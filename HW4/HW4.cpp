#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Disk
{
    int number;
    char pegPosition = 'A';
};

void hanoi3(int disks, char src, char dest, char temp, int arr[])
{
    if (disks > 0)
    {
        hanoi3(disks - 1, src, temp, dest, arr);
        printf("move disc from %c to %c\n", src, dest);
        hanoi3(disks - 1, temp, dest, src, arr);
    }
}

int main(int argc, char *argv[])
{
    // Number of Pegs, Number of Disks and Output File Name.
    //./HW4 3 4 "3_4.txt"

    if (argc != 4)
    {
        cout << "Not a valid input\n\tExample input: ./HW4 3 4 \"3_4.txt\"";
        return -1;
    }

    // convert inputs into actual types needed
    int numPegs = stoi(argv[1]);
    int numDisks = stoi(argv[2]);
    string output_file_name = argv[3];
    // create a list of disk to track all disk names and locations
    Disk *listOfDisks = new Disk[numDisks];

    for (int i = 0; i < numDisks; i++)
    {
        listOfDisks[i].number = i + 1;
    }
    for (int i = 0; i < numDisks; i++)
    {
        cout << listOfDisks[i].number;
    }

    return 0;
}