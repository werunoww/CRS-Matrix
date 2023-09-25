#include "Header.h"
#include <iostream>
#include <fstream>
#include <string>
//Функция для создания и заполнения матрицы с клавиатуры
double** createAndFillMatrix(int n)
{
    double** matrix = new double* [n];
    for (int i = 0; i < n; ++i)
    {
        matrix[i] = new double[n];
        for (int j = 0; j < n; ++j)
        {
            std::cout << "Введите элемент [" << i << "][" << j << "]: ";
            std::cin >> matrix[i][j];
            if (!std::cin.good())
            {
                std::cout << "Ошибка... Это не число \n";
                exit(-1);
            }
        }
    }
    return matrix;
}


//Функция для освобождения памяти
void freeMatrix(double** matrix, int n)
{
    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

//Функция для вывода матрицы на экран
void printMatrix(double** matrix, int n)
{
    std::cout << "Матрица: \n";
    std::cout << "---------- \n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "---------- \n";
}

//Функция для нахождения определителя
double determinant(double** matrix, int n) {
    if (n == 1)                         //если матрица размера 1х1
    {
        return matrix[0][0];            //то значением определителя является единственный элемент матрицы
    }
    else if (n == 2)                    //если матрица размера 2х2
    {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];   //определитель вычисляется по следующей формуле
    }
    else                                //если матрица размера NxN
    {
        double det = 0;
        for (int i = 0; i < n; ++i)                     //динамически
        {                                               //создаем
            double** minor = new double* [n - 1];       //матрицу
            for (int j = 1; j < n; ++j)                 //для
            {                                           //нахождения
                minor[j - 1] = new double[n - 1];       //минора
                for (int k = 0; k < n; ++k) {
                    if (k < i) {
                        minor[j - 1][k] = matrix[j][k];
                    }
                    else if (k > i) {
                        minor[j - 1][k - 1] = matrix[j][k];
                    }
                }
            }
            det += (i % 2 == 0 ? 1 : -1) * matrix[0][i] * determinant(minor, n - 1);
            //Очищаем память
            freeMatrix(minor, n - 1);
        }
        return det;
    }
}

//Функция для меню
void printMenu()
{
    std::cout << "1. Заполнить обычную матрицу вручную и вычислить её определитель \n";
    std::cout << "2. Заполнить разреженную матрицу CRS и вычислить её определитель\n";
    std::cout << "3. Записать разреженную матрицу CRS в файл \n";
    std::cout << "4. Считать разреженную матрицу CRS из файла и вычислить её определитель\n";
}

//Функция для создания и заполнения разреженной матрицы 
CRS createCRS()
{
    CRS matrix;
    std::cout << "Введите количество строк в матрице: ";
    std::cin >> matrix.numRows;
    checkInput(matrix.numRows);

    std::cout << "Введите количество ненулевых элементов: ";
    std::cin >> matrix.nonZero;
    checkInput(matrix.nonZero);
    if (matrix.nonZero > (matrix.numRows*2))
    {
        std::cout << "\033[0;31mОшибка ввода\033[0m \n";
        exit(-1);
    }

    matrix.values = new double[matrix.nonZero];           //создание массива A
    matrix.colIndices = new int[matrix.nonZero];          //создание массива LJ
    matrix.rowPointers = new int[matrix.numRows + 1];     //создание массива LI

    std::cout << "Введите значения ненулевых элементов: \n";
    for (int i = 0; i < matrix.nonZero; i++)            //заполнение
    {                                                   //массива 
        std::cin >> matrix.values[i];                   //A
        if (!std::cin.good())
        {
            std::cout << "\033[0;31mОшибка ввода\033[0m \n";
            exit(-1);
        }
    }

    std::cout << "Введите индексы столбцов для каждого ненулевого элемента: (первый столбец - ноль) \n";
    for (int i = 0; i < matrix.nonZero; ++i)            //заполнение 
    {                                                   //массива
        std::cin >> matrix.colIndices[i];               //LJ
        checkInput(matrix.colIndices[i]);
    }

    std::cout << "Введите указатели на строки: \n";
    for (int i = 0; i <= matrix.numRows; ++i)           //заполнение
    {                                                   //массива
        std::cin >> matrix.rowPointers[i];              //LI
        checkInput(matrix.rowPointers[i]);
        if (matrix.rowPointers[0] != 0)
        {
            std::cout << "\033[0;31mОшибка ввода... Первый элемент должен быть равен нулю \033[0m \n";
            exit(-1);
        }
    }
    return matrix;
}


