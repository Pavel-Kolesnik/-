// Лаб 1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <iostream>
#include <cstring>
#include <stdio.h>
using namespace std;

const int m = 5;
const int n = 6;

//Начальная матрица
int a[m][n] = {{8,  12, 4,  9,  10, 60},
               {7,  5,  15, 3,  6,  40},
               {9,  4,  6,  12, 7, 100},
               {5,  3,  2,  6,  4,  50},
               {30, 80, 65, 35, 40,  0}};

//Матрица для распределения товаров
int arr2[m][n] = {{0,  0,  0,  0,  0,  60},
                  {0,  0,  0,  0,  0,  40},
                  {0,  0,  0,  0,  0, 100},
                  {0,  0,  0,  0,  0,  50},
                  {30, 80, 65, 35, 40,  0}};

void SearchSum(int arr[m][n]) {
    int sum = 0;
    for (int i = 0; i < m - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (arr[i][j] != 0) sum = sum + arr[i][j] * a[i][j];
        }
    }
    cout << endl;
    cout << "Price = " << sum << " $" << endl;
    cout << endl;
}

void InitializationArray(int arr[m][m][n]) {
    for (int z = 0; z < m; z++) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                arr[z][i][j] = a[i][j];
            }
        }
    }
}

void OutputMatrix(int arr[m][n]) {
    for (int i = 0; i < m; i++) {
        if (i != m - 1) {
            for (int j = 0; j < n; j++) {
                cout.width(3);
                if (j == n - 2) cout << arr[i][j] << "| ";
                else {
                    cout << arr[i][j] << " ";
                }
            }
            cout << endl;
        }
        else {
            cout << "------------------------" << endl;
            for (int j = 0; j < n; j++) {
                cout.width(3);
                cout << arr[i][j] << " ";
            }
        }
    }
    cout << endl;
}

void ZeroProductMatrix(int arr[m][n]) {
    for (int i = 0; i < m - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            arr[i][j] = 0;
        }
    }
}

