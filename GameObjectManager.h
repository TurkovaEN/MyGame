#ifndef GAMEOBJECTMANAGER_H
#define GAMEOBJECTMANAGER_H

#include <vector>
#include <memory> // Для использования std::unique_ptr

template <typename T>
class GameObjectManager {
private:
    std::vector<std::unique_ptr<T>> objects; // Вектор для хранения объектов

public:
    // Метод для добавления объекта
    void addObject(T* object) {
        objects.emplace_back(object); // Используем уникальный указатель
    }

    // Метод для обновления всех объектов
    void updateAll(float time, MapCollider& mapCollider) {
        for (const auto& object : objects) {
            object->update(time, mapCollider); // Вызываем метод update для каждого объекта
        }
    }

    // Метод для отображения всех объектов
    void displayAll(std::ostream& os) const {
        for (const auto& object : objects) {
            object->display(os); // Вызываем метод display для каждого объекта
        }
    }

    // Метод для получения количества объектов
    size_t getCount() const {
        return objects.size();
    }
};

#endif // GAMEOBJECTMANAGER_H