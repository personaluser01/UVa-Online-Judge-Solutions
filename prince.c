#include <stdio.h>
#include <memory.h>

int EuclidDistSqre( int x1, int y1, int x2, int y2 ){
   return ((x1 - x2)*(x1 - x2)+(y1 - y2)*(y1 - y2));
   }

   bool isObscuredIcon( int region[250][4], int ri, int iconrow, int iconcol)
   {
      for ( int i = 0; i < ri; i++){
	        if ((iconrow >= region[i][0] && iconrow <= region[i][2]) &&
			(iconcol >= region[i][1] && iconcol <= region[i][3]))
			         return true;
					    }
						   return false;
						   }

						   int main(){
						      
							     int Region[250][4], Icon[500][2], Mouse[2],
								 Ri = 0, Ii = 0, dist[2500], minDist, i , j;
								    char c[10000];
									   bool obscuredFlag[500], firstMouseEvent
									   = false;
									      memset(obscuredFlag, 1,
										  500*sizeof(bool));
										     //freopen("M:\\Documents and
											 //Settings\\prince\\Desktop\\142.txt","r",stdin);
											    while (scanf("%s",c) != EOF){
												      if (c[0] == '#'){
													           Ii = Ri = 0;
															            memset(obscuredFlag,
																		1,
																		500*sizeof(bool));
																		         firstMouseEvent
																				 =
																				 false;
																				          continue;
																						        }
																								      if
																									  (c[0]
																									  ==
																									  'I'){
																									           scanf("%d%d",&Icon[Ii][0],&Icon[Ii++][1]);
																											         }
																													       else
																														   if
																														   (c[0]
																														   ==
																														   'R'){
																														            scanf("%d%d%d%d",&Region[Ri][0],&Region[Ri][1],&Region[Ri][2],&Region[Ri++][3]);
																																	      }
																																		        else
																																				if(c[0]
																																				==
																																				'M'){
																																				         scanf("%d%d",&Mouse[0],&Mouse[1]);
																																						          bool
																																								  flag
																																								  =
																																								  false;
																																								           if
																																										   (!firstMouseEvent){
																																										               firstMouseEvent
																																													   =
																																													   true;
																																													               for
																																																   (
																																																   i
																																																   =
																																																   0;
																																																   i
																																																   <
																																																   Ii;
																																																   i++){
																																																                  if
																																																				  (!isObscuredIcon(Region,Ri,Icon[i][0],Icon[i][1]))
																																																				                    obscuredFlag[i]
																																																									=
																																																									false;
																																																									            }
																																																												         }
																																																														          for
																																																																  (
																																																																  i
																																																																  =
																																																																  Ri
																																																																  - 1;
																																																																	i
																																																																	>=
																																																																	>0;
																																																																	>i--){
																																																																	            if
																																																																				((Mouse[0]
																																																																				>=
																																																																				>Region[i][0]
																																																																				>&&
																																																																				>Mouse[0]
																																																																				><=
																																																																				>Region[i][2])
																																																																				>&&
																																																																				>(Mouse[1]
																																																																				>>=
																																																																				>>Region[i][1]
																																																																				>>&&
																																																																				>>Mouse[1]
																																																																				>><=
																																																																				>>Region[i][3])){ 
																																																																				               printf("%c",65+i);
																																																																							                  flag
																																																																											  =
																																																																											  true;
																																																																											                 break;
																																																																															             }
																																																																																		          }
																																																																																				           
																																																																																						            
																																																																																									         if
																																																																																											 (!flag){
																																																																																											             minDist
																																																																																														 =
																																																																																														 1000000;
																																																																																														             for
																																																																																																	 (i
																																																																																																	 =
																																																																																																	 0;
																																																																																																	 i
																																																																																																	 <
																																																																																																	 Ii;
																																																																																																	 i++){
																																																																																																	                dist[i]
																																																																																																					=
																																																																																																					EuclidDistSqre(
																																																																																																					Mouse[0],
																																																																																																					Mouse[1],
																																																																																																					Icon[i][0],
																																																																																																					Icon[i][1]
																																																																																																					);
																																																																																																					               if(minDist
																																																																																																								   > dist[i])
																																																																																																								                     minDist
																																																																																																													 =
																																																																																																													 dist[i];
																																																																																																													             }
																																																																																																																             

																																																																																																																			             for
																																																																																																																						 (j
																																																																																																																						 =
																																																																																																																						 0;
																																																																																																																						 j
																																																																																																																						 <
																																																																																																																						 i;
																																																																																																																						 j++){
																																																																																																																						                if
																																																																																																																										(dist[j]
																																																																																																																										==
																																																																																																																										minDist
																																																																																																																										&&
																																																																																																																										!obscuredFlag[j]){
																																																																																																																										                  printf("%3d",j+1);
																																																																																																																														                 }
																																																																																																																																		             }
																																																																																																																																					          }
																																																																																																																																							           printf("\n");

																																																																																																																																									         }
																																																																																																																																											    }
																																																																																																																																												   return
																																																																																																																																												   0;
																																																																																																																																												   }