int main() {
    cout << "Start matrix:" << endl;
    OutputMatrix(a);
    cout << endl;
    //Метод северо-западного угла
    cout << "Metod N-W ygla:" << endl;
    for (int j = 0; j < n; j++) {
        int k = 0;
        for (int i = 0; i < m; i++) {
            if (arr2[i][n - 1] == arr2[m - 1][j]) {
                arr2[i][j] = arr2[i][n - 1];
                arr2[i][n - 1] = 0;
                j = j + 1;
            }
            if (arr2[i][n - 1] < arr2[m - 1][j]) {
                arr2[i][j] = arr2[i][n - 1];
                k = k + arr2[i][j];
                arr2[i][n - 1] = arr2[i][n - 1] - arr2[i][j];
                if (k == arr2[m - 1][j]) j = j + 1;
            }
            if (arr2[i][n - 1] > arr2[m - 1][j]) {
                if (k == 0) {
                    arr2[i][j] = arr2[m - 1][j];
                    arr2[i][n - 1] = arr2[i][n - 1] - arr2[i][j];
                    i = i - 1;
                    j = j + 1;
                }
                else if (k != 0) {
                    arr2[i][j] = arr2[m - 1][j] - k;
                    arr2[i][n - 1] = arr2[i][n - 1] - arr2[i][j];
                    k = 0;
                    i = i - 1;
                    j = j + 1;
                }
            }
        }
    }
    OutputMatrix(arr2);
    SearchSum(arr2);
    ZeroProductMatrix(arr2);
    //Метод наименьшей стоимости
    cout << "Metod min price:" << endl;
    int arr3[m][m][n];
    InitializationArray(arr3);
    for (int z = 0; z < m; z++) {
        int min = arr3[z][0][0];
        int nom = 0;
        for (int j = 0; j < n - 1; j++) {
            for (int i = 0; i < m - 1; i++) {
                if ((arr3[z][i][j] < min) && (arr3[z][m - 1][j] != 0) && (arr3[z][i][n - 1] != 0)) {
                    min = arr3[z][i][j];
                    nom = j;
                }
            }
        }
        int nom_ex = -1;
        if (min == arr3[z][0][0]) {
            int max = min;
            for (int j = 0; j < n - 1; j++) {
                for (int i = 0; i < m - 1; i++) {
                    if ((arr3[z][i][j] > max) && (arr3[z][m - 1][j] != 0) && (arr3[z][i][n - 1] != 0)) {
                        max = arr3[z][i][j];
                        nom_ex = j;
                        nom = nom_ex;
                    }
                }
            }
            min = max;
            for (int j = 0; j < n - 1; j++) {
                for (int i = 0; i < m - 1; i++) {
                    if ((arr3[z][i][j] < min) && (arr3[z][m - 1][j] != 0) && (arr3[z][i][n - 1] != 0)) {
                        min = arr3[z][i][j];
                        nom_ex = j;
                        nom = nom_ex;
                    }
                }
            }
        }
        int k = 0;
        for (int p = 0; p < m - 1; p++) {
            int min_k = arr3[z][0][nom];
            if (k < arr3[z][m - 1][nom]) {
                if (nom == nom_ex) {
                    for (int i = 0; i < m - 1; i++) if (arr3[z][i][n - 1] != 0) min_k = arr3[z][i][nom];
                }
                for (int i = 0; i < m - 1; i++) {
                    if ((arr3[z][i][nom] < min_k) && (arr3[z][i][n - 1] != 0)) min_k = arr3[z][i][nom];
                }
                for (int i = 0; i < m - 1; i++) {
                    if (arr3[z][i][nom] == min_k) {
                        if (k == 0) {
                            k = k + arr3[z][i][n - 1];
                            if (arr3[z][i][n - 1] <= arr3[z][m - 1][nom]) {
                                arr3[z][i][nom] = arr3[z][i][n - 1];
                                arr2[i][nom] = arr3[z][i][nom];
                                arr3[z][i][n - 1] = 0;
                            }
                            if (arr3[z][i][n - 1] > arr3[z][m - 1][nom]) {
                                arr3[z][i][nom] = arr3[z][m - 1][nom];
                                arr2[i][nom] = arr3[z][i][nom];
                                arr3[z][i][n - 1] = arr3[z][i][n - 1] - arr3[z][i][nom];
                            }
                        }
                        else if ((k + arr3[z][i][n - 1] <= arr3[z][m - 1][nom]) && (arr3[z][i][n - 1] != 0)) {
                            k = k + arr3[z][i][n - 1];
                            arr3[z][i][nom] = arr3[z][i][n - 1];
                            arr2[i][nom] = arr3[z][i][nom];
                            arr3[z][i][n - 1] = 0;
                            k = k + arr3[z][i][n - 1];
                        }
                        else if ((k + arr3[z][i][n - 1] > arr3[z][m - 1][nom]) && (arr3[z][i][n - 1] != 0)) {
                            arr3[z][i][nom] = arr3[z][m - 1][nom] - k;
                            arr2[i][nom] = arr3[z][i][nom];
                            k = k + arr3[z][i][n - 1];
                            arr3[z][i][n - 1] = arr3[z][i][n - 1] - arr3[z][i][nom];
                        }
                    }
                }
            }
        }
        int t = 0;
        if (k < arr3[z][m - 1][nom]) {
            int max = arr3[z][0][nom];
            for (int i = 0; i < m - 1; i++) {
                if ((arr3[z][i][nom] > max) && (arr3[z][i][n - 1] != 0)) {
                    max = arr3[z][i][nom];
                    t = i;
                }
            }
            int min_k = max;
            for (int i = 0; i < m - 1; i++) {
                if ((arr3[z][i][nom] < min_k) && (arr3[z][i][n - 1] != 0)) {
                    min_k = arr3[z][i][nom];
                    t = i;
                }
            }
            if ((k + arr3[z][t][n - 1] <= arr3[z][m - 1][nom]) && (arr3[z][t][n - 1] != 0)) {
                k = k + arr3[z][t][n - 1];
                min_k = arr3[z][t][n - 1];
                arr2[t][nom] = min_k;
                arr3[z][t][n - 1] = 0;
                k = k + arr3[z][t][n - 1];
            }
            else if ((k + arr3[z][t][n - 1] > arr3[z][m - 1][nom]) && (arr3[z][t][n - 1] != 0)) {
                min_k = arr3[z][m - 1][nom] - k;
                arr2[t][nom] = min_k;
                k = k + arr3[z][t][n - 1];
                arr3[z][t][n - 1] = arr3[z][t][n - 1] - arr3[z][t][nom];
            }
        }
        arr3[z][m - 1][nom] = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (z != m - 1) arr3[z + 1][i][j] = arr3[z][i][j];
            }
        }
    }
    OutputMatrix(arr2);
    SearchSum(arr2);
    ZeroProductMatrix(arr2);
    //Метод штрафов   
    cout << "Metod shtrafov:" << endl;
    InitializationArray(arr3);
    int k = 0;
    int arr_s[m - 1];
    int arr_k[n - 1];
    int arrmin_s[m - 1];
    int arrmin_k[n - 1];
    int nom = 0;
    for (int z = 0; z < m; z++) {      
        int nom_s = 0;
        int nom_k = 0;
        int pos = 0;
        for (int i = 0; i < m - 1; i++) arrmin_s[i] = 0;
        for (int j = 0; j < n - 1; j++) arrmin_k[j] = 0;
        int kol_null_s = 0, kol_null_k = 0;
        for (int i = 0; i < m - 1; i++) {
            if (arr3[z][i][n - 1] == 0) kol_null_s = kol_null_s + 1;
        }
        for (int j = 0; j < n - 1; j++) {       
            if (arr3[z][m - 1][j] == 0) kol_null_k = kol_null_k + 1;
        }
        if (z != 0) cout << endl;
        if ((kol_null_s < 3) && (kol_null_k < 4)) {
            nom = nom + 1;
            cout << "Shtrafi strok " << nom << ": ";
            for (int i = 0; i < m - 1; i++) {
                int min_s = arr3[z][i][0];
                if (arr3[z][m - 1][0] == 0) {
                    int max = min_s;
                    for (int j = 0; j < n - 1; j++) {
                        if ((arr3[z][i][j] > max) && (arr3[z][m - 1][j] != 0)) max = arr3[z][i][j];
                    }
                    min_s = max;
                    for (int j = 0; j < n - 1; j++) {
                        if ((arr3[z][i][j] < min_s) && (arr3[z][m - 1][j] != 0)) min_s = arr3[z][i][j];
                    }
                }
                else if (arr3[z][m - 1][0] != 0) {
                    for (int j = 0; j < n - 1; j++) {
                        if ((arr3[z][i][j] < min_s) && (arr3[z][m - 1][j] != 0)) min_s = arr3[z][i][j];
                    }
                }
                for (int j = 0; j < n - 1; j++) {
                    if (arr3[z][m - 1][j] != 0) arr3[z][i][j] = arr3[z][i][j] - min_s;
                }
                min_s = arr3[z][i][0];
                if ((arr3[z][m - 1][0] == 0) || (min_s == 0)) {
                    int max = min_s;
                    for (int j = 0; j < n - 1; j++) {
                        if ((arr3[z][i][j] > max) && (arr3[z][m - 1][j] != 0)) max = arr3[z][i][j];
                    }
                    min_s = max;
                    for (int j = 0; j < n - 1; j++) {
                        if ((arr3[z][i][j] < min_s) && (arr3[z][i][j] != 0) && (arr3[z][m - 1][j] != 0)) min_s = arr3[z][i][j];
                    }
                }
                else if ((arr3[z][m - 1][0] != 0) && (min_s != 0)) {
                    for (int j = 0; j < n - 1; j++) {
                        if ((arr3[z][i][j] < min_s) && (arr3[z][i][j] != 0) && (arr3[z][m - 1][j] != 0)) min_s = arr3[z][i][j];
                    }
                }
                if (arr3[z][i][n - 1] == 0) min_s = 0;
                arr_s[i] = min_s;
                cout << arr_s[i] << " ";
            }
            int max_s = arr_s[0];
            for (int i = 0; i < m - 1; i++) {
                if (arr_s[i] > max_s) {
                    max_s = arr_s[i];
                    nom_s = i;
                }
            }
            if (z == 0) {
                for (int i = 0; i < m - 1; i++) {
                    for (int j = 0; j < n - 1; j++) {
                        arr3[z][i][j] = a[i][j];
                    }
                }
            }
            else {
                for (int i = 0; i < m - 1; i++) {
                    for (int j = 0; j < n - 1; j++) {
                        arr3[z][i][j] = arr3[z - 1][i][j];
                    }
                }
            }
            int kol = 0;
            for (int i = 0; i < m - 1; i++) {
                if (arr_s[i] == max_s) {
                    pos = i;
                    int min_s = arr3[z][pos][0];
                    for (int j = 0; j < n - 1; j++) {
                        if ((arr3[z][pos][j] < min_s) && (arr3[z][m - 1][j] != 0)) {
                            min_s = arr3[z][pos][j];
                        }
                    }
                    arrmin_s[i] = min_s;
                    kol = kol + 1;
                }
            }
            cout << endl;
            if (kol > 1) {
                int need_min_s = 1000000;
                for (int i = 0; i < m - 1; i++) {
                    if ((arrmin_s[i] < need_min_s) && (arrmin_s[i] != 0)) {
                        need_min_s = arrmin_s[i];
                        nom_s = i;
                    }
                }
            }
            cout << "Strafi stolbcov " << nom << ": ";
            for (int j = 0; j < n - 1; j++) {
                int min_k = arr3[z][0][j];
                if (arr3[z][0][n - 1] == 0) {
                    int max = min_k;
                    for (int i = 0; i < m - 1; i++) {
                        if ((arr3[z][i][j] > max) && (arr3[z][i][n - 1] != 0)) max = arr3[z][i][j];
                    }
                    min_k = max;
                    for (int i = 0; i < m - 1; i++) {
                        if ((arr3[z][i][j] < min_k) && (arr3[z][i][n - 1] != 0)) min_k = arr3[z][i][j];
                    }
                }
                else if (arr3[z][0][n - 1] != 0) {
                    for (int i = 0; i < m - 1; i++) {
                        if ((arr3[z][i][j] < min_k) && (arr3[z][i][n - 1] != 0)) min_k = arr3[z][i][j];
                    }
                }
                for (int i = 0; i < m - 1; i++) {
                    if (arr3[z][i][n - 1] != 0) arr3[z][i][j] = arr3[z][i][j] - min_k;
                }
                min_k = arr3[z][0][j];
                if ((arr3[z][0][n - 1] == 0) || (min_k == 0)) {
                    int max = min_k;
                    for (int i = 0; i < m - 1; i++) {
                        if ((arr3[z][i][j] > max) && (arr3[z][i][n - 1] != 0)) max = arr3[z][i][j];
                    }
                    min_k = max;
                    for (int i = 0; i < m - 1; i++) {
                        if ((arr3[z][i][j] < min_k) && (arr3[z][i][j] != 0) && (arr3[z][i][n - 1] != 0)) min_k = arr3[z][i][j];
                    }
                }
                else if ((arr3[z][0][n - 1] != 0) && (min_k != 0)) {
                    for (int i = 0; i < m - 1; i++) {
                        if ((arr3[z][i][j] < min_k) && (arr3[z][i][j] != 0) && (arr3[z][i][n - 1] != 0)) min_k = arr3[z][i][j];
                    }
                }
                if (arr3[z][m - 1][j] == 0) min_k = 0;
                arr_k[j] = min_k;
                cout << arr_k[j] << " ";
            }
            cout << endl;
            int max_k = arr_k[0];
            for (int j = 0; j < n - 1; j++) {
                if (arr_k[j] > max_k) {
                    max_k = arr_k[j];
                    nom_k = j;
                }
            }
            if (z == 0) {
                for (int i = 0; i < m - 1; i++) {
                    for (int j = 0; j < n - 1; j++) {
                        arr3[z][i][j] = a[i][j];
                    }
                }
            }
            else {
                for (int i = 0; i < m - 1; i++) {
                    for (int j = 0; j < n - 1; j++) {
                        arr3[z][i][j] = arr3[z - 1][i][j];
                    }
                }
            }
            kol = 0;
            for (int j = 0; j < n - 1; j++) {
                if (arr_k[j] == max_k) {
                    pos = j;
                    int min_k = arr3[z][0][pos];
                    for (int i = 0; i < m - 1; i++) {
                        if ((arr3[z][i][pos] < min_k) && (arr3[z][i][n - 1] != 0)) {
                            min_k = arr3[z][i][pos];
                        }
                    }
                    arrmin_k[j] = min_k;
                    kol = kol + 1;
                }
            }
            if (kol > 1) {
                int need_min_k = 1000000;
                for (int j = 0; j < n - 1; j++) {
                    if ((arrmin_k[j] < need_min_k) && (arrmin_k[j] != 0)) {
                        need_min_k = arrmin_k[j];
                        nom_k = j;
                    }
                }
            }
            int t = 0;
            int min_s = arr3[z][nom_s][0];
            int min_k = arr3[z][0][nom_k];
            int min = 0;
            if (max_s == max_k) {
                if (arr3[z][m - 1][0] == 0) {
                    int max = min_s;
                    for (int j = 0; j < n - 1; j++) {
                        if ((arr3[z][nom_s][j] > max) && (arr3[z][m - 1][j] != 0)) max = arr3[z][nom_s][j];
                    }
                    min_s = max;
                    for (int j = 0; j < n - 1; j++) {
                        if ((arr3[z][nom_s][j] < min_s) && (arr3[z][m - 1][j] != 0)) min_s = arr3[z][nom_s][j];
                    }
                }
                else if (arr3[z][m - 1][0] != 0) {
                    for (int j = 0; j < n - 1; j++) {
                        if ((arr3[z][nom_s][j] < min_s) && (arr3[z][m - 1][j] != 0)) min_s = arr3[z][nom_s][j];
                    }
                }
                if (arr3[z][0][n - 1] == 0) {
                    int max = min_k;
                    for (int i = 0; i < m - 1; i++) {
                        if ((arr3[z][i][nom_k] > max) && (arr3[z][i][n - 1] != 0)) max = arr3[z][i][nom_k];
                    }
                    min_k = max;
                    for (int i = 0; i < m - 1; i++) {
                        if ((arr3[z][i][nom_k] < min_k) && (arr3[z][i][n - 1] != 0)) min_k = arr3[z][i][nom_k];
                    }
                }
                else if (arr3[z][0][n - 1] != 0) {
                    for (int i = 0; i < m - 1; i++) {
                        if ((arr3[z][i][nom_k] < min_k) && (arr3[z][i][n - 1] != 0)) min_k = arr3[z][i][nom_k];
                    }
                }
                if (min_s <= min_k) min = min_s;
                else if (min_k <= min_s) min = min_k;
            }
            if ((max_s > max_k) || (min == min_s)) {
                int min_s = arr3[z][nom_s][0];
                if (arr3[z][m - 1][0] == 0) {
                    int max = min_s;
                    for (int j = 0; j < n - 1; j++) {
                        if ((arr3[z][nom_s][j] > max) && (arr3[z][m - 1][j] != 0)) {
                            max = arr3[z][nom_s][j];
                            t = j;
                        }
                    }
                    min_s = max;
                    for (int j = 0; j < n - 1; j++) {
                        if ((arr3[z][nom_s][j] < min_s) && (arr3[z][m - 1][j] != 0)) {
                            min_s = arr3[z][nom_s][j];
                            t = j;
                        }
                    }
                }
                else if (arr3[z][m - 1][0] != 0) {
                    for (int j = 0; j < n - 1; j++) {
                        if ((arr3[z][nom_s][j] < min_s) && (arr3[z][m - 1][j] != 0)) {
                            min_s = arr3[z][nom_s][j];
                            t = j;
                        }
                    }
                }
                if (arr3[z][nom_s][n - 1] <= arr3[z][m - 1][t]) {
                    arr3[z][nom_s][t] = arr3[z][nom_s][n - 1];
                    arr2[nom_s][t] = arr3[z][nom_s][t];
                    arr3[z][nom_s][n - 1] = 0;
                    arr3[z][m - 1][t] = arr3[z][m - 1][t] - arr3[z][nom_s][t];
                }
                if (arr3[z][nom_s][n - 1] > arr3[z][m - 1][t]) {
                    arr3[z][nom_s][t] = arr3[z][m - 1][t];
                    arr2[nom_s][t] = arr3[z][nom_s][t];
                    arr3[z][nom_s][n - 1] = arr3[z][nom_s][n - 1] - arr3[z][nom_s][t];
                    arr3[z][m - 1][t] = 0;
                }
            }
            else if ((max_k > max_s) || (min == min_k)) {
                for (int p = 0; p < m - 1; p++) {
                    int min_k = arr3[z][0][nom_k];
                    if (k < arr3[z][m - 1][nom_k]) {
                        for (int i = 0; i < m - 1; i++) {
                            if ((arr3[z][i][nom_k] < min_k) && (arr3[z][i][n - 1] != 0)) min_k = arr3[z][i][nom_k];
                        }
                        for (int i = 0; i < m - 1; i++) {
                            if (arr3[z][i][nom_k] == min_k) {
                                if (k == 0) {
                                    k = k + arr3[z][i][n - 1];
                                    if (arr3[z][i][n - 1] <= arr3[z][m - 1][nom_k]) {
                                        arr3[z][i][nom_k] = arr3[z][i][n - 1];
                                        arr2[i][nom_k] = arr3[z][i][nom_k];
                                        arr3[z][i][n - 1] = 0;
                                    }
                                    if (arr3[z][i][n - 1] > arr3[z][m - 1][nom_k]) {
                                        arr3[z][i][nom_k] = arr3[z][m - 1][nom_k];
                                        arr2[i][nom_k] = arr3[z][i][nom_k];
                                        arr3[z][i][n - 1] = arr3[z][i][n - 1] - arr3[z][i][nom_k];
                                    }
                                }
                                else if ((k + arr3[z][i][n - 1] <= arr3[z][m - 1][nom_k]) && (arr3[z][i][n - 1] != 0)) {
                                    k = k + arr3[z][i][n - 1];
                                    arr3[z][i][nom_k] = arr3[z][i][n - 1];
                                    arr2[i][nom_k] = arr3[z][i][nom_k];
                                    arr3[z][i][n - 1] = 0;
                                    k = k + arr3[z][i][n - 1];
                                }
                                else if ((k + arr3[z][i][n - 1] > arr3[z][m - 1][nom_k]) && (arr3[z][i][n - 1] != 0)) {
                                    arr3[z][i][nom_k] = arr3[z][m - 1][nom_k] - k;
                                    arr2[i][nom_k] = arr3[z][i][nom_k];
                                    k = k + arr3[z][i][n - 1];
                                    arr3[z][i][n - 1] = arr3[z][i][n - 1] - arr3[z][i][nom_k];
                                }
                            }
                        }
                    }
                }
                if (k < arr3[z][m - 1][nom_k]) {
                    int max = arr3[z][0][nom_k];
                    for (int i = 0; i < m - 1; i++) {
                        if ((arr3[z][i][nom_k] > max) && (arr3[z][i][n - 1] != 0)) {
                            max = arr3[z][i][nom_k];
                            t = i;
                        }
                    }
                    int min_k = max;
                    for (int i = 0; i < m - 1; i++) {
                        if ((arr3[z][i][nom_k] < min_k) && (arr3[z][i][n - 1] != 0)) {
                            min_k = arr3[z][i][nom_k];
                            t = i;
                        }
                    }
                    if ((k + arr3[z][t][n - 1] <= arr3[z][m - 1][nom_k]) && (arr3[z][t][n - 1] != 0)) {
                        k = k + arr3[z][t][n - 1];
                        min_k = arr3[z][t][n - 1];
                        arr2[t][nom_k] = min_k;
                        arr3[z][t][n - 1] = 0;
                        k = k + arr3[z][t][n - 1];
                    }
                    else if ((k + arr3[z][t][n - 1] > arr3[z][m - 1][nom_k]) && (arr3[z][t][n - 1] != 0)) {
                        min_k = arr3[z][m - 1][nom_k] - k;
                        arr2[t][nom_k] = min_k;
                        k = k + arr3[z][t][n - 1];
                        arr3[z][t][n - 1] = arr3[z][t][n - 1] - arr3[z][t][nom_k];
                    }
                }
                arr3[z][m - 1][nom_k] = 0;
                k = 0;
            }
        }
        if (z == m - 1) {
            for (int j = 0; j < n; j++) {
                int k = 0;
                if ((k < arr3[z][m - 1][j]) && (arr3[z][m - 1][j] != 0)) {
                    for (int i = 0; i < m; i++) {
                        if (k == 0) {
                            k = k + arr3[z][i][n - 1];
                            if (arr3[z][i][n - 1] <= arr3[z][m - 1][j]) {
                                arr3[z][i][j] = arr3[z][i][n - 1];
                                arr2[i][j] = arr3[z][i][j];
                                arr3[z][i][n - 1] = 0;
                            }
                            if (arr3[z][i][n - 1] > arr3[z][m - 1][j]) {
                                arr3[z][i][j] = arr3[z][m - 1][j];
                                arr2[i][j] = arr3[z][i][j];
                                arr3[z][i][n - 1] = arr3[z][i][n - 1] - arr3[z][i][j];
                            }
                        }
                        else if ((k + arr3[z][i][n - 1] <= arr3[z][m - 1][j]) && (arr3[z][i][n - 1] != 0)) {
                            k = k + arr3[z][i][n - 1];
                            arr3[z][i][j] = arr3[z][i][n - 1];
                            arr2[i][j] = arr3[z][i][j];
                            arr3[z][i][n - 1] = 0;
                            k = k + arr3[z][i][n - 1];
                        }
                        else if ((k + arr3[z][i][n - 1] > arr3[z][m - 1][j]) && (arr3[z][i][n - 1] != 0)) {
                            arr3[z][i][j] = arr3[z][m - 1][j] - k;
                            arr2[i][j] = arr3[z][i][j];
                            k = k + arr3[z][i][n - 1];
                            arr3[z][i][n - 1] = arr3[z][i][n - 1] - arr3[z][i][j];
                        }
                    }
                }
            }
            k = 0;
        }       
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (z != m - 1) arr3[z + 1][i][j] = arr3[z][i][j];
            }
        }
    }
    cout << endl;
    OutputMatrix(arr2);
    SearchSum(arr2);
    ZeroProductMatrix(arr2);
}

