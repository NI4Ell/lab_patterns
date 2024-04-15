#pragma once
#include "animals.h"
#include <iostream>
#include <vector>
using namespace std;
class Composite_animals
{
private:
	vector<Animals*> animals;
public:
	void addAnimal(Animals* animal) {
		animals.push_back(animal);
	}
	void removeAnimal(Animals* animal) {
		auto it = find(animals.begin(), animals.end(), animal);
		if (it != animals.end()) {
			animals.erase(it);
			delete animal;
		}
	}
	void print() const {
		for (auto animal : animals) {
			cout << "��������: " << animal->getOwnerName() << ", ���: " << animal->getType() << ", ������: " << animal->name << ", �������: " << animal->age << endl;
		}
	}
	int size() const {
		return animals.size();
	}
	Composite_animals* getComposite() {
		return this;
	}
};

