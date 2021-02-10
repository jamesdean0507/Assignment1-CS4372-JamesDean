#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cmath>

#include "Point.cpp"
#include "Node.cpp"
#include "QuadTree.cpp"

using namespace std;


int varianceThreshold();


int main()
{
    QuadTree qt;

    int row = 0, col = 0, numCols = 0, numRows = 0;
    ifstream infile("baboon.pgma");
    stringstream ss;
    ofstream out;
    out.open("baboonOutput.pgma");
    ofstream copy;
    copy.open("baboonCopy.pgma");
    string inputTxt = "";

    getline(infile, inputTxt);

    if (inputTxt.compare("P2") != 0)
        cerr << "Version error" << endl;
    out << inputTxt << endl;
    copy << inputTxt << endl;

    getline(infile,inputTxt);
    out << inputTxt << endl;
    copy << inputTxt << endl;

    ss << infile.rdbuf();

    ss >> numCols >> numRows;
    out << numCols << "  " << numRows << endl;
    copy << numCols << "  " << numRows << endl;
    const int constCols = 512;
    const int constRows = 512;

    int array[constRows][constCols];

    // Following lines : data
    for (row = 0; row < numRows; ++row)
    {
        for (col = 0; col < numCols; ++col)
        {
            ss >> array[row][col];
            copy << array[row][col] << "  ";
        }
        copy << endl;
    }

    int threshold = varianceThreshold();
    QuadTree image(Point(0, 0), Point(numRows, numCols), threshold);
    Node node(Point(numRows, numCols), *array);
    // ERROR NEXT LINE
    image.insert(&node);

    for (row = 0; row < numRows; ++row)
    {
        for (col = 0; col < numCols; ++col)
        {
            out << image.find(Point(row, col))->data << "  ";
            cout << image.find(Point(row, col))->data << "  ";
        }
        out << endl;
    }

    infile.close();
    out.close();
    copy.close();

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
