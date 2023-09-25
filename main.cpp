#include <iostream>
#include "Header.h"
int main()
{
    setlocale(LC_ALL, "Rus");
    int n, variant;
    printMenu();
    std::cin >> variant;
    system("cls");
    if (variant == 1)
    {
        while (true)
        {
            std::cout << "Введите размер матрицы N: ";
            std::cin >> n;

            // Проверка на ошибки ввода
            if (std::cin.fail())
            {
                std::cin.clear();                                   // очистка ошибки
                std::cin.ignore(32767, '\n');                       // очистка буфера ввода
                std::cout << "Это не число. Попробуйте снова. \n";
                continue;                                           // переход к следующей итерации цикла
            }

            if (n > 0)
            {
                double** matrix = createAndFillMatrix(n);
                printMatrix(matrix, n);
                std::cout << "\033[0;32mОпределитель матрицы: \033[0m" << determinant(matrix, n) << std::endl;
                freeMatrix(matrix, n);
                break;
            }
            else {
                std::cout << "Число должно быть положительным. Попробуйте снова. \n";
            }
        }
    }
    if (variant == 2)
    {
        CRS crs = createCRS();
        double** matrix = convertCRStoMatrix(crs);
        std::cout << "************** \n";
        printMassA(crs);
        printMassLJ(crs);
        printMassLI(crs);
        printMatrix(matrix, crs.numRows);
        std::cout << "\033[0;32mОпределитель матрицы:\033[0m" << determinant(matrix, crs.numRows) << std::endl;
        delete[] crs.values;
        delete[] crs.colIndices;
        delete[] crs.rowPointers;
        freeMatrix(matrix, crs.numRows);
    }
    
    if (variant == 3)
    {
        CRS crs = createCRS();
        inputInFile(crs);
    }
    if (variant == 4)
    {
        std::cout << "Разреженные матрицы из файла: \n";
        std::cout << "----------------------------- \n";
        checkFile();
    }
    return 0;
}

