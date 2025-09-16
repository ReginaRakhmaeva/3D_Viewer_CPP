// RENDERING.H - Классы для отрисовки (часть View)
//
// ЗАЧЕМ НУЖЕН:
// Обеспечивает отрисовку 3D моделей через Qt виджеты. Реализует паттерн Strategy
// для различных способов рендеринга. Инкапсулирует всю логику отрисовки
// и настройки визуализации с использованием стандартных Qt инструментов.
//
// ЧТО СОДЕРЖИТ:
// - SceneDrawerBase абстрактный класс (интерфейс для отрисовки) - паттерн Strategy
// - QtSceneDrawer класс (конкретная реализация для Qt) - Qt рендеринг
// - Методы для отрисовки Scene, Mesh, Vertex, Edge
// - Настройки отрисовки (цвета, толщина линий, размер вершин)
// - Поддержка разных типов проекции (параллельная/центральная)
// - Простая 3D проекция: ортогональная проекция 3D координат в 2D экранные
// - Оптимизация рендеринга для больших моделей
// - Стратегии рендеринга: WireframeStrategy, SolidStrategy, PointCloudStrategy
//
// КАК РАБОТАЕТ:
// 1. SceneDrawerBase::DrawScene() - абстрактный метод отрисовки сцены
// 2. QtSceneDrawer::DrawScene() - конкретная реализация через QPainter
// 3. Отрисовка каркасной модели:
//    - Создание QPainter для отрисовки
//    - Проекция 3D координат в 2D экранные координаты
//    - Отрисовка линий между вершинами (QPainter::drawLine)
// 4. Отрисовка вершин:
//    - Отрисовка вершин как точек (QPainter::drawPoint)
// 5. Настройки отображения:
//    - Цвета через QPen и QBrush
//    - Толщина линий через QPen::setWidth
//    - Размер вершин через QPen::setWidth
//
// ПРИНЦИПЫ MVC:
// - НИКАКОЙ бизнес-логики, только отрисовка
// - Получает данные модели от Controller
// - Отображает модель без изменения данных
// - Инкапсулирует всю логику визуализации
//
// Все в namespace s21
// В rendering.h уже есть SceneDrawerBase - это хорошая основа!
// Можно добавить разные стратегии:

class RenderingStrategy {
public:
    virtual ~RenderingStrategy() = default;
    virtual void Render(const Scene& scene, QPainter& painter) = 0;
};

class WireframeStrategy : public RenderingStrategy {
    void Render(const Scene& scene, QPainter& painter) override {
        // Отрисовка только линий (каркас)
    }
};

class SolidStrategy : public RenderingStrategy {
    void Render(const Scene& scene, QPainter& painter) override {
        // Отрисовка залитых граней
    }
};

class PointCloudStrategy : public RenderingStrategy {
    void Render(const Scene& scene, QPainter& painter) override {
        // Отрисовка только вершин
    }
};