#ifndef GAMEOBJECTMANAGER_H
#define GAMEOBJECTMANAGER_H

#include <vector>
#include <memory> // ��� ������������� std::unique_ptr

template <typename T>
class GameObjectManager {
private:
    std::vector<std::unique_ptr<T>> objects; // ������ ��� �������� ��������

public:
    // ����� ��� ���������� �������
    void addObject(T* object) {
        objects.emplace_back(object); // ���������� ���������� ���������
    }

    // ����� ��� ���������� ���� ��������
    void updateAll(float time, MapCollider& mapCollider) {
        for (const auto& object : objects) {
            object->update(time, mapCollider); // �������� ����� update ��� ������� �������
        }
    }

    // ����� ��� ����������� ���� ��������
    void displayAll(std::ostream& os) const {
        for (const auto& object : objects) {
            object->display(os); // �������� ����� display ��� ������� �������
        }
    }

    // ����� ��� ��������� ���������� ��������
    size_t getCount() const {
        return objects.size();
    }
};

#endif // GAMEOBJECTMANAGER_H