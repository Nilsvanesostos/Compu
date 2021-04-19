#include <iostream>
#include <cmath>
#include <fstream>
#include <random>
#include <time.h>

#define N 150
#define T 0.5

double CalcularP(int n, int m, double s[N][N]); 


using namespace std;
int main(void)
{
    int i,j,k,n,m;
    double num,chi,p,s[N][N];
    double aleatorio;
    
    
    mt19937 semilla(time(NULL));
    uniform_real_distribution<double> numeroaleatorio_real(0.0,1.0);
    uniform_int_distribution<int> numeroaleatorio_entero(0,N-1);
    
    ofstream da,re;

    da.open("datos");
    re.open("posiciones");

    //Inicialicemos la matriz s aleatoriamente

    for(i=0; i<N; i++)
    {
        for(j=0; j<N; j++)
        {
            aleatorio=numeroaleatorio_real(semilla);
            if(aleatorio<=0.5)
                s[i][j]=1.0;
            else
                s[i][j]=-1.0;
        }
    }

    //Escribimos los resultados

    
    for(k=0; k<200; k++)
    {
        for(i=0;i<N*N;i++)
        {
            //Elegimos un elemento aleatorio de la matriz 

            n=numeroaleatorio_entero(semilla);
            m=numeroaleatorio_entero(semilla);

            //Evaluamos p=min(1,exp(-[E/T]))

            p=CalcularP(n,m,s);

            //Generamos un número aleatorio uniforme entre 0 y 1, y provamos si es menor que p

            chi=numeroaleatorio_real(semilla);
            

            if(chi<p)
            {
            	
                s[n][m]=-s[n][m];
            }

        }
            

    }
    
 	//Escribimos los resultado  
    for(i=0; i<N; i++)
    {
       for(j=0; j<N; j++)
       {
            da<<s[i][j]<<"\t";
            if(s[i][j]==(-1.))
            {
            	re<<i<<"\t"<<j<<endl;
            }
        }
        da<<endl;
    }

    da.close();
    re.close();
    

    return 0;
}

//Funcion para calcular p

double CalcularP(int n, int m, double s[N][N])
{
    double p,E;

    //Calculemos E

    if((n==0)&&(m==0))
    {
        E=2.*s[n][m]*(s[n+1][m]+s[N-1][m]+s[n][m+1]+s[n][N-1]);
    }
    
    if((n==0)&&(m==N-1))
    {
        E=2.*s[n][m]*(s[n+1][m]+s[N-1][m]+s[n][0]+s[n][m-1]);
    }

    if((n==N-1)&&(m==0))
    {
        E=2.*s[n][m]*(s[0][m]+s[n-1][m]+s[n][m+1]+s[n][N-1]);
    }

    if((n==N-1)&&(m==N-1))
    {
        E=2.*s[n][m]*(s[0][m]+s[n-1][m]+s[n][0]+s[n][m-1]);
    }

    if(((n==0)&&(m!=0))&&(m!=N-1))
    {
        E=2.*s[n][m]*(s[n+1][m]+s[N-1][m]+s[n][m+1]+s[n][m-1]);
    }

    if(((n==N-1)&&(m!=0))&&(m!=N-1))
    {
        E=2.*s[n][m]*(s[0][m]+s[n-1][m]+s[n][m+1]+s[n][m-1]);
    }

    if(((m==0)&&(n!=0))&&(n!=N-1))
    {
        E=2.*s[n][m]*(s[n+1][m]+s[n-1][m]+s[n][m+1]+s[n][N-1]);
    }

    if(((m==N-1)&&(n!=0))&&(n!=N-1))
    {
        E=2.*s[n][m]*(s[n+1][m]+s[n-1][m]+s[n][0]+s[n][m-1]);
    }

    else
    {
        E=2.*s[n][m]*(s[n+1][m]+s[n-1][m]+s[n][m+1]+s[n][m-1]);   
    }
    
    //Ahora podemos calcular p

	p=min(1.0,exp(-E/T));


    return p;
}
