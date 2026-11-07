#include "caveintel/qnetwork.hpp"
#include "caveintel/backprop.hpp"
#include <algorithm>

using namespace caveintel;

void caveintel::QNetworkStudent::backprop(double learning_rate = 1e-5, double future_discount = .0999)
{
    for (const auto &[state, next, reward, action, done] : replays)
    {
        TrainingData data = {state, net};
        auto targetY = target(next);
        data.Y.at(action) = reward + future_discount * (*max_element(targetY.begin(), targetY.end())) * (int)(!done);
        ::backprop(net, data, learning_rate);
    }
    if ((iteration++) % 1000 == 0)
        target = net;
}