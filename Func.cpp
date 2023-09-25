#include "Header.h"
#include <iostream>
#include <fstream>
#include <string>
//������� ��� �������� � ���������� ������� � ����������
double** createAndFillMatrix(int n)
{
    double** matrix = new double* [n];
    for (int i = 0; i < n; ++i)
    {
        matrix[i] = new double[n];
        for (int j = 0; j < n; ++j)
        {
            std::cout << "������� ������� [" << i << "][" << j << "]: ";
            std::cin >> matrix[i][j];
            if (!std::cin.good())
            {
                std::cout << "������... ��� �� ����� \n";
                exit(-1);
            }
        }
    }
    return matrix;
}


//������� ��� ������������ ������
void freeMatrix(double** matrix, int n)
{
    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

//������� ��� ������ ������� �� �����
void printMatrix(double** matrix, int n)
{
    std::cout << "�������: \n";
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

//������� ��� ���������� ������������
double determinant(double** matrix, int n) {
    if (n == 1)                         //���� ������� ������� 1�1
    {
        return matrix[0][0];            //�� ��������� ������������ �������� ������������ ������� �������
    }
    else if (n == 2)                    //���� ������� ������� 2�2
    {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];   //������������ ����������� �� ��������� �������
    }
    else                                //���� ������� ������� NxN
    {
        double det = 0;
        for (int i = 0; i < n; ++i)                     //�����������
        {                                               //�������
            double** minor = new double* [n - 1];       //�������
            for (int j = 1; j < n; ++j)                 //���
            {                                           //����������
                minor[j - 1] = new double[n - 1];       //������
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
            //������� ������
            freeMatrix(minor, n - 1);
        }
        return det;
    }
}

//������� ��� ����
void printMenu()
{
    std::cout << "1. ��������� ������� ������� ������� � ��������� � ������������ \n";
    std::cout << "2. ��������� ����������� ������� CRS � ��������� � ������������\n";
    std::cout << "3. �������� ����������� ������� CRS � ���� \n";
    std::cout << "4. ������� ����������� ������� CRS �� ����� � ��������� � ������������\n";
}

//������� ��� �������� � ���������� ����������� ������� 
CRS createCRS()
{
    CRS matrix;
    std::cout << "������� ���������� ����� � �������: ";
    std::cin >> matrix.numRows;
    checkInput(matrix.numRows);

    std::cout << "������� ���������� ��������� ���������: ";
    std::cin >> matrix.nonZero;
    checkInput(matrix.nonZero);
    if (matrix.nonZero > (matrix.numRows*2))
    {
        std::cout << "\033[0;31m������ �����\033[0m \n";
        exit(-1);
    }

    matrix.values = new double[matrix.nonZero];           //�������� ������� A
    matrix.colIndices = new int[matrix.nonZero];          //�������� ������� LJ
    matrix.rowPointers = new int[matrix.numRows + 1];     //�������� ������� LI

    std::cout << "������� �������� ��������� ���������: \n";
    for (int i = 0; i < matrix.nonZero; i++)            //����������
    {                                                   //������� 
        std::cin >> matrix.values[i];                   //A
        if (!std::cin.good())
        {
            std::cout << "\033[0;31m������ �����\033[0m \n";
            exit(-1);
        }
    }

    std::cout << "������� ������� �������� ��� ������� ���������� ��������: (������ ������� - ����) \n";
    for (int i = 0; i < matrix.nonZero; ++i)            //���������� 
    {                                                   //�������
        std::cin >> matrix.colIndices[i];               //LJ
        checkInput(matrix.colIndices[i]);
    }

    std::cout << "������� ��������� �� ������: \n";
    for (int i = 0; i <= matrix.numRows; ++i)           //����������
    {                                                   //�������
        std::cin >> matrix.rowPointers[i];              //LI
        checkInput(matrix.rowPointers[i]);
        if (matrix.rowPointers[0] != 0)
        {
            std::cout << "\033[0;31m������ �����... ������ ������� ������ ���� ����� ���� \033[0m \n";
            exit(-1);
        }
    }
    return matrix;
}


//������� �������������� CRS ������� � �������
double** convertCRStoMatrix(const CRS& crs) 
{
    double** matrix = new double* [crs.numRows];
    for (int i = 0; i < crs.numRows; ++i) 
    {
        matrix[i] = new double[crs.numRows]();          // ������������� ������
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
        std::cout << "\033[0;31m������ �����\033[0m \n";
        exit(-1);
    }
}

//������� ��� ������ ������� � (�������� ��������� ���������)
void printMassA(const CRS matrix)
{
    std::cout << "A: ";
    for (int i = 0; i < matrix.nonZero; i++)
    {
        std::cout << matrix.values[i] << " ";
    }
    std::cout << std::endl;
}

//������� ��� ������ ������� LJ (�������� �������� ��������� ���������)
void printMassLJ(const CRS matrix)
{
    std::cout << "LJ: ";
    for (int i = 0; i < matrix.nonZero; i++)
    {
        std::cout << matrix.colIndices[i] << " ";
    }
    std::cout << std::endl;
}

//������� ��� ������ ������� LI 
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
    std::ofstream file;               //��������� ���� ��� ������
    file.open("text.txt");
    if (!file.is_open())              //�������� �������� �����
    {
        std::cout << "\033[0;31m������ �������� �����\033[0m \n";
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
        
        std::cout << "\033[0;32m������ �������!\033[0m";
    }
}

void checkFile()
{
    std::ifstream file;             //��������� ���� ��� ������
    std::string str, str2;
    file.open("text.txt");
    if (!file.is_open())            //�������� �������� �����
    {
        std::cout << "\033[0;31m������ �������� �����\033[0m \n";
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
        std::cout << "\033[0;32m������������ �������: \033[0m" << determinant(matrix, crs.numRows) << std::endl;
    }
}