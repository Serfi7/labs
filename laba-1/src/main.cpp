#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

#include "../include/Sorter.hpp"

#include "../include/array/ArraySequence.hpp"
#include "../include/list/LinkedListSequence.hpp"

using namespace std;

int compNums(const int& num1, const int& num2) {
    return num1 > num2;
}

int matrixCommand() {
    int command = -1;

    cout << "Input command:"<< endl;
    cout << "    1) Print first matrix"<< endl;
    cout << "    2) Print second matrix"<< endl;
    cout << "    3) Multiple matrix to scalar"<< endl;
    cout << "    4) Summarize first and second matrixes"<< endl;
    cout << "    5) Calculate matrix norm" << endl;
    cout << "Command: ";

    cin >> command;

    return command;
}

Sequence<int>* generateSequence(int length) {
    Sequence<int>* seq = new ArraySequence<int>(length);

    for (int i = 0; i < length; i++) {
        int random = rand() - RAND_MAX / 2;

        seq->Append(random);
    }

    return seq;
}

int renderRandomSequenceCommands() {
    cout << "Input command:"<< endl;
    cout << "    1) Sharek sort sequence"<< endl;
    cout << "    2) Quick sort sequence"<< endl;
    cout << "    3) Print source sequence" << endl;
    cout << "    4) Menu"<< endl;
    cout << "Command: ";

    int command;
    cin >> command;

    cout << command;

    return command;
}

string joinSequence(Sequence<int>* seq, string delimiter = " "){
    string strSeq;
    int length = seq->GetLength();

    for (int i = 0; i < length - 1; i++) {
        int current = seq->Get(i);

        strSeq += to_string(current);
        strSeq += delimiter;
    }

    strSeq += to_string(seq->Get(length - 1));

    return strSeq;
}

void randomSequence() {
    cout << "Input sequence length: ";

    int length;
    cin >> length;

    if (length < 1) {
        cout << "Wrong length (less 1)" << endl;

        return;
    }

    Sequence<int>* seq = generateSequence(length);

    ISorter<int>* sorter = new Sorter<int>();

    while (1) {
        int command = renderRandomSequenceCommands();

        switch (command) {
            case 1: {
                auto start = std::chrono::high_resolution_clock::now();
                Sequence<int>* sortedSeq = sorter->ShakerSort(seq, &compNums);
                auto end = std::chrono::high_resolution_clock::now();

                double microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                cout << "Sequence was sorted using shaker sorting (" << microseconds / 1000 << " ms). Print?(y/n)";

                char no = 'n';
                cin >> no;

                if (no == 'y') {
                    cout << joinSequence(sortedSeq, ", ") << endl;
                }

                break;
            }
            case 2: {
                auto start = std::chrono::high_resolution_clock::now();
                Sequence<int>* sortedSeq = sorter->QuickSort(seq, &compNums);

                for (int i = 0; i < seq->GetLength() - 1; i++) {
                    if (sortedSeq->Get(i) >= seq->Get(i + 1)) {
                        cout << "Not sorted";
                    }
                }

                for (int i = 0; i < sortedSeq->GetLength() - 1; i++) {
                    if (sortedSeq->Get(i) >= sortedSeq->Get(i + 1)) {
                        cout << "Bad sort " << i << " " << i + 1 << endl;
                    } else {
                        cout << "Good " << i << " ";
                    }
                }
                cout << endl;
                auto end = std::chrono::high_resolution_clock::now();

                double microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                cout << "Sequence was sorted using quick sorting (" << microseconds / 1000 << " ms). Print?(y/n)";

                char no = 'n';
                cin >> no;

                if (no == 'y') {
                    cout << joinSequence(sortedSeq, ", ") << endl;
                }
                break;
            }
            case 3:
                cout << joinSequence(seq) << endl;
                break;
            case 4:
                return;
        }
    }
}

Sequence<int>* enterSequence(int length) {
    int data[length];

    cout << "Input numbers: ";

    for (int j = 0; j < length; ++j) {
        while (!(cin >> data[j])) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid numbers." << endl;
        }
    }

    return new ArraySequence<int>(data, length);
}

