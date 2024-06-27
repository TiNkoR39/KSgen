#include "Solver.cpp"



int main(){

    std::string filename = "ks_100_2";
    Parser p;
    Solver s(p.parse(filename), 100);
    std::vector<bool> ans = s.solve(100);

    for(int i = 0; i < ans.size(); i++) std::cout << ans[i] << " ";
    std::cout << std::endl;
    return 0;
}