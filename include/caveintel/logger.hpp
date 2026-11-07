#pragma once
#include <string>
#include <mutex>
#include <fstream>
#include <unordered_map>
#include <vector>

using namespace std;
namespace caveintel
{
    enum class LogType
    {
        INFO,
        WARNING,
        ERROR
    };

    class Logger
    {
        int col = 1, row = 1;
        unordered_map<long long, tuple<int, string, double, int>> bars;
        ofstream file = ofstream("log.txt");
        static inline mutex m = mutex();

        Logger();

        static vector<string> split(const string &s, char delimiter);

    public:
        Logger(Logger &) = delete;

        Logger(Logger &&) = delete;

        void newBar(long long id, string what, double doneratio, int percent_per_cell);

        void updateBar(long long id, double doneratio);

        static Logger &get();

        void operator()(LogType type, string message);

        void space();

        template <typename T>
        void get_input(T &var);
    };
}