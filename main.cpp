#include <iostream>
#include "NN.h"

using namespace std;

int test(NeuralNet &net);

int main() {
    NeuralNet net = NeuralNet();
    net.buildNeuralNet("testUntrained.txt");
    int before = test(net);
    net.trainNeuralNet("trainingSet.txt", 100, 0.05);
    int after = test(net);
    cout << "\nBefore: " << before << ", After: " << after << "\n";
    net.saveNeuralNet("testOut.txt");
    return 0;
}

int test(NeuralNet &net) {
    // open file
    fstream file;
    file.open("testSet.txt");
    if (!file.is_open()) {
        cerr << "File Does Not Exist";
    }

    string line, testSetLength, inputLength, outputLength, input, output;
    getline(file, line);
    stringstream buffer(line);
    
    buffer >> testSetLength;
    buffer >> inputLength;
    buffer >> outputLength;

    int wrong = 0;
    for (int t = 0; t < stoi(testSetLength); t++) {

        getline(file, line);
        stringstream buffer(line);

        vector<double> inputs = vector<double>();

        for (int i = 0; i < stoi(inputLength); i++) {
            buffer >> input;
            inputs.push_back(stod(input));
        }

        buffer >> output;
        if (static_cast<int>(round(net.runNeuralNet(inputs)[0])) != stoi(output)) {
            // cout << net.runNeuralNet(inputs)[0] << "\n";
            wrong++;
        }

    }

    // cout << "\n" << wrong << "\n\n";
    return wrong;
}