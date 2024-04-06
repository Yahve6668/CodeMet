#include <fstream>
#include <iostream>
#include <random>
#include <string>

int main(int argc, const char* argv[]) try {
   if (argc < 1 + 3) {
      throw std::invalid_argument("argc");
   }
   int t = std::stoi(argv[1]);
   int q = std::stoi(argv[2]);
   int s = std::stoi(argv[3]);
   std::mt19937_64 gen(s);

   std::uniform_int_distribution<int> dist_tam(1, 3);
   int tamaños[t];
   for (int i = 0; i < t; ++i) {
      tamaños[i] = dist_tam(gen);
   }

   std::ofstream ofs(std::to_string(t) + "_" + std::to_string(q) + "_" + std::to_string(s) + ".tr");
   std::uniform_int_distribution<int> dist_query(0, t - 1);
   for (int i = 0; i < q; ++i) {
      int elegido = dist_query(gen);
      ofs << i + 1 << " " << elegido + 1 << " " << tamaños[elegido] << " 0\n";
   }
} catch (...) {
   std::cout << argv[0] << " tipos queries semilla\n";
}
