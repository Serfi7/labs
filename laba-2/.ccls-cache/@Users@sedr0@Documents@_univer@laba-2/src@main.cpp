#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>

#include "../test/Mock.hpp"
#include "../include/array/ArraySequence.hpp"
#include "../include/binary-search-tree/BinaryTreeBuilder.hpp"

#include "../include/histogram/Histogram.hpp"
#include "../include/histogram/HistogramBuilder.hpp"

using namespace std;
using namespace Mock;

void joinSequence(Sequence<int>* nums) {
    for (int i = 0; i < nums->GetLength() - 1; i++) {
        cout << nums->Get(i) << ", ";
    }

    cout << nums->Get(nums->GetLength() - 1) << endl;
}

void joinSequence(Sequence<string>* strs) {
    for (int i = 0; i < strs->GetLength() - 1; i++) {
        cout << strs->Get(i) << ", ";
    }

    cout << strs->Get(strs->GetLength() - 1) << endl;
}

void joinSequence(Sequence<Cat>* cats) {
    for (int i = 0; i < cats->GetLength(); i++) {
        cout << cats->Get(i).name << " " << cats->Get(i).age << ", " << endl;
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

ArraySequence<int>* readAges(ifstream &file) {
    auto ages = new ArraySequence<int>();

    string agesLine;
    getline(file, agesLine);

    istringstream iss(agesLine);
    int age;
    while (iss >> age) {
        ages->Append(age);
    }

    return ages;
}

ArraySequence<string>* readNames(ifstream &file) {
    auto names = new ArraySequence<string>();

    string namesLine;
    getline(file, namesLine);

    istringstream iss(namesLine);
    string name;
    while (iss >> name) {
        names->Append(name);
    }

    return names;
}

ArraySequence<Cat>* readCats(ifstream &file) {
    ArraySequence<Cat>* cats = new ArraySequence<Cat>();

    string catLine;
    while (getline(file, catLine)) {
        istringstream iss(catLine);
        string name;
        int age;

        iss >> name >> age;

        auto cat = Cat(name, age);
        cats->Append(cat);
    }

    return cats;
}

Histogram<Cat, int>* agesHistogram(Sequence<Cat>* cats, Sequence<int>* ages) {
    auto splitter = [](const Cat& cat) -> int {
        return cat.age;
    };

    auto histogramBuilder = HistogramBuilder<Cat, int>();
    auto histogram = histogramBuilder.FromSequence(
        cats,
        ages,
        splitter
    );

    return histogram;
}

Histogram<Cat, string>* namesHistogram(Sequence<Cat>* cats, Sequence<string>* names) {
    auto splitter = [](const Cat& cat) -> string {
        return cat.name;
    };

    auto histogramBuilder = HistogramBuilder<Cat, string>();
    auto histogram = histogramBuilder.FromSequence(
        cats,
        names,
        splitter
    );

    return histogram;
}

void writeResultToFile(Sequence<int>* seq, double microseconds, string sortSort) {
    ofstream output("output.txt", ios::ios_base::app);

    if (!output.is_open()) {
        cout << "Could not open file. Try again." << endl;
    }

    output << "Sort: " << sortSort << endl;
    output << "Sequence length: " << seq->GetLength() << endl;
    output << "Sorting time: " << microseconds / 1000 << " ms" << endl;
    output << endl;
    output.close();
}

void writeAgesHistogram(Histogram<Cat, int>* histogram) {
    ofstream output("output.txt", ios::ios_base::app);

    if (!output.is_open()) {
        cout << "Could not open file. Try again." << endl;
    }

    output << "Histogram by ages: " << endl;
    output << histogram->joinDevision("\n");
    output << endl;

    output.close();

    cout << "Histogram by ages was successfully write to 'output.txt'" << endl;
}

void writeNamesHistogram(Histogram<Cat, string>* histogram) {
    ofstream output("output.txt", ios::ios_base::app);

    if (!output.is_open()) {
        cout << "Could not open file. Try again." << endl;
    }

    output << "Histogram by names: " << endl;
    output << histogram->joinDevision("\n");
    output << endl;

    output.close();

    cout << "Histogram by names was successfully write to 'output.txt'" << endl;
    // cout << "Histogram by ages was successfully write to 'output.txt'" << endl;
    // cout << "Histogram by names:" << endl;
    // cout << histogram->joinDevision("\n");
    // cout << endl;
}

void fromFile() {
    ifstream file("input.txt");

    if (!file.good()) {
        cout << "Bad file. Back to menu" << endl;
        return;
    }

    auto agesRange = readAges(file);
    auto namesRange = readNames(file);
    auto cats = readCats(file);

    file.close();

    auto histogramByAges = agesHistogram(cats, agesRange);
    auto histogramByNames = namesHistogram(cats, namesRange);

    writeAgesHistogram(histogramByAges);
    writeNamesHistogram(histogramByNames);

    delete agesRange;
    delete namesRange;
    delete cats;
    delete histogramByAges;
    delete histogramByNames;
}

int main() {
    while (1) {
        cout << "Enter command:" << endl;
        cout << "1) From file" << endl;
        cout << "0) Exit" << endl;
        cout << "Command: ";

        int command = -1;

        cin >> command;

        switch (command) {
            case 1:
                fromFile();
                break;
            case 3:
                return 0;
        }

        cin.clear();
    }

    return 0;
}
