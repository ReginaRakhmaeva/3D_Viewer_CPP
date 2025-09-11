// MODEL.CPP - Реализация основной модели
//
// ЧТО РЕАЛИЗУЕТ:
// - Facade паттерн - упрощенный интерфейс для сложной подсистемы
// - Загрузка OBJ файлов с парсингом вершин (v) и граней (f)
// - Аффинные преобразования через TransformMatrixBuilder (используя s21_matrix+)
// - Нормализация модели при загрузке (центрирование, масштабирование)
// - Обработка ошибок и возврат FacadeOperationResult
// - Работа с Scene, Figure, Vertex, Edge классами
//
// КАК РАБОТАЕТ:
// 1. LoadScene() -> создает FileReader, парсит OBJ, создает Scene, нормализует
// 2. MoveScene() -> создает матрицу перемещения и применяет к сцене
// 3. RotateScene() -> создает матрицу поворота и применяет к сцене
// 4. ScaleScene() -> создает матрицу масштабирования и применяет к сцене

#include "model.h"
#include "geometry.h"  // TransformMatrixBuilder, TransformMatrix

FacadeOperationResult Model::MoveScene(double x, double y, double z) {
    try {
        // 1. Создает матрицу перемещения
        TransformMatrix matrix = TransformMatrixBuilder::CreateMoveMatrix(x, y, z);
        
        // 2. Применяет к сцене
        scene_.Transform(matrix);
        
        return FacadeOperationResult(true, "Move successful");
        
    } catch (const std::exception& e) {
        return FacadeOperationResult(false, e.what());
    }
}

FacadeOperationResult Model::RotateScene(double x, double y, double z) {
    try {
        // 1. Создает матрицу поворота
        TransformMatrix matrix = TransformMatrixBuilder::CreateRotationMatrix(x, y, z);
        
        // 2. Применяет к сцене
        scene_.Transform(matrix);
        
        return FacadeOperationResult(true, "Rotation successful");
        
    } catch (const std::exception& e) {
        return FacadeOperationResult(false, e.what());
    }
}

FacadeOperationResult Model::ScaleScene(double x, double y, double z) {
    try {
        // 1. Создает матрицу масштабирования
        TransformMatrix matrix = TransformMatrixBuilder::CreateScaleMatrix(x, y, z);
        
        // 2. Применяет к сцене
        scene_.Transform(matrix);
        
        return FacadeOperationResult(true, "Scaling successful");
        
    } catch (const std::exception& e) {
        return FacadeOperationResult(false, e.what());
    }
}
