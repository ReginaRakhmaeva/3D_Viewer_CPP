// GEOMETRY.H - Геометрические классы

// Vertex (Вершина) \
// Edge (Ребро)

// ЗАЧЕМ НУЖЕН:
// Содержит всю геометрическую иерархию объектов 3D сцены. Реализует паттерн
// "Композит" - Scene содержит Figure'ы, Figure содержит Vertex'ы и Edge'ы.
// Каждый объект может быть трансформирован через матрицы.
//
// ЧТО СОДЕРЖИТ:
// - 3DPoint класс (x, y, z координаты) - базовая точка в 3D пространстве
// - TransformMatrix класс (4x4 матрица для аффинных преобразований)
// - TransformMatrixBuilder класс (статические методы создания матриц поворота/перемещения/масштабирования)
// - Vertex класс (наследует от SceneObject, содержит 3DPoint) - вершина модели
// - Edge класс (связь между двумя Vertex) - ребро между вершинами
// - Figure класс (наследует от SceneObject, содержит vector<Vertex> и vector<Edge>) - 3D объект
// - Scene класс (содержит vector<Figure>) - вся 3D сцена
// - SceneObject абстрактный базовый класс с методом Transform() - интерфейс для трансформируемых объектов
//
// КАК РАБОТАЕТ:
// 1. Scene содержит коллекцию Figure объектов
// 2. Figure содержит коллекции Vertex и Edge объектов  
// 3. Vertex (Вершина) содержит 3DPoint с координатами
// 4. Edge (Ребро) связывает два Vertex (не трансформируется напрямую)
// 5. При трансформации Figure -> трансформируются все его Vertex'ы
// 6. При трансформации Scene -> трансформируются все Figure'ы
// 7. TransformMatrixBuilder создает матрицы для разных типов трансформаций
// 8. TransformMatrix применяется к 3DPoint через умножение матриц
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
    
    // Геометрические объекты
    class Vertex {
    public:
        void Transform(const TransformMatrix& matrix);
    private:
        3DPoint position_;
    };
    class Edge { Vertex* begin_, *end_; };

    
    class Figure {
    public:
        void Transform(const TransformMatrix& matrix);
    private:
        std::vector<Vertex> vertices_;
    };

    
    class Scene {
    public:
        void Transform(const TransformMatrix& matrix);
    private:
        std::vector<Figure> figures_;
    };
}
