//Este es voluntario de hopfield para más de un patrón, en este caso 3 patrones

#include <iostream>
#include <cmath>
#include <fstream>
#include <random>
#include <time.h>

#define N 40
#define T 0.0001

double omega[N][N][N][N];

double CalcularP(int n,int m,double omega[N][N][N][N],double theta[N][N],double s[N][N]);


using namespace std;

int main(void)
{
    int i,j,k,l,n,m,mu,xi[N][N][3],contador;
    double num,chi,p,s[N][N],a[3],theta[N][N];
    double aleatorio,number,sum,sol[3];
    
    
    mt19937 semilla(time(NULL));
    uniform_real_distribution<double> numeroaleatorio_real(0.0,1.0);
    uniform_int_distribution<int> numeroaleatorio_entero(0,N-1);
    
    ifstream fo1,fo2,fo3,de;

    fo1.open("datos1");
    fo2.open("datos2");
    fo3.open("datos3");
    de.open("deformado2");

    ofstream da,re,po,dat,data,sola;

    da.open("foto1");
    dat.open("foto2");
    data.open("foto3");
    re.open("estado_f");
    po.open("estado_i");
    sola.open("solapamiento");
    
    //Hay que leer la imagen que queremos pintar
    
    i=N-1;
    j=0;
    
    while(fo1>>number)
    {
        xi[i][j][0]=number;

        if(j==N-1)
        {
            i--;
            j=0;
        }   
        else
            j++;     
    }

    for(i=0; i<N; i++)
    {
        for(j=0; j<N; j++)
        {
            if(xi[i][j][0]==1)  
                da<<j<<" "<<i<<endl;
        }
    }

    i=N-1;
    j=0;
    
    while(fo2>>number)
    {
        xi[i][j][1]=number;

        if(j==N-1)
        {
            i--;
            j=0;
        }   
        else
            j++;     
    }

    for(i=0; i<N; i++)
    {
        for(j=0; j<N; j++)
        {
            if(xi[i][j][1]==1)  
                dat<<j<<" "<<i<<endl;
        }
    }

    i=N-1;
    j=0;
    
    while(fo3>>number)
    {
        xi[i][j][2]=number;

        if(j==N-1)
        {
            i--;
            j=0;
        }   
        else
            j++;     
    }
    
    for(i=0; i<N; i++)
    {
        for(j=0; j<N; j++)
        {
            if(xi[i][j][2]==1)  
                data<<j<<" "<<i<<endl;
        }
    }


    for(mu=0; mu<3; mu++)
    {
        a[mu]=0.0;
        
        for(k=0; k<N; k++)
        {
            for(l=0; l<N; l++)
            {
                a[mu]=a[mu]+xi[k][l][mu];   
            }   
        }

        a[mu]=a[mu]/(N*N);
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
                        omega[i][j][k][l]=((xi[i][j][0]-a[0])*(xi[k][l][0]-a[0]))+((xi[i][j][1]-a[1])*(xi[k][l][1]-a[1]))+((xi[i][j][2]-a[2])*(xi[k][l][2]-a[2]));
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

    //Inicialicemos la matriz s aleatoriamente
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
        for(mu=0; mu<3; mu++)
        {
            sum=0.0;

            for(i=0; i<N; i++)
            {
                for(j=0; j<N; j++)
                    sum=sum+(((double)xi[i][j][mu]-a[mu])*(s[i][j]-a[mu]));
            }
            sol[mu]=sum/(a[mu]*(1.-a[mu])*N*N);
           
        }
        
        sola<<k<<"  "<<sol[0]<<"  "<<sol[1]<<"  "<<sol[2]<<endl;
    }

    for(i=0; i<N; i++)
    {
        for(j=0; j<N; j++)
        {
            if(s[i][j]==1)  
                re<<j<<" "<<i<<endl;
        }
    }

    cout<<sol[0]<<"  "<<sol[1]<<"  "<<sol[2]<<endl;

    

    

    da.close();
    re.close();
    fo1.close();
    fo2.close();
    fo3.close();    
    dat.close();
    data.close();
    po.close();
    sola.close();
    de.close();
    
    return 0;
}


//Funcion para calcular p

double CalcularP(int n,int m,double omega[N][N][N][N],double theta[N][N],double s[N][N])
{    
    int i,j,k,l;
    double sum,p,H;        

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
