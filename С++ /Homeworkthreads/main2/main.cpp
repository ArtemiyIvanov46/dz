#include <iostream>
#include <vector>
#include <stdexcept>
#include <random>
#include <thread>
#include <chrono>

class Matrix {
private:
    std::vector<std::vector<int>> data_;
    std::size_t rows_;
    std::size_t cols_;

public:
    Matrix(std::size_t n, std::size_t m)
        : data_(n, std::vector<int>(m, 0)), rows_(n), cols_(m) {}

    Matrix(const std::vector<std::vector<int>>& data)
        : data_(data), rows_(data.size()), cols_(data.empty() ? 0 : data[0].size()) {}

    std::size_t rows() const { return rows_; }
    std::size_t cols() const { return cols_; }

    std::vector<int>& operator[](std::size_t i) {
        return data_[i];
    }

    const std::vector<int>& operator[](std::size_t i) const {
        return data_[i];
    }

    Matrix operator*(const Matrix& other) const {
        if (cols_ != other.rows_) {
            throw std::invalid_argument("Нельзя умножить матрицы: несовместимые размеры");
        }

        Matrix result(rows_, other.cols_);

        for (std::size_t i = 0; i < rows_; ++i) {
            for (std::size_t j = 0; j < other.cols_; ++j) {
                for (std::size_t k = 0; k < cols_; ++k) {
                    result[i][j] += data_[i][k] * other[k][j];
                }
            }
        }

        return result;
    }

    Matrix operator~() const {
        Matrix result(cols_, rows_);

        for (std::size_t i = 0; i < rows_; ++i) {
            for (std::size_t j = 0; j < cols_; ++j) {
                result[j][i] = data_[i][j];
            }
        }

        return result;
    }
    
    
    
    Matrix parallel_multiply(const Matrix& other, int num_threads) const {
        if (cols_ != other.rows_) {
            throw std::invalid_argument("Нельзя умножить матрицы: несовместимые размеры");
        }
        if (num_threads <= 0) {
            throw std::invalid_argument("Количество потоков должно быть положительным");
        }
        Matrix other_t = ~other;
        Matrix result(rows_, other.cols_);
        if (num_threads > static_cast<int>(rows_)) {
            num_threads = static_cast<int>(rows_);
        }
        std::vector<std::thread> threads;
        threads.reserve(num_threads);
        for (int t = 0; t < num_threads; ++t) {
            std::size_t row_begin = rows_ * t / num_threads;
            std::size_t row_end   = rows_ * (t + 1) / num_threads;
            threads.emplace_back([this, &other_t, &result, row_begin, row_end]() {
                for (std::size_t i = row_begin; i < row_end; ++i) {
                    for (std::size_t j = 0; j < other_t.rows_; ++j) {
                        int sum = 0;
                        for (std::size_t k = 0; k < cols_; ++k) {
                            sum += data_[i][k] * other_t[j][k];
                        }
                        result[i][j] = sum;
                    }
                }
            });
        }
        for (auto& th : threads) {
            th.join();
        }
        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
        for (std::size_t i = 0; i < matrix.rows_; ++i) {
            for (std::size_t j = 0; j < matrix.cols_; ++j) {
                os << matrix[i][j] << ' ';
            }
            os << '\n';
        }
        return os;
    }
    static Matrix multiply_using_transposed(const Matrix& a, const Matrix& b_transposed) {
            if (a.cols_ != b_transposed.cols_) {
                throw std::invalid_argument("Несовместимые размеры матриц");
            }
            Matrix result(a.rows_, b_transposed.rows_);
            for (std::size_t i = 0; i < a.rows_; ++i) {
                for (std::size_t j = 0; j < b_transposed.rows_; ++j) {
                    for (std::size_t k = 0; k < a.cols_; ++k) {
                        result[i][j] += a[i][k] * b_transposed[j][k];
                    }
                }
            }
            return result;
        }
};
    Matrix random_matrix(std::size_t n, std::size_t m) {
        Matrix mat(n, m);
        std::mt19937 gen(42);
        std::uniform_real_distribution<double> dist(0.0, 1.0);
        for (std::size_t i = 0; i < n; ++i) {
            for (std::size_t j = 0; j < m; ++j) {
                mat[i][j] = dist(gen);
            }
        }
        return mat;
    }

int main() {
    Matrix A = random_matrix(500, 500);
    Matrix B = random_matrix(500, 500);

    auto start1 = std::chrono::high_resolution_clock::now();
    Matrix C1 = A * B;
    auto end1 = std::chrono::high_resolution_clock::now();

    auto start2 = std::chrono::high_resolution_clock::now();
    Matrix Bt = ~B;
    Matrix C2 = Matrix::multiply_using_transposed(A, Bt);
    auto end2 = std::chrono::high_resolution_clock::now();

    int num_threads = 4;
    auto start3 = std::chrono::high_resolution_clock::now();
    Matrix C3 = A.parallel_multiply(B, num_threads);
    auto end3 = std::chrono::high_resolution_clock::now();

    auto time1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1).count();
    auto time2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count();
    auto time3 = std::chrono::duration_cast<std::chrono::milliseconds>(end3 - start3).count();

    std::cout << "Прямое умножение: " << time1 << " ms\n";
    std::cout << "С транспонированием: " << time2 << " ms\n";
    std::cout << "Параллельное умножение: " << time3 << " ms\n";
}
