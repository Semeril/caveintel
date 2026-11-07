#include "caveintel/network.hpp"
#include "cereal/archives/json.hpp"
#include "cereal/types/vector.hpp"
#include <bits/stdc++.h>

random_device rd;
mt19937 gen(rd());

using namespace std;
using namespace caveintel;

Layer::Layer(size_t previous_layer_size, size_t size, function<double(double)> act, function<double(double)> actDer) : values(size, 0),
                                                                                                                       act(act),
                                                                                                                       actDer(actDer),
                                                                                                                       biases(size, 0),
                                                                                                                       size(size)

{
    normal_distribution<> distr(0, sqrt(2. / previous_layer_size));
    for (size_t i = 0; i < size * previous_layer_size; i++)
    {
        weights.push_back(distr(gen));
    }
}

double &Layer::operator[](size_t i)
{
    return values[i];
}

template <class Archive>
void Layer::save(Archive &ar) const
{
    ar(CEREAL_NVP(weights), CEREAL_NVP(biases));
}

template <class Archive>
void Layer::load(Archive &ar)
{
    ar(CEREAL_NVP(weights), CEREAL_NVP(biases));
}

Network::Network(const vector<int> &shape, function<double(double)> act, function<double(double)> actDer) : inputs(shape[0])
{
    for (size_t i = 1; i < shape.size(); i++)
    {
        if (i == shape.size() - 1)
            layers.emplace_back(shape[i - 1], shape[i], act, actDer);
        else
            layers.emplace_back(shape[i - 1], shape[i], [](double x)
                                { return max(0., x); }, [](double x)
                                { return ((x > 0) ? 1 : 0); });
    }
}
template <class Archive>
void Network::save(Archive &ar) const
{
    ar(CEREAL_NVP(layers));
}
template <class Archive>
void Network::load(Archive &ar)
{
    ar(CEREAL_NVP(layers));
}

vector<double> Network::operator()(const vector<double> &input) // Worst complexity O(l*max(n)**2) : n-neurons in one layer, l-layers
{
    if (input.size() != inputs)
        throw invalid_argument("input");
    for (size_t i = 0; i < layers.size(); i++)
    {
        auto &layer = layers[i];
        if (i == 0)
        {
            for (size_t j = 0; j < layer.size; j++)
            {
                layer[j] = 0;
                for (size_t k = 0; k < input.size(); k++)
                {
                    layer[j] += input[k] * layer.weights[k * layer.size + j];
                }
                layer[j] += layer.biases[j];
            }
        }
        else
        {
            auto &previous_layer = layers[i - 1];
            for (size_t j = 0; j < layer.size; j++)
            {
                layer[j] = 0;
                for (size_t k = 0; k < previous_layer.size; k++)
                {
                    layer[j] += previous_layer.act(previous_layer[k]) * layer.weights[k * layer.size + j];
                }
                layer[j] += layer.biases[j];
            }
        }
    }
    vector<double> output;
    for (auto z : layers[layers.size() - 1].values)
    {
        output.push_back(layers[layers.size() - 1].act(z));
    }
    return output;
}

void save_network(const Network &net, string filename) // in json format
{
    ofstream file(filename);
    cereal::JSONOutputArchive archive(file);

    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    ostringstream oss;
    oss << put_time(localtime(&currentTime), "%H:%M:%S %d-%m-%Y");

    archive(cereal::make_nvp("SaveDate", oss.str()), cereal::make_nvp("Network", net));
}

Network load_network(string filename, const vector<int> &shape, const function<double(double)> &act, const function<double(double)> &actDer)
{
    ifstream file(filename);
    cereal::JSONInputArchive archive(file);
    string _;
    Network net(shape, act, actDer);
    archive(_, net);
    return net;
}