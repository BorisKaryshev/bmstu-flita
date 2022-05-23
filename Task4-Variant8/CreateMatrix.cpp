#include <iostream>
#include <random>
#include <fstream>
#include <chrono>

class RandIntPair {
private:
    std::default_random_engine engine;
    std::uniform_int_distribution<> dist;
    float probability_of_loop = 0.1; 
public:
    RandIntPair(int a, int b) :dist{a, b} {
        engine.seed(std::chrono::system_clock::now().time_since_epoch().count());
        };
    ~RandIntPair() {};
    void SetProbability(const float x) {probability_of_loop = x;};
    std::pair<int, int> operator()() {
        int range = dist.max() - dist.min();
        if (dist(engine) - dist.min() < range*probability_of_loop + 1 && probability_of_loop != 0) {
            int x = dist(engine);
            return std::make_pair(x, x);
        }
        int x = dist(engine);
        int y = dist(engine);
        while (x == y) 
            y = dist(engine);
        return std::make_pair(x, y);
    };
};

void CreateMatrix(RandIntPair *eng, const int number_of_nodes, const int number_of_edges, const std::string filename = "input.txt") {
    std::ofstream f (filename);
    for(int i = 0 ; i < number_of_nodes; i++)
        f << i+1 << " ";
    f << '\n';

    for(int i = 0; i < number_of_edges; i++) {
        auto pair = (*eng)();
        for(int j = 0; j < number_of_nodes; j++) {
            if(j == pair.first || j == pair.second)
                f << "1 ";
            else 
                f << "0 ";
        }
        f << "\n";
    }

    f.close();
}

inline double strtoi(const char *str) {
    double output = 0;
    int x = 0;
    for(int i = 0; str[i] != '\0'; i++) { 
        if(str[i] >= '0' && str[i] <= '9' && x == 0)
            output = output* 10 +str[i] - '0';
        else if (str[i] >= '0' && str[i] <= '9' && x != 0) 
            output += (str[i] - '0')/pow(10, x++);
        else if (str[i] == '.')
            x++;
        
    }
    return output;
}

int main(int argc, char *argv[])
{
    int number_of_vertecies = (int) strtoi(argv[1]);
    int number_of_edges = (int) strtoi(argv[2]);
    double probability =  strtoi(argv[3]);

    RandIntPair r {0, number_of_vertecies-1};
    r.SetProbability(probability);
    CreateMatrix(&r, number_of_vertecies, number_of_edges);

    return 0;
} 
