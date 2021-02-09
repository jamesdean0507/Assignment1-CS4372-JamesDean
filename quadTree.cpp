#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cmath>

using namespace std;

int THRESHOLD;

int varianceThreshold();

struct Point
{
    int x;
    int y;
    Point(int _x, int _y)
    {
        x = _x;
        y = _y;
    }
    Point()
    {
        x = 0;
        y = 0;
    }
};

struct Node
{
    Point position;
    int data;
    Node(Point _position, int _data)
    {
        position = _position;
        data = _data;
    }
    Node()
    {
        data = 0;
    }
};

class quadTree
{
    Point topLeft;
    Point bottomRight;
    Node *node;

    quadTree *topLeftQuad;
    quadTree *topRightQuad;
    quadTree *bottomLeftQuad;
    quadTree *bottomRightQuad;

public:
    quadTree()
    {
        topLeft = Point(0, 0);
        bottomRight = Point(0, 0);
        node = NULL;
        topLeftQuad = NULL;
        topRightQuad = NULL;
        bottomLeftQuad = NULL;
        bottomRightQuad = NULL;
    }
    quadTree(Point _topLeft, Point _bottomRight)
    {
        node = NULL;
        topLeftQuad = NULL;
        topRightQuad = NULL;
        bottomLeftQuad = NULL;
        bottomRightQuad = NULL;
        topLeft = _topLeft;
        bottomRight = _bottomRight;
    }
    void insert(Node*);
    Node* find(Point);
    bool inContainer(Point);
    int arithmeticMean();
    int arithmeticVariance();
};

void quadTree::insert(Node *_node)
{
    if (_node == NULL)
    {
        return;
    }

    if (!inContainer(_node->position))
    {
        return;
    }

    if (abs(topLeft.x - bottomRight.x) <= 1 && abs(topLeft.y - bottomRight.y) <= 1)
    {
        if (node == NULL)
        {
            node = _node;
        }
        return;
    }

    if((topLeft.x + bottomRight.x) / 2 >= _node->position.x)
    {
        //TopLeftQuad
        if ((topLeft.y + bottomRight.y) / 2 >= _node->position.y)
        {
            if (topLeftQuad == NULL)
            {
                topLeftQuad = new quadTree(Point(topLeft.x, topLeft.y), Point((topLeft.x + bottomRight.x) / 2, (topLeft.y + bottomRight.y) / 2));
            }
            topLeftQuad->insert(_node);

            if (arithmeticVariance() <= THRESHOLD)
            {
                topLeftQuad->node->data = arithmeticMean();
                return;
            }
        }
        //BottomLeftQuad
        else
        {
            if (bottomLeftQuad == NULL)
            {
                bottomLeftQuad = new quadTree(Point(topLeft.x, (topLeft.y + bottomRight.y) / 2), Point((topLeft.x + bottomRight.x) / 2, bottomRight.y));
            }
            bottomLeftQuad->insert(_node);

            if (arithmeticVariance() <= THRESHOLD)
            {
                bottomLeftQuad->node->data = arithmeticMean();
                return;
            }
        }
    }
    else
    {
        //TopRightQuad
        if ((topLeft.y + bottomRight.y) / 2 >= _node->position.y)
        {
            if (topRightQuad == NULL)
            {
                topRightQuad = new quadTree(Point((topLeft.x + bottomRight.x) / 2, topLeft.y), Point(bottomRight.x, (topLeft.y + bottomRight.y) / 2));
            }
            topRightQuad->insert(_node);

            if (arithmeticVariance() <= THRESHOLD)
            {
                topRightQuad->node->data = arithmeticMean();
                return;
            }
        }
        //BottomRightQuad
        else
        {
            if (bottomRightQuad == NULL)
            {
                bottomRightQuad = new quadTree(Point((topLeft.x + bottomRight.x) / 2, (topLeft.y + bottomRight.y) / 2), Point(bottomRight.x, bottomRight.y));
            }
            bottomRightQuad->insert(_node);

            if (arithmeticVariance() <= THRESHOLD)
            {
                bottomRightQuad->node->data = arithmeticMean();
                return;
            }
        }
    }
}

Node* quadTree::find(Point point)
{
    if (!inContainer(point))
    {
        return NULL;
    }

    if (node != NULL)
    {
        return node;
    }

    if ((topLeft.x + bottomRight.x) / 2 >= point.x)
    {
        //TopLeftQuad
        if ((topLeft.y + bottomRight.y) / 2 >= point.y)
        {
            if (topLeftQuad == NULL)
            {
                return NULL;
            }
            return topLeftQuad->find(point);
        }
        //BottomLeftQuad
        else
        {
            if (bottomLeftQuad == NULL)
            {
                return NULL;
            }
            return bottomLeftQuad->find(point);
        }
    }
    else
    {
        //TopRightQuad
        if ((topLeft.y + bottomRight.y) / 2 >= point.y)
        {
            if (topRightQuad == NULL)
            {
                return NULL;
            }
            return topRightQuad->find(point);
        }
        //BottomRightQuad
        else
        {
            if (bottomRightQuad == NULL)
            {
                return NULL;
            }
            return bottomRightQuad->find(point);
        }
    }
};

bool quadTree::inContainer(Point point)
{
    if (point.x >= topLeft.x && point.x <= bottomRight.x && point.y >= topLeft.y && point.y <= bottomRight.y)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int quadTree::arithmeticMean()
{
    int sum = 0;
    int quadSize =  (abs(bottomRight.x - topLeft.x)) * (abs(topLeft.y - bottomRight.y));

    for (int i = 1; i <= quadSize; i++)
    {
        sum = sum + node->data;
        node++;
    }

    return (sum / quadSize);
}

int quadTree::arithmeticVariance()
{
    int sum, base;
    int quadSize =  (abs(bottomRight.x - topLeft.x)) * (abs(topLeft.y - bottomRight.y));
    int mean = arithmeticMean();

    for (int i = 1; i <= quadSize; i++)
    {
        base = node->data - mean;
        sum = sum + pow(base, 2);
        node++;
    }

    return (sum / (quadSize - 1));
}

int main()
{
    THRESHOLD = varianceThreshold();

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
    for (row = 0; row < numRows; ++row)
    {
        for (col = 0; col < numCols; ++col)
        {
            ss >> array[row][col];
        }
    }

    quadTree image(Point(0, 0), Point(numRows, numCols));
    Node node(Point(numRows, numCols), array);
    image.insert(&node);

    for (row = 0; row < numRows; ++row)
    {
        for (col = 0; col < numCols; ++col)
        {
            out << image.find(Point(row, col))->data << "  ";
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
