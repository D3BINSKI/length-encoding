#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int lengthOfSameCharacters(const char *s, int *index) {
    int length = 0;
    int i = *index;
    while (s[i] == s[i + 1] && s[i + 1] != '\0') {
        length++;
        i++;
        *index = i + 1;
    }
    return length;
}

char *run_length_encode(char const *input) {
    if (input == NULL || strlen(input) == 0) {
        return NULL;
    }
    // IMPLEMENT
    int index = 0;
    int output_index = 0;
    char *output = (char *) malloc((strlen(input) + 1) * sizeof(char));

    while (index < strlen(input)) {
        int currComboLen = lengthOfSameCharacters(input, &index);
        if (currComboLen == 0) {
            output[output_index] = input[index];
            output_index++;
            index++;
        } else {
            output[output_index] = input[index - currComboLen];
            output[output_index + 1] = currComboLen + 1 + '0';
            output_index += 2;
        }
    }
    output[output_index] = '\0';
    return output;
}

char *run_length_decode(char const *input) {
    if (input == NULL || strlen(input) == 0) {
        return NULL;
    }
    // IMPLEMENT
    int currIndex = 0;
    int outputIndex = 0;
    char *output = (char *) malloc(9 * (strlen(input) + 1) * sizeof(char));
    while (currIndex < strlen(input)) {
        if (!isdigit(input[currIndex]) && isdigit(input[currIndex + 1])) {
            for (int i = 0; i < input[currIndex + 1] - '0'; ++i) {
                output[outputIndex] = input[currIndex];
                outputIndex++;
            }
            currIndex += 2;
        } else {
            output[outputIndex] = input[currIndex];
            currIndex++;
            outputIndex++;
        }
    }
    output[outputIndex] = '\0';
    return output;
}

int main() {
    char *output;
    char *encoded;
    char **inputTestCases = (char **) malloc(sizeof(char *) * 3);
    inputTestCases[0] = "helloworldddd";
    inputTestCases[1] = "Hardgamingisfun";
    inputTestCases[2] = "aabbccddee";
    for (int i = 0; i < 3; i++) {
        output = run_length_encode(inputTestCases[i]);
        printf("%s\n", output);
        encoded = run_length_decode(output);
        printf("%s\n", encoded);
    }
    return 0;
}
