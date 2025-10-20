#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <chrono>
#include <random>
#include <thread>
#include <mutex>

using namespace std;
using namespace chrono;

// ============ CPU-bound: parallel prime computation ============
void compute_primes_segment(int start, int end, vector<int>& results) {
    for (int n = start; n < end; ++n) {
        bool is_prime = true;
        for (int i = 2; i <= sqrt(n); ++i) {
            if (n % i == 0) { is_prime = false; break; }
        }
        if (is_prime) results.push_back(n);
    }
}

void compute_primes_parallel(int limit, int threads) {
    vector<thread> workers;
    vector<vector<int>> partial(threads);
    int chunk = limit / threads;

    for (int t = 0; t < threads; ++t) {
        int start = t * chunk + 2;
        int end   = (t == threads - 1) ? limit : (t + 1) * chunk + 2;
        workers.emplace_back(compute_primes_segment, start, end, ref(partial[t]));
    }
    for (auto& w : workers) w.join();

    size_t total = 0;
    for (auto& p : partial) total += p.size();
    cout << "Primes found: " << total << endl;
}

// ============ Memory-bound: parallel matrix multiplication ============
void matrix_multiply_worker(
        const vector<vector<double>>& A,
        const vector<vector<double>>& B,
        vector<vector<double>>& C,
        int row_start, int row_end) {

    int n = A.size();
    for (int i = row_start; i < row_end; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k)
                C[i][j] += A[i][k] * B[k][j];
}

void random_matrix_multiply_parallel(int n, int threads) {
    vector<vector<double>> A(n, vector<double>(n));
    vector<vector<double>> B(n, vector<double>(n));
    vector<vector<double>> C(n, vector<double>(n, 0.0));

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            A[i][j] = dis(gen);
            B[i][j] = dis(gen);
        }

    vector<thread> workers;
    int rows_per_thread = n / threads;

    for (int t = 0; t < threads; ++t) {
        int start = t * rows_per_thread;
        int end = (t == threads - 1) ? n : (t + 1) * rows_per_thread;
        workers.emplace_back(matrix_multiply_worker, cref(A), cref(B), ref(C), start, end);
    }

    for (auto& w : workers) w.join();
    cout << "Matrix multiplication done for size " << n << "x" << n << endl;
}

// ============ I/O-bound: parallel file writing ============
void write_file_part(const string& filename, long start, long end, mutex& mtx) {
    ofstream out(filename, ios::app);
    for (long i = start; i < end; ++i) {
        lock_guard<mutex> lock(mtx);  // serialize file access
        out << "This is line " << i << '\n';
    }
}

void write_file_parallel(long lines, int threads) {
    mutex file_mutex;
    vector<thread> workers;
    long chunk = lines / threads;
    const string filename = "tempfile.txt";

    // truncate first
    ofstream truncate(filename, ios::trunc);
    truncate.close();

    for (int t = 0; t < threads; ++t) {
        long start = t * chunk;
        long end = (t == threads - 1) ? lines : (t + 1) * chunk;
        workers.emplace_back(write_file_part, cref(filename), start, end, ref(file_mutex));
    }
    for (auto& w : workers) w.join();
    cout << "File written with " << lines << " lines." << endl;
}

// ============ main ============
int main() {
    auto start = high_resolution_clock::now();

    int threads = thread::hardware_concurrency();
    if (threads == 0) threads = 4;  // fallback

    cout << "Using " << threads << " threads.\n";

    cout << "\n[CPU-bound]\n";
    compute_primes_parallel(20000, threads);

    cout << "\n[Memory-bound]\n";
    random_matrix_multiply_parallel(300, threads);

    cout << "\n[I/O-bound]\n";
    write_file_parallel(200000, threads);

    auto end = high_resolution_clock::now();
    duration<double> elapsed = end - start;
    cout << "\nTotal time: " << elapsed.count() << " s\n";
}

