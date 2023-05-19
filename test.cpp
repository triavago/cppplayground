#include<iostream>
#include<vector>
#include<random>
#include <memory>
#include<algorithm>

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

    void weaken()
    {
        size -= 1;
        cout << "Fish size: " << size <<endl;
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
        createFish(fishNums);    
    }

    void simulatePond()
    {
        for(auto& currentFish : fishes)
        {
            for(auto& otherFish : fishes)
            {
                if(currentFish->getSize() > otherFish->getSize())
                {
                    currentFish->eat(*otherFish);
                }
                else
                {
                    otherFish->eat(*currentFish);
                    break;
                }
            }
            currentFish->weaken();
        }
        printFishState();
        cout << "end loop" << endl;
        removeDeadFish();
    }

    void printFishState()
    {
        int i = 0;
        for(const auto& currentFish : fishes)
        {
            i++;
            if(currentFish->isAlive())
                cout << "Fish " << i << ": size " << currentFish->getSize() << endl;
            else
                cout << "Fish " << i << " is dead" << endl;
        }
    }
private:
    vector<unique_ptr<Fish>> fishes;

    void createFish(int numFish)
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1, 10);

        for (int i = 0; i < numFish; i++) 
        {
            int size = dis(gen);
            fishes.push_back(make_unique<Fish>(size));
        }
    }

    void removeDeadFish()
    {
        fishes.erase(remove_if(fishes.begin(), fishes.end(), [](const unique_ptr<Fish>& f) {
            return !f->isAlive();
        }), fishes.end());
    }
};

int main()
{
    Pond pond(5);

    for(int i = 0; i < 5; i++)
    {
        pond.simulatePond();
        pond.printFishState();
    }

    return 0;
}