void enterSequence() {
    cout << "Input sequence length: ";

    int length;
    cin >> length;

    if (length < 1) {
        cout << "Wrong length (less 1)" << endl;

        return;
    }

    Sequence<int>* seq = enterSequence(length);

    ISorter<int>* sorter = new Sorter<int>();

    while (1) {
        int command = renderRandomSequenceCommands();

        switch (command) {
            case 1: {
                auto start = std::chrono::high_resolution_clock::now();
                Sequence<int>* sortedSeq = sorter->ShakerSort(seq, &compNums);
                auto end = std::chrono::high_resolution_clock::now();

                double microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                cout << "Sequence was sorted using shaker sorting (" << microseconds / 1000 << " ms). Print?(y/n)";

                char no = 'n';
                cin >> no;

                if (no == 'y') {
                    cout << joinSequence(sortedSeq, ", ") << endl;
                }

                break;
            }
            case 2: {
                auto start = std::chrono::high_resolution_clock::now();
                Sequence<int>* sortedSeq = sorter->QuickSort(seq, &compNums);
                auto end = std::chrono::high_resolution_clock::now();

                double microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                cout << "Sequence was sorted using quick sorting (" << microseconds / 1000 << " ms). Print?(y/n)";

                char no = 'n';
                cin >> no;

                if (no == 'y') {
                    cout << joinSequence(sortedSeq, ", ") << endl;
                }
                break;
            }
            case 3:
                cout << joinSequence(seq, ", ") << endl;
                break;
            case 4:
                return;
        }
    }
}

vector<int> readNumsFromFile() {
    vector<int> data;

    ifstream file("input.txt");

    if (!file.good()) {
        return data;
    }

    int number;

    while (file >> number) {
        data.push_back(number);
    }

    file.close();

    return data;
}

void writeResultToFile(Sequence<int>* seq, double microseconds, string sortSort) {
    ofstream output("output.txt", ios::ios_base::app);

    if (!output.is_open()) {
        cout << "Could not open file. Try again." << endl;
    }

    output << "Sort: " << sortSort << endl;
    output << "Sequence: " << joinSequence(seq) << endl;
    output << "Sequence length: " << seq->GetLength() << endl;
    output << "Sorting time: " << microseconds / 1000 << " ms" << endl;
    output << endl;
    output.close();
}

void fromFile() {
    vector<int> data = readNumsFromFile();

    if (!data.size()) {
        cout << "Bad file. Try again" << endl;

        return;
    }

    int nums[data.size()];
    for (int i = 0; i < data.size(); i++) {
        nums[i] = data[i];
    }

    Sequence<int>* seq = new ArraySequence<int>(nums, data.size());

    ISorter<int>* sorter = new Sorter<int>();

    while (1) {
        int command = renderRandomSequenceCommands();

        switch (command) {
            case 1: {
                auto start = std::chrono::high_resolution_clock::now();
                Sequence<int>* sortedSeq = sorter->ShakerSort(seq, &compNums);
                auto end = std::chrono::high_resolution_clock::now();

                double microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                cout << "Sequence was sorted using shaker sorting (" << microseconds / 1000 << " ms). Write to? (Console/File/No):";

                string writeMethod = "N";
                cin >> writeMethod;

                if (writeMethod == "C" || writeMethod == "Console") {
                    cout << joinSequence(sortedSeq, ", ") << endl;
                    break;
                }

                if (writeMethod == "F" || writeMethod == "File") {
                    writeResultToFile(sortedSeq, microseconds, "Shaker");
                    break;
                }

                break;
            }
            case 2: {
                auto start = std::chrono::high_resolution_clock::now();
                Sequence<int>* sortedSeq = sorter->QuickSort(seq, &compNums);
                auto end = std::chrono::high_resolution_clock::now();

                double microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                cout << "Sequence was sorted using shaker sorting (" << microseconds / 1000 << " ms). Write to? (Console/File/No):";

                string writeMethod = "N";
                cin >> writeMethod;

                if (writeMethod == "C" || writeMethod == "Console") {
                    cout << joinSequence(sortedSeq) << endl;
                    break;
                }

                if (writeMethod == "F" || writeMethod == "File") {
                    writeResultToFile(sortedSeq, microseconds, "Quick");
                    break;
                }

                break;
            }
            case 3:
                cout << joinSequence(seq) << endl;
                break;
            case 4:
                return;
        }
    }
}

