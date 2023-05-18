#include<iostream>
#include<vector>
#include<random>
#include <memory>

using namespace std;

class Fish
{
public:
    Fish(int size) : size(size), alive(true) {}

    int getSize()
    {
        return size;
    }

    int isAlive()
    {
        return alive;
    }

    void setAlive(bool isAlive)
    {
        alive = isAlive;
    }

    void eat(Fish& otherFish)
    {
        if(size > otherFish.getSize())
        {
            size += otherFish.getSize();
            otherFish.setAlive(false);
        }
        else
        {
            alive = false;
        }
    }
private:
    int size;
    bool alive;
};

class Stone
{
public:
    Stone()
    {
        cout << "This is a stone" << endl;
    }
};

class Mussels
{
public:
    Mussels()
    {
        cout << "This is mussels" << endl;
    }
};

class Pond
{
public:
    Pond(int fishNums)
    {
        fishes.reserve(fishNums);
            
    }
private:
    vector<unique_ptr<Fish>> fishes;

};