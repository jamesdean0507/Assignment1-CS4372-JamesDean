#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cmath>

using namespace std;

const int constCols = 512;

const int constRows = 512;

int varianceThreshold();

void quad(int array[constRows][constCols], int threshold, int numRows, int numCols, int x, int y)
{
    double sumMean = 0, sumVar = 0, variance = 0;
    int area = numRows * numCols;
    int mean = 0;

    //One Pixel
    if (numRows == 1 && numCols == 1)
    {
        return;
    }

    //Calculate Mean
    for(int i = x; i < x + numCols; i++)
    {
        for (int j = y; j < y + numRows; j++)
        {
            sumMean += array[i][j];
        }
    }
    mean = sumMean / area;

    //Calculate Variance
    for(int i = x; i < x + numCols; i++)
    {
        for (int j = y; j < y + numRows; j++)
        {
            sumVar += pow(array[i][j] - mean, 2);
        }
    }
    variance = sumVar / (area - 1);

    if (variance <= threshold)
    {
        //Replace pixels under threshold with the mean
        for(int i = x; i < x + numCols; i++)
        {
            for (int j = y; j < y + numRows; j++)
            {
                array[i][j] = mean;
            }
        }
        return;
    }
    else
    {
        //Recursive call into 4 quads
        quad(array, threshold, numRows/2, numCols/2, x, y);
        quad(array, threshold, numRows/2, numCols/2, x + numCols/2, y);
        quad(array, threshold, numRows/2, numCols/2, x, y + numRows/2);
        quad(array, threshold, numRows/2, numCols/2, x + numCols/2, y + numRows/2);
    }
}

int main()
{
    int numCols = 0, numRows = 0, x = 0, y = 0;
    ifstream infile("baboon.pgma");
    stringstream ss;
    ofstream out;
    out.open("baboonOutput.pgma");
    string inputTxt = "";

    getline(infile, inputTxt);
    out << inputTxt << endl;

    getline(infile,inputTxt);
    out << inputTxt << endl;

    ss << infile.rdbuf();

    ss >> numCols >> numRows;
    out << numCols << "  " << numRows << endl;

    int array[constRows][constCols];

    for (int i = 0; i < numRows; ++i)
    {
        for (int j = 0; j < numCols; ++j)
        {
            ss >> array[i][j];
        }
    }

    int threshold = varianceThreshold();
    quad(array, threshold, numRows, numCols, x, y);

    for (int i = 0; i < numRows; ++i)
    {
        for (int j = 0; j < numCols; ++j)
        {
            out << array[i][j] << " ";
        }
        out << endl;
    }

    infile.close();
    out.close();

    return 0;
}

int varianceThreshold()
{
    int _threshold;
    cout << "Specify Variance Threshold (0-1024): " << endl;
    cin >> _threshold;
    while (_threshold < 0 || _threshold > 1024)
    {
        cout << "Please try again \n"
            << "Variance Threshold must be an integer between 0 and 1024.\n";
        cin >> _threshold;
    }
    return _threshold;
}
