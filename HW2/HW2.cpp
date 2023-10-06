#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

class Node {
public:
    double value;
    int row, col;
    Node* right;
    Node* below;

    Node(double val, int r, int c) : value(val), row(r), col(c), right(nullptr), below(nullptr) {}
};

class MatrixLinkedList {
private:
    Node* root;

public:
    MatrixLinkedList() : root(nullptr) {}

    bool isListEmpty() {
        return root == nullptr;
    }

    Node* getRoot() {
        return root;
    }
MatrixLinkedList getSubMatrix(int rowExclude, int colExclude, int size) {
        MatrixLinkedList subMat;
        for (int i = 1; i <= size; ++i) {
            if (i == rowExclude) continue;
            for (int j = 1; j <= size; ++j) {
                if (j == colExclude) continue;
                double value = getElement(i, j); 
                subMat.addNode(value, i - (i > rowExclude), j - (j > colExclude));
            }
        }
        return subMat;
    }
    void addNode(double value, int row, int col) {
        Node* newNode = new Node(value, row, col);
        if (isListEmpty()) {
            root = newNode;
            return;
        }

        Node* rowPtr = root;
        Node* prevRow = nullptr;
        while (rowPtr && rowPtr->row < row) {
            prevRow = rowPtr;
            rowPtr = rowPtr->below;
        }

        Node* colPtr = rowPtr;
        Node* prevCol = nullptr;
        while (colPtr && colPtr->col < col) {
            prevCol = colPtr;
            colPtr = colPtr->right;
        }

        if (colPtr && colPtr->col == col) {
            newNode->right = colPtr->right;
            colPtr->right = newNode;
        } else {
            if (prevCol) {
                prevCol->right = newNode;
                newNode->right = colPtr;
            } else {
                newNode->right = rowPtr;
                if (prevRow) {
                    prevRow->below = newNode;
                } else {
                    root = newNode;
                }
            }
        }

        if (rowPtr && rowPtr != newNode) {
            newNode->below = rowPtr;
        }
    }

    void outputToFile(std::ofstream& outFile) {
        Node* rowPtr = root;
        while (rowPtr) {
            Node* colPtr = rowPtr;
            while (colPtr) {
                outFile << std::fixed << std::setprecision(1) << colPtr->value << " ";
                colPtr = colPtr->right;
            }
            outFile << std::endl;
            rowPtr = rowPtr->below;
        }
    }

    void sumMatrices(MatrixLinkedList& mat1, MatrixLinkedList& mat2, std::ofstream& outFile) {
        Node* row1 = mat1.getRoot();
        Node* row2 = mat2.getRoot();
        while (row1 && row2) {
            Node* col1 = row1;
            Node* col2 = row2;
            while (col1 && col2) {
                double sum = col1->value + col2->value;
                outFile << std::fixed << std::setprecision(1) << sum << " ";
                col1 = col1->right;
                col2 = col2->right;
            }
            outFile << std::endl;
            row1 = row1->below;
            row2 = row2->below;
        }
    }

    void differenceMatrices(MatrixLinkedList& mat1, MatrixLinkedList& mat2, std::ofstream& outFile) {
        Node* row1 = mat1.getRoot();
        Node* row2 = mat2.getRoot();
        while (row1 && row2) {
            Node* col1 = row1;
            Node* col2 = row2;
            while (col1 && col2) {
                double diff = col1->value - col2->value;
                outFile << std::fixed << std::setprecision(1) << diff << " ";
                col1 = col1->right;
                col2 = col2->right;
            }
            outFile << std::endl;
            row1 = row1->below;
            row2 = row2->below;
        }
    }
double getElement(int row, int col) {
    Node* rowPtr = root;
    while (rowPtr) {
        if (rowPtr->row == row) {
            Node* colPtr = rowPtr;
            while (colPtr) {
                if (colPtr->col == col) {
                    return colPtr->value;
                }
                colPtr = colPtr->right;
            }
        }
        rowPtr = rowPtr->below;
    }
    return 0.0; // or throw an exception
}




    void multiplyMatrices(MatrixLinkedList& mat1, MatrixLinkedList& mat2, std::ofstream& outFile) {
        Node* row1 = mat1.getRoot();
        Node* row2 = mat2.getRoot();

        // Assuming the matrices are square and the dimensions match for now
        while (row1 && row2) {
            Node* row2Start = row2;
            Node* col1 = row1;

            while (col1) {
                double sum = 0.0;
                Node* col2 = row2Start;
                while (col2) {
                    sum += col1->value * col2->value;
                    col1 = col1->right;
                    col2 = col2->below;
                }
                outFile << std::fixed << std::setprecision(1) << sum << " ";
                col1 = row1;
                row2Start = row2Start->right;
            }
            outFile << std::endl;
            row1 = row1->below;
            row2 = row2->below;
        }
    }

