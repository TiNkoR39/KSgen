#include "Parser.cpp"


bool cmp(std::pair<std::vector<bool>, double>, std::pair<std::vector<bool>, double>);

class Solver{
    int size_of_population;
    double max_weight;
    std::vector<item> items;
    std::vector<std::pair<std::vector<bool>, double>> gen;
    const double mutation_chanse = 0.01;
    const double crossover_chasse = 0.3;

public:
    Solver(std::pair<double, std::vector<item>>, int);
    
    void init_gen();
    void mate();
    void mutation();
    double fit(std::vector<bool>);

    std::vector<bool> solve(int);

};