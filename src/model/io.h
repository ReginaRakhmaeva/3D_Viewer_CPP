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
// - Нормализация координат mesh'а (центрирование в начало координат, масштабирование)
// - Обработка ошибок чтения файлов (файл не найден, неправильный формат, поврежденные данные)
//
// Все в namespace s21

#ifndef IO_H_
#define IO_H_

#include <string>
#include <vector>
#include "geometry.h"  // 3DPoint, TransformMatrix
#include "model.h"     // Mesh, Vertex, Edge

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
    FacadeOperationResult ReadMesh(const std::string& filepath, 
                                   const NormalizationParameters& params);
    
    // 1. Открытие файла
    // 2. Парсинг вершин (v x y z) -> temp_vertices_
    // 3. Парсинг граней (f v1 v2 v3 ...) -> temp_faces_
    // 4. Создание Vertex объектов из temp_vertices_
    // 5. Создание Edge объектов из temp_faces_
    // 6. Создание Mesh с Vertex и Edge
    // 7. Нормализация mesh'а
    // 8. Возврат результата

private:
    // Временные контейнеры для парсинга
    std::vector<3DPoint> temp_vertices_;           // Сырые координаты из OBJ
    std::vector<std::vector<int>> temp_faces_;     // Индексы граней из OBJ
    
    // Вспомогательные методы парсинга OBJ
    bool parseVertex(const std::string& line, 3DPoint& point); // Парсит "v x y z" -> 3DPoint
    bool parseFace(const std::string& line, std::vector<int>& indices); // Парсит "f v1 v2 v3" -> индексы
    void normalizeMesh(Mesh& mesh, const NormalizationParameters& params); // Нормализует mesh
    
    // Создание финальных структур
    Mesh createMeshFromTempData(); // Создает Mesh из temp_vertices_ и temp_faces_
    void createEdgesFromFaces(Mesh& mesh); // Преобразует Face'ы (грани) в Edge'ы (ребра)
    
    // Вспомогательные методы
    std::vector<std::string> splitString(const std::string& str, char delimiter);
    bool isValidVertexIndex(int index, size_t vertexCount);
    void clearTempData(); // Очищает временные контейнеры
};

}  // namespace s21

#endif  // IO_H_
