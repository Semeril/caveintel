#pragma once
#include <vector>
#include "caveintel/network.hpp"

using namespace std;

namespace caveintel
{
    struct TrainingData
    {
        vector<double> X;
        vector<double> Y;
        TrainingData(vector<double> X, vector<double> Y) : X(X), Y(Y) {};
        TrainingData(vector<double> X, function<vector<double>(vector<double>)> f) : X(X), Y(f(X)) {};
    };

    double backprop(Network &net, const TrainingData &data, const double learning_rate); // Worst complexity O(l*max(n)**2) : n-neurons in one layer, l-layers
}