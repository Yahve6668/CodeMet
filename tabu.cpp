#include <bits/stdc++.h>
bool comparePair(const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
    return (p1.first != p2.first?p1.first < p2.first: p1.second < p2.second); // Comparar por el primer elemento del par de mayor a menor
}

 
 
std::pair<std::vector<std::pair<int,int>> , double> solgloton(int n,int m, std::vector<int> v [ 10000+1 ],
    std::vector<int >sizes ,
    std::vector<int >querys){
    
    std::vector<std::pair<int,int>> solv;
 
    std::vector<std::pair< int , int > >cache;
    int espa = m;
    int accesos = 0;
    for (int i = 0; i < n; ++i){
         int k = querys [ i ];
 
 
         std::pair<int ,int >r = { k , sizes [ k ] };
         if(std::binary_search(cache.begin() ,cache.end() , r ,comparePair)){
            continue;
         }
         accesos+=1;
         if(  espa >= sizes [ k ]  ){
                cache.push_back( { k , sizes [ k ] } );
                espa -= sizes [ k ];
                std::sort( cache.begin() , cache.end() , comparePair);
                continue;
         }
           if( espa < sizes [ k ]  ) {
               std::vector< std::pair<int,int> > candidados;
               for(int x = 0 ;x < cache.size() ; ++x){
                 auto a = cache[x];
                 auto can = std::lower_bound( v[ a.first ].begin(), v[ a.first ].end() , i + 2);
                 if(can!=v[ a.first ].end() && *can - (i+1) != 1){
                    candidados.push_back({  x ,  *can-i });
                 }else if( can == v[ a.first ].end() ){
                   candidados.push_back({ x ,  INT_MAX });
                 }
               }

               std::partial_sort(candidados.begin(), candidados.begin() + std::min(3, static_cast<int>(candidados.size())),candidados.end(), [](auto a, auto b) {
                     return a.second != b.second ? a.second > b.second : a.first < b.first;
              });
 
 
                int tamallo = candidados.size();
 
                // for que indica que show con los que saca
               for(int x = 0;x < candidados.size(); ++x ){
                     if(candidados[x].second==INT_MAX){
                         espa+= cache[ candidados[x].first ].second;
                         solv.push_back({ cache[ candidados[x].first ].first  , cache[ candidados[x].first ].second });
                         cache[ candidados[x].first ].first = -1;
                     }else if( espa <= sizes [ k ] ){
                         espa+= cache[ candidados[x].first ].second;
                         solv.push_back({ cache[ candidados[x].first ].first  , cache[ candidados[x].first ].second });
                         cache[ candidados[x].first ].first = -1;
                     }else{
                        break;
                     }
               }
               cache.erase(std::remove_if(cache.begin(), cache.end(), [](const std::pair<int, int>& p) { return p.first == -1; }), cache.end());
       
               
               if( tamallo!=0 && espa >= sizes [ k ] ){
                   cache.push_back(r);
                   std::sort( cache.begin() , cache.end() , comparePair);
                   espa -= sizes [ k ];
                 }

         }
     }
       for(auto r:cache){
         solv.push_back(r);
       }
      return {solv,double(n - accesos)/n};
 
}


double costo(std::vector<std::pair<int,int>> orden,std::vector<int>sizes,int m,int n,std::vector<int>querys){
        std::deque<std::pair<int,int>> querysper(orden.begin(), orden.end());
        int espa=m;
        int s=0;
        std::vector<std::pair< int , int > >cache;
        int nerror=0;
            for(int i=0 ; i < n ;++i){
                 //std::cout<<i<<"ww\n";
                     int k = querys [ i ]  ;      
                         
                     std::pair<int ,int >r = { k , sizes [ k ] };
                     if(std::binary_search(cache.begin() ,cache.end() , r ,comparePair)){
                        continue;
                     }
                     ++s; // acesos

                     if( espa >= sizes [ k ]  ){
                       cache.push_back( { k , sizes [ k ] } );
                       espa -= sizes [ k ];
                       std::sort( cache.begin() , cache.end() , comparePair);
                       continue;
                     }

                   
                    if( espa < sizes [ k ]  ) {
                         while(!querysper.empty()){

                             if(espa >= sizes [ k ] ){
                                cache.push_back( { k , sizes [ k ] } );
                                espa-=sizes [ k ];
                                std::sort( cache.begin() , cache.end() , comparePair);
                                break;
                              }

                              if(std::binary_search(cache.begin() ,cache.end() , querysper.front() ,comparePair)){
                             
                                  espa+=querysper.front().second ;
                                 
                                  auto a = std::lower_bound(cache.begin() ,cache.end() , querysper.front() ,comparePair);
                                  querysper.pop_front();

                                  cache[a-cache.begin()].first = -1;
                                  cache.erase(std::remove_if(cache.begin(), cache.end(), [](const std::pair<int, int>& p) { return p.first == -1; }), cache.end());
                                  std::sort( cache.begin() , cache.end() , comparePair);
                              }else{
                                   //std::cout<<"aquiiiii puede siclarse \n";
                                   ++nerror;
                                   querysper.push_back(querysper.front());
                                   querysper.pop_front();
                                   if(nerror==n/2){
                                    //break;
                                   }
                              }
                        }
                    }
                     if(nerror==n){
                       break;
                    }
                 }
                return (nerror!=n  ? double (n-s) /n - (0.0001)*nerror : -100.0);
}

