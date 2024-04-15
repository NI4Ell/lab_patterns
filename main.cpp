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
		unordered_map<string, vector<Animals*>> ownerAnimals; // Владелец -> животные

		while (getline(fin, st)) { // Считывание данных из файла
			string owner_name, type, name;
			int age;
			istringstream ss(st);
			getline(ss, owner_name, ',');
			getline(ss, type, ',');
			getline(ss, name, ',');
			ss >> age;
			if (name == "") { // Если имя не указано, то присваиваем имя "Noname"
				name = "Noname";
			}

			// Создание объекта владельца
			Owner owner(owner_name);

			// Используйте фабричный метод для создания объектов Animals
			AnimalFactory* factory = nullptr;
			// Создание объекта фабрики в зависимости от типа животного
			if (type == "Кот") {
				factory = new CatFactory();
			}
			else if (type == "Собака") {
				factory = new DogFactory();
			}
			else if (type == "Рыбка") {
				factory = new FishFactory();
			}
			// Создание объекта животного
			if (factory != nullptr) {
				Animals* animal = factory->createAnimal(owner, name, age);
				ownerAnimals[owner.name].push_back(animal);
				delete factory; // Освобождение ресурсов фабрики
			}
			else {
				cerr << "Ошибка: Неизвестный тип животного: " << type << endl;
			}
		}

		while (true) {
			cout << "МЕНЮ С ЗАДАНИЯМИ" << endl
				<< "1) Посчитать количество различных видов животных у каждого владельца." << endl
				<< "2) Для конкретного вида животного (вводится пользователем) вывести всех его владельцев и клички." << endl
				<< "3) Определить, сколько видов животных носит определённую кличку" << endl
				<< "4) Вывести информацию о возрасте самого старого и самого молодого животного каждого вида." << endl
				<< "5) move-семантика" << endl
				<< "6) Выйти из программы" << endl
				<< "Введите номер выбранного пункта: ";
			string number;
			cin >> number;
			
			if (number == "6") {
				break;
			}
			if(number == "1"){
				for (auto& owner : ownerAnimals)
				{
					cout << "Владелец: " << owner.first << ", имеет " << owner.second.size() << " животных" << endl;
				}
				break;
			}
			else if(number == "2") {
				string animalType;
				cout << "Введите вид животного: ";
				cin >> animalType;
				for (const auto& owner : ownerAnimals) {
					for (const auto& animal : owner.second) {
						if (animal->type == animalType) {
							cout << "Владелец: " << owner.first << ", Кличка: " << (*animal).name << endl;
							break;
						}
					}
				}

				break;
			}
			else if(number == "3") {

				string petName;
				cout << "Введите кличку: ";
				cin >> petName;

				unordered_set<string> animalTypes;

				for (auto& owner : ownerAnimals) {
					for (auto& animal : owner.second) {
						if (animal->name == petName) {
							animalTypes.insert(animal->type);
						}
					}
				}

				cout << "Количество видов животных с кличкой \"" << petName << "\": " << animalTypes.size() << endl;
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
					cout << "Владелец: " << owner.first << endl;
					for (const auto& typeMinMax : minMaxAge) {
						cout << "   Вид: " << typeMinMax.first << ", Минимальный возраст: "
							<< typeMinMax.second.first
							<< ", Максимальный возраст: " << typeMinMax.second.second << endl;
					}
				}
				break;

			}
			else if (number == "5") {
				//создание двух котов
				Owner owner1("Владелец1");
				Owner owner2("Владелец2");
				AnimalFactory* factory = new CatFactory();
				Animals* cat1 = factory->createAnimal(owner1, "Кот1", 5);
				Animals* cat2 = factory->createAnimal(owner2, "Кот2", 3);
				delete factory;
				//вывод информации о котах
				cout << "Информация о котах до присваивания:" << endl;
				cout << "Кот1: " << cat1->owner.name << ", " << cat1->name << ", " << cat1->age << endl;
				cout << "Кот2: " << cat2->owner.name << ", " << cat2->name << ", " << cat2->age << endl;
				//присваивание перемещением
				*dynamic_cast<Cat*>(cat1) = move(*dynamic_cast<Cat*>(cat2));
				//вывод информации о котах после присваивания
				cout << "Информация о котах после присваивания:" << endl;
				cout << "Кот1: " << cat1->getOwnerName() << ", " << cat1->getName2() << ", " << cat1->getAge() << endl;
				cout << "Кот2: " << cat2->getOwnerName() << ", " << cat2->getName2() << ", " << cat2->getAge() << endl;
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
