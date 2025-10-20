#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <chrono>
#include <random>

using namespace std;
using namespace chrono;

// Simple primality check (CPU-bound)
void compute_primes(int limit) {
    vector<int> primes;
    for (int n = 2; n < limit; ++n) {
        bool is_prime = true;
        for (int p : primes) {
            if (n % p == 0) {
                is_prime = false;
                break;
            }
        }
        if (is_prime)
            primes.push_back(n);
    }
    cout << "Primes computed: " << primes.size() << endl;
}

// Random dense matrix multiply (Memory-bound)
void random_matrix_multiply(int n) {
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

    // Intentional cache-unfriendly loop order (i, j, k)
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k)
                C[i][j] += A[i][k] * B[k][j];

    cout << "Matrix multiplication done for size " << n << "x" << n << endl;
}

// I/O-bound section
void write_file(long lines) {
    ofstream out("tempfile.txt");
    for (long i = 0; i < lines; ++i)
        out << "This is line " << i << '\n';
    cout << "File written with " << lines << " lines." << endl;
}

int main() {
    auto start = high_resolution_clock::now();

    cout << "Starting CPU-bound section..." << endl;
    compute_primes(20000);

    cout << "Starting memory-bound section..." << endl;
    random_matrix_multiply(300);

    cout << "Starting I/O-bound section..." << endl;
    write_file(1000000);

    auto end = high_resolution_clock::now();
    duration<double> elapsed = end - start;
    cout << "Total time: " << elapsed.count() << " s\n";
}

