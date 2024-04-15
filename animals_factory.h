#pragma once

#include "animals.h"
//абстрактный класс фабрики животных
class AnimalFactory {
public:
    virtual Animals* createAnimal(const Owner& owner, const string& name, int age) const = 0; //создание животного
    virtual ~AnimalFactory() = default;//деструктор
};

