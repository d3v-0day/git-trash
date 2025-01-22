#include <stdio.h>
#include <string.h>

void decimalToBinary(int decimal, char *binaryStr, int isUnsigned) {
    int binary[8] = {0}; // Initialize all bits to 0
    int i = 7;

    if (!isUnsigned && decimal < 0) { // Handle signed negative numbers
        decimal = 256 + decimal; // Convert to two’s complement equivalent
    }

    // Convert to binary
    while (decimal > 0 && i >= 0) {
        binary[i--] = decimal % 2;
        decimal /= 2;
    }

    // Convert binary array to string
    for (i = 0; i < 8; i++) {
        binaryStr[i] = binary[i] + '0';
    }
    binaryStr[8] = '\0'; // Null-terminate string
}

int main() {
    int userDecimal;
    char userBinary[9];

    // Step 1: Take user input (decimal)
    printf("Enter a decimal number (-128 to 255): ");
    scanf("%d", &userDecimal);

    // Step 2: Validate input range
    if (userDecimal < -128 || userDecimal > 255) {
        printf("Error: Number out of range (must be between -128 and 255)\n");
        return 1;
    }

    // Step 3: Convert user decimal input to binary and store it
    decimalToBinary(userDecimal, userBinary, (userDecimal >= 0)); // Unsigned for 0-255, signed for negatives
    printf("Binary of %d: %s\n", userDecimal, userBinary);

    int foundSigned = 0, foundUnsigned = 0;

    // Step 4: Generate all signed (-128 to 127) and unsigned (0 to 255) binary numbers
    for (int num = -128; num < 128; num++) {
        char binaryStr[9];
        decimalToBinary(num, binaryStr, 0); // Signed
        if (strcmp(binaryStr, userBinary) == 0) {
            printf("Matching signed decimal number: %d -> Binary: %s\n", num, binaryStr);
            foundSigned = 1;
        }
    }

    for (int num = 0; num < 256; num++) {
        char binaryStr[9];
        decimalToBinary(num, binaryStr, 1); // Unsigned
        if (strcmp(binaryStr, userBinary) == 0) {
            printf("Matching unsigned decimal number: %d -> Binary: %s\n", num, binaryStr);
            foundUnsigned = 1;
        }
    }

    // Step 5: If no match was found
    if (!foundSigned && !foundUnsigned) {
        printf("No matching representation found!\n");
    }

    return 0;
}
