#pragma once

#include<iostream>

struct CRS {
    double* values;
    int nonZero;
    int numRows;
    int* colIndices;
    int* rowPointers;
};

//������� ��� �������� � ���������� ������� � ����������
double** createAndFillMatrix(int n);

//������� ��� ������������ ������
void freeMatrix(double** matrix, int n);

//������� ��� ������ ������� �� �����
void printMatrix(double** matrix, int n);

//������� ��� ���������� ������������
double determinant(double** matrix, int n);

//������� ��� ����
void printMenu();

//������� ��� �������� � ���������� ����������� ������� 
CRS createCRS();

//������� �������������� CRS ������� � �������
double** convertCRStoMatrix(const CRS&);

//������� �������� ����� ������
void checkInput(int);

//������� ��� ������ ������� � (�������� ��������� ���������)
void printMassA(const CRS);

//������� ��� ������ ������� LJ (�������� �������� ��������� ���������)
void printMassLJ(const CRS);

//������� ��� ������ ������� LI
void printMassLI(const CRS);

//������� ������ ����������� ������� � ����
void inputInFile(const CRS);

//������� ������ ����������� ������� �� �����
void checkFile();