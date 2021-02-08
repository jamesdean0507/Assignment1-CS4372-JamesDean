#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cmath>

using namespace std;

int varianceThreshold();

int arithmeticMean(int[], int, int);

int arithmeticVariance(int[], int, int, int);

int main()
{
    int threshold = varianceThreshold();

    int row = 0, col = 0, numRows = 0, numCols = 0;
    ifstream infile("baboon.pgma");
    stringstream ss;
    ofstream out;
    out.open("baboonOutput.pgma");
    string inputTxt = "";

    // First line : version
    getline(infile, inputTxt);

    if (inputTxt.compare("P2") != 0)
        cerr << "Version error" << endl;
    else
        cout << "Version : " << inputTxt << endl;
        out << inputTxt << endl;

    // Second line : comment
    getline(infile,inputTxt);
    cout << "Comment : " << inputTxt << endl;
    out << inputTxt << endl;

    // Continue with a stringstream
    ss << infile.rdbuf();

    // Third line : size
    ss >> numCols >> numRows;
    cout << numCols << " columns and " << numRows << " rows" << endl;
    out << numCols << "  " << numRows << endl;

    int array[numRows][numCols];

    // Following lines : data
    for(row = 0; row < numRows; ++row)
    {
        for (col = 0; col < numCols; ++col)
        {
            ss >> array[row][col];
            out << array[row][col] << "  ";
        }
        out << endl;
    }

    infile.close();


    out.close();

    return 0;
}

int varianceThreshold()
{
    int threshold;
    cout << "Specify Variance Threshold (0-1024): " << endl;
    cin >> threshold;
    while (threshold < 0 || threshold > 1024)
    {
        cout << "Please try again \n"
            << "Variance Threshold must be an integer between 0 and 1024.\n";
        cin >> threshold;
    }
    return threshold;
}

int arithmeticMean(int arr[][], int rowSize, int colSize)
{
    int sum = 0;
    for (int i = 1; i <= rowSize; i++)
    {
        for(int n = 1; n <= colSize; n++)
        {
            sum = sum + arr[i][n];
        }
    }
    return (sum / (rowSize * colSize));
}

int arithmeticVariance(int arr[][], int rowSize, int colSize, int varianceThreshold)
{
    int sum, base;
    int arrSize = rowSize * colSize;
    for (int i = 1; i <= rowSize; i++)
    {
        for (int n = 1; n <= colSize; n++)
        {
            base = arr[i][n] - varianceThreshold;
            sum = sum + pow(base, 2);
        }
    }
    return (sum / (arrSize - 1));
}