    void transposeMatrix(MatrixLinkedList& mat, std::ofstream& outFile) {
        Node* row = mat.getRoot();
        while (row) {
            Node* colStart = row;
            while (colStart) {
                Node* col = colStart;
                outFile << std::fixed << std::setprecision(1) << col->value << " ";
                while (col && col->right) {
                    col = col->right;
                    outFile << std::fixed << std::setprecision(1) << col->value << " ";
                }
                outFile << std::endl;
                colStart = colStart->below;
            }
            row = row->below;
        }
    }

double determinant(int size) {
        if (size == 1) {
            return root->value;
        }
        if (size == 2) {
            Node* row = root;
            double a = row->value;
            double b = row->right->value;
            row = row->below;
            double c = row->value;
            double d = row->right->value;
            return (a * d) - (b * c);
        }

        double det = 0;
        int sign = 1;
        for (int j = 1; j <= size; ++j) {
            double value = getElement(1, j);
            MatrixLinkedList subMat = getSubMatrix(1, j, size);
            det += sign * value * subMat.determinant(size - 1);
            sign *= -1;
        }
        return det;
    }
	MatrixLinkedList getSubMatrix(MatrixLinkedList& mat, int rowExclude, int colExclude, int size) {
	    MatrixLinkedList subMat;
	    for (int i = 1; i <= size; ++i) {
		if (i == rowExclude) continue;
		for (int j = 1; j <= size; ++j) {
		    if (j == colExclude) continue;
		    double value = mat.getElement(i, j); 
		    subMat.addNode(value, i - (i > rowExclude), j - (j > colExclude));
		}
	    }
	    return subMat;
}
};




int main(int argc, char* argv[]) {
    int rowNum = 0, colNum = 0;
    std::string cmd = argc >= 2 ? argv[1] : "";
    std::string inputFile1 = argc >= 3 ? argv[2] : "";
    std::string inputFile2 = argc >= 4 ? argv[3] : "";
    std::string outputFile = argc >= 5 ? argv[4] : "";

    MatrixLinkedList mat1;
    std::ifstream inFile1(inputFile1);
    if (inFile1.is_open()) {
        std::string line;
        int tempRowNum = 0, tempColNum = 0;
        while (std::getline(inFile1, line)) {
            tempRowNum++;
            tempColNum = 0;
            std::istringstream iss(line);
            double num;
            while (iss >> num) {
                tempColNum++;
                mat1.addNode(num, tempRowNum, tempColNum);
            }
            // Store the column count of the first row
            if(tempRowNum == 1) {
                colNum = tempColNum;
            }
            // Check if all rows have the same column count
            if(tempColNum != colNum) {
                std::cerr << "Matrix is not well-formed. Rows have different numbers of columns.";
                return 1;
            }
        }
        rowNum = tempRowNum;  // Set the row count once reading is complete
        inFile1.close();
    }

    MatrixLinkedList mat2;
    if (!inputFile2.empty()) {
        std::ifstream inFile2(inputFile2);
        if (inFile2.is_open()) {
            std::string line;
            int rowNum = 0, colNum;
            while (std::getline(inFile2, line)) {
                rowNum++;
                colNum = 0;
                std::istringstream iss(line);
                double num;
                while (iss >> num) {
                    colNum++;
                    mat2.addNode(num, rowNum, colNum);
                }
            }
            inFile2.close();
        }
    }



    std::ofstream outFile(outputFile);
    if (cmd == "add") {
        MatrixLinkedList result;
        result.sumMatrices(mat1, mat2, outFile);
    } else if (cmd == "sub") {
        MatrixLinkedList result;
        result.differenceMatrices(mat1, mat2, outFile);
    } else if (cmd == "mul") {
        MatrixLinkedList result;
        result.multiplyMatrices(mat1, mat2, outFile);
    } else if (cmd == "transpose") {
        MatrixLinkedList result;
        result.transposeMatrix(mat1, outFile);
    } else if (cmd == "det") {
        if (rowNum != colNum) {
            outFile << "The matrix must be square to compute the determinant." << std::endl;
        } else {
            double det = mat1.determinant(rowNum); // call determinant
            outFile << "Determinant: " << det << std::endl;
        }
    }
    outFile.close();
    return 0;
}

