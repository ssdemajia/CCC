/*
待缓冲的读取
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* getStdinWithBuf() {
    int count = 10;
    char* buf = (char*)malloc(count);
    char* result = (char*)malloc(count);
    int cur = 0;
    int curlen = 10;
    while (fgets(buf, count, stdin) != NULL) {
        size_t len = strlen(buf);
        if (curlen - cur < len) {
            char *temp = result;
            curlen *= 2;
            result = (char*)malloc(curlen);
            memcpy(result, temp, curlen/2);
            free(temp);
        }
        memcpy(result+cur, buf, len);
        cur += len;
        printf("len: %ld, count:%d, buf:%s\n", strlen(buf), count, buf);
    }
    result[curlen] = '\0';
    return result;
}

int main(int argc, char const *argv[])
{
    char* result = getStdinWithBuf();
    printf("result:%s\n", result);
    return 0;
}
