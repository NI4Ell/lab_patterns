#pragma once

#include "animals_factory.h"

class DogFactory : public AnimalFactory {
public:
    Animals* createAnimal(const Owner& owner, const string& name, int age) const override {
        return new Dog(owner, "Собака", name, age);
    }
};
