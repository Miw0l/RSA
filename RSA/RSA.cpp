/*
 * C++ Program to Implement the RSA Algorithm
 */
#include <iostream>
#include <string>
#include <Windows.h>
#include <stdio.h>
#include <winbase.h>
#include <winuser.h>
#include <time.h>
#include <string> 
#include <fstream>
#include "MurmurHash3.h"

using namespace std;

long int p, q, n, t, flag, e, d, temp[100], j, m[100], en[100], i;
char msg[100];
int prime(long int);
void ce();
long int cd(long int);
void encrypt();
void decrypt();


uint32_t MurmurHash(const char* key, uint32_t len, uint32_t seed) {
    uint32_t c1 = 0xcc9e2d51;
    uint32_t c2 = 0x1b873593;
    uint32_t r1 = 15;
    uint32_t r2 = 13;
    uint32_t m = 5;
    uint32_t n = 0xe6546b64;
    uint32_t h = 0;
    uint32_t k = 0;
    uint8_t* d = (uint8_t*)key; // 32 bit extract from `key'
    const uint32_t* chunks = NULL;
    const uint8_t* tail = NULL; // tail - last 8 bytes
    int i = 0;
    int l = len / 4; // chunk length

    h = seed;

    chunks = (const uint32_t*)(d + l * 4); // body
    tail = (const uint8_t*)(d + l * 4); // last 8 byte chunk of `key'

    // for each 4 byte chunk of `key'
    for (i = -l; i != 0; ++i) {
        // next 4 byte chunk of `key'
        k = chunks[i];

        // encode next 4 byte chunk of `key'
        k *= c1;
        k = (k << r1) | (k >> (32 - r1));
        k *= c2;

        // append to hash
        h ^= k;
        h = (h << r2) | (h >> (32 - r2));
        h = h * m + n;
    }

    k = 0;

    // remainder
    switch (len & 3) { // `len % 4'
    case 3: k ^= (tail[2] << 16);
    case 2: k ^= (tail[1] << 8);

    case 1:
        k ^= tail[0];
        k *= c1;
        k = (k << r1) | (k >> (32 - r1));
        k *= c2;
        h ^= k;
    }

    h ^= len;

    h ^= (h >> 16);
    h *= 0x85ebca6b;
    h ^= (h >> 13);
    h *= 0xc2b2ae35;
    h ^= (h >> 16);

    return h;
}


int prime(long int pr)
{
    int i;
    j = sqrt(pr);
    for (i = 2; i <= j; i++)
    {
        if (pr % i == 0)
            return 0;
    }
    return 1;
}
void ce()
{
    int k;
    k = 0;
    for (i = 2; i < t; i++)
    {
        if (t % i == 0)
            continue;
        flag = prime(i);
        if (flag == 1 && i != p && i != q)
        {
            e = i;
            flag = cd(e);
            if (flag > 0)
            {
                d = flag;
                break;
                k++;
            }
            if (k == 99)
                break;
        }
    }
}
long int cd(long int x)
{
    long int k = 1;
    while (1)
    {
        k = k + t;
        if (k % x == 0)
            return (k / x);
    }
}

void encrypt()
{
    long int pt, ct, key = e, k, len;
    i = 0;
    len = strlen(msg);
    while (i != len)
    {
        pt = m[i];
        pt = pt - 96;
        k = 1;
        for (j = 0; j < key; j++)
        {
            k = k * pt;
            k = k % n;
        }
        temp[i] = k;
        ct = k + 96;
        en[i] = ct;
        i++;
    }
    en[i] = -1;
    cout << "Zakodowana wiadomosc: " << endl;
    for (i = 0; en[i] != -1; i++)
        printf("%c", en[i]);
}

void decrypt()
{
    long int pt, ct, key = d, k;
    i = 0;
    while (en[i] != -1)
    {
        ct = temp[i];
        k = 1;
        for (j = 0; j < key; j++)
        {
            k = k * ct;
            k = k % n;
        }
        pt = k + 96;
        m[i] = pt;
        i++;
    }
    m[i] = -1;
    cout << "Odkodowana wiadomosc: " << endl;
    for (i = 0; m[i] != -1; i++)
        printf("%c", m[i]);
}

int main()
{
    cout << "Wpisz wiadomość";
    fflush(stdin);
    cin >> msg;
    for (i = 0; msg[i] != '\0'; i++)
        m[i] = msg[i];

    system("cls"); 
    SetConsoleTitleA("CPU Current Working Speed - by Devoney"); 
    __int64 Answer = 0; 

    clock_t t2;
    int f;


    Answer = 1000;

    __int64 unsigned BeginClock = 0;
    __int64 unsigned EndClock = 0;
    __int64 unsigned Speed = 0;
    __int64 unsigned Speed2 = 0;
    cout << "\nVariables initialized...\n";

    if (SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS))
    {
        cout << "Priority Class Set To Realtime...\n";
    }
    else
    {
        cout << "Priority Class Could Not Be Set To Realtime...\n";
    }

    cout << "Waiting for interval to pass...\n\n";

    int tab2[8];
    for (int x = 0; x < 1000; x++) {
        int tab = 0;
        int j = 1;
        while (j <= 8) {

            BeginClock = __rdtsc();
            Sleep(Answer); 
            EndClock = __rdtsc();
            Speed = (EndClock - BeginClock);
            Speed = Speed / (1000000 * (Answer / 1000)); 
            int number = 1234;

            std::string tmp = std::to_string(Speed);
            char const* num_char = tmp.c_str();

            BeginClock = __rdtsc();


            Sleep(Answer);

            EndClock = __rdtsc();

            Speed2 = (EndClock - BeginClock);
            Speed2 = Speed2 / (1000000 * (Answer / 1000));
            std::string s2 = std::to_string(Speed);

            uint64_t seed = 1;
            uint64_t hash_otpt[2];
            const char* key = "hi";
            MurmurHash3_x64_128(num_char, (uint64_t)strlen(num_char), Speed2, hash_otpt);

            int temp = hash_otpt[1] & 1;
            tab2[j - 1] = hash_otpt[1] & 1;
            j++;

        }

        for (int i = 0; i < 8; i++) {
            tab = tab * 2 + tab2[i];
        }
        cout << endl;
        cout << tab;
        if (prime(tab) == 1 and p == 0 and q == 0) {
            p = tab;
        }
        else if (prime(tab) == 1 and q == 0) {
            q = tab;
            break;
        }
    }

    n = p * q;
    t = (p - 1) * (q - 1);
    ce();
    encrypt();
    decrypt();
    return 0;
}