std::vector<std::vector<std::pair<int,int>> > get_neighbors(const std::vector<std::pair<int,int>>& solution){
    std::vector<std::vector<std::pair<int,int>>> neighbors;
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 100  ; j+=4) {
            std::vector<std::pair<int,int>> neighbor = solution;
            if(solution.size() % 4!=0 && j==solution.size() / 4){
              std::next_permutation(neighbor.begin() + j , neighbor.end());
            }else{
              std::next_permutation(neighbor.begin() + j , neighbor.begin() + j + 4);    
            }

            neighbors.push_back(neighbor);
        }
    }

    return neighbors;
}


std::pair<std::vector<std::pair<int,int>> , double>tabu(std::vector<std::pair<int,int>>solucionglo ,std::vector<int>querys ,std::vector<int> sizes,int n,int m,double solg,int iter,int rtabu){
    std::vector <std::pair<int,int>> bestorden = solucionglo;
    double betscosto=solg;   //  {2 3} {1 5} {4 6}  
    std::vector<std::pair<int,int>> solucion_actual = solucionglo;
    std::vector<std::vector<std::pair<int,int>> > lista;

       for(int i = 0 ; i < iter ; ++i ){
            std::cout<<i<<"\n";
            std::vector<std::vector<std::pair<int,int>>> vecinos = get_neighbors(solucion_actual);
            std::vector<std::pair<int,int>>  mejor_vecino ;//best_neighbor;
            double best_neighbor_fitness = std::numeric_limits<double>::min();


        for (const std::vector<std::pair<int,int>>& neighbor : vecinos) {
            if (std::find(lista.begin(),lista.end(), neighbor) == lista.end()) {
                //std::cout<<"sss\n";
                double neighbor_fitness = costo(neighbor,sizes,m,n,querys) ;
               // std::cout<<neighbor_fitness<<"dd\n ";
                if (neighbor_fitness > best_neighbor_fitness) {
                    mejor_vecino = neighbor;
                    best_neighbor_fitness = neighbor_fitness;
                }
            }
        }


        if (mejor_vecino.empty()) {
            break;
        }

        solucion_actual = mejor_vecino;
        lista.push_back(mejor_vecino);
        if (lista.size() > rtabu) {
            lista.erase(lista.begin());
        }
        if (costo(mejor_vecino,sizes,m,n,querys)
            > costo(bestorden,sizes,m,n,querys)) {
             bestorden = mejor_vecino;
             betscosto = best_neighbor_fitness;
        }
    }


   return {bestorden ,  betscosto};
}
 
 
 
 
 
int main(){
    int n,m;
    std::cin >> n >> m;
    std::vector<int> v [ 10000+1 ];
    std::vector<int >sizes ( 10000+1 );
    std::vector<int >querys ( 10000 );
    std::map<int,int>mapa;
    for (int i = 0; i < n; ++i){
        int time ,typ ,size ,op;
        std::cin >> time >> typ >> size >> op;
        v[ typ ].push_back( i+1 );
        mapa[typ]+=1;
        sizes[ typ ] = size;
        querys[ i ] = typ;
    }
 
    std::pair<std::vector<std::pair<int ,int> > , double> s=solgloton(n,m,v,sizes,querys);
    std::vector<std::pair<int,int>>orden=s.first;
    double costo= s.second;

     std::map<int,int>mapa2;
     for(auto a: s.first){
         std::cout<<a.first<<" ";
         mapa2[a.first]+=1;
     }
     int suma=0;
     for(auto a:mapa){
        for(int i=0;i < a.second-mapa2[a.first];++i){
            orden.push_back( {a.first , sizes [a.first]} );
            suma+=a.second-mapa2[a.first];
        }
     }

    std::pair<std::vector<std::pair<int ,int> > , double> res= tabu(orden,querys,sizes,n,m,costo,3,3);
     
     std::cout<<"\n";
     std::cout<<  costo <<"ttt\n";
     std::cout<< s.first.size()<<"x\n";
     for(auto a: res.first){
        std::cout<<a.first<<" ";
     }
     
     std::cout<<"\n";
     std::cout<< res.second<<"\n";
   return 0;
}