// GEOMETRY.CPP - Реализация геометрических классов
//
// ЗАЧЕМ НУЖЕН:
// Реализует всю геометрическую логику 3D объектов. Обеспечивает корректные
// аффинные преобразования через матрицы. Использует библиотеку s21_matrix+
// для матричных операций.
//
// ЧТО РЕАЛИЗУЕТ:
// - 3DPoint: базовые операции с 3D точками (сложение, вычитание, нормализация)
// - TransformMatrix: умножение матриц, применение к точкам, комбинирование трансформаций
// - TransformMatrixBuilder: создание матриц поворота (по осям X,Y,Z), перемещения, масштабирования
// - Vertex: трансформация позиции через матрицы (TransformMatrix * 3DPoint)
// - Edge: связь между вершинами (не трансформируется напрямую, обновляется при трансформации вершин)
// - Figure: трансформация всех вершин фигуры (делегирует трансформацию каждой вершине)
// - Scene: трансформация всех фигур в сцене (делегирует трансформацию каждой фигуре)
// - SceneObject: абстрактный интерфейс для трансформируемых объектов


TransformMatrix TransformMatrixBuilder::CreateRotationMatrix(double angleX, double angleY, double angleZ) {
    // Создаем матрицы поворота используя s21_matrix+
    S21Matrix rotateX = createRotationXMatrix(angleX);
    S21Matrix rotateY = createRotationYMatrix(angleY);
    S21Matrix rotateZ = createRotationZMatrix(angleZ);
    
    // Комбинируем матрицы
    S21Matrix result = rotateZ * rotateY * rotateX;
    
    return TransformMatrix(result);
}
