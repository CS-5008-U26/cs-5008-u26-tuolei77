#include <stdio.h>

int main () {
    char s[100];

    for (int x = 0; x <= 1500; x += 63) {

        printf("%6d\n", x); // 把整数放在 宽度为 6 的位置里，右对齐。

    }


    fgets(s, 100, stdin);
    return 0;
}