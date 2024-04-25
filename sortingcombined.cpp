#include <iostream>
#include <stdlib.h>
#include <omp.h>
using namespace std;
void bubble(int *, int);
void swap(int &, int &);
void bubble(int *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        int first = i % 2;
#pragma omp parallel for shared(a, first)
        for (int j = first; j < n - 1; j += 2)
        {
            if (a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
            }
        }
    }
}
void swap(int &a, int &b)
{
    int test;
    test = a;
    a = b;
    b = test;
}

// MERGE SORT
void mergesort(int a[], int i, int j);
void merge(int a[], int i1, int j1, int i2, int j2);
void mergesort(int a[], int i, int j)
{
    int mid;
    if (i < j)
    {
        mid = (i + j) / 2;
#pragma omp parallel sections
        {
#pragma omp section
            {
                mergesort(a, i, mid);
            }
#pragma omp section
            {
                mergesort(a, mid + 1, j);
            }
        }
        merge(a, i, mid, mid + 1, j);
    }
}
void merge(int a[], int i1, int j1, int i2, int j2)
{
    int temp[1000];
    int i, j, k;
    i = i1;
    j = i2;
    k = 0;
    while (i <= j1 && j <= j2)
    {
        if (a[i] < a[j])
        {
            temp[k++] = a[i++];
        }
        else
        {
            temp[k++] = a[j++];
        }
    }
    while (i <= j1)
    {
        temp[k++] = a[i++];
    }
    while (j <= j2)
    {
        temp[k++] = a[j++];
    }
    for (i = i1, j = 0; i <= j2; i++, j++)
    {
        a[i] = temp[j];
    }
}
int main()
{
    int *a, n;
    cout << "\n enter total no of elements for bubble sort =>";
    cin >> n;
    a = new int[n];
    cout << "\n enter elements=>";
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    bubble(a, n);
    cout << "\n sorted array using bubble sort is=>";
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << endl;
    }
//  MERGE SORT
    int *b, m, i;
    cout << "\n enter total no of elements=>";
    cin >> m;
    b = new int[m];
    cout << "\n enter elements=>";
    for (i = 0; i < m; i++)
    {
        cin >> b[i];
    }
    mergesort(b, 0, m - 1);
    cout << "\n sorted array using  merge sort is=>";
    for (i = 0; i < m; i++)
    {
        cout << "\n"
             << b[i];
    }


    return 0;
}