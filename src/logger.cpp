#include "caveintel/logger.hpp"
#include "fmt/format.h"
#include <bits/stdc++.h>

using namespace caveintel;

string progressbar(double doneratio, int percent_per_cell)
{
    stringstream ss;
    doneratio *= 100;
    doneratio = floor(doneratio);
    ss << fmt::format("[{}%] [", (int)doneratio);
    for (int i = 0; i < ((int)doneratio) / percent_per_cell; i++)
    {
        ss << "#";
    }
    for (int i = 0; i < (100 / percent_per_cell - ((int)doneratio) / percent_per_cell); i++)
    {
        ss << "-";
    }
    ss << "]";
    string out = ss.str();
    return out;
};

Logger::Logger()
{
    cout << "\033[2J\033[H";
}

vector<string> Logger::split(const string &s, char delimiter)
{
    vector<string> result;
    stringstream ss(s);
    string part;

    while (getline(ss, part, delimiter))
        result.push_back(part);

    return result;
}

void Logger::newBar(long long id, string what, double doneratio, int percent_per_cell)
{
    lock_guard<mutex> lock(m);
    bars[id] = {row, what, doneratio, percent_per_cell};
    cout << fmt::format("\033[{};1H[\033[38;2;200;112;0m{}\033[0m] {}", row++, what, progressbar(doneratio, percent_per_cell));
    file << fmt::format("[{}] {}\n", what, progressbar(1, percent_per_cell));
}

void Logger::updateBar(long long id, double doneratio)
{
    lock_guard<mutex> lock(m);
    auto &[brow, what, ratio, ppc] = bars[id];
    ratio = doneratio;
    cout << fmt::format("\033[{};1H[\033[38;2;200;112;0m{}\033[0m] {}\033[{};1H", brow, what, progressbar(ratio, ppc), row - 1);
}

Logger &Logger::get()
{
    lock_guard<mutex> lock(m);
    static Logger logger;
    return logger;
}

void Logger::operator()(LogType type, string message)
{
    lock_guard<mutex> lock(m);
    auto lines = split(message, '\n');
    lines[0].at(0) = toupper(lines[0].at(0));
    switch (type)
    {
    case LogType::INFO:
        cout << fmt::format("\033[{};1H[\033[38;2;0;0;255m{}\033[0m] {}", row, "INFO", lines[0]);
        file << fmt::format("[{}] {}\n", "INFO", lines[0]);
        break;
    case LogType::WARNING:
        cout << fmt::format("\033[{};1H[\033[38;2;255;255;0m{}\033[0m] {}", row, "WARNING", lines[0]);
        file << fmt::format("[{}] {}\n", "WARNING", lines[0]);
        break;
    case LogType::ERROR:
        cout << fmt::format("\033[{};1H[\033[38;2;255;0;0m{}\033[0m] {}", row, "ERROR", lines[0]);
        file << fmt::format("[{}] {}\n", "ERROR", lines[0]);
        break;

    default:
        break;
    }

    row++;
}

void Logger::space()
{
    lock_guard<mutex> lock(m);
    row++;
    file << '\n';
}

template <typename T>
void Logger::get_input(T &var)
{
    lock_guard<mutex> lock(m);
    cout << fmt::format("\033[{};1H[\033[38;2;112;112;112m{}\033[0m] ", row, "USER INPUT");
    cin >> var;
    row++;
}
