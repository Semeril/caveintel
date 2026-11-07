#pragma once
#include <vector>
#include <functional>
#include <string>

using namespace std;
namespace caveintel
{
    struct Layer
    {

        function<double(double)> act;
        function<double(double)> actDer;
        vector<double> values;
        vector<double> weights;
        vector<double> biases;
        size_t size;

        Layer() = default;

        Layer(size_t previous_layer_size, size_t size, function<double(double)> act, function<double(double)> actDer);

        double &operator[](size_t i);

        template <class Archive>
        void save(Archive &ar) const;

        template <class Archive>
        void load(Archive &ar);
    };

    struct Network
    {
        vector<Layer> layers;
        size_t inputs;

        Network(const vector<int> &shape, function<double(double)> act, function<double(double)> actDer);

        template <class Archive>
        void save(Archive &ar) const;

        template <class Archive>
        void load(Archive &ar);

        vector<double> operator()(const vector<double> &input); // Worst complexity O(l*max(n)**2) : n-neurons in one layer, l-layers
    };

    void save_network(const Network &net, string filename); // in json format

    Network load_network(string filename, const vector<int> &shape, const function<double(double)> &act, const function<double(double)> &actDer);
}