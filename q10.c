#include <stdio.h>
#include <string.h>

int countRepeat(char s[], int i) {
    if (s[i + 1] != s[i] || s[i] == '\0')
        return 1;
    return 1 + countRepeat(s, i + 1);
}

void compress(char s[], int i, char out[], int j) {
    if (s[i] == '\0') {
        out[j] = '\0';
        return;
    }
    int c = countRepeat(s, i);
    out[j]     = s[i];
    out[j + 1] = '0' + c;
    compress(s, i + c, out, j + 2);
}

void writeRun(char ch, int count, char out[], int j) {
    if (count == 0) return;
    out[j] = ch;
    writeRun(ch, count - 1, out, j + 1);
}

void expand(char in[], int i, char out[], int j) {
    if (in[i] == '\0') {
        out[j] = '\0';
        return;
    }
    int count = in[i + 1] - '0';
    writeRun(in[i], count, out, j);
    expand(in, i + 2, out, j + count);
}

int main(void) {
    char original[100] = "AAAAAABBBCCCCD";
    char compressed[200], expanded[100];

    compress(original, 0, compressed, 0);
    expand(compressed, 0, expanded, 0);

    printf("Original:   %s\n", original);
    printf("Compressed: %s\n", compressed);
    printf("Expanded:   %s\n", expanded);
    printf("Match: %s\n", strcmp(original, expanded) == 0 ? "Yes" : "No");
    return 0;
}
