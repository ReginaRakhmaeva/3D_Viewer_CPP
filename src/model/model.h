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
// - Undo/redo функциональность через Command паттерн (стек команд)
// - Управление стратегиями трансформации (Strategy паттерн)
// - Работа с TransformMatrix для аффинных преобразований
// - Загрузка OBJ файлов через FileReader
// - Управление Scene с Figure объектами (Vertex, Edge)
//
// ЧТО ПРОИСХОДИТ:
// 1. Пользователь нажимает "Загрузить файл" -> Controller вызывает model.LoadScene()
// 2. Model делегирует загрузку FileReader'у, получает Scene
// 3. Пользователь поворачивает модель -> Controller вызывает model.RotateScene()
// 4. Model создает RotateStrategy, оборачивает в TransformCommand, выполняет
// 5. Команда сохраняется в стек для undo/redo
// 6. View запрашивает отрисовку -> Model делегирует SceneDrawer'у
//
// Все в namespace s21