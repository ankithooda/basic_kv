#include <stdio.h>

struct kv {
    int k;
    const char* v;
};

void printf_s(struct kv a){
    a.k = 100;
    printf("%d - %s\n", a.k, a.v);
}

void printf_ptr(struct kv *a) {
    a->k = 100;
    printf("%d - %s\n", a->k, a->v);
}

struct kv 

int main() {


    struct kv a;
    struct kv* b;

    b = &a;

    a.k = 1;
    a.v = "acbded";


    printf("%d - %s\n", a.k, a.v);
    printf_s(a);
    printf("%d - %s\n", a.k, a.v);
    printf_ptr(b);
    printf("%d - %s\n", a.k, a.v);
    printf("%d - %s\n", b->k, b->v);

    return 0;

}