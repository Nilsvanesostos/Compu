#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>

using namespace std;

int main()
{
    int i,n,n_max;
    double m[2][2], g[2], msup[2][2], minf[2][2], denominador, inf[2], numerador, sup[2],alpha_num, aux[2][2],alpha_anal;
    
    //Declaramos el fichero de escritura
    ofstream datos;
    
    datos.open("datos");

    //Definimos los valores de la matriz m y gamma
    
    m[0][0]=0.7; 
    m[0][1]=0.35;
    m[1][0]=0.35;
    m[1][1]=0.4; 

    g[0]=0.6;               
   	g[1]=0.8;

    //Calculamos el alpha analitica

    alpha_anal=0.5*((m[0][0]-m[1][1])+sqrt(((m[1][1]-m[0][0])*(m[1][1]-m[0][0]))+(4.*m[1][0]*m[1][0])))+m[1][1];
   
    //Inicializamos el contador n
    n_max=701;
    
    for(n=1;n<n_max;n++)
    {
        //Inicializamos las matrices auxiliares que usaremos en el programa

        msup[0][0]=minf[0][0]=.7; 
        msup[0][1]=minf[0][1]=0.35;
        msup[1][0]=minf[1][0]=0.35;
        msup[1][1]=minf[1][1]=0.4; 

        sup[0]=inf[0]=0.6; 
        sup[1]=inf[1]=0.8;


        //Calculamos el término que hirá en el numerador
    	for(i=0; i<(2*n)+1; i++)
    	{
            aux[0][0]=msup[0][0];
            aux[1][0]=msup[1][0];
            aux[0][1]=msup[0][1];
            aux[1][1]=msup[1][1];

        	msup[0][0]=aux[0][0]*m[0][0]+aux[0][1]*m[1][0];
        	msup[0][1]=aux[0][0]*m[0][1]+aux[0][1]*m[1][1];
        	msup[1][0]=aux[1][0]*m[0][0]+aux[1][1]*m[1][0];
        	msup[1][1]=aux[1][0]*m[0][1]+aux[1][1]*m[1][1];
    
    	}
    
        sup[0]=msup[0][0]*g[0]+msup[0][1]*g[1]; //matriz auxiliar gamma
    	sup[1]=msup[1][0]*g[0]+msup[1][1]*g[1];
    
    	numerador=sup[0]*g[0]+sup[1]*g[1];

		//Calculamos el término que hirá en el denominador
    	for(i=0; i<(2*n); i++)
    	{
            aux[0][0]=minf[0][0];
            aux[1][0]=minf[1][0];
            aux[0][1]=minf[0][1];
            aux[1][1]=minf[1][1];
            
        	minf[0][0]=aux[0][0]*m[0][0]+aux[0][1]*m[1][0];
        	minf[0][1]=aux[0][0]*m[0][1]+aux[0][1]*m[1][1];
        	minf[1][0]=aux[1][0]*m[0][0]+aux[1][1]*m[1][0];
       	 	minf[1][1]=aux[1][0]*m[0][1]+aux[1][1]*m[1][1];
    
    	}
    
    	inf[0]=minf[0][0]*g[0]+minf[0][1]*g[1];
    	inf[1]=minf[1][0]*g[0]+minf[1][1]*g[1];
    
    	denominador=inf[0]*g[0]+inf[1]*g[1];
    	
    	//Calculamos el alpha numerica

       	alpha_num=numerador/denominador;
    	
    	datos<<std::setprecision(25)<< n<<"\t"<<alpha_num<<"\t"<<alpha_anal<<endl;
    	
    	
	}	
    
    datos.close();
		
    return 0;
	}
