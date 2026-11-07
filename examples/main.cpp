#include <bits/stdc++.h>
#include "caveintel/logger.hpp"
#include "caveintel/network.hpp"
#include "caveintel/backprop.hpp"

using namespace std;
using namespace caveintel;

double sigmoid(double x)
{
    return 1. / (1. + exp(-x));
}

double ident(double x)
{
    return x;
}

double relu(double x)
{
    return max(0., x);
}

double reluDer(double x)
{
    return ((x > 0) ? 1 : 0);
}

long long getId()
{
    static long long id;
    return ++id;
}

main()
{
    Network nn({1, 16, 32, 32, 16, 1}, ident, [](double)
               { return 1.; });
    // progressbar(.99, 5);
    auto &log = Logger::get();
    log(LogType::INFO, "succes.");
    log.newBar(1, "smth", .65, 5);
    cin.get();
}