#include "Node.cpp"
#include "Point.cpp"
#include "math.h"
#include <cmath>
#include <stddef.h>

class QuadTree
{
    Point topLeft;
    Point bottomRight;
    Node *node;

    QuadTree *topLeftQuad;
    QuadTree *topRightQuad;
    QuadTree *bottomLeftQuad;
    QuadTree *bottomRightQuad;
    int THRESHOLD;

public:
    QuadTree()
    {
        topLeft = Point(0, 0);
        bottomRight = Point(0, 0);
        node = NULL;
        topLeftQuad = NULL;
        topRightQuad = NULL;
        bottomLeftQuad = NULL;
        bottomRightQuad = NULL;
        THRESHOLD = 0;
    }
    QuadTree(Point _topLeft, Point _bottomRight, int thresh)
    {
        node = NULL;
        topLeftQuad = NULL;
        topRightQuad = NULL;
        bottomLeftQuad = NULL;
        bottomRightQuad = NULL;
        topLeft = _topLeft;
        bottomRight = _bottomRight;
        THRESHOLD = thresh;
    }
    void insert(Node*);
    Node* find(Point);
    bool inContainer(Point);
    double arithmeticMean();
    double arithmeticVariance();
};


void QuadTree::insert(Node *_node)
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
                topLeftQuad = new QuadTree(Point(topLeft.x, topLeft.y), Point((topLeft.x + bottomRight.x) / 2, (topLeft.y + bottomRight.y) / 2), THRESHOLD);
            }
            topLeftQuad->insert(_node);

            if (arithmeticVariance() <= THRESHOLD)
            {
                *topLeftQuad->node->data = arithmeticMean();
                return;
            }
        }
        //BottomLeftQuad
        else
        {
            if (bottomLeftQuad == NULL)
            {
                bottomLeftQuad = new QuadTree(Point(topLeft.x, (topLeft.y + bottomRight.y) / 2), Point((topLeft.x + bottomRight.x) / 2, bottomRight.y), THRESHOLD);
            }
            bottomLeftQuad->insert(_node);

            if (arithmeticVariance() <= THRESHOLD)
            {
                *bottomLeftQuad->node->data = arithmeticMean();
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
                topRightQuad = new QuadTree(Point((topLeft.x + bottomRight.x) / 2, topLeft.y), Point(bottomRight.x, (topLeft.y + bottomRight.y) / 2), THRESHOLD);
            }
            topRightQuad->insert(_node);

            if (arithmeticVariance() <= THRESHOLD)
            {
                *topRightQuad->node->data = arithmeticMean();
                return;
            }
        }
        //BottomRightQuad
        else
        {
            if (bottomRightQuad == NULL)
            {
                bottomRightQuad = new QuadTree(Point((topLeft.x + bottomRight.x) / 2, (topLeft.y + bottomRight.y) / 2), Point(bottomRight.x, bottomRight.y), THRESHOLD);
            }
            bottomRightQuad->insert(_node);

            if (arithmeticVariance() <= THRESHOLD)
            {
                *bottomRightQuad->node->data = arithmeticMean();
                return;
            }
        }
    }
}

Node* QuadTree::find(Point point)
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

bool QuadTree::inContainer(Point point)
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

double QuadTree::arithmeticMean()
{
    double sum = 0;
    int quadSize =  (abs(bottomRight.x - topLeft.x)) * (abs(topLeft.y - bottomRight.y));

    for (int i = 1; i <= quadSize; i++)
    {
        sum = sum + *node->data;
        node++;
    }

    return (sum / quadSize);
}

double QuadTree::arithmeticVariance()
{
    double sum, base;
    int quadSize =  (abs(bottomRight.x - topLeft.x)) * (abs(topLeft.y - bottomRight.y));
    double mean = arithmeticMean();

    for (int i = 1; i <= quadSize; i++)
    {
        base = *node->data - mean;
        sum = sum + pow(base, 2);
        node++;
    }

    return (sum / (quadSize - 1));
}
