#pragma once
#include <vector>

class Observer
{
public:
	virtual void update() = 0;
};

class Observable
{
private:
	std::vector<Observer*> observers;

protected:
	void notify()
	{
		for (auto observer : this->observers)
		{
			observer->update();
		}
	}

public:
	void addObserver(Observer* observer)
	{
		this->observers.push_back(observer);
	}
	void removeObserver(Observer* observer)
	{
		this->observers.erase(std::remove(this->observers.begin(), this->observers.end(), observer));
	}
};