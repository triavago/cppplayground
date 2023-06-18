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
        size = size - size/10;
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

    void createRock() {}
};

class Mussels
{
public:
    Mussels()
    {
        cout << "This is mussels" << endl;
    }

    void createMussels() {}
};

class Pond
{
public:
    Pond(int fishNums)
    {
        fishes.reserve(fishNums);
        createFish(fishNums);
        pondRock.createRock();
        pondMussels.createMussels();
    }

    void simulatePond()
    {
        for(auto& currentFish : fishes)
        {
            if(!currentFish->isAlive())
                continue;
            for(auto& otherFish : fishes)
            {
                if(otherFish == currentFish || !otherFish->isAlive())
                    continue;
                if(currentFish->getSize() > otherFish->getSize())
                {
                    currentFish->eat(*otherFish);
                    break;
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
    Stone pondRock;
    Mussels pondMussels;

    void createFish(int numFish)
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1, 10);

        for (int i = 0; i < numFish; i++) 
        {
            int size = dis(gen);
            cout << "Fish size: " << size <<endl;
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