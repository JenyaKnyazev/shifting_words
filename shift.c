#include <stdio.h>
#include <stdlib.h>
int string_len(char *s) {
    int res = 0;
    while (*s != '\0') {
        res++;
        s++;
    }
    return res;
}
void shift_left(char *s) {
    char ch;
    int i = 1;
    ch = s[0];
    while (s[i] != '\0') {
        s[i - 1] = s[i];
        i++;
    }
    s[i - 1] = ch;
}
void shift_right(char* s) {
    char ch;
    int i= string_len(s)-1;
    ch = s[i];
    while (i > 0) {
        s[i] = s[i - 1];
        i--;
    }
    s[0] = ch;
}
char** split(char *s, int *len) {
    char** res = NULL;
    *len = 0;
    int len2;
    while (*s != '\0') {
        if (*s != ' ') {
            (*len)++;
            res = (char**)realloc(res, sizeof(char*) * (*len));
            res[*len - 1] = NULL;
            len2 = 1;
            while (*s != ' ' && *s != '\0') {
                len2++;
                res[*len - 1] = (char*)realloc(res[*len - 1], sizeof(char) * len2);
                res[*len - 1][len2 - 2] = *s;
                s++;
            }
            res[*len - 1][len2 - 1] = '\0';
        }
        if (*s != '\0') {
            (*len)++;
            res = (char**)realloc(res, sizeof(char*) * (*len));
            res[*len - 1] = NULL;
            len2 = 1;
            while (*s == ' ') {
                len2++;
                res[*len - 1] = (char*)realloc(res[*len - 1],sizeof(char) * len2);
                res[*len - 1][len2 - 2] = *s;
                s++;
            }
            res[*len - 1][len2 - 1] = '\0';
        }
    }
    return res;
}
char* concate_strings(char **s, int len) {
    int length = 1;
    int i,r,k;
    char *res;
    for (i = 0; i < len; i++)
        length += string_len(s[i]);
    res = (char*)malloc(sizeof(char) * length);
    k = 0;
    for (i = 0; i < len; i++) {
        for (r = 0; s[i][r] != '\0'; r++,k++)
            res[k] = s[i][r];
    }
    res[k] = '\0';
    return res;
}
char* shift_words_right(char* s) {
    int len;
    char** splited = split(s, &len);
    int i;
    for (i = 0; i < len; i++) {
        shift_right(splited[i]);
    }
    return concate_strings(splited, len);
}
char* shift_words_left(char* s) {
    int len;
    char** splited = split(s, &len);
    int i;
    for (i = 0; i < len; i++) {
        shift_left(splited[i]);
    }
    return concate_strings(splited, len);
}
char* shift_words_left2(char* s) {
    int len;
    char** splited = split(s, &len);
    int i=0,r,k;
    char* first_word;
    char* spaces;
    char** arr;
    while (splited[i][0] == ' ')
        i++;
    if (i == 0) {
        first_word = splited[i];
        i++;
        spaces = splited[i];
        i++;
        for (r = 0; i < len; i++, r++)
            splited[r] = splited[i];
        splited[i - 2] = spaces;
        splited[i - 1] = first_word;
        return concate_strings(splited, len);
    }
    k = i;
    arr = (char**)malloc(sizeof(char*) * (k + 1));
    for (i = 0; i <= k; i++)
        arr[i] = splited[i];
    i = k+1;
    for (r = 0; i < len; i++, r++)
        splited[r] = splited[i];
    for (i = 0; r < len; i++,r++)
        splited[r] = arr[i];
    return concate_strings(splited, len);
}
char* shift_words_right2(char* s) {
    int len;
    char** splited = split(s, &len);
    int i = 0, r, k;
    char* last_word;
    char* spaces;
    char** arr;
    i = len - 1;
    while (splited[i][0] == ' ')
        i--;
    if (i == len - 1) {
        last_word = splited[i];
        i--;
        spaces = splited[i];
        i--;
        for (r = len - 1; i >= 0; i--, r--)
            splited[r] = splited[i];
        splited[r--] = spaces;
        splited[r--] = last_word;
        return concate_strings(splited, len);
    }
    arr = (char**)malloc(sizeof(char*) * (len-i));
    for (r = 0, k = i; k < len; k++, r++)
        arr[r] = splited[k];
    for (r = i - 1, k = len - 1; r >= 0; r--, k--)
        splited[k] = splited[r];
    for (r = 0; r < len - i; r++)
        splited[r] = arr[r];
    return concate_strings(splited, len);
}
void change(char* s) {
    puts(shift_words_right(s));
    puts(shift_words_left(s));
    puts(shift_words_right2(s));
    puts(shift_words_left2(s));
}
void main() {
    char s[200];
    puts("Enter a line of words");
    gets(s);
    puts("");
    change(s);
    system("pause");
}

