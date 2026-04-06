#include <iostream>
#include <vector>
#include <iterator>
#include <random>
#include <limits>
#include <functional>
#include <utility>
#include <chrono>
#include <cmath>
#include <iomanip>

template <typename T, typename Compare = std::less<T>>
class SkipList{
private:
    struct Node {
        T data;
        int count;
        std::vector<Node*> next;
        Node(const T& value, int level) : data(value), count(1), next(level + 1, nullptr) {}
    };
    
    Node* head;
    int maxLevel;
    float probability;
    int currentLevel;
    size_t m_size;
    Compare comp;
    mutable std::mt19937 rng{std::random_device{}()};
    //рандомайзер
    int randomLevel() const {
        int level = 1;
        std::uniform_real_distribution<double> dist(0.0, 1.0);
        while (dist(rng) < probability && level < maxLevel) {
            level++;
        }
        return level;
    }
    //равенство
    bool equal(const T& a, const T& b) const {
        return !comp(a, b) && !comp(b, a);
    }
    
public:
    //итератор
    class iterator {
    private:
        Node* current;
        const SkipList* list;
        
    public:
        //нужно для совместимости
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        //констркуторы
        iterator() : current(nullptr), list(nullptr) {}
        iterator(Node* node, const SkipList* lst = nullptr) : current(node), list(lst) {}
        //разыменование
        reference operator*() const {
            return current->data;
        }
        //доступ
        pointer operator->() const {
            return &(current->data);
        }
        //операторы инкрементов и декрементов
        iterator& operator++() {
            if (current) {
                current = current->next[0];
            }
            return *this;
        }
        
        iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }
        
        iterator& operator--() {
            if (!list || !list->head) {
                throw std::runtime_error("Нет доступа к списку");
            }
            
            if (current == nullptr) {
                current = list->head->next[0];
                if (!current) {
                    throw std::runtime_error("Пустой список");
                }
                while (current->next[0] != nullptr) {
                    current = current->next[0];
                }
            } else {
                Node* prev = list->head;
                while (prev->next[0] != nullptr && prev->next[0] != current) {
                    prev = prev->next[0];
                }
                if (prev == list->head) {
                    current = nullptr;
                } else {
                    current = prev;
                }
            }
            return *this;
        }
        
        iterator operator--(int) {
            iterator temp = *this;
            --(*this);
            return temp;
        }
        //равенство неравенство
        bool operator==(const iterator& other) const {
            return current == other.current;
        }
        
