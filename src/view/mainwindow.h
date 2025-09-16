// MAINWINDOW.H - Главное окно Qt (View в MVC)
//
// ЗАЧЕМ НУЖЕН:
// Представляет пользовательский интерфейс приложения. Реализует View в MVC
// паттерне - только отображение данных и обработку пользовательского ввода.
// НЕ содержит бизнес-логики, только UI элементы и сигналы.
//
// ЧТО СОДЕРЖИТ:
// - MainWindow класс (наследует от QMainWindow) - главное окно приложения
// - UI элементы: кнопки, поля ввода, зона визуализации, меню, панели инструментов
// - Кнопка выбора файла модели (QPushButton + QFileDialog)
// - Поля для перемещения mesh'а (QDoubleSpinBox для X, Y, Z)
// - Поля для поворота mesh'а (QDoubleSpinBox для углов X, Y, Z) 
// - Поля для масштабирования mesh'а (QDoubleSpinBox для коэффициентов X, Y, Z)
// - Информация о mesh'е: название файла, количество вершин и ребер (QLabel)
// - Виджет для отображения 3D mesh'а (ModelWidget) - простая 2D проекция
// - Сигналы для взаимодействия с Controller (Qt signals)
// - Настройки отображения (цвета, толщина линий, размер вершин)
//
// КАК РАБОТАЕТ:
// 1. Пользователь нажимает кнопку "Загрузить" -> emit signalLoadFile()
// 2. Пользователь вводит значения трансформации -> emit signalTransform()
// 3. Controller обновляет данные -> updateModelInfo(), updateDisplay()
// 4. Model виджет отображает 3D mesh
// 5. Обработка событий мыши для интерактивного управления
//
// ПРИНЦИПЫ MVC:
// - НИКАКОЙ бизнес-логики, только UI
// - Только сигналы и слоты для взаимодействия с Controller
// - Отображение данных, полученных от Model через Controller
// - Обработка пользовательского ввода и отправка сигналов
//
// Все в namespace s21

namespace s21 {
    class MainWindow : public QMainWindow {
        // UI элементы: кнопки, поля ввода, ModelWidget
    };
}

// src/view/modelwidget.h
namespace s21 {
    class ModelWidget : public QWidget {
        Model* model_;
        
    protected:
        void paintEvent(QPaintEvent* event) override;
        
    private:
        void drawScene(const Scene& scene);
        void project3DTo2D(const 3DPoint& point3d, QPoint& point2d);
    };
}