//Функция преобразования CRS матрицы в обычную
double** convertCRStoMatrix(const CRS& crs) 
{
    double** matrix = new double* [crs.numRows];
    for (int i = 0; i < crs.numRows; ++i) 
    {
        matrix[i] = new double[crs.numRows]();          // Инициализация нулями
        for (int j = crs.rowPointers[i]; j < crs.rowPointers[i + 1]; ++j) 
        {
            matrix[i][crs.colIndices[j]] = crs.values[j];
        }
    }
    return matrix;
}

void checkInput(int n)
{
    if (!std::cin.good() || n < 0)
    {
        std::cout << "\033[0;31mОшибка ввода\033[0m \n";
        exit(-1);
    }
}

//Функция для вывода массива А (значений ненулевых элементов)
void printMassA(const CRS matrix)
{
    std::cout << "A: ";
    for (int i = 0; i < matrix.nonZero; i++)
    {
        std::cout << matrix.values[i] << " ";
    }
    std::cout << std::endl;
}

//Функция для вывода массива LJ (индексов столбцов ненулевых элементов)
void printMassLJ(const CRS matrix)
{
    std::cout << "LJ: ";
    for (int i = 0; i < matrix.nonZero; i++)
    {
        std::cout << matrix.colIndices[i] << " ";
    }
    std::cout << std::endl;
}

//Функция для вывода массива LI 
void printMassLI(const CRS matrix)
{
    std::cout << "LI: ";
    for (int i = 0; i < (matrix.numRows + 1); i++)
    {
        std::cout << matrix.rowPointers[i] << " ";
    }
    std::cout << std::endl;
}

void inputInFile(CRS crs)
{
    std::ofstream file;               //открываем файл для записи
    file.open("text.txt");
    if (!file.is_open())              //проверка открытия файла
    {
        std::cout << "\033[0;31mОшибка открытия файла\033[0m \n";
    }
    else
    {
        for (int i = 0; i < crs.nonZero; i++)
        {
            file << crs.values[i];
        }
        file << std::endl;

        for (int i = 0; i < crs.nonZero; i++)
        {
            file << crs.colIndices[i];
        }
        file << std::endl;

        for (int i = 0; i < (crs.numRows + 1); i++)
        {
            file << crs.rowPointers[i];
        }
        file << std::endl;
        
        std::cout << "\033[0;32mЗапись сделана!\033[0m";
    }
}

void checkFile()
{
    std::ifstream file;             //открываем файл для чтения
    std::string str, str2;
    file.open("text.txt");
    if (!file.is_open())            //проверка открытия файла
    {
        std::cout << "\033[0;31mОшибка открытия файла\033[0m \n";
    }
    else
    {
        getline(file, str);
        CRS crs{};
        crs.values = new double[str.length()];
        for (int i = 0; i < str.length(); i++)
        {
            char ch = str[i];
            double value = static_cast<double>(ch - '0');
            crs.values[i] = value;
        }
        std::cout << "A: ";
        for (int i = 0; i < str.length(); i++)
        {
            std::cout << crs.values[i] << " ";
        }
        std::cout << std::endl;

        getline(file, str);
        crs.colIndices = new int[str.length()];
        for (int i = 0; i < str.length(); i++)
        {
            crs.colIndices[i] = str[i] - '0';
        }
        std::cout << "LJ: ";
        for (int i = 0; i < str.length(); i++)
        {
            std::cout << crs.colIndices[i] << " ";
        }
        std::cout << std::endl;
        
        getline(file, str);
        crs.rowPointers = new int[str.length()];
        for (int i = 0; i < str.length(); i++)
        {
            crs.rowPointers[i] = str[i] - '0';
        }
        crs.numRows = str.length()-1;
        std::cout << "LI: ";
        for (int i = 0; i < str.length(); i++)
        {
            std::cout << crs.rowPointers[i] << " ";
        }
        std::cout << std::endl;
        double** matrix = convertCRStoMatrix(crs);
        printMatrix(matrix, crs.numRows);
        std::cout << "\033[0;32mОпределитель матрицы: \033[0m" << determinant(matrix, crs.numRows) << std::endl;
    }
}