// Lab1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <stdio.h>
#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>  
#include <string>  
#include <vector>  
#include <sstream> 
#include <cstring>
#include "inipp.h"
#include <chrono>
#include <vector>
using namespace std;

void quick_sort(int *tab, int left, int right)
{
	int i = left;
	int j = right;
	int x = tab[(left + right) / 2];
	do
	{
		while (tab[i] < x)
			i++;

		while (tab[j] > x)
			j--;

		if (i <= j)
		{
			swap(tab[i], tab[j]);

			i++;
			j--;
		}
	} while (i <= j);

	if (left < j) quick_sort(tab, left, j);

	if (right > i) quick_sort(tab, i, right);

}

int	*bbl_sort(int *tablica, int size)
{
	bool swap = false;
	int temp = 0;
	while (true)
	{
		swap = false;
		for (int i = 0; i < size - 1; i++)
		{
			if (tablica[i] > tablica[i + 1])
			{
				temp = tablica[i];
				tablica[i] = tablica[i + 1];
				tablica[i + 1] = temp;
				swap = true;
			}
		}
		if (swap == false)
		{
			break;
		}
	}
	return tablica;
}

 int *wstawianie(int* tablica,int size)
{
    int temp = 0;
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (tablica[i] < tablica[j])
            {
                temp =  tablica[i];
                tablica[i] = tablica[j];
                tablica[j] = temp;
            }
        }
    }
    return tablica;
}



int main()
{

	inipp::Ini<char> ini;
	std::ifstream is("ustawienia.ini");
	ini.parse(is);
	int zmienna = 1;
	int loops = 1;
	string algorithm = "algorithm";
	inipp::get_value(ini.sections["SETTINGS"], "AmountOfNumbers", zmienna);
	inipp::get_value(ini.sections["SETTINGS"], "Loops", loops);
	inipp::get_value(ini.sections["SETTINGS"], "Algorithm", algorithm);

	string STRING, T;
	int counter = 0;
	int* liczby = new int[zmienna];
	double* czas = new double[loops];


	ifstream infile;
	infile.open("liczby.txt");
	while (!infile.std::ios::eof())
	{
		getline(infile, STRING);
	}
	stringstream X(STRING);
	while (getline(X, T, ',')) {
		liczby[counter] = stoi(T);
		if (counter + 1 == zmienna) {
			break;
		}
		counter++;
	}



	//miejsce na sorotwanie
	for (int i = 0; i < loops; i++)
	{
		int* kopie = new int[zmienna];
		for (int j = 0; j < zmienna; j++)
		{
			kopie[j] = liczby[j];
		}
	auto start = chrono::steady_clock::now();
	
	if (algorithm == "bubble_sort") 
	{
		bbl_sort(kopie, zmienna);
	}else if(algorithm == "quick_sort")
	{
		quick_sort(kopie, 0, zmienna - 1);
	}
	else if (algorithm == "insert_sort")
	{
		wstawianie(kopie, zmienna);
	}
	auto end = chrono::steady_clock::now();

	czas[i] = chrono::duration_cast<chrono::milliseconds>(end - start).count();

	}
	ofstream excel("czasy.csv", ios::app);
	double suma = 0;
	for (int i = 0; i < loops; i++)
	{
		suma=suma+czas[i];
	}
	double srednia = suma / loops;
	excel <<srednia<<";"<< algorithm << ";" << zmienna << endl;
	excel.close();

	//zapis juz posortowanych
	ofstream zapis("posortowane.txt");
	for (int x = 0; x < zmienna; x++) {
		zapis << liczby[x]<<endl;
	}
	ofstream zapis2("czasy.txt");
	for (int x = 0; x < loops; x++)
	{
		zapis2 << czas[x] << endl;
	}
	zapis.close();
	zapis2.close();
	delete liczby;
	delete czas;
	return 0;
}