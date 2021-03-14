#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
ifstream  fin("date2.in");
ofstream fout("date.out");

void Bubblesort(vector<int> &vect){
    for(int i=0; i<vect.size()-1; i++)
        for(int j=0; j<vect.size()-i-1; j++)
            if(vect[j]>vect[j+1])
            {
                int aux= vect[j];
                vect[j]= vect[j+1];
                vect[j+1]= aux;

            }
};

void Countsort(vector<int> &vect){
    int max= vect[0];
    int sortedvect[vect.size()];
    for (int i = 0; i <vect.size(); i++) {
        if (vect[i] > max) {
            max = vect[i];
        }
    }
        int frecv[max+1];
        memset(frecv, 0, sizeof(frecv));

        for(int i=0; i<= vect.size()-1; i++){
            ++frecv[vect[i]];

        }

        for (int i=1; i<=max; i++){
            frecv[i]= frecv[i]+frecv[i-1];
        }

        for(int i=vect.size()-1; i>=0; i--){
          sortedvect[--frecv[vect[i]]]=vect[i];
        }
        for(int i=0; i<vect.size(); i++ ){
            vect[i]=sortedvect[i];
        }

};
void cntsort_radix(vector<int> &vect, int &pos ){
    int sortedvect[vect.size()];

    //construim vect de frecventa
    int frecv[10];
    memset(frecv, 0, sizeof(frecv));

    //aflam de cate ori se repeta fiecare element din vect
    for(int i=0; i<= vect.size()-1; i++){
        frecv[(vect[i] / pos) % 10]++;
    }

    //update vector de frecventa cu numarul indexului unde se va termina fiecare nr de la 0 la max in vectorul sortat
    for (int i=1; i<10; i++){
        frecv[i]= frecv[i]+frecv[i-1];
    }

    //construim vect sortat
    for(int i=vect.size()-1; i>=0; i--){
        sortedvect[frecv[(vect[i]/pos)%10]-1]=vect[i];
        --frecv[(vect[i] / pos) % 10];

    }
    //inlocuim vect initial cu sortedvect
    for(int i=0; i<vect.size(); i++ ){
        vect[i]=sortedvect[i];
    }

};
void Radixsort(vector<int> &vect){
    int max= vect[0];
    for (int i = 0; i <vect.size(); i++) {
        if (vect[i] > max) {
            max = vect[i];
        }
    }

    for(int position=1; max/position>0; position*=10 )
    {
        cntsort_radix(vect, position);
    }

    int frecv[max+1];
    memset(frecv, 0, sizeof(frecv));
};


void Merge(vector<int> &vect, int left, int m, int right)
{
    int b[sizeof(vect)];

    //copy the current elements into temp array
    int v;
    for (v = left; v <= right; v++){
        b[v] = vect[v];
    }

    int i = left;
    int j = m + 1;
    int k = left;

    //merge left side and right side into array in sorted order
    while (i <= m && j <= right) {
        if (b[i] <= b[j])
            vect[k++] = b[i++];
        else
            vect[k++] = b[j++];
    }

    //The left side might have left-over elements
    while (i <= m)
        vect[k++] = b[i++];


}

void midpoint(vector<int> &vect, int left, int right)
{
    int m;
    if (left < right) {
        m = (right + left) / 2;
        midpoint(vect, left, m);
        midpoint(vect, m+ 1, right);
        Merge(vect, left, m, right);
    }

}

int part(vector<int> &vect, int left, int right, int index) {
    int pval = vect[index];
    int now_index = left;
    int aux;

    aux = vect[index];
    vect[index] = vect[right];
    vect[right] = aux;

    for (int i = left; i < right; i++) {
        if (vect[i] <= pval) {
            aux = vect[i];
            vect[i] = vect[now_index];
            vect[now_index] = aux;

            now_index++;
        }
    }

    aux = vect[now_index];
    vect[now_index] = vect[right];
    vect[right] = aux;

    return now_index;
}
int quicksort(vector<int> &vect, int left, int right, int pivot) {
    //int pivot = 0;

    if (left < right) {
        pivot = part(vect, left, right, pivot);

        quicksort(vect, left, pivot - 1, left);
        quicksort(vect, pivot + 1, right, pivot + 1);

    }
    return 0;
}


