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
            std::cout << "������� ������ ������� N: ";
            std::cin >> n;

            // �������� �� ������ �����
            if (std::cin.fail())
            {
                std::cin.clear();                                   // ������� ������
                std::cin.ignore(32767, '\n');                       // ������� ������ �����
                std::cout << "��� �� �����. ���������� �����. \n";
                continue;                                           // ������� � ��������� �������� �����
            }

            if (n > 0)
            {
                double** matrix = createAndFillMatrix(n);
                printMatrix(matrix, n);
                std::cout << "\033[0;32m������������ �������: \033[0m" << determinant(matrix, n) << std::endl;
                freeMatrix(matrix, n);
                break;
            }
            else {
                std::cout << "����� ������ ���� �������������. ���������� �����. \n";
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
        std::cout << "\033[0;32m������������ �������:\033[0m" << determinant(matrix, crs.numRows) << std::endl;
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
        std::cout << "����������� ������� �� �����: \n";
        std::cout << "----------------------------- \n";
        checkFile();
    }
    return 0;
}

