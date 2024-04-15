#pragma once

#include "animals_factory.h"
// Класс для создания рыбок
class FishFactory : public AnimalFactory {
public:
    Animals* createAnimal(const Owner& owner, const string& name, int age) const override {
        return new Fish(owner, "Рыбка", name, age);
    }
};
