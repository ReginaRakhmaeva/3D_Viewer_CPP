// MODEL.H - Основная модель (Facade паттерн)
// 
// ЗАЧЕМ НУЖЕН:
// Это центральный класс всей системы - Facade, который упрощает работу с сложной подсистемой.
// Вместо того чтобы View/Controller работали с множеством классов (FileReader, Scene, Mesh, 
// TransformMatrix, etc.), они работают только с одним классом Model.
//
// ЧТО СОДЕРЖИТ:
// - Класс Model как Facade для всей подсистемы
// - Агрегирует: FileReader (загрузка), NormalizationService (нормализация), Mesh (данные)
// - Упрощенный интерфейс: LoadMesh(), MoveMesh(), RotateMesh(), ScaleMesh()
// - Возвращает FacadeOperationResult для всех операций (успех/ошибка)
// - Управление стратегиями трансформации (Strategy паттерн)
// - Работа с TransformMatrix для аффинных преобразований
// - Загрузка OBJ файлов через FileReader
// - Нормализация mesh'а через NormalizationService
// - Управление Mesh объектами (Vertex, Edge)
//
// ЧТО ПРОИСХОДИТ:
// 1. Пользователь нажимает "Загрузить файл" -> Controller вызывает model.LoadMesh()
// 2. Model делегирует загрузку FileReader'у, получает Mesh
// 3. Model делегирует нормализацию NormalizationService'у
// 4. Пользователь поворачивает модель -> Controller вызывает model.RotateMesh()
// 5. Model создает матрицу поворота и применяет к mesh'у
// 6. View запрашивает отрисовку -> Model возвращает mesh'а
//
// Все в namespace s21

#include "geometry.h"  // 3DPoint, TransformMatrix

namespace s21 {

// Структуры данных модели
class Vertex {
public:
    Vertex(const 3DPoint& position) : position_(position) {}
    void Transform(const TransformMatrix& matrix);
    const 3DPoint& GetPosition() const { return position_; }
    
private:
    3DPoint position_;
};

class Edge {
public:
    Edge(Vertex* begin, Vertex* end) : begin_(begin), end_(end) {}
    Vertex* GetBegin() const { return begin_; }
    Vertex* GetEnd() const { return end_; }
    
private:
    Vertex* begin_;
    Vertex* end_;
};

class Mesh {
public:
    void Transform(const TransformMatrix& matrix);
    void AddVertex(const 3DPoint& position);
    void AddEdge(size_t begin_index, size_t end_index);
    
    // Информация о модели
    std::string GetFilename() const { return filename_; }
    size_t GetVertexCount() const { return vertices_.size(); }
    size_t GetEdgeCount() const { return edges_.size(); }
    const std::vector<Vertex>& GetVertices() const { return vertices_; }
    const std::vector<Edge>& GetEdges() const { return edges_; }
    
    // Настройки отображения
    void SetLineColor(const QColor& color) { line_color_ = color; }
    void SetVertexColor(const QColor& color) { vertex_color_ = color; }
    void SetLineWidth(int width) { line_width_ = width; }
    
private:
    std::vector<Vertex> vertices_;
    std::vector<Edge> edges_;
    std::string filename_;
    
    // Настройки отображения
    QColor line_color_;
    QColor vertex_color_;
    int line_width_;
};

// Model = Facade для сложной подсистемы
class Model {
public:
    Model();
    ~Model();
    
    FacadeOperationResult LoadMesh(const std::string& path);
    FacadeOperationResult MoveMesh(double x, double y, double z);
    FacadeOperationResult RotateMesh(double x, double y, double z);
    FacadeOperationResult ScaleMesh(double x, double y, double z);
    
    // Информация о mesh'е
    bool HasMesh() const { return !mesh_.GetVertices().empty(); }
    const Mesh& GetMesh() const { return mesh_; }
    
    // Настройки отображения
    void SetLineColor(const QColor& color);
    void SetVertexColor(const QColor& color);
    void SetLineWidth(int width);

private:
    Mesh mesh_;
    std::unique_ptr<FileReader> file_reader_;
    std::unique_ptr<NormalizationService> normalization_service_;
    
    // Вспомогательные методы
    void initializeServices();
};

// ====== Результат операций Facade ======
class FacadeOperationResult {
 public:
    FacadeOperationResult(bool success, const std::string& message);
    FacadeOperationResult(bool success, const std::string& message, Mesh mesh);
    
    bool IsSuccess() const { return success_; }
    bool IsError() const { return !success_; }
    
    std::string GetErrorMessage() const { return message_; }
    const Mesh& GetMesh() const { return mesh_; }

 private:
     bool success_;
     std::string message_;
     Mesh mesh_;
};

}  // namespace s21