        bool operator!=(const iterator& other) const {
            return current != other.current;
        }
        //возвращение нода по итератору
        Node* getNode() const { return current; }
        //подсчет по итератор
        int getCount() const {
            return current ? current->count : 0;
        }
    };
    //реверс итераторы
    using reverse_iterator = std::reverse_iterator<iterator>;
    //бегин и энд
    iterator begin() const {
        if (head == nullptr || head->next[0] == nullptr) {
            return end();
        }
        return iterator(head->next[0], this);
    }
    
    iterator end() const {
        return iterator(nullptr, this);
    }
    //обратные бегин и энд
    reverse_iterator rbegin() const {
        return reverse_iterator(end());
    }
    
    reverse_iterator rend() const {
        return reverse_iterator(begin());
    }
    //метод поиска
    iterator find(const T& value) const {
        if (head == nullptr) {
            return end();
        }
        
        Node* current = head;
        
        for (int i = currentLevel - 1; i >= 0; i--) {
            while (current->next[i] != nullptr && comp(current->next[i]->data, value)) {
                current = current->next[i];
            }
        }
        
        current = current->next[0];
        
        if (current != nullptr && equal(current->data, value)) {
            return iterator(current, this);
        }
        
        return end();
    }
    //подсчет
    size_t count(const T& value) const {
        auto it = find(value);
        if (it == end()) return 0;
        return it.getNode()->count;
    }
    //первый не меньше
    iterator lower_bound(const T& value) const {
        Node* current = head;
        
        for (int i = currentLevel - 1; i >= 0; i--) {
            while (current->next[i] != nullptr && comp(current->next[i]->data, value)) {
                current = current->next[i];
            }
        }
        
        Node* result = current->next[0];
        return (result != nullptr) ? iterator(result, this) : end();
    }
    //первый больше
    iterator upper_bound(const T& value) const {
        Node* current = head;
        
        for (int i = currentLevel - 1; i >= 0; i--) {
            while (current->next[i] != nullptr && !comp(value, current->next[i]->data)) {
                current = current->next[i];
            }
        }
        
        Node* result = current->next[0];
        return (result != nullptr) ? iterator(result, this) : end();
    }
    //одинаковые элементы
    std::pair<iterator, iterator> equal_range(const T& value) const {
        iterator lower = lower_bound(value);
        if (lower == end() || !equal(*lower, value)) {
            return std::make_pair(end(), end());
        }
        iterator upper = upper_bound(value);
        return std::make_pair(lower, upper);
    }
    //метод вставки, расписал основные пункты его работы
    void insert(const T& value) {
        //Вектор для хранения узлов, которые нужно обновить на каждом уровне
        std::vector<Node*> update(maxLevel, nullptr);
        Node* current = head;
        //Ищем позицию для вставки на всех уровнях (сверху вниз)
        for (int i = currentLevel - 1; i >= 0; i--) {
            while (current->next[i] != nullptr && comp(current->next[i]->data, value)) {
                current = current->next[i];
            }
            update[i] = current;// Запоминаем узел, после которого нужно вставить
        }
        //Переходим к следующему на уровне 0
        current = current->next[0];
        //Проверяем, не существует ли уже такой элемент
        if (current != nullptr && equal(current->data, value)) {
            current->count++;
            m_size++;
            return;
        }
        //Генерируем случайный уровень для нового узла
        int newLevel = randomLevel();
        //Если новый уровень выше текущего, обновляем update и currentLevel
        if (newLevel > currentLevel) {
            for (int i = currentLevel; i < newLevel; i++) {
                update[i] = head;// На новых уровнях вставляем после головы
            }
            currentLevel = newLevel;
        }
        //Создаем новый узел
        Node* newNode = new Node(value, newLevel);
        //Вставляем узел на всех уровнях (перенаправляем указатели)
        for (int i = 0; i < newLevel; i++) {
            newNode->next[i] = update[i]->next[i];
            update[i]->next[i] = newNode;
        }
        //Увеличиваем размер
        m_size++;
    }
    //инсерт через итераторы
    template <typename Iterator>
    void insert(Iterator begin, Iterator end) {
        for (Iterator i = begin; i != end; ++i) {
            insert(*i);
        }
    }
    //удаление по итератору
    iterator erase(iterator pos) {
        if (pos == end()) {
            return end();
        }
        
        Node* nodeToDelete = pos.getNode();
        
        if (nodeToDelete->count > 1) {
            iterator next = pos;
            ++next;
            nodeToDelete->count--;
            m_size--;
            return next;
        }
        
        T value = nodeToDelete->data;
        iterator next = pos;
        ++next;
        
        std::vector<Node*> update(maxLevel, nullptr);
        Node* current = head;
        
        for (int i = currentLevel - 1; i >= 0; i--) {
            while (current->next[i] != nullptr && comp(current->next[i]->data, value)) {
                current = current->next[i];
            }
            update[i] = current;
        }
        
        current = current->next[0];
        if (current != nodeToDelete) {
            return end();
        }
        
        for (int i = 0; i < currentLevel; i++) {
            if (update[i]->next[i] == nodeToDelete) {
                update[i]->next[i] = nodeToDelete->next[i];
            }
        }
        
        delete nodeToDelete;
        m_size--;
        
        while (currentLevel > 1 && head->next[currentLevel - 1] == nullptr) {
            currentLevel--;
        }
        
        return next;
    }
    //удаление по значению
    bool erase(const T& value) {
        auto it = find(value);
        if (it == end()) return false;
        erase(it);
        return true;
    }
    //удаление диапазона
    iterator erase(iterator first, iterator last) {
        iterator it = first;
        while (it != last) {
            it = erase(it);
        }
        return last;
    }
    //удалить все элементы со значением
    size_t erase_all(const T& value) {
        size_t removed = 0;
        auto it = find(value);
        while (it != end() && equal(*it, value)) {
            it = erase(it);
            removed++;
        }
        return removed;
    }
    //обычный конструктор
    SkipList(int maxLvl = 16, float prob = 0.5)
        : maxLevel(maxLvl), probability(prob), currentLevel(1), m_size(0) {
        head = new Node(T(), maxLevel);
        head->count = 0;
    }
    //конструктор по итераторам
    template <typename Iter>
    SkipList(Iter start, Iter end, int maxLvl = 16, float prob = 0.5)
        : SkipList(maxLvl, prob) {
        for (Iter i = start; i != end; ++i) {
            insert(*i);
        }
    }
    //конструктор копирования
    SkipList(const SkipList& other)
        : maxLevel(other.maxLevel), probability(other.probability),
          currentLevel(1), m_size(0), comp(other.comp) {
        head = new Node(T(), maxLevel);
        head->count = 0;
        Node* current = other.head->next[0];
        while (current != nullptr){
            for (int i = 0; i < current->count; i++) {
                insert(current->data);
            }
            current = current->next[0];
        }
    }
    //конструктор перемещения
    SkipList(SkipList&& other) noexcept
        : head(other.head),
          maxLevel(other.maxLevel),
          probability(other.probability),
          currentLevel(other.currentLevel),
          m_size(other.m_size),
          comp(std::move(other.comp)) {
        other.head = nullptr;
        other.currentLevel = 1;
        other.m_size = 0;
    }
    //очищение
    void clear() noexcept {
        if (head == nullptr) return;
        Node* current = head->next[0];
        while (current != nullptr) {
            Node* next = current->next[0];
            delete current;
            current = next;
        }
        for (int i = 0; i != maxLevel; i++) {
            head->next[i] = nullptr;
        }
        head->count = 0;
        currentLevel = 1;
        m_size = 0;
    }
    //опреатор присваивания копированием
    SkipList& operator=(const SkipList& other) {
        if (this != &other) {
            clear();
            maxLevel = other.maxLevel;
            probability = other.probability;
            comp = other.comp;
            
            Node* current = other.head->next[0];
            while (current != nullptr) {
                for (int i = 0; i < current->count; i++) {
                    insert(current->data);
                }
                current = current->next[0];
            }
        }
        return *this;
    }
    //оператор присваивания перемещением
    SkipList& operator=(SkipList&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            maxLevel = other.maxLevel;
            probability = other.probability;
            currentLevel = other.currentLevel;
            m_size = other.m_size;
            comp = std::move(other.comp);
            
            other.head = nullptr;
            other.currentLevel = 1;
            other.m_size = 0;
        }
        return *this;
    }
    //пустота и размер
    bool empty() const {
        return head == nullptr || head->next[0] == nullptr;
    }
    
    size_t size() const {
        return m_size;
    }
    //деструктор
    ~SkipList() {
        clear();
    }
};

