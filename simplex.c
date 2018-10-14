#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int main()
{
int rr,i=0,j=0,m=0,n=0,number,q=0,length=0,cons=0,p=0,t_var=0,x,l=0,enter,leave,value=0,rak,itr,count=0,counter=0;
float *b,*c,y=0,max=0,diff[10],mn=0,min[10],*cB,k,o,sum=0;
	  float **A,**a;	
FILE *ptr;
ptr = fopen("test.txt","r");
if(ptr == NULL)
   {
      printf("Error!");   
      exit(1);             
   }
       printf("Enter the problem type\n1.MAX\n2.MIN\n");
       scanf("%d",&rak);
		printf("Enter the number of variables:\n");
		scanf("%d",&cons);
number=cons+2;		
printf("-----------------------------\n");
	//creating two dimensional array
	A = (float**)malloc(number*sizeof(float *));
	for (i=0; i<10; i++)
	{
         A[i] = (float *)malloc(10 * sizeof(float));
	}


	a = (float**)malloc(number*sizeof(float *));
	for (i=0; i<10; i++)
	{
         a[i] = (float *)malloc(10 * sizeof(float));
	}

	b = (float*)malloc(number*sizeof(float));
	

	c = (float*)malloc(number*2*sizeof(float));

	cB = (float*)malloc(number*2*sizeof(float));
	
		while(!feof(ptr))
		{ 
		        for(i=0;i<number;i++)
				{ 
				fscanf(ptr,"%f",&A[m][i]);
				printf("%f ",A[m][i]);
				}
	
				printf("\n");
				 m=m+1;
	
		}

m--;
		for(j=1;j<=m;j++)
		{
			b[j-1]=A[j][number-1];
			printf("%f ",b[j-1]);
		}

printf("\n");

for(j=0;j<cons;j++)
{
	c[j]=A[0][j];
	printf("%f ",c[j]);
}	
printf("\n");
	p=cons;	//printf("%d",);
for(i=1;i<=m;i++)	
{	
   for(j=0;j<m;j++)
   {
    A[i][cons+j]=0;
     //printf("%f\n",A[i][cons+j]);
   }

   A[i][p]=1;
   //printf("%f\n",A[i][p]);
   p++;

}
t_var=cons+m;
//-------------------copying them to the a[][]matrix and printing the array after adding slack values
for(i=1;i<=m;i++)
{
	for(j=0;j<(t_var);j++)
	{
		
		a[i-1][j]=A[i][j];
		printf("%f ",a[i-1][j]);
	}
printf("\n");	
}
//------------------------------------------cal cj-zj

if(rak==2)
	for(i=0;i<t_var;i++)
	{
		c[i]=c[i]*(-1);
	}
	while(1)
	{ 
		count=0;
		for(i=0;i<t_var;i++)
		{
				for(j=0;j<m;j++)
					{
					  y = y + (cB[j]*a[j][i]);
					}
				
				diff[i]=c[i]-y;
				//printf("%f ",diff[i]);
		  
			y=0;	 

		         	
		}

		 printf("\n");

					for(i=0;i<t_var;i++)
					{
							if(diff[i]>0)
							{
								value++;
							}
					}
			  if(value > 0)
			  {value=0;
			        
													  for(i=0;i<t_var;i++)
													  {
													   if(diff[i]>0)
															   {
														 	        max = diff[0];
													                for (x = 0; x < t_var; x++)
													                {
														                 if (diff[x] >= max)
														                 {
														                 max = diff[x];
														                 enter=x;

														                 }
													               

														     	     }
													  }
													 }
													               printf("%d th value of c[],enters the b.f.s\n",enter);
			                                    

									//---------------------min ratio 
									for(i=0;i<m;i++)
									{
										if(a[i][enter]>0)
									    {
										  min[i]=b[i]/a[i][enter];
										  count++;
									    }
									    else 
									    	min[i]=10000;

									}
									if(count==0)
									{
										printf("Unbounded solution");
										break;
									}

									                                mn=min[0];
									 								for (x = 0; x < m; x++)
													                {
														                 if (min[x] <= mn)
														                 {
														                 mn = min[x];
														                 leave=x;
														                 }
													               
									   					    		}

									printf("%d th min[]leaves the b.f.s\n",leave);
									cB[leave]=c[enter];


									for(i=0;i<m;i++)
									{
									 //printf("%f ",cB[i]);
									}
									k=a[leave][enter];


												  for(i=0;i<t_var;i++)
												   {
													a[leave][i]=a[leave][i]/k;
												    }
												b[leave]=b[leave]/k;
									            for(i=0;i<m;i++)
									            {
														o=a[i][enter];
														for(j=0;j<t_var;j++)
														{
															
															if(i!=leave)
											                {
														     a[i][j]=a[i][j]-a[leave][j]*o;
											                }

														}
														if(i!=leave)
											             {
														  b[i]=b[i]-o*b[leave];
													     }
												}

												 for(i=0;i<m;i++)
									            {
														for(j=0;j<t_var;j++)
														{
									                    printf("%f ",a[i][j]);
									                    }
									                      printf("\n");
									               }

			 }
			 else
			  {
			     break;
			  }
}
printf("solution is: \n");

 for(i=0;i<cons;i++)
 {
 rr=0;
 	for(j=0;j<m;j++)
 	{
 		if(cB[j]==c[i])
 		{
 			printf("%f,",b[j]);
 			rr=1;
 			break;
 		}
 	}
 		if(rr!=1)
 		{
 			printf("0 ");
 		}

 }
 
 
			 	for(i=0;i<cons;i++)
			 	{
				 	//printf("%f ",b[i]);
			    }

for(i=0;i<m;i++)
{
	
		if(diff[i]<0)
			counter++;
}
if(counter==0)
printf("\nHas Alternate Solution\n");
else 
printf("\nHas Unique Solution\n");

for(i=0;i<m;i++)
{
sum=sum+b[i]*cB[i];
}
if(rak==2)
	{
		sum=sum*(-1);
	}
	

printf("Cost is %f \n",sum);

return 0;
}