// AlgoritmoLRU.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <Windows.h>
#include <time.h>

#define PRINT(x) std::cout << x << " ";

void PRINT_MATRIX();

template<typename C, typename T>
bool contains(C&& c, T e) {
    return std::find(std::begin(c), std::end(c), e) != std::end(c);
};

const char P[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', '-'}; //0-9
int R1[30];
int M[5][30];
int LRU[5] = {10, 10, 10, 10, 10};
int C1[6] = {0, 1, 2, 3, 4, 5};

enum PROCESO {
    A, B, C, D, E, F, G, H, I, J
};

void init() {
    int rand;
    for(int r = 0; r < 5; r++) {
        for(int c = 0; c < 30; c++) {
            M[r][c] = 10;
        }
    }
    for(int i = 0; i < 30; i++) {
        rand = std::rand() % 10;
        R1[i] = rand;
    }
};

int main() {
    srand(time(NULL));
    int target, faults = 0, temp;
    bool check = true, flag = false;
    init();
    for(int c = 0; c < 30; c++) {
        if(contains(LRU, R1[c])) {
            for(int i = 4; i != 0; i--) {
                if(LRU[i] == R1[c]) {
                    temp = LRU[i - 1];
                    LRU[i - 1] = LRU[i];
                    LRU[i] = temp;
                }
            }
        }
        else {
            faults++;
            target = LRU[4];
            for(int i = 4; i != 0; i--) {
                LRU[i] = LRU[i - 1];
            }
            LRU[0] = R1[c];
        }
        for(int r = 0; r < 5; r++) {
            if(c == 0) {
                if(r == 0) {
                    M[0][0] = R1[0];
                }
            }
            else if(contains(LRU, M[r][c - 1]) && M[r][c - 1] != 10) {
                M[r][c] = M[r][c - 1];
            }
            else if(check) {
                check = false;
                for(int i = 0; i < r; i++) {
                    if(LRU[0] == M[i][c]) {
                        flag = true;
                    }
                }
                if(!flag) {
                    M[r][c] = LRU[0];
                }
            }
        }
        flag = false;
        check = true;
    }
    PRINT_MATRIX();
    PRINT("Fallas:");
    PRINT(faults);
    std::cout << std::endl;
    PRINT("Rendimiento:");
    PRINT((double) ((faults / 30.0) * 100));
    std::cout << std::endl;
    return 0;
}

void PRINT_MATRIX() {
    std::cout << std::endl;
    PRINT(C1[0])
    for(int i : R1) {
        PRINT(P[PROCESO(i)]);
    }
    std::cout << std::endl;
    for(int r = 0; r < 5; r++) {
        PRINT(C1[r + 1]);
        for(int c = 0; c < 30; c++) {
            PRINT(P[M[r][c]]);
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
