#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

#define MAX 26

using namespace std;

string cleanKey(string key) {
    string cleanedKey;
    bool alphabet[MAX] = {false};

    for (char ch : key) {
        if (isalpha(ch) && !alphabet[toupper(ch) - 'A']) {
            cleanedKey.push_back(toupper(ch));
            alphabet[toupper(ch) - 'A'] = true;
        }
    }

    cleanedKey.erase(remove(cleanedKey.begin(), cleanedKey.end(), 'J'), cleanedKey.end());
    return cleanedKey;
}

void generateMatrix(const string& key, char matrix[5][5]) {
    string cleanedKey = cleanKey(key);

    int i = 0;
    int j = 0;
    for (char ch : cleanedKey) {
        matrix[i][j] = ch;
        j++;
        if (j == 5) {
            j = 0;
            i++;
        }
    }

    char letter = 'A';
    for (int k = 0; k < MAX; k++) {
        if (letter == 'J')
            letter++;
        if (cleanedKey.find(letter) == string::npos) {
            matrix[i][j] = letter;
            j++;
            if (j == 5) {
                j = 0;
                i++;
            }
        }
        letter++;
    }
}

void findPosition(const char matrix[5][5], char ch, int& row, int& col) {
    if (ch == 'J')
        ch = 'I';
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == ch) {
                row = i;
                col = j;
                return;
            }
        }
    }
}

string encrypt(const string& message, const string& key) {
    char matrix[5][5];
    generateMatrix(key, matrix);

    string encryptedMessage;
    for (size_t i = 0; i < message.length(); i += 2) {
        char ch1 = toupper(message[i]);
        char ch2 = (i + 1 < message.length()) ? toupper(message[i + 1]) : 'X';

        int row1, col1, row2, col2;
        findPosition(matrix, ch1, row1, col1);
        findPosition(matrix, ch2, row2, col2);

        if (row1 == row2) {
            col1 = (col1 + 1) % 5;
            col2 = (col2 + 1) % 5;
        } else if (col1 == col2) {
            row1 = (row1 + 1) % 5;
            row2 = (row2 + 1) % 5;
        } else {
            swap(col1, col2);
        }

        encryptedMessage += matrix[row1][col1];
        encryptedMessage += matrix[row2][col2];
    }
    return encryptedMessage;
}

string decrypt(const string& message, const string& key) {
    char matrix[5][5];
    generateMatrix(key, matrix);

    string decryptedMessage;
    for (size_t i = 0; i < message.length(); i += 2) {
        char ch1 = toupper(message[i]);
        char ch2 = (i + 1 < message.length()) ? toupper(message[i + 1]) : 'X';

        int row1, col1, row2, col2;
        findPosition(matrix, ch1, row1, col1);
        findPosition(matrix, ch2, row2, col2);

        if (row1 == row2) {
            col1 = (col1 - 1 + 5) % 5;
            col2 = (col2 - 1 + 5) % 5;
        } else if (col1 == col2) {
            row1 = (row1 - 1 + 5) % 5;
            row2 = (row2 - 1 + 5) % 5;
        } else {
            swap(col1, col2);
        }

        decryptedMessage += matrix[row1][col1];
        decryptedMessage += matrix[row2][col2];
    }
    return decryptedMessage;
}

bool isValidText(string text) {
    for (char ch : text) {
        if (!isalpha(ch))
            return false;
    }
    return true;
}

int main() {
    int choice;
    string text;
    string key;

    cout << "Name: Prayusha Acharya" << endl;
    cout << "Roll no: 1023" << endl;
    cout << "\n*******************" << endl;

    do {
        cout << "\nMenu:" << endl;
        cout << "1. Encrypt plain text" << endl;
        cout << "2. Decrypt cipher text" << endl;
        cout << "3. Exit" << endl;
        cout << "\nEnter your choice (1/2/3): ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter plain text string: ";
            cin >> text;

            if (!isValidText(text)) {
                cout << "Insert only alphabets!" << endl;
                continue;
            }

            cout << "Enter key: ";
            cin >> key;
            if (!isValidText(key)) {
                cout << "Insert only alphabets!" << endl;
                continue;
            }

            cout << "Cipher text: " << encrypt(text, key) << endl;
        } else if (choice == 2) {
            cout << "Enter cipher text string: ";
            cin >> text;

            if (!isValidText(text)) {
                cout << "Insert only alphabets!" << endl;
                continue;
            }

            cout << "Enter key: ";
            cin >> key;
            if (!isValidText(key)) {
                cout << "Insert only alphabets!" << endl;
                continue;
            }

            cout << "Plain text: " << decrypt(text, key) << endl;
        } else if (choice == 3) {
            cout << "Exiting..." << endl;
            break;
        } else {
            cout << "Invalid choice. Please choose 1, 2, or 3." << endl;
        }
    } while (true);

    return 0;
}
