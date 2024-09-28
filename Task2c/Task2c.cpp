#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_set>
#include <random>
#include <SFML/Graphics.hpp>

using namespace std;

bool isPrime(long long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

long long nextPrime(long long n) {
    while (!isPrime(n)) {
        n++;
    }
    return n;
}

vector<int> BBS(long long p, long long q, long long seed, int length) {
    long long M = p * q;
    long long x = (seed * seed) % M;
    vector<int> randomBits;

    for (int i = 0; i < length; ++i) {
        x = (x * x) % M;
        randomBits.push_back(x % 2);
    }

    return randomBits;
}

void frequencyTest(const vector<int>& sequence) {
    int ones = 0;
    int zeros = 0;

    for (int bit : sequence) {
        if (bit == 1) ones++;
        else zeros++;
    }

    cout << "Частотный тест:\n";
    cout << "Единицы: " << ones << "\n";
    cout << "Нули: " << zeros << "\n";
}

void runsTest(const vector<int>& sequence) {
    int currentRun = 1;
    int runsOfOnes = 0, runsOfZeros = 0;

    for (size_t i = 1; i < sequence.size(); ++i) {
        if (sequence[i] == sequence[i - 1]) {
            currentRun++;
        }
        else {
            if (sequence[i - 1] == 1) runsOfOnes++;
            else runsOfZeros++;
            currentRun = 1;
        }
    }

    cout << "Тест на последовательности:\n";
    cout << "Последовательности единиц: " << runsOfOnes << "\n";
    cout << "Последовательности нулей: " << runsOfZeros << "\n";
}

int findPeriod(const vector<int>& sequence) {
    unordered_set<int> seen;
    for (int i = 0; i < sequence.size(); ++i) {
        int val = sequence[i];
        if (seen.find(val) != seen.end()) {
            return i;
        }
        seen.insert(val);
    }
    return -1;
}


vector<pair<double, double>> generate2DNormalDistribution(int numPoints, double mean, double stddev) {
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<> dist(mean, stddev);

    vector<pair<double, double>> points;
    for (int i = 0; i < numPoints; ++i) {
        double x = dist(gen);
        double y = dist(gen);
        points.push_back({ x, y });
    }

    return points;
}

int main() {

    setlocale(LC_ALL, "ru");

    long long p = 104729;
    long long q = 105013;

    p = nextPrime(p);
    q = nextPrime(q);

    long long seed = 7;
    int length = 10;

    vector<int> randomSequence = BBS(p, q, seed, length);

    cout << "Сгенерированная последовательность бит: ";
    for (int bit : randomSequence) {
        cout << bit;
    }
    cout << endl;

    frequencyTest(randomSequence);
    runsTest(randomSequence);

    int period = findPeriod(randomSequence);
    if (period == -1) {
        cout << "Период не найден в рамках последовательности длиной " << length << endl;
    }
    else {
        cout << "Длина периода: " << period << endl;
    }

    vector<pair<double, double>> points = generate2DNormalDistribution(1000, 0.0, 1.0);
   
    sf::RenderWindow window(sf::VideoMode(800, 800), "2D Normal Distribution");
    
    double scale = 100.0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        
        window.clear(sf::Color::White);

        for (const auto& point : points) {
            sf::CircleShape dot(2);
            dot.setFillColor(sf::Color::Black);
            
            dot.setPosition(400 + point.first * scale, 400 + point.second * scale);
            window.draw(dot);
        }

        
        window.display();
    }

    return 0;
}
