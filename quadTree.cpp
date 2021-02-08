#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cmath>

using namespace std;

int** inputToArray();

int varianceThreshold();

int arithmeticMean(int[], int);

int arithmeticVariance(int[], int, int);

int main()
{
    int threshold = varianceThreshold();
    int arr[][] = inputToArray();

    cout << arr[0][0] << "[0][0]\n";
    cout << arr[0][1] << "[0][1]\n";
    cout << arr[1][1] << "[1][1]\n";

    ofstream out;
    out.open("baboonOutput.pgma");
    out.close();

    return 0;
}

int** inputToArray()
{
    int row = 0, col = 0, numrows = 0, numcols = 0;
    ifstream infile("baboon.pgma");
    stringstream ss;
    string inputTxt = "";

    // First line : version
    getline(infile, inputTxt);

    if (inputTxt.compare("P2") != 0)
        cerr << "Version error" << endl;
    else
        cout << "Version : " << inputTxt << endl;

    // Second line : comment
    getline(infile,inputTxt);
    cout << "Comment : " << inputTxt << endl;

    // Continue with a stringstream
    ss << infile.rdbuf();

    // Third line : size
    ss >> numcols >> numrows;
    cout << numcols << " columns and " << numrows << " rows" << endl;

    int array[numrows][numcols];

    // Following lines : data
    for(row = 0; row < numrows; ++row)
    {
        for (col = 0; col < numcols; ++col)
        {
            ss >> array[row][col];
        }
    }

    infile.close();
    return array;
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

int arithmeticMean(int arr[], int arrSize)
{
    int sum = 0;
    for (int i = 1; i <= arrSize; i++)
    {
        sum = sum + arr[i];
    }
    return (sum / arrSize);
}

int arithmeticVariance(int arr[], int arrSize, int varianceThreshold)
{
    int sum, base;
    for (int i = 1; i <= arrSize; i++)
    {
        base = arr[i] - varianceThreshold;
        sum = sum + pow(base, 2);
    }
    return (sum / (arrSize - 1));
}
