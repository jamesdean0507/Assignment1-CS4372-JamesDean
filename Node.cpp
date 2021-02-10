#include "Point.cpp"


#ifndef NODE
#define NODE
struct Node
{
    Point position;
    int *data;
    Node(Point _position, int *_data)
    {
        position = _position;
        data = _data;
    }
    Node()
    {
        data = 0;
    }
};

#endif