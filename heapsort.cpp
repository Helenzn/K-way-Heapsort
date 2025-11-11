#include<iostream>
#include<vector>
#include<algorithm>
#include<iomanip>
#include<cassert>
#include<chrono>
#include<random>

using namespace std;

#define MAXN 200000
#define MAXM 100
#define ALL(x) (x).begin(), (x).end()

//#define PAI(x) ((((x)- 1) / 2))
//#define ESQ(x) ( 2 *(x) + 1)
//#define DIR(x) ( 2 *(x) + 2)

enum inputType {
    allRandom  = 0,
    allEqual   = 1,
    allSorted  = 2,
    allReverse = 3
};

string randomString() {
    static mt19937 rng(random_device{}());
    static uniform_int_distribution<int> len_dist(1, MAXM);
    static const char charset[] =
        //"!\"#$%'()*+,-./:;<=>?@[\\]^_`{|}~"
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    static uniform_int_distribution<size_t> char_dist(0, sizeof(charset) - 2);

    int len = len_dist(rng);
    string s;
    s.resize(len);
    for (int i = 0; i < len; ++i) {
        s[i] = charset[char_dist(rng)];
    }
    return s;
}

template <typename T>
void fillVector(vector<T> &a, inputType input){
    if(input == allEqual){
        fill(ALL(a), randomString());
        cout << "Equal strings:  ";
        return;
    }
    int n = (int)a.size();
    for(int i = 0; i < n; i++){
        a[i] = randomString();
    }
    if(input == allRandom){
        cout << "Random strings: ";
        return;
    }
    sort(ALL(a));
    if(input == allSorted){
        cout << "Sorted input:   ";
    }
    if(input == allReverse){
        reverse(ALL(a));
        cout << "Reversed input: ";
    }
}

template <typename T>
void measureSortingTime(vector<T> &a, void (*f)(vector<T> &)){
    using namespace chrono;
    auto started = high_resolution_clock::now();
    f(a);
    auto finished = high_resolution_clock::now();

    assert(is_sorted(ALL(a)));

    auto elapsed =
        duration_cast<milliseconds>(finished-started).count();
    cout << fixed << setprecision(3)
        << ((double)elapsed / (double)1000.0) << "s\n";
}

template <typename T>
void testAlgorithm(void (*f)(vector<T> &)){
    vector<T> a(MAXN);
    for(int it = 0; it < 4; ++it){
        fillVector(a, (inputType)it);
        measureSortingTime(a, f);
    }
}

template <typename T>
void heapsort(vector<T> &a);

template <typename T>
void maxHeapify(vector<T> &a, int i, int tam) {
    int maior = i;
    for(int k = 1; k <= 3; k++){
        int filho = 3*i+k;
        if(filho < tam && a[filho] > a[maior]){
            maior = filho;
        }
    }

    if(maior != i){
        swap(a[i],a[maior]);
        maxHeapify<T>(a,maior,tam);
    }

}

template <typename T>
void buildMaxHeap(vector<T> &a) {
    int n = a.size();
    for(int i = n/3; i >= 0; i--){
        maxHeapify<T>(a,i,n);
    }
}

template <typename T>
void heapsort(vector<T> &a) {
    int n = a.size();
    buildMaxHeap<T>(a);

    for(int i = (n-1); i > 0; i--){
        swap(a[0],a[i]);
        maxHeapify<T>(a,0,i);
    }
}



int main(){

    cout << "\n-- Heapsort --\n";
    testAlgorithm<string>(heapsort);

    return 0;
}

