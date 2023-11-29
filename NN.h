#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>

using namespace std;

class NeuralNet {

    public:

        NeuralNet() {
            inputToHiddenLayerWeights = vector<vector<double>*>();
            hiddenLayerToOutputWeights = vector<vector<double>*>();
            hiddenLayerBiases = vector<double>();
            outputBiases = vector<double>();
        }
        
        ~NeuralNet() {
            for (int h = 0; h < hiddenLayerNodes; h++) {
                delete inputToHiddenLayerWeights[h];
            }
            for (int o = 0; o < outputNodes; o++) {
                delete hiddenLayerToOutputWeights[o];
            }
        }

        // builds the neural net from an input file
        void buildNeuralNet(string inputFileName);

        // saves the weights and biases to a file
        void saveNeuralNet(string outputFileName);

        // runs the neural net on a single input case and stores the outputs of each node in the hidden layer
        vector<double> runNeuralNet(const vector<double> &inputs, vector<double> *hiddenLayerOutputs = nullptr);

        // trains the neural net on the given test set for specified epochs
        void trainNeuralNet(const string &trainingSetFile, const unsigned long int &epochs, const double &learningRate);

    private:

        int inputNodes = 0; // number of input nodes
        int hiddenLayerNodes = 0; // number of nodes in the hidden layer
        int outputNodes = 0; // number of output nodes
        
        vector<vector<double>*> inputToHiddenLayerWeights; // (*inputToHiddenLayerWeights[hidden])[input]
        vector<vector<double>*> hiddenLayerToOutputWeights; // (*hiddenLayerToOutputWeights[output])[hidden]
        vector<double> hiddenLayerBiases; // hiddenLayerBiases[hidden]
        vector<double> outputBiases; // outputBiases[output]

        // trains neural net for a single epoch on the entire test set
        void singleEpoch(const string &trainingSetFile, const double &learningRate);

        // 1 / (1 + e^d)
        [[nodiscard]] inline double sigmoid(double d) const {return 1.0/(1.0+exp(d));}

        // nodeOutput * (1 - nodeOutput)
        [[nodiscard]] inline double sigmoidPrime(double nodeOutput) const {return nodeOutput*(1-nodeOutput);}

        // helper function for printing doubles up to given decimal places
        [[nodiscard]] string doubleToString(double d, int decimals = 3) const;
};