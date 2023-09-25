#pragma once

#include<iostream>

struct CRS {
    double* values;
    int nonZero;
    int numRows;
    int* colIndices;
    int* rowPointers;
};

//Функция для создания и заполнения матрицы с клавиатуры
double** createAndFillMatrix(int n);

//Функция для освобождения памяти
void freeMatrix(double** matrix, int n);

//Функция для вывода матрицы на экран
void printMatrix(double** matrix, int n);

//Функция для нахождения определителя
double determinant(double** matrix, int n);

//Функция для меню
void printMenu();

//Функция для создания и заполнения разреженной матрицы 
CRS createCRS();

//Функция преобразования CRS матрицы в обычную
double** convertCRStoMatrix(const CRS&);

//Функция проверки ввода данных
void checkInput(int);

//Функция для вывода массива А (значений ненулевых элементов)
void printMassA(const CRS);

//Функция для вывода массива LJ (индексов столбцов ненулевых элементов)
void printMassLJ(const CRS);

//Функция для вывода массива LI
void printMassLI(const CRS);

//Функция записи разреженной матрицы в файл
void inputInFile(const CRS);

//Функция чтения разреженной матрицы из файла
void checkFile();