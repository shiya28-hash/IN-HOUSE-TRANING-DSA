#include <iostream>
#include <stack>
#include <string>
using namespace std;

// Operation types for undo/redo
enum OperationType {
    ADD,
    DELETE
};

// Structure to store an operation
struct Operation {
    OperationType operationType;
    char character;
    int position;
};

// Text Editor class
class TextEditor {
private:
    string textContent;
    stack<Operation> undoStack;
    stack<Operation> redoStack;

public:
    // Show current text
    void showContent() {
        cout << "\nText: \"" << textContent << "\"\n";
    }

    // Add character at position
    void addCharacter(char ch, int pos) {
        if (pos < 0 || pos > textContent.length()) {
            cout << "Invalid position!\n";
            return;
        }
        textContent.insert(pos, 1, ch);
        undoStack.push({ADD, ch, pos});
        while (!redoStack.empty()) redoStack.pop(); // Clear redo
        cout << "Added '" << ch << "' at position " << pos << ".\n";
        showContent();
    }

    // Delete character from position
    void deleteCharacter(int pos) {
        if (pos < 0 || pos >= textContent.length()) {
            cout << "Invalid position!\n";
            return;
        }
        char removedChar = textContent[pos];
        textContent.erase(pos, 1);
        undoStack.push({DELETE, removedChar, pos});
        while (!redoStack.empty()) redoStack.pop(); // Clear redo
        cout << "Deleted '" << removedChar << "' from position " << pos << ".\n";
        showContent();
    }

    // Undo last operation
    void undo() {
        if (undoStack.empty()) {
            cout << "Nothing to undo.\n";
            return;
        }
        Operation last = undoStack.top();
        undoStack.pop();

        if (last.operationType == ADD) {
            textContent.erase(last.position, 1);
            cout << "Undo Add: Removed '" << last.character << "'\n";
        } else {
            textContent.insert(last.position, 1, last.character);
            cout << "Undo Delete: Restored '" << last.character << "'\n";
        }
        redoStack.push(last);
        showContent();
    }

    // Redo last undone operation
    void redo() {
        if (redoStack.empty()) {
            cout << "Nothing to redo.\n";
            return;
        }
        Operation last = redoStack.top();
        redoStack.pop();

        if (last.operationType == ADD) {
            textContent.insert(last.position, 1, last.character);
            cout << "Redo Add: Added '" << last.character << "'\n";
        } else {
            textContent.erase(last.position, 1);
            cout << "Redo Delete: Deleted '" << last.character << "'\n";
        }
        undoStack.push(last);
        showContent();
    }
};

int main() {
    TextEditor editor;
    int choice;
    char inputChar;
    int position;

    do {
        cout << "\nText Editor Menu:\n";
        cout << "1. Add Character\n";
        cout << "2. Delete Character\n";
        cout << "3. Undo\n";
        cout << "4. Redo\n";
        cout << "5. Show Text\n";
        cout << "0. Exit\n";
        cout << "Choose option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter character to add: ";
                cin >> inputChar;
                cout << "Enter position: ";
                cin >> position;
                editor.addCharacter(inputChar, position);
                break;
            case 2:
                cout << "Enter position to delete: ";
                cin >> position;
                editor.deleteCharacter(position);
                break;
            case 3:
                editor.undo();
                break;
            case 4:
                editor.redo();
                break;
            case 5:
                editor.showContent();
                break;
            case 0:
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid option.\n";
        }
    } while (choice != 0);

    return 0;
}
