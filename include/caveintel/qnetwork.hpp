#pragma once
#include "caveintel/network.hpp"

using namespace std;
namespace caveintel
{
    struct Replay
    {
        vector<double> state;
        vector<double> next_state;
        double reward;
        int action;
        bool done;
    };

    struct QNetworkStudent
    {
        Network &net;
        Network target;
        vector<Replay> replays = {};
        int iteration = 1;

        QNetworkStudent(Network &net) : net(net), target(net) {};
        void backprop(double learning_rate, double future_discount);
    };
}