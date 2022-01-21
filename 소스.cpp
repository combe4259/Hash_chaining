/*
* Hash
* chaining
*/

#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int strcmp(const char* s, const char* t) {
    while (*s && *s == *t) ++s, ++t;
    return *s - *t;
}

void strcpy(char* dest, const char* src) {
    while ((*dest++ = *src++));
}

char str[23];
int value, strID;
const int SIZE = 1 << 18;
const int MASK = SIZE - 1;


struct Hash {
    char str[23];
    int id, value;
    Hash* next;
    Hash* alloc(char _str[], int _value, Hash* _next) {
        strcpy(str, _str);
        value = _value;
        next = _next;
        id = ++strID;
        return this;
    }
}hbuf[200003], * htab[SIZE];
int hcnt;

unsigned long hash(char* str)
{
    int code = 0;
    for (int i = 0; str[i]; i++) {
        if (str[i] < 'a') str[i] += 32;
        code = (code * 27 + str[i] - 'a' + 1) & MASK;
    }
    return code;
}

Hash* probing() {
    int hidx = hash(str);
    for (Hash* p = htab[hidx]; p; p = p->next) {
        if (!strcmp(str, p->str)) {
            if (value > p->value) p->value = value;
            return p;
        }
    }
    htab[hidx] = hbuf[hcnt++].alloc(str, value, htab[hidx]);
    return htab[hidx];
}

int main() {
    int k;
    FILE* for_open=NULL;
    fopen_s(&for_open, "C:\\Windows\\startlineup_manu.txt", "r");
    fscanf_s(for_open,"%d",&k,sizeof(k));
    for (int i = 0;i < k - 3;i++) {
        fscanf_s(for_open, "%s %d", str, sizeof(str), &value);
        probing();
    }
    for (int i = 0;i < hcnt;i++)printf("%d %d\n", hbuf[i].id, hbuf[i].value);
    for (int i = k - 3;i < k;i++) {
        fscanf(for_open, "%s %d", str, &value);
        for (Hash* pi = htab[hash(str)];pi;pi = pi->next) {
            if (strcmp(str, pi->str)==0) {
                printf("%d %d\n", pi->id, pi->value);
                break;
            }
        }
    }
    return 0;
}