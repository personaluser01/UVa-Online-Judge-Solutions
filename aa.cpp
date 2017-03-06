#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <bitset>
#include <cstring>
#include <stack>
#include <queue>
typedef unsigned long long ll;
using namespace std;

queue<int> stations[102];
int n,cap,q;
stack<int> cargo;
int moves;
int posicao;
int cont;

int main()
{
		    int sets; scanf("%d", &sets);
			    while (sets--){
						        posicao=0;
								        cont=0;
										        moves = 0;
												        scanf("%d %d %d", &n, &cap, &q);
														        for (int i = 1; i<=n; i++){
																		            int number; scanf("%d", &number);
																					            while (number--){
																										                int a; scanf("%d", &a);
																														                moves++;
																																		                stations[i].push(a);
																																						            }
																								        }

																        while (moves){
																				            posicao += 1;
																							            while (!cargo.empty() && stations[posicao].size()<q){
																												                if (cargo.top() != posicao) {stations[posicao].push(cargo.top());}// Puts on queue
																																                else { moves--;} // Unloads
																																				                cargo.pop();
																																								                cont++;
																																												            }
																										           
																										            if (!cargo.empty() && cargo.top() == posicao){
																															                cargo.pop();
																																			                moves--;
																																							                cont++;
																																											            }
																													           
																													            while (cargo.size()<cap && !stations[posicao].empty()){
																																		                cargo.push(stations[posicao].front());
																																						         
																																						                stations[posicao].pop();
																																										                cont++;
																																														            }
																																           
																																            posicao -=1;
																																			            if (moves){
																																								                posicao = (posicao+1)%n;
																																												                cont+=2;
																																																            }
																																						           
																																						        }
																		       
																		        cout << cont << endl;
																				        for (int i = 0; i<102; i++){
																								            while (!stations[i].empty()){
																													                stations[i].pop();
																																	            }
																											        }
																						        while (!cargo.empty()) cargo.pop();
																       
																    }
				    return 0;
}
