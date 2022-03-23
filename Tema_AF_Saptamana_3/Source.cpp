/*
* Student: Spaczai Carla Noemi
* Grupa: 30229
* Am implementat: algoritmul "Heapsort", metoda de construire a unui heap "Bottom-Up" si metoda de construire a unui heap "Top-Down".
*
* Metoda de construire a unui heap "Bottom-Up" incepe prin a verifica daca ultimul nod parinte (cel mai din dreapta si cel mai de jos) are vreun nod copil cu o 
* valoare mai mare decat a lui. Daca da, cei doi se vor interschimba (si se vor verifica ramurile de jos). Daca nu, se reia acest proces cu urmatorul nod de acest
* tip. Aceste verificari si interschimbari au loc pana cand va fi ordonat tot arborele (fiecare nod parinte trebuie sa aiba o valoare mai mare decat cele doua noduri
* copil).
* Complexitate: O(n*log(n)). (GRESIT: O(n))
* 
* Algoritmul "Heapsort" incepe prin a schimba valoarea radacinii cu valoarea ultimei frunze (cea mai din dreapta si cea mai de jos). Se vor face interschimbari cu
* nodurile copii de cea mai mare valoare (daca valoarea e mai mare decat cea a nodului parinte) pana cand noua radacina va ajunge la pozitia ei corecta in arbore. Se
* reia acest proces cu urmatorul nod de acest tip pana cand va fi ordonat tot arborele (fiecare nod parinte trebuie sa aiba o valoare mai mare decat cele doua noduri
* copil).
* Complexitate: O(n*log(n)).
*
* Metoda de construire a unui heap "Top-Down" incepe prin a introduce pe rand cate un nod in arbore. Dupa fiecare introducere, arborele va fi aranjat astfel incat
* fiecare nod parinte sa fie mai mare decat cele doua noduri copii (interschimbari). Acest proces are loc pana cand nu mai sunt noduri de introdus si arborele e
* complet ordonat.
* Complexitate: O(n*log(n)).
*
* Comparand cele doua metode de construire a unui heap observam ca:
* "Bottom-Up" este cea mai eficienta metoda, dar este de dimensiune fixa.
* "Top_Down" este cea mai ineficienta metoda, dar este de dimensiune variabila.
*/

#include <stdio.h>
#include "Profiler.h"

Profiler p("HEAP");

#define MAX_SIZE 10000
#define STEP_SIZE 100
#define NR_TESTS 5

void bottom_up_2(int v[], int i, int n) //heapify
{
	Operation OP = p.createOperation("Bottom_Up", n);

	int k;
	int left = i * 2 + 1;
	int right = (i + 1) * 2;
	OP.count();
	if (left < n && v[left] > v[i])
	{
		k = left;
	}
	else
	{
		k = i;
	}
	OP.count();
	if (right < n && v[right] > v[k])
	{
		k = right;
	}
	if (k != i)
	{
		OP.count(3);
		int x = v[i];
		v[i] = v[k];
		v[k] = x;
		bottom_up_2(v, k, n);
	}
}

void bottom_up(int v[], int n)
{
	for (int i = (n - 1) / 2; i >= 0; i--)
	{
		bottom_up_2(v, i, n);
	}
}

void heapsort(int v[], int n)
{
	bottom_up(v, n);
	for (int i = n - 1; i >= 0; i--)
	{
		int x = v[0];
		v[0] = v[i];
		v[i] = x;
		n -= 1;
		bottom_up_2(v, 0, n);
	}
}

void top_down_2(int v[], int k, int n, int y) //insert, increase
{
	Operation OP = p.createOperation("Top_Down", n);

	OP.count();
	v[y] = k;
	OP.count();
	while (y > 0 && v[(y + 1) / 2 - 1] < v[y])
	{
		OP.count(3);
		int x = v[y];
		v[y] = v[(y + 1) / 2 - 1];
		v[(y + 1) / 2 - 1] = x;
		y = (y + 1) / 2 - 1;
	}
}

void top_down(int v[], int n)
{
	for (int i = 1; i < n; i++)
	{
		top_down_2(v, v[i], n, i);
	}
}

void demo()
{
	int v[] = { 7, 2, 8, 9, -1, 2, 4, 1, 3, 6 };
	int n = sizeof(v) / sizeof(v[0]);

	bottom_up(v, n);
	printf("Bottom-Up: ");
	//heapsort(v, n);
	//printf("Heapsort: ");
	//top_down(v, n);
	//printf("Top-Down: ");

	for (int i = 0; i < n; i++)
	{
		printf("%d ", v[i]);
	}
}

void perf(int order)
{
	int v1[MAX_SIZE], v2[MAX_SIZE];
	int n;
	for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE)
	{
		for (int test = 0; test < NR_TESTS; test++)
		{
			FillRandomArray(v1, n, 10, 50000, false, order);
			CopyArray(v2, v1, n);
			bottom_up(v1, n);
			top_down(v2, n);
		}
	}

	p.divideValues("Bottom_Up", NR_TESTS);
	p.divideValues("Top_Down", NR_TESTS);
	p.createGroup("Comparare", "Bottom_Up", "Top_Down");
	p.showReport();
}

void perf_all()
{
	perf(UNSORTED);
	p.reset("Worst Case");
	perf(ASCENDING);
	p.showReport();
}

int main()
{
	demo();
	//perf_all();
	return 0;
}