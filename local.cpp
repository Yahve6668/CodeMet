#include <bits/stdc++.h> 
bool comparePair(const std::pair<int, int>& p1, const std::pair<int, int>& p2) { 
    return (p1.first != p2.first?p1.first < p2.first: p1.second < p2.second); // Comparar por el primer elemento del par de mayor a menor 
} 
int main(){ 
   int n,m; 
   std::cin>>n>>m; 
 
 
   std::vector<int> v [ 10000+1 ]; 
   std::vector<int >sizes ( 10000+1 ); 
   std::deque<int> querys ( n ); 
   std::deque<int> querysper(n); 
    std::deque<int> querysper2(n); 
   std::deque<int> recorridocache(n); 
   for (int i = 0; i < n; ++i){ 
      int time ,typ ,size ,op; 
      std::cin >> time >> typ >> size >> op; 
      v[ typ ].push_back( i+1 ); 
      sizes[ typ ] = size; 
      querys[ i ] = typ; 
   } 
    querysper = querys; 
    
    std::next_permutation(querysper.begin(),querysper.end()); 
    std::next_permutation(querysper.begin(),querysper.end()); 
    std::next_permutation(querysper.begin(),querysper.end()); 
    std::next_permutation(querysper.begin(),querysper.end()); 
    std::next_permutation(querysper.begin(),querysper.end()); 
    int sol = INT_MAX; 
    int nv=30
    ;
    int neroresg=INT_MAX;

    srand(time(0));
     do{ 
            int s=0; 
            int espa=m;
            int nerores=0;
           
            querysper2=querysper;
           //std::cout<<"----------------------"<< nv <<"\n";
           for(auto a:querysper){
                     std::cout<<a<<"x---";
            }
            std::cout<<"\n";
            std::vector<std::pair< int , int > >cache; 
            bool malasol= false;
             for(int i=0 ; i < n ;++i){ 

                     int k = querys [ i ]  ;      
            //         std::cout<<"i" <<i <<" "<<querys [ i ] << " "<< sizes [ k ]  <<"*******************\n";
                     int ress=0;
                    // for(auto ll:cache){
                    //   std::cout<<ll.first <<" ";
                    //   ress+= sizes[ll.first];
                    // }

                 //    std::cout<<"\n"<< ress << " es "<< m <<" cache \n";
                     if(malasol){
                       break;
                     }        
                     std::pair<int ,int >r = { k , sizes [ k ] }; 
                     if(std::binary_search(cache.begin() ,cache.end() , r ,comparePair)){ 
                        continue; 
                     } 
                     ++s; //sol
           //          std::cout<<"acesos "<< s <<"nerores "<<nerores  <<"\n";

                     if( espa >= sizes [ k ]  ){ 
                       cache.push_back( { k , sizes [ k ] } ); 
                       espa -= sizes [ k ]; 
                       std::sort( cache.begin() , cache.end() , comparePair); 
                       continue; 
                     }

                    
                    if( espa < sizes [ k ]  ) { 
           //              std::cout<<"aquiiiii ";
                         while(!querysper.empty()){
                             // meto el objeto k a la cache por que ya cabe

                             if(espa >= sizes [ k ] ){
                               cache.push_back( { k , sizes [ k ] } ); 
                               espa-=sizes [ k ];
                               std::sort( cache.begin() , cache.end() , comparePair); 
                                break; 
                              }

                              // la solucion ya tiene muchos errores 
                             if(nerores > neroresg ){
                                malasol = true;
                                break; 
                              } 

                              std::pair<int ,int >pc={querysper.front(),sizes[ querysper.front() ]}; 
                 //             std::cout<<querysper.front() <<" querry "<<sizes[ querysper.front() ] <<"\n";
                              if(std::binary_search(cache.begin() ,cache.end() , pc ,comparePair)){

                                  
                                  espa+=sizes[ querysper.front() ];
                 //                 std::cout<<"sale "<< querysper.front()<<" "<< espa<<"\n";
                                  querysper.pop_front();
                                  auto a = std::lower_bound(cache.begin() ,cache.end() , pc ,comparePair);

                                  cache[a-cache.begin()].first = -1;
                                  cache.erase(std::remove_if(cache.begin(), cache.end(), [](const std::pair<int, int>& p) { return p.first == -1; }), cache.end());
                                  std::sort( cache.begin() , cache.end() , comparePair); 
                              }else{
                                   querysper.push_back(querysper.front());
                                   ++nerores;
                        //           std::cout<<"aaaxx ";
                                   querysper.pop_front(); 
                              } 
                        } 
                    } 


                 }

                 long long t=sol + (long long)neroresg;
                 if(s + nerores < t && !malasol ){ 
                    sol=s; 
                    // std::cout<<"la solucion fue "<<malasol;
                    // std::cout<<"\n";
                     neroresg=nerores;
                     recorridocache=querysper2;

                }


            int pos1 = rand() % querysper2.size(); 
            int pos2 = rand() % querysper2.size();  
            while (pos1 == pos2) { 
                pos2 = rand() % querysper2.size(); 
            } 
            querysper = querysper2;
            std::swap(querysper[pos1], querysper[pos2]); 
            --nv;
            //std::cout<<s <<" sol "<<sol<<" "<<nerores <<" "<<neroresg <<"\n";
       
          } while (nv>0); 
         for(auto a:recorridocache){
            std::cout<<a<<" ";
         }
        std::cout<<"\n";
        std::cout<<sol<<" "<<neroresg<<" "<<double(n-sol)/n<<"\n"; 
       
} 
 

