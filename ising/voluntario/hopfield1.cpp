//Este es el voluntario de hopfield para un solo patrón

#include <iostream>
#include <cmath>
#include <fstream>
#include <random>
#include <time.h>

#define N 120
#define T 0.001

double omega[N][N][N][N];

double CalcularP(int n,int m,double omega[N][N][N][N],double theta[N][N],double s[N][N]);


using namespace std;

int main(void)
{
    int i,j,k,l,n,m,mu,xi[N][N],contador;
    double num,chi,p,s[N][N],a,theta[N][N];
    double aleatorio,number,sum,sol;
    
    
    mt19937 semilla(time(NULL));
    uniform_real_distribution<double> numeroaleatorio_real(0.0,1.0);
    uniform_int_distribution<int> numeroaleatorio_entero(0,N-1);
    
    ifstream fo,de;

    fo.open("prueba");
    de.open("deformado");

    ofstream da,re,sola,po;

    da.open("datos'");
    po.open("estado_i");
    re.open("estado_f");
    sola.open("solapamiento2");
    
    //Hay que leer la imagen que queremos pintar
    
    i=N-1;
    j=0;

    while(fo>>number)
    {
        xi[i][j]=number;

        if(j==N-1)
        {
            i--;
            j=0;
        }   
        else
            j++;     
    }

    i=N-1;
    j=0;

    while(de>>number)
    {
        s[i][j]=number;

        if(j==N-1)
        {
            i--;
            j=0;
        }   
        else
            j++;     
    }

    
    a=0.0;
    
    for(k=0; k<N; k++)
    {
        for(l=0; l<N; l++)
        {
            a=a+xi[k][l];   
        }   
    }

    a=a/(N*N);
 

    //Calculo omega

    for(i=0; i<N; i++)
    {
        for(j=0; j<N; j++)
        {
            for(k=0; k<N; k++)
            {
                for(l=0; l<N; l++)
                {
                    if((i==k)&&(j==l))
                    {
                        omega[i][j][k][l]=0.;
                    }
                    else
                    {
                        omega[i][j][k][l]=(xi[i][j]-a)*(xi[k][l]-a);
                        omega[i][j][k][l]=omega[i][j][k][l]/(N*N);
                    }
                    
                    
                }
            }
        }
    }  

    //Calculamos theta
    
    for(i=0; i<N; i++)
    {
        for(j=0; j<N; j++)
        {    
            sum=0.;

            for(k=0; k<N; k++)
            {
                for(l=0; l<N; l++)
                {
                    sum=sum+omega[i][j][k][l];
                }    
            }
            theta[i][j]=0.5*sum;
        }
    }   

    //Inicialicemos la matriz s aleatoriamente y escribamosla en un fichero
/*
    for(i=0; i<N; i++)
    {
        for(j=0; j<N; j++)
        {
            aleatorio=numeroaleatorio_real(semilla);
            if(aleatorio<=0.5)
                s[i][j]=1.0;
            else
                s[i][j]=0.0;
        }
    }
*/
    for(i=0; i<N; i++)
    {
        for(j=0; j<N; j++)
        {
            if(s[i][j]==1)  
                po<<j<<" "<<i<<endl;
        }
    }

    
    for(k=0; k<=20; k++)
    {
        //Dibujamos la imagen en un archivo .dat

            for(i=N-1; i>=0; i--)
            {
                for(j=0; j<N; j++)
                {
                    if(j==N-1)
                        da<<s[i][j]<<endl;
                    else
                        da<<s[i][j]<<",";
                }
            }

            da<<endl;

        for(i=0;i<N*N;i++)
        {
            

            //Elegimos un elemento aleatorio de la matriz 

            n=numeroaleatorio_entero(semilla);
            m=numeroaleatorio_entero(semilla);


            //Evaluamos p=min(1,exip(-[E/T]))

            p=CalcularP(n,m,omega,theta,s);


            //Generamos un número aleatorio uniforme entre 0 y 1, y provamos si es menor que p

            chi=numeroaleatorio_real(semilla);
            

            if(chi<p)
            {
                if(s[n][m]==1.)
                    s[n][m]=0.;
                else
                    s[n][m]=1.;	
                
            }

        }

        //Finalmente, calculamos el solapamiento como 

        sum=0.;
        for(i=0; i<N; i++)
        {
            for(j=0; j<N; j++)
                sum=sum+(((double)xi[i][j]-a)*(s[i][j]-a));
        }
        sol=sum/(a*(1.-a)*N*N);

        sola<<k<<"   "<<sol<<endl;
            

    }

    

    for(i=0; i<N; i++)
    {
        for(j=0; j<N; j++)
        {
            if(s[i][j]==1)  
                re<<j<<" "<<i<<endl;
        }
    }

    da.close();
    re.close();
    fo.close();
    sola.close();
    po.close();
    de.close();

    return 0;
}


//Funcion para calcular p

double CalcularP(int n,int m,double omega[N][N][N][N],double theta[N][N],double s[N][N])
{    
    int i,j,k,l;
    double sum,p,H,sprima[N][N];        

    //Calculamos el hamiltoniano

    sum=0.;
    
    for(k=0; k<N; k++)
    {
        for(l=0; l<N; l++)
        {
            if((k==n)&&(l==m))
                sum=sum+(omega[n][m][k][l]*((s[n][m]*s[k][l])-(1.+s[n][m]-2.*s[n][m])));
            else
                sum=sum+(omega[n][m][k][l]*s[k][l]*((2.*s[n][m])-1.));
            
        }
    }

    H=(0.5*sum)+(theta[n][m]*((1.-s[n][m])-s[n][m])); 

    //De modo que podemos calcular p

    p=min(1.0,exp(-H/T));


    return p;
}
