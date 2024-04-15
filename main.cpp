#include "animals_factory.h"
#include "cat_factory.h"
#include "dog_factory.h"
#include "fish_factory.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <Windows.h>

using namespace std;

int main() {
	setlocale(LC_ALL, ".1251");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	ifstream fin("animals.txt");
	if (!fin.is_open()) {
		cout << "Error";
	}
	else {
		string st;
		unordered_map<string, vector<Animals*>> ownerAnimals; // �������� -> ��������

		while (getline(fin, st)) { // ���������� ������ �� �����
			string owner_name, type, name;
			int age;
			istringstream ss(st);
			getline(ss, owner_name, ',');
			getline(ss, type, ',');
			getline(ss, name, ',');
			ss >> age;
			if (name == "") { // ���� ��� �� �������, �� ����������� ��� "Noname"
				name = "Noname";
			}

			// �������� ������� ���������
			Owner owner(owner_name);

			// ����������� ��������� ����� ��� �������� �������� Animals
			AnimalFactory* factory = nullptr;
			// �������� ������� ������� � ����������� �� ���� ���������
			if (type == "���") {
				factory = new CatFactory();
			}
			else if (type == "������") {
				factory = new DogFactory();
			}
			else if (type == "�����") {
				factory = new FishFactory();
			}
			// �������� ������� ���������
			if (factory != nullptr) {
				Animals* animal = factory->createAnimal(owner, name, age);
				ownerAnimals[owner.name].push_back(animal);
				delete factory; // ������������ �������� �������
			}
			else {
				cerr << "������: ����������� ��� ���������: " << type << endl;
			}
		}

		while (true) {
			cout << "���� � ���������" << endl
				<< "1) ��������� ���������� ��������� ����� �������� � ������� ���������." << endl
				<< "2) ��� ����������� ���� ��������� (�������� �������������) ������� ���� ��� ���������� � ������." << endl
				<< "3) ����������, ������� ����� �������� ����� ����������� ������" << endl
				<< "4) ������� ���������� � �������� ������ ������� � ������ �������� ��������� ������� ����." << endl
				<< "5) move-���������" << endl
				<< "6) ����� �� ���������" << endl
				<< "������� ����� ���������� ������: ";
			string number;
			cin >> number;
			
			if (number == "6") {
				break;
			}
			if(number == "1"){
				for (auto& owner : ownerAnimals)
				{
					cout << "��������: " << owner.first << ", ����� " << owner.second.size() << " ��������" << endl;
				}
				break;
			}
			else if(number == "2") {
				string animalType;
				cout << "������� ��� ���������: ";
				cin >> animalType;
				for (const auto& owner : ownerAnimals) {
					for (const auto& animal : owner.second) {
						if (animal->type == animalType) {
							cout << "��������: " << owner.first << ", ������: " << (*animal).name << endl;
							break;
						}
					}
				}

				break;
			}
			else if(number == "3") {

				string petName;
				cout << "������� ������: ";
				cin >> petName;

				unordered_set<string> animalTypes;

				for (auto& owner : ownerAnimals) {
					for (auto& animal : owner.second) {
						if (animal->name == petName) {
							animalTypes.insert(animal->type);
						}
					}
				}

				cout << "���������� ����� �������� � ������� \"" << petName << "\": " << animalTypes.size() << endl;
				break;
			}
			else if(number == "4") {
				for (const auto& owner : ownerAnimals) {
					unordered_map<string, pair<int, int>> minMaxAge;
					for (const auto& animal : owner.second) {
						auto& minMax = minMaxAge[animal->type];
						if (minMax.first == 0 || animal->age < minMax.first) {
							minMax.first = animal->age;
						}
						if (animal->age > minMax.second) {
							minMax.second = animal->age;
						}
					}
					cout << "��������: " << owner.first << endl;
					for (const auto& typeMinMax : minMaxAge) {
						cout << "   ���: " << typeMinMax.first << ", ����������� �������: "
							<< typeMinMax.second.first
							<< ", ������������ �������: " << typeMinMax.second.second << endl;
					}
				}
				break;

			}
			else if (number == "5") {
				//�������� ���� �����
				Owner owner1("��������1");
				Owner owner2("��������2");
				AnimalFactory* factory = new CatFactory();
				Animals* cat1 = factory->createAnimal(owner1, "���1", 5);
				Animals* cat2 = factory->createAnimal(owner2, "���2", 3);
				delete factory;
				//����� ���������� � �����
				cout << "���������� � ����� �� ������������:" << endl;
				cout << "���1: " << cat1->owner.name << ", " << cat1->name << ", " << cat1->age << endl;
				cout << "���2: " << cat2->owner.name << ", " << cat2->name << ", " << cat2->age << endl;
				//������������ ������������
				*dynamic_cast<Cat*>(cat1) = move(*dynamic_cast<Cat*>(cat2));
				//����� ���������� � ����� ����� ������������
				cout << "���������� � ����� ����� ������������:" << endl;
				cout << "���1: " << cat1->getOwnerName() << ", " << cat1->getName2() << ", " << cat1->getAge() << endl;
				cout << "���2: " << cat2->getOwnerName() << ", " << cat2->getName2() << ", " << cat2->getAge() << endl;
				break;

			}

			else
			{
				cout << "Incorrect input.";
				break;
			}
		}

		for (auto& owner : ownerAnimals) {
			for (auto& animal : owner.second) {
				delete animal;
			}
		}
	}
}
