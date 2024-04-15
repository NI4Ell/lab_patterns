#include <iostream>
#include <string>

using namespace std;

class Owner {
public:
	Owner(const string& name) : name(name) {}
	Owner() = default;
	string name;

	friend ostream& operator<<(ostream& os, const Owner& owner) {
		os << owner.name;
		return os;
	}
};
;

class Animals
{
public:


	Animals(const Owner& owner, const string& type, const string& name = "", int age = 0)
		: owner(owner), type(type), name(name), age(age) {}

	Animals() : age(0) {}

	// ����������� �����������
	Animals(Animals&& other) noexcept
		: owner(move(other.owner)), type(move(other.type)), name(move(other.name)), age(other.age) {
		other.age = 0;
	}

	// �������� ������������ ������������
	Animals& operator=(Animals&& other) noexcept {
		if (this != &other) {
			owner = move(other.owner);
			type = move(other.type);
			name = move(other.name);
			age = other.age;
			other.age = 0;
		}
		return *this;
	}

	Owner owner;
	string type;
	string name;
	int age;

	string getOwnerName() const {
		return owner.name;
	}

	void setOwnerName(const string& name) {
		owner.name = name;
	}

	string getType() const {
		return type;
	}

	string getName2() const {
		return name;
	}

	int getAge() const {
		return age;
	}

	void setType(const string& animalType) {
		type = animalType;
	}

	void setName2(const string& animalName) {
		name = animalName;
	}

	void setAge(int animalAge) {
		age = animalAge;
	}

	void Print() {
		cout << "��������: " << owner << " ";
		cout << "��� ���������: " << type << " ";
		if (!name.empty()) {
			cout << "��� ���������: " << name << endl;
		}
		cout << "�������: " << age << " ";
	}

	virtual void sound() = 0;
};

class Cat : public Animals {
public:
	Cat(const Owner& owner, const string type, const string& name, const int& age) : Animals(owner, "���", name, age) {}

	// ����������� �����������
	Cat(Cat&& other) noexcept : Animals(move(other)) {}

	// �������� ������������ ������������
	Cat& operator=(Cat&& other) noexcept {
		Animals::operator=(move(other));
		return *this;
	}

	void sound() override {
		cout << "Meow";
	}

};

class Dog : public Animals {
public:
	Dog(const Owner& owner, const string type, const string& name, const int& age) : Animals(owner, "������", name, age) {}
	
	// ����������� �����������
	Dog(Dog&& other) noexcept : Animals(move(other)) {}

	// �������� ������������ ������������
	Dog& operator=(Dog&& other) noexcept {
		Animals::operator=(move(other));
		return *this;
	}
	void sound() override {
		cout << "Woof";
	}
};

class Fish : public Animals {
public:
	Fish(const Owner& owner, const string type, const string& name, const int& age) : Animals(owner, "�����", name, age) {}
	// ����������� �����������
	Fish(Fish&& other) noexcept : Animals(move(other)) {}

	// �������� ������������ ������������
	Fish& operator=(Fish&& other) noexcept {
		Animals::operator=(move(other));
		return *this;
	}
	void sound() override {
		cout << "Bool";
	}
};