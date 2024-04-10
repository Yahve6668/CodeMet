#include <bits/stdc++.h> 
bool comparePair(const std::pair<int, int>& p1, const std::pair<int, int>& p2) { 
    return (p1.first != p2.first?p1.first < p2.first: p1.second < p2.second); // Comparar por el primer elemento del par de mayor a menor 
} 
 

int main(){ 
	int n,m; 
	std::cin >> n >> m; 
    std::cout<< n<< " "<<m;
	std::vector<int> v [ 10000+1 ]; 
	std::vector<int >sizes ( 10000+1 ); 
	std::vector<int >querys ( 10000 ); 
	for (int i = 0; i < n; ++i){ 
		int time ,typ ,size ,op; 
		std::cin >> time >> typ >> size >> op; 
		v[ typ ].push_back( i+1 ); 
		sizes[ typ ] = size; 
		querys[ i ] = typ; 
	} 

	std::vector<std::pair< int , int > >cache; 
    int espa = m; 
    int accesos = 0; 
    for (int i = 0; i < n; ++i){ 
         int k = querys [ i ];
         //std::cout << i+1 <<" es "<<espa<<" ase "<< accesos <<" cahce "; 
         for(auto a:cache){
            std::cout<<a.first<<" ";
         }

        std::cout<<"\n";

         std::pair<int ,int >r = { k , sizes [ k ] };   
         if(std::binary_search(cache.begin() ,cache.end() , r ,comparePair)){
            continue;
         }
         accesos+=1;   
         if( v[ k ].size() > 1  && espa >= sizes [ k ]  ){ 
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
               // ordeno por ditancias si no por k 
               //std::sort(candidados.begin(), candidados.end(),[](auto a,auto b){
               std::partial_sort(candidados.begin(), candidados.begin() + std::min(3, static_cast<int>(candidados.size())),candidados.end(), [](auto a, auto b) { 
                     return a.second != b.second ? a.second > b.second : a.first < b.first; 
              });
                

                int tamallo = candidados.size();

                // for que indica que show con los que saca 
               for(int x = 0;x < candidados.size(); ++x ){
                     if(candidados[x].second==INT_MAX){
                         // libero el k espacio 
                         espa+= cache[ candidados[x].first ].second;
                         cache[ candidados[x].first ].first = -1;  
                         cache.erase( cache.begin() + candidados[x].first );
                     }else if( espa <= sizes [ k ] ){
                         espa+= cache[ candidados[x].first ].second;
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
     
     std::cout<<accesos<<" "<<double(n - accesos) / n;
	return 0; 
}
/*
35 
*/