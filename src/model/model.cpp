// MODEL.CPP - Реализация основной модели
//
// ЧТО РЕАЛИЗУЕТ:
// - Facade паттерн - упрощенный интерфейс для сложной подсистемы
// - Загрузка OBJ файлов с парсингом вершин (v) и граней (f)
// - Аффинные преобразования через TransformMatrixBuilder (используя s21_matrix+)
// - Нормализация модели при загрузке (центрирование, масштабирование)
// - Обработка ошибок и возврат FacadeOperationResult
// - Работа с Scene, Mesh, Vertex, Edge классами
//
// КАК РАБОТАЕТ:
// 1. LoadMesh() -> создает FileReader, парсит OBJ, создает Mesh, нормализует
// 2. MoveMesh() -> создает матрицу перемещения и применяет к сцене
// 3. RotateMesh() -> создает матрицу поворота и применяет к сцене
// 4. ScaleScene() -> создает матрицу масштабирования и применяет к сцене

#include "model.h"
#include "geometry.h"  // TransformMatrixBuilder, TransformMatrix

FacadeOperationResult Model::MoveMesh(double x, double y, double z) {

        // 1. Создает матрицу перемещения
        TransformMatrix matrix = TransformMatrixBuilder::CreateMoveMatrix(x, y, z);
        
        // 2. Применяет к сцене
        mesh_.Transform(matrix);
        
        return FacadeOperationResult(true, "Move successful");
        
  
}

FacadeOperationResult Model::RotateMesh(double x, double y, double z) {
  
        // 1. Создает матрицу поворота
        TransformMatrix matrix = TransformMatrixBuilder::CreateRotationMatrix(x, y, z);
        
        // 2. Применяет к сцене
        mesh_.Transform(matrix);
        
        return FacadeOperationResult(true, "Rotation successful");
        
   
}

FacadeOperationResult Model::ScaleMesh(double x, double y, double z) {
   
        // 1. Создает матрицу масштабирования
        TransformMatrix matrix = TransformMatrixBuilder::CreateScaleMatrix(x, y, z);
        
        // 2. Применяет к сцене
        mesh_.Transform(matrix);
        
        return FacadeOperationResult(true, "Scaling successful");
    
}
