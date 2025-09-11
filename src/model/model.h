// MODEL.H - Основная модель (Facade паттерн)
// 
// ЗАЧЕМ НУЖЕН:
// Это центральный класс всей системы - Facade, который упрощает работу с сложной подсистемой.
// Вместо того чтобы View/Controller работали с множеством классов (FileReader, Scene, Figure, 
// TransformMatrix, etc.), они работают только с одним классом Model.
//
// ЧТО СОДЕРЖИТ:
// - Класс Model как Facade для всей подсистемы
// - Агрегирует: BaseFileReader (загрузка), SceneDrawerBase (отрисовка), Scene (данные)
// - Упрощенный интерфейс: LoadScene(), MoveScene(), RotateScene(), ScaleScene(), DrawScene()
// - Возвращает FacadeOperationResult для всех операций (успех/ошибка)
// - Управление стратегиями трансформации (Strategy паттерн)
// - Работа с TransformMatrix для аффинных преобразований
// - Загрузка OBJ файлов через FileReader
// - Управление Scene с Figure объектами (Vertex, Edge)
//
// ЧТО ПРОИСХОДИТ:
// 1. Пользователь нажимает "Загрузить файл" -> Controller вызывает model.LoadScene()
// 2. Model делегирует загрузку FileReader'у, получает Scene
// 3. Пользователь поворачивает модель -> Controller вызывает model.RotateScene()
// 4. Model создает RotateStrategy и применяет к сцене
// 6. View запрашивает отрисовку -> Model делегирует SceneDrawer'у
//
// Все в namespace s21

// Model содержит Scene как основную структуру данных
// Model = Facade для сложной подсистемы
class Model {
    // Агрегирует сложные компоненты:
    std::unique_ptr<BaseFileReader> file_reader_;     // Загрузка файлов
    Scene scene_;                                     // Данные модели
    
 public:
    // Упрощенный интерфейс для сложной подсистемы:
    FacadeOperationResult LoadScene(const std::string& path); //Загрузка файла
    FacadeOperationResult MoveScene(double x, double y, double z); //Перемещение модели
    FacadeOperationResult RotateScene(double x, double y, double z); //Поворот модели
    FacadeOperationResult ScaleScene(double x, double y, double z); //Масштабирование модели
    const Scene& GetScene() const;
    bool HasScene() const;
};

// ====== Результат операций Facade ======
class FacadeOperationResult {
 public:
    FacadeOperationResult(bool success, const std::string& message);
    FacadeOperationResult(bool success, const std::string& message, Scene scene);
    
    bool IsSuccess() const { return success_; }
    bool IsError() const { return !success_; }
    
    std::string GetErrorMessage() const { return message_; }
    const Scene& GetScene() const { return scene_; }

 private:
    bool success_;
    std::string message_;
    Scene scene_;
};