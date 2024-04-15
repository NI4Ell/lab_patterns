
#pragma once

#include "animals_factory.h"
// Класс фабрики котов
class CatFactory : public AnimalFactory {
public:
    Animals* createAnimal(const Owner& owner, const string& name, int age) const override {
        return new Cat(owner, "Кот", name, age);
    }
};
