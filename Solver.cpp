#include "Solver.h"


bool cmp(std::pair<std::vector<bool>, double> pair1, std::pair<std::vector<bool>, double> pair2){
    return pair1.second > pair2.second;
}

Solver::Solver(std::pair<double, std::vector<item>> data, int N = 20){
    size_of_population = N;
    items = data.second;
    max_weight = data.first;
}
double Solver::fit(std::vector<bool> X){

    double value = 0;
    double weight = 0;

    for(int i = 0; i < X.size(); i++){
        if(X[i]){
            value += items[i].first;
            weight += items[i].second;
        }
    }

    return weight <= max_weight ? value : 0;
}


void Solver::init_gen(){
    gen.resize(size_of_population);
    for(int k = 0; k < size_of_population; k++){
        gen[k].first.resize(items.size());
        for(int i = 0; i < items.size(); i++){
            if(double(rand())/RAND_MAX < 0.2) gen[k].first[i] = true;
        }
        gen[k].second = fit(gen[k].first);
    }
    sort(gen.begin(), gen.end(), cmp);

}

void Solver::mutation(){
    for(int k = 0; k < gen.size(); k++){
        for(int i = 0; i < items.size(); i++){
            if(double(rand())/RAND_MAX < mutation_chanse) gen[k].first[i] = !gen[k].first[i];
        }
        gen[k].second = fit(gen[k].first);
    }
    sort(gen.begin(), gen.end(), cmp);
    return;
}

void Solver::mate(){
    int n = items.size();
    int i, j, k;
    std::vector<std::pair<std::vector<bool>, double>> new_gen;
    std::vector<bool> new_ind1(n), new_ind2(n);
    
    for(i = 0; i < size_of_population; i++){
        for( j = i+1; j < size_of_population; j++){
            if(double(rand())/RAND_MAX < crossover_chasse){
                std::cout << "IF\n";
                for(k = 0; k < n/2; k++){
                    new_ind1[k] = gen[i].first[k];
                    new_ind2[k] = gen[j].first[k];
                }
                for(k = n/2; k < n; k++){
                    new_ind1[k] = gen[j].first[k];
                    new_ind2[k] = gen[i].first[k];
                }
                std::cout << "ROJAU\n";
                new_gen.push_back(std::make_pair(new_ind1, fit(new_ind1)));
                new_gen.push_back(std::make_pair(new_ind2, fit(new_ind2)));
                std::cout << "RODIL\n";
            }
        }
    }
    gen = new_gen;
    mutation();
    std::cout << "MUTIROVAL\n";
    gen.resize(size_of_population);

    return;
}


std::vector<bool> Solver::solve(int number_of_generetions){
    init_gen();
    for(int i = 0; i < number_of_generetions; i++) mate();
    
    std::cout << gen[0].second << std::endl;
    return gen[0].first;
}

