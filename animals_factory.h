#pragma once

#include "animals.h"
//����������� ����� ������� ��������
class AnimalFactory {
public:
    virtual Animals* createAnimal(const Owner& owner, const string& name, int age) const = 0; //�������� ���������
    virtual ~AnimalFactory() = default;//����������
};

