#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main(int argc, char** argv) {
    if(argc < 2) {
        printf("%s: expected 1 argument, got none\n", argv[0]);
        exit(-1);
    }
    FILE* file = fopen(argv[1], "r");
    if(!file) {
        printf("%s: no such file\n", argv[0]);
        exit(-1);
    }
    uint8_t* arr = malloc(512);
    if(!arr) {
        exit(-1);
    }
    memset(arr, 0, 512);
    int p = 0;
    int c;
    while((c = fgetc(file)) != EOF) {
        switch(c) {
            case '+': {
                arr[p]++;
                break;
            }
            case '>': {
                p = (p + 1) % 512;
                break;
            }
            case '<': {
                p = (p - 1 + 512) % 512;
                break;
            }
            case '-': {
                arr[p]--;
                break;
            }
            case '.': {
                putchar(arr[p]);
                break;
            }
            case ',': {
                arr[p] = getchar();
                break;
            }
            case '*': {
                if(p+2 >= 512) p = 0;
                arr[p+2] = arr[p] * arr[p+1];
                break;
            }
            case '/': {
                if(p+2 >= 512) p = 0;
                arr[p+2] = arr[p] / arr[p+1];
                break;
            }
            case '@': {
                if(fseek(file, arr[p], SEEK_CUR)) {
                    printf("%s: error while seeking", argv[0]);
                    exit(-1);
                }
                break;
            }
            case '_': {
                if(p+2 >= 512) p = 0;
                arr[p+2] = arr[p] | arr[p+1];
                break;
            }
            case '`': {
                if(p+2 >= 512) p = 0;
                arr[p+2] = arr[p] & arr[p+1];
                break;
            }
            case ';': {
                if(p+2 >= 512) p = 0;
                arr[p+2] = arr[p] ^ arr[p+1];  
                break;
            }
            default: break;
        }
    }

    fclose(file);
    free(arr);
    return 0;
}