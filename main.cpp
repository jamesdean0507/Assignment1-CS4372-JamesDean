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
    const int constCols = 512;
    const int constRows = 512;

    int array[constRows][constCols];

    // Following lines : data
    for (row = 0; row < numRows; ++row)
    {
        for (col = 0; col < numCols; ++col)
        {
            ss >> array[row][col];
        }
    }

    int threshold = varianceThreshold();
    QuadTree image(Point(0, 0), Point(numRows, numCols), threshold);
    Node node(Point(numRows, numCols), *array);
    cout << "ERR in next line, image.insert &node" << endl;
    image.insert(&node);
    cout << "after all ";

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