class Cat {
public:
    string name;
    int age;

public:
    Cat() : name(""), age(0) {}
    Cat(string name, int age)
        : name(name),
          age(age)
    {}

    bool operator==(const Cat &other) {
        return this->name == other.name && this->age == other.age;
    }

    bool operator!=(const Cat &other) {
        return !(*this == other);
    }
};

int comp(const Cat& cat1, const Cat& cat2) {
    return cat1.age > cat2.age;
};

string joinSequence(Sequence<Cat>* seq, string delimiter = " "){
    string strSeq;
    int length = seq->GetLength();

    for (int i = 0; i < length - 1; i++) {
        Cat current = seq->Get(i);

        strSeq += current.name;
        strSeq += " ";
        strSeq += to_string(current.age);
        strSeq += ", ";
    }

    Cat last = seq->Get(length - 1);
    strSeq += last.name;
    strSeq += " ";
    strSeq += to_string(last.age);

    return strSeq;
}

string joinCat(Cat cat) {
    string str = cat.name;
    str += " ";
    str += to_string(cat.age);

    return str;
}

int OddCat(const Cat& cat) {
    int oddCat = cat.age % 2 == 1;
    cout << oddCat << endl;
    return oddCat;
}

int main() {
    Cat cat1 = Cat("Barcik", 2);
    Cat cat2 = Cat("Vacya", 1);
    Cat cat3 = Cat("Vacya", 8);
    Cat cat4 = Cat("Vacya", 14);
    Cat cat5 = Cat("Vacya", 4);
    Cat cat6 = Cat("Vacya", 88);
    Cat cat7 = Cat("Vacya", 33);
    Cat cat8 = Cat("Ivan", 5);

    // Remove

    ArraySequence<Cat>* catsArr = new ArraySequence<Cat>(8);
    catsArr->Append(cat1);
    catsArr->Append(cat2);
    catsArr->Append(cat3);
    catsArr->Append(cat4);
    catsArr->Append(cat5);
    catsArr->Append(cat6);
    catsArr->Append(cat7);
    catsArr->Append(cat8);

    auto oddCat = [](const Cat& cat) -> int {
        int oddCat = cat.age % 2 == 1;
        cout << "odd cat" << endl;
        return oddCat;
    };

    catsArr->Remove(oddCat);
    cout << catsArr->GetLength() << endl;
    cout << joinSequence(catsArr) << endl;

    return 0;

    // int
    ISorter<int>* sorterInt = new Sorter<int>();

    // LinkedListSequence<int>
    LinkedListSequence<int>* intList = new LinkedListSequence<int>();
    intList->Append(55);
    intList->Append(44);
    intList->Append(66);

    cout << "LinkedListSequence<int>: "<< endl;
    cout << joinSequence(intList) << endl;
    Sequence<int>* intSortedList = sorterInt->LinkedListSort(intList, *compNums);
    cout << joinSequence(intSortedList) << endl << endl;

    // Cats
    // ISorter<Cat>* sorter = new Sorter<Cat>();

    // LinkedListSequence<Cat>
    // LinkedListSequence<Cat>* catsLinkedList = new LinkedListSequence<Cat>();
    // catsLinkedList->Append(cat1);
    // catsLinkedList->Append(cat2);
    // catsLinkedList->Append(cat3);
    // catsLinkedList->Append(cat4);
    // catsLinkedList->Append(cat5);
    // catsLinkedList->Append(cat6);
    // catsLinkedList->Append(cat7);
    // catsLinkedList->Append(cat8);

    // cout << "LinkedListSequence<Cat>: " << endl;
    // cout << joinSequence(catsLinkedList) << endl;
    // Sequence<Cat>* sortedCatsList = sorter->LinkedListSort(catsLinkedList, *comp);
    // cout << joinSequence(sortedCatsList) << endl << endl;

    return 0;

    while (1) {
        cout << "Enter command:" << endl;
        cout << "1) Generate sequence" << endl;
        cout << "2) Enter sequence" << endl;
        cout << "3) Read from file (input.txt)" << endl;
        cout << "0) Exit" << endl;
        cout << "Command: ";

        int command = -1;

        cin >> command;

        switch (command) {
            case 1:
                randomSequence();
                break;
            case 2:
                enterSequence();
                break;
            case 3:
                fromFile();
                break;
            default:
                return 0;
        }

        cin.clear();
    }
}