bool verification(vector<int> vect) {
    vector<int> v = vect; //cream un vector v cu aceleasi elemente ca cel initial
    sort(begin(v), end(v)); //sortam v
    for (int i = 0; i < vect.size(); i++)
        if (vect[i] != v[i]) //verificam daca elementele de pe aceeasi pozitie sunt egale
            return false;
    return true;
};

void sort_mergesort(vector<int> &vect){
    midpoint(vect, 0, vect.size()-1);};
void sort_quicksort(vector<int> &vect){
    quicksort(vect, 0, vect.size(), 0);
};


int main() {

    int nr_teste, n, val_max;
    vector<int> v;
    fin >> nr_teste;
    for (int test = 1; test < nr_teste; test++) {
        fin >> n >> val_max;
        fout << '\n' << "\nTest " << test << ", N= " << n << ", valoare maxima= " << val_max << '\n';
        for (int i = 0; i < n; i++) {
            v.push_back(rand() % val_max + 1);
        }
        for (int j = 0; j < 5; j++) {
            if (j == 0) {
                if(n>=10000 or val_max>=10000){
                    fout << "\nBubblesort nu merge\n";
                }
                else{
                    fout << "\nBubblesort \n";
                    auto startb = chrono::high_resolution_clock::now();
                    Bubblesort(v);
                    auto stopb = chrono::high_resolution_clock::now();
                    auto durationb = chrono::duration_cast<chrono::microseconds>(stopb - startb);
                    verification(v) ? fout << "A fost sortat\n" : fout << "Nu a fost sortat\n";
                    fout << durationb.count() << 'ms\n';

                }

            }
                if (j = 1) {
                    if(n>=100000 or val_max>=100000){
                        fout << "\nCountsort nu merge\n";
                    }
                    else {
                        fout << "\nCountsort \n";
                        auto startc = chrono::high_resolution_clock::now();
                        Countsort(v);
                        auto stopc = chrono::high_resolution_clock::now();
                        auto durationc = chrono::duration_cast<chrono::microseconds>(stopc - startc);
                        verification(v) ? fout << "A fost sortat\n" : fout << "Nu a fost sortat\n";
                        fout << durationc.count() / 1000 << 'ms\n';

                }
                }

                if (j = 2) {
                    if(n>=1000000 or val_max>=1000000){
                        fout << "\nRadixsort nu merge \n";
                    }
                    else {
                        fout << "\nRadixsort \n";
                        auto startr = chrono::high_resolution_clock::now();
                        Radixsort(v);
                        auto stopr = chrono::high_resolution_clock::now();
                        auto durationr = chrono::duration_cast<chrono::microseconds>(stopr - startr);
                        verification(v) ? fout << "A fost sortat\n" : fout << "Nu a fost sortat\n";
                        fout << durationr.count() / 1000 << 'ms\n';
                    }
                }
                if (j = 3) {
                    if(n>=100 or val_max>=100){
                        fout << "\nMergesort nu merge\n";
                    }
                    else {
                        fout << "\nMergesort\n";
                        auto startm = chrono::high_resolution_clock::now();
                        sort_mergesort(v);
                        auto stopm = chrono::high_resolution_clock::now();
                        auto durationm = chrono::duration_cast<chrono::microseconds>(stopm - startm);
                        verification(v) ? fout << "A fost sortat\n" : fout << "Nu a fost sortat\n";
                        fout << durationm.count() / 1000 << 'ms\n';
                    }


                }
                if (j = 4) {
                    if(n>=100000000 or val_max>=10000000){
                        fout << "\nQuicksort nu merge\n";
                    }
                    else {
                        fout << "\nQuicksort\n";
                        auto startq = chrono::high_resolution_clock::now();
                        sort_quicksort(v);
                        auto stopq = chrono::high_resolution_clock::now();
                        auto durationq = chrono::duration_cast<chrono::microseconds>(stopq - startq);
                        verification(v) ? fout << "A fost sortat\n" : fout << "Nu a fost sortat\n";
                        fout << durationq.count() / 1000 << 'ms\n';
                    }
                }
            }
        }


        return 0;

    };