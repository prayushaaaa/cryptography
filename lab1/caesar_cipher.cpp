#include<iostream>
#include<string>

#define MAX 26

using namespace std;

int isValidText(string text) {
    for (int i = 0; i < text.length(); i++) {
        if (!isalpha(text[i]))
            return false;
    }
    return true;
}

int isValidKey(int key) {
    return (key >= 0 && key <= 25);
}

string createCipher(string text, int key) {
    string cipherText;
    for (int i = 0; i < text.length(); i++) {
        char ch = toupper(text[i]);
        cipherText += char(int((ch + key - 65) % 26 + 65));
    }
    return cipherText;
}

string createPlainText(string text, int key) {
    string plainText;
    for (int i = 0; i < text.length(); i++) {
        char ch = toupper(text[i]);
        plainText += char(int((ch - key - 65 + 26) % 26 + 65));
    }
    return plainText;
}

int main() {
    int choice;
    string text;
    int key;

    cout << "Name: Prayusha Acharya" << endl;\
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

            cout << "Enter key (0-25): ";
            cin >> key;

            if (!isValidKey(key)) {
                cout << "Key should range from 0 to 25!" << endl;
                continue;
            }

            cout << "Cipher text: " << createCipher(text, key) << endl;
        } else if (choice == 2) {
            cout << "Enter cipher text string: ";
            cin >> text;

            if (!isValidText(text)) {
                cout << "Insert only alphabets!" << endl;
                continue;
            }

            cout << "Enter key (0-25): ";
            cin >> key;

            if (!isValidKey(key)) {
                cout << "Key should range from 0 to 25!" << endl;
                continue;
            }

            cout << "Plain text: " << createPlainText(text, key) << endl;
        } else if (choice == 3) {
            cout << "Exiting..." << endl;
            break;
        } else {
            cout << "Invalid choice. Please choose 1, 2, or 3." << endl;
        }
    } while (true);

    return 0;
}
