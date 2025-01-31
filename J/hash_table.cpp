#include <bits/stdc++.h>
using namespace std;

class HashTable {
    static const int Prime_const = 31;
    static const int Arr_size = 3001;
    int arr[Arr_size];

    public:
        HashTable() {
            fill(arr, arr + Arr_size, 0);
        }

        void put(string key, int val) {
            int idx = hashFunc(key);
            arr[idx] = val;
        } 

        static int hashFunc(string key) {
            size_t sum;
            for (int i = 0; i < key.size(); i++) {
                sum += (key[i] * (int)pow(Prime_const, i)) % Arr_size;
            }
            return sum % Arr_size;
        }

        void printall() {
            for (int i = 0; i < Arr_size; i++) {
                if (arr[i] > 0) {
                    cout << i << ": " << arr[i] << '\n';
                }
            }
            cout << '\n';
        }
};

int main() {
    HashTable HT;
    HT.put("abc", 1);
    HT.put("longString", 200);
    HT.put("veryLongString", 3000);
    HT.printall();
}
