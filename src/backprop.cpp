#include "caveintel/backprop.hpp"
#include <bits/stdc++.h>

using namespace std;
using namespace caveintel;

double train(Network &net, const TrainingData &data, const double learning_rate) // Worst complexity O(l*max(n)**2) : n-neurons in one layer, l-layers
{
    auto Ynet = net(data.X);
    if (Ynet.size() != data.Y.size())
        throw invalid_argument("data");
    double loss = 0;
    for (size_t i = 0; i < Ynet.size(); i++)
    {
        net.layers[net.layers.size() - 1][i] = net.layers[net.layers.size() - 1].actDer(net.layers[net.layers.size() - 1][i]) * (Ynet[i] - data.Y[i]);
        loss += pow(Ynet[i] - data.Y[i], 2) * .5;
    }
    for (int i = net.layers.size() - 1; i >= 0; i--)
    {
        auto &layer = net.layers[i];
        if (i == 0)
        {
            auto &prev_layer = data.X;
            // apply gradient
            for (size_t j = 0; j < prev_layer.size(); j++)
            {
                auto y = prev_layer[j];
                for (size_t k = 0; k < layer.size; k++)
                {
                    layer.weights[j * layer.size + k] -= learning_rate * y * layer[k];
                }
            }
            for (size_t k = 0; k < layer.size; k++)
            {
                layer.biases[k] -= learning_rate * layer[k];
            }
        }
        else
        {
            auto &prev_layer = net.layers[i - 1];
            // apply gradient
            for (size_t j = 0; j < prev_layer.size; j++)
            {
                auto actDer = prev_layer.actDer(prev_layer[j]);
                auto y = prev_layer.act(prev_layer[j]);
                prev_layer[j] = 0;
                for (size_t k = 0; k < layer.size; k++)
                {
                    prev_layer[j] += layer[k] * layer.weights[j * layer.size + k];
                    layer.weights[j * layer.size + k] -= learning_rate * y * layer[k];
                }
                prev_layer[j] *= actDer;
            }
            for (size_t k = 0; k < layer.size; k++)
            {
                layer.biases[k] -= learning_rate * layer[k];
            }
        }
    }
    return loss;
}
