#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;
ifstream fin("input.txt");

///quicksort
int di(vector <int> &v, int inc, int sf)
{
    int st=inc, dr=sf,pivot=v[st];
    while(st<dr)
    {
       while(v[dr]>=pivot && dr>st) dr--;
       v[st]=v[dr];
       while(v[st]<=pivot && st<dr) st++;
       v[dr]=v[st];
    }
    v[st]=pivot;
    return st;
}


void Quicksort(vector <int> &v, int st, int dr)
{
    int poz;
    if(st<dr)
    {
        poz=di(v,st,dr);
        Quicksort(v,st,poz-1);
        Quicksort(v,poz+1,dr);
    }
}

void interclasare(vector <int> &v, int inc,int sf)
{
    vector <int> c;
    int i,j,u,mij=inc+sf; mij/=2;
    i=inc; j=mij+1;
    while(i<=mij && j<=sf)
    {
        if(v[i]<v[j]) c.push_back(v[i++]);
        else c.push_back(v[j++]);
    }
    while(i<=mij)
        c.push_back(v[i++]);
    while(j<=sf)
        c.push_back(v[j++]);
    for(i=inc, u=0;i<=sf;i++, u++)
        v[i]=c[u];
}


void MergeSort(vector <int> &v,int st,int dr)
{
    if(st<dr)
    {
        int mij=(st+dr)/2;
        MergeSort(v,st,mij);
        MergeSort(v,mij+1,dr);
        interclasare(v, st,dr);
    }
}


void Radixsort_baza_10(vector <int> &v)
{
    int exp,i,n=v.size(), maxi;
    maxi = v[0];
    for (auto it = v.begin(); it != v.end(); it++)
        if(maxi<*it) maxi=*it;
    vector <int> c(n,0);
    int fr[10]={0};
    exp=1;
    while(maxi/exp>0)
    {
        for (auto it = v.begin(); it != v.end(); it++)
            fr[(*it / exp) % 10]++;

        for (i = 1; i < 10; i++)
            fr[i] += fr[i - 1];

        for (auto it = v.end()-1; it >= v.begin(); it--)
            c[--fr[(*it / exp) % 10]] = *it;
        v=c;
        exp*=10;
        for (i = 0; i < 10; i++)
            fr[i]=0;
    }
}


void Radixsort_baza_2(vector <int> &v, int baza)
{
    int putere2=1<<baza, masca=putere2-1;
    int exp,i,n=v.size(), maxi;
    maxi = v[0];
    for (auto it = v.begin(); it != v.end(); it++)
        if(maxi<*it) maxi=*it;

    vector <int> c(n,0);
    int fr[putere2]={0};
    exp=0;


    while( (maxi>>exp) >0)
    {
        for (auto it = v.begin(); it != v.end(); it++)
            fr[(*it >> exp) & masca]++;

        for (i = 1; i < putere2; i++)
            fr[i] += fr[i - 1];

        for (auto it = v.end()-1; it >= v.begin(); it--)
            c[--fr[(*it >> exp) & masca]] = *it;

        v=c;
        exp+=baza;
        for (i = 0; i < putere2; i++)
            fr[i]=0;
    }
}

void ShellSort(vector <int> &v)
{
    int n=v.size(), gap, i,j, aux;
    for(gap=n>>1; gap>0; gap=gap>>1)
        for(i=gap;i<n;i++)
        {
            j=i;
            aux=v[j];
            while(j>=gap && v[j-gap]>aux)
            {
                v[j]=v[j-gap];
                j-=gap;
            }
            v[j]=aux;
        }
}

void InsertionSort(vector <int> &v)
{
    int n=v.size(),i,j, x;
    if (n>10000)
        return;
    for(i=1;i<n;i++)
        {
            x=v[i];
            for (j=i-1;j>=0 && x<v[j];j--)
                v[j+1]=v[j];
            v[j+1]=x;
        }
}

bool test(vector <int> v, int n)
{
    for(int i=0;i<n-1;i++)
        if(v[i]>v[i+1])
                return 0;
    return 1;
}


void generare(vector<int> &v, int N, int Max)
{
    int x,cn=N;
    while(cn--)
        v.push_back(rand() %Max);
    v.resize(N);
}

int main()
{
    vector <int> generat,v;
    int N,Max,T;
    fin>>T;

    while(T--)
    {
        fin>>N>>Max;
        generare(generat,N,Max);
/*
        for (auto it = generat.begin(); it != generat.end(); it++)
            cout<<*it<<" ";
        cout<<'\n';*/

        cout<<"Numar elemente: "<<N<<"\nNumarul maxim din vector: "<<Max<<'\n';

        std::chrono::time_point<std::chrono::system_clock> Timp_start, Timp_end;
        v=generat;
        Timp_start = std::chrono::system_clock::now();
        MergeSort(v,0,N-1);
        Timp_end = std::chrono::system_clock::now();
        auto timp = duration_cast<microseconds>(Timp_end - Timp_start);
        cout<<"Merge Sort: "<<timp.count() << " microseconds ";
        test(v,N)? cout<<"Sortat": cout<<"Nesortat";
        cout<<'\n';

        v=generat;
        Timp_start = high_resolution_clock::now();
        Quicksort(v,0,N-1);
        Timp_end = high_resolution_clock::now();
        timp = duration_cast<microseconds>(Timp_end - Timp_start);
        cout<<"Quick Sort: "<<timp.count() << " microseconds ";
        test(v,N)? cout<<"Sortat": cout<<"Nesortat";
        cout<<'\n';

        v=generat;
        Timp_start = high_resolution_clock::now();
        InsertionSort(v);
        Timp_end = high_resolution_clock::now();
        timp = duration_cast<microseconds>(Timp_end - Timp_start);
        cout<<"Insertion Sort: "<<timp.count() << " microseconds ";
        test(v,N)? cout<<"Sortat": cout<<"Dureaza prea mult sortarea";
        cout<<'\n';

        v=generat;
        Timp_start = high_resolution_clock::now();
        ShellSort(v);
        Timp_end = high_resolution_clock::now();
        timp = duration_cast<microseconds>(Timp_end - Timp_start);
        cout<<"Shell Sort: "<<timp.count() << " microseconds ";
        test(v,N)? cout<<"Sortat": cout<<"Nesortat";
        cout<<'\n';

        v=generat;
        Timp_start = high_resolution_clock::now();
        Radixsort_baza_10(v);
        Timp_end = high_resolution_clock::now();
        timp = duration_cast<microseconds>(Timp_end - Timp_start);
        cout<<"Radix Sort, base 10: "<<timp.count() << " microseconds ";
        test(v,N)? cout<<"Sortat": cout<<"Nesortat";
        cout<<'\n';

        for (int i=1;i<=4;i++)
        {
            v=generat;
            Timp_start = high_resolution_clock::now();
            Radixsort_baza_2(v,i);
            Timp_end = high_resolution_clock::now();
            timp = duration_cast<microseconds>(Timp_end - Timp_start);
            cout<<"Radix Sort, base "<<(1<<i)<<": "<<timp.count() << " microseconds ";
            test(v,N)? cout<<"Sortat": cout<<"Nesortat";
            cout<<'\n';
        }

        v=generat;
        Timp_start = high_resolution_clock::now();
        sort(v.begin(),v.end());
        Timp_end = high_resolution_clock::now();
        timp = duration_cast<microseconds>(Timp_end - Timp_start);
        cout<<"STL Sort: "<<timp.count() << " microseconds "<<'\n';
        cout<<'\n';
    }

    return 0;
}

