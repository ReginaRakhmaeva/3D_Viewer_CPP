// GEOMETRY.H - Математические структуры для 3D
//
// ЗАЧЕМ НУЖЕН:
// Содержит базовые математические структуры для работы с 3D координатами
// и аффинными преобразованиями. Обеспечивает математическую основу для
// трансформаций 3D объектов.
//
// ЧТО СОДЕРЖИТ:
// - 3DPoint структура (x, y, z координаты) - базовая точка в 3D пространстве
// - TransformMatrix класс (4x4 матрица для аффинных преобразований)
// - TransformMatrixBuilder класс (статические методы создания матриц поворота/перемещения/масштабирования)
//
// КАК РАБОТАЕТ:
// 1. 3DPoint хранит координаты точки в 3D пространстве
// 2. TransformMatrix применяет аффинные преобразования к точкам
// 3. TransformMatrixBuilder создает матрицы для разных типов трансформаций
// 4. Матрицы применяются к 3DPoint через умножение
//
// Все классы в namespace s21

namespace s21 {
    // Базовые структуры
    struct 3DPoint { double x, y, z; };
    
    // Матрицы трансформации
    class TransformMatrix {
    private:
        S21Matrix matrix_;  // ← Используем s21_matrix+
        
    public:
        // Обертка над s21_matrix+:
        void ApplyToPoint(3DPoint& point);
        TransformMatrix Multiply(const TransformMatrix& other);
    };
    class TransformMatrixBuilder {
    public:
        static TransformMatrix CreateMoveMatrix(double dx, double dy, double dz);
        static TransformMatrix CreateRotationMatrix(double angleX, double angleY, double angleZ);
        static TransformMatrix CreateScaleMatrix(double scaleX, double scaleY, double scaleZ);
    };
    
}