//генератор чисео
std::vector<int> generateRandomNumbers(int count) {
    std::vector<int> numbers;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 1000000);
    
    for (int i = 0; i < count; ++i) {
        numbers.push_back(dist(gen));
    }
    return numbers;
}
//замер времени
double measureTime(auto func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    return duration.count();
}

//тестирования помогли написать друзья
int main() {
    std::cout << "===============================================\n";
    std::cout << "     ТЕСТИРОВАНИЕ СПИСКА С ПРОПУСКАМИ\n";
    std::cout << "===============================================\n";
    
    // Часть 1: Демонстрация работы с повторяющимися элементами
    std::cout << "\n--- ЧАСТЬ 1: Демонстрация работы с повторениями ---\n";
    SkipList<int> demoList;
    
    demoList.insert(10);
    demoList.insert(20);
    demoList.insert(10);
    demoList.insert(30);
    demoList.insert(10);
    demoList.insert(20);
    
    std::cout << "Размер списка (с учетом повторений): " << demoList.size() << std::endl;
    std::cout << "count(10) = " << demoList.count(10) << std::endl;
    std::cout << "count(20) = " << demoList.count(20) << std::endl;
    std::cout << "count(30) = " << demoList.count(30) << std::endl;
    
    std::cout << "Элементы: ";
    for (auto it = demoList.begin(); it != demoList.end(); ++it) {
        std::cout << *it << "(" << it.getCount() << ") ";
    }
    std::cout << std::endl;
    
    // Часть 2: Тестирование асимптотической сложности
    std::cout << "\n--- ЧАСТЬ 2: Тестирование асимптотической сложности ---\n";
    
    std::vector<int> sizes = {1000, 5000, 10000, 50000};
    std::vector<float> probabilities = {0.5};
    
    std::cout << std::setw(10) << "p"
              << std::setw(10) << "Размер"
              << std::setw(15) << "Вставка(ms)"
              << std::setw(15) << "Поиск(ms)"
              << std::setw(15) << "Удаление(ms)"
              << std::setw(15) << "log2(n)" << std::endl;
    std::cout << std::string(80, '-') << std::endl;
    
    for (float p : probabilities) {
        for (int size : sizes) {
            auto numbers = generateRandomNumbers(size);
            
            // Создаем список с заданной вероятностью p
            SkipList<int> list(16, p);
            
            // Тест вставки
            double insertTime = measureTime([&]() {
                for (int num : numbers) {
                    list.insert(num);
                }
            });
            
            // Тест поиска
            double searchTime = measureTime([&]() {
                for (int num : numbers) {
                    list.find(num);
                }
            });
            
            // Тест удаления
            double deleteTime = measureTime([&]() {
                for (int num : numbers) {
                    list.erase(num);
                }
            });
            
            double logN = std::log2(size);
            
            std::cout << std::setw(10) << p
                      << std::setw(10) << size
                      << std::setw(15) << std::fixed << std::setprecision(2) << insertTime
                      << std::setw(15) << searchTime
                      << std::setw(15) << deleteTime
                      << std::setw(15) << std::setprecision(2) << logN << std::endl;
        }
    }
    return 0;
}
