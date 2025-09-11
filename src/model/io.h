// IO.H - Классы для работы с OBJ файлами
//
// ЗАЧЕМ НУЖЕН:
// Обеспечивает загрузку 3D моделей из OBJ файлов. Обрабатывает ошибки
// и нормализует модели для корректного отображения.
//
// ЧТО СОДЕРЖИТ:
// - FileReader класс (парсинг OBJ файлов) - только OBJ!
// - NormalizationParameters класс (параметры нормализации модели)
// - FacadeOperationResult класс (результат операций с ошибками)
// - Парсинг OBJ файлов: вершины (v x y z) и грани (f v1 v2 v3 ...)
// - Нормализация координат модели (центрирование в начало координат, масштабирование)
// - Обработка ошибок чтения файлов (файл не найден, неправильный формат, поврежденные данные)
//
// Все в namespace s21

#ifndef IO_H_
#define IO_H_

#include <string>
#include <vector>
#include "geometry.h"  // Scene, Figure, Vertex, Edge, 3DPoint

namespace s21 {



// ====== Параметры нормализации ======
// ДО нормализации:
// Модель находится в координатах от (0,0,0) до (1000,1000,1000)
// Центр модели: (500, 500, 500)

// ПОСЛЕ центрирования:
// Модель перемещается так, чтобы центр был в (0,0,0)
// Новые координаты: от (-500,-500,-500) до (500,500,500)
class NormalizationParameters {
public:
    NormalizationParameters(double targetSize = 1.0, bool centerModel = true);
    
    double GetTargetSize() const { return targetSize_; }
    bool ShouldCenterModel() const { return centerModel_; }
    
private:
    double targetSize_;    // Целевой размер модели
    bool centerModel_;     // Центрировать модель в (0,0,0)
};

// ====== Чтение OBJ файлов ======
class FileReader {
public:
    FacadeOperationResult ReadScene(const std::string& filepath, 
                                   const NormalizationParameters& params);
            // 1. Открытие файла
        // 2. Парсинг вершин (v x y z)
        // 3. Парсинг граней (f v1 v2 v3 ...)
        // 4. Создание Vertex и Edge объектов
        // 5. Создание Figure и Scene
        // 6. Нормализация модели
        // 7. Возврат результата
private:
    // Вспомогательные методы парсинга OBJ
    bool parseVertex(const std::string& line, 3DPoint& point); // Парсит строку "v x y z" в 3DPoint
    bool parseFace(const std::string& line, std::vector<int>& indices); // Парсит строку "f v1 v2 v3" в индексы вершин
    void normalizeScene(Scene& scene, const NormalizationParameters& params); // Нормализует сцену (центрирование + масштабирование)
    
    // Вспомогательные методы
    std::vector<std::string> splitString(const std::string& str, char delimiter); // Разбивает строку по разделителю
    bool isValidVertexIndex(int index, size_t vertexCount); // Проверяет корректность индекса вершины
};

}  // namespace s21

#endif  // IO_H_
