#include <bits/stdc++.h> 
bool comparePair(const std::pair<long long, long long>& p1, const std::pair<long long, long long>& p2) { 
    return (p1.first != p2.first?p1.first < p2.first: p1.second < p2.second); // Comparar por el primer elemento del par de mayor a menor 
} 
 
int main(){  
long long n,m; 
std::cin >> n >> m; 

    std::vector<long long> v [ 10000+1 ]; 
    std::vector<long long >sizes ( 10000+1 ); 
    std::vector<long long >querys ( 10000 );
for (long long i = 0; i < n; ++i){ 
  long long time ,typ ,size ,op; 
      std::cin >> time >> typ >> size >> op; 
      v[ typ ].push_back( i+1 ); 
      sizes[ typ ] = size; 
      querys[ i ] = typ; 
} 
 
std::vector<std::pair< long long , long long > >cache; 
    long long espa = m; 
    long long accesos = 0; 
    for (long long i = 0; i < n; ++i){ 
         long long k = querys [ i ]; 
         //std::cout << i+1 <<" es "<<espa<<" ase "<< accesos <<" cahce "; 
         for(auto a:cache){ 
            std::cout<<a.first<<" "; 
         }   
 
        std::cout<<"\n"; 
 
         std::pair<long long ,long long >r = { k , sizes [ k ] }; 
         if(std::binary_search(cache.begin() ,cache.end() , r ,comparePair)){ 
            continue; 
         } 
         accesos+=1; 
         // me todo da igual siempre y cuando tenaga al menos dos peticones 
         if( v[ k ].size() > 1  && espa >= sizes [ k ]  ){ 
                cache.push_back( { k , sizes [ k ] } ); 
                espa -= sizes [ k ]; 
                std::sort( cache.begin() , cache.end() , comparePair); 
                continue; 
         } 
           // decido si es bueno meterlo o no en base al criterio de pesos*ditancias*npeticiones 
 
           if( espa < sizes [ k ]  ) { 
               // k y distancias * size +  npeticones 
               std::vector< std::pair<long long,long long> > candidados; 
                 long long tamallo = candidados.size(); 
                  auto ojo =  std::lower_bound( v[ k ].begin(), v[ k ].end() , i + 2); 
 
                  long long sojo = LLONG_MAX; 
                  if(ojo!= v[ k ].end() ){ 
                     sojo =  (*ojo - (i+1) ) * sizes[ k ] + v[ k ].end() -ojo; 
                  } 

               for(long long x = 0 ;x < cache.size() ; ++x){ 
                 auto a = cache[x]; 
                 auto can = std::lower_bound( v[ a.first ].begin(), v[ a.first ].end() , i + 2); 
                 if(can!=v[ a.first ].end() && *can - (i+1) != 1&& sojo < (*can-(i+1)) * sizes[ a.first ] + v[ a.first ].end() -can ){ 
                    candidados.push_back({  x ,  (*can-(i+1)) * sizes[ a.first ] + v[ a.first ].end() -can}); 
                 }else if( can == v[ a.first ].end() ){ 
                   candidados.push_back({ x , LLONG_MAX}); 
                 } 
               } 
               // ordeno por ditancias si no por k 
                //std::sort(candidados.begin(), candidados.end(),[](auto a,auto b){
                  std::partial_sort(candidados.begin(), candidados.begin() + std::min(3, static_cast<int>(candidados.size())),candidados.end(), [](auto a, auto b) { 
                     return a.second != b.second ? a.second > b.second : a.first < b.first; 
              });

 
              
                // for que indica que show con los que saca 
 
               for(long long x = 0;x < candidados.size(); ++x ){ 
                     if(candidados[x].second==LLONG_MAX){ 
                         // libero el k espacio 
                         espa+= cache[ candidados[x].first ].second; 
                         cache[ candidados[x].first ].first = -1; 
                     }else if( espa <= sizes [ k ] ){ 
                         espa+= cache[ candidados[x].first ].second; 
                         cache[ candidados[x].first ].first = -1; 
                     }else{ 
                        break; 
                     } 
               }
              cache.erase(std::remove_if(cache.begin(), cache.end(), [](const std::pair<long long, long long>& p) { return p.first == -1; }), cache.end());
 
               if( tamallo!=0 && espa >= sizes [ k ] ){ 
                   cache.push_back(r); 
                   std::sort( cache.begin() , cache.end() , comparePair); 
                   espa -= sizes [ k ]; 
                 } 
         } 
     } 
     std::cout<<accesos<<" " << double(n - accesos) / n; 
return 0; 
}
//34