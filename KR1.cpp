#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <queue>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <functional>
#include <array>
#include <iostream>
#include <iterator>
#include <stdlib.h>  
#include <iostream> 
#include <stdio.h>
using namespace std;


int N = 0;

class Graph
{
private:
	int **G1;
	int **G;
public:
	int result = 0;
	int *num;

	Graph()
	{
		FILE *f;
		char file[100];
		//G
		cout << "Введите файл с матрицей G: ";
		cin >> file;
		f = fopen(file, "r");
		if (f == NULL)
			cout << "Uncorrect command" << endl;
		char stroka[1000];
		fgets(stroka, 1000, f);
		for (int i = 0; stroka[i] != '\0'; i++)
		{
			if (stroka[i] == ' ')
			{
				++N;
			}
		}
		cout << "Количество вершин в графе G: " << N << endl;

		int **Adjacency = (int **)malloc(N * sizeof(int *));
		for (int i = 0; i < N; i++) {
			Adjacency[i] = (int *)malloc(N *sizeof(int));
		}
		G = (int**)malloc(N * sizeof(int*));
		for (int i = 0; i < N; i++) {
			G[i] = (int *)malloc(N *sizeof(int));
		}
		G1 = (int**)malloc(N * sizeof(int*));
		for (int i = 0; i < N; i++) {
			G1[i] = (int *)malloc(N *sizeof(int));
		}
		
		fseek(f, 0, SEEK_SET);
		while (!feof(f))
		{
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					fscanf(f, "%i", &Adjacency[i][j]);
				}
			}
		}
		/*cout << "Исходная матрица G: "<<endl;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				printf("%i ", Adjacency[i][j]);
			}
			cout << endl;
		}*/

		for (int i = 0; i < N; i++)
		{
			memcpy(&G[i], &Adjacency[i], sizeof(G[0]));
		}
	};
	

	void init()
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				G1[i][j] = 0;
			}
		}
	}

	void print_graph()
	{
	
			cout  << endl;
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					cout << G1[i][j] << ", ";
				}
				cout << " "<< endl;
			}
		
		
	}

	


	void buble_sort(int **R, int m)
	{
		int x;
		for (int i = 0; i < m; i++)
		{            
			for (int j = m - 1; j > i; j--)
			{    
				if (R[j - 1][0] > R[j][0])
				{
					x = R[j - 1][0]; R[j - 1][0] = R[j][0]; R[j][0] = x;
					x = R[j - 1][1]; R[j - 1][1] = R[j][1]; R[j][1] = x;
					x = R[j - 1][2]; R[j - 1][2] = R[j][2]; R[j][2] = x;
				}
			}
		}
	}
	
	void kr()
	{
		int j = 0;
		int **R = new int* [N*N]; //строки
		for (int i = 0; i < N*N; i++) {
			R[i] = new int[3];
		}

		int m = 0;
		
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (G[i][j] != 0)
				{
					R[m][0] = G[i][j];
					R[m][1] = i;//start
					R[m][2] = j;//end
					m++;
				}		
			}		
		}
		
		int *comp = (int*)malloc(N*sizeof(int)); //компонент связности по количеству вершин
		for (int i = 0; i < N; i++)
		{
			comp[i] = i;
		}
	
		buble_sort(R, m);

		for (int k=0; k<m; k++) 
		{
			int weight = R[k][0];
			int start = R[k][1];
			int end = R[k][2];
			if (comp[start] != comp[end])
			{
				result += weight;
				G1[start][end] = 1;
				G1[end][start] = 1;
				cout<< "(" << start + 1 << "," <<end+1 << ")";
				int a = comp[start];
				int b = comp[end];
				for (int i = 0; i < N; ++i)
					if (comp[i] == b)
						comp[i] = a;
			}
		}
		free(R);
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");
	Graph G;
	G.init();
	cout << "Последовательность рёбер:" << endl;
	G.kr();
	cout << endl <<endl<< "G: Матрица смежности остова минимального веса: ";
	G.print_graph();
	cout << "Вес:" << G.result << endl;
	_getch();
	return 0;
}

