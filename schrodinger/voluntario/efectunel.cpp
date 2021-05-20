//Este es el voluntario del tema de schrodinger

#include <iostream>
#include <cmath>
#include <fstream>
#include <random>
#include <time.h>
#include "complex.hpp"

#define pi 3.141592
#define N 500
#define nciclos N/10.
#define lambda 0.7
#define h 0.05
#define n_D 500

double Potencial(int j,double k);
void CalcularAlfa(double s,double V[N],fcomplex gamma[N],fcomplex alfa[N]);
void CalcularBeta(fcomplex gamma[N],fcomplex b[N], fcomplex beta[N]);
void CalcularChi(fcomplex alfa[N],fcomplex beta[N],fcomplex chi[N]);
void CalcularPhi(fcomplex chi[N],fcomplex phi[N]);
double posicionEsp(fcomplex phi[N]);
double momentoEsp(fcomplex phi[N]);
double posicioncEsp(fcomplex phi[N]);
double momentocEsp(fcomplex phi[N]);

using namespace std;

int main()
{
    int i,j,t,m,m_T,condicion;
    double s,k,V[N],norma,aleatorio,x,P_D,P_I,posicion,momento,posicionc,momentoc;       
    fcomplex cero,imaginario,gamma[N],b[N],alfa[N],beta[N],chi[N],phi[N];

    ofstream sch,pot,norm,pro;
    
    sch.open("Phi");
    pot.open("V");
    norm.open("Norma");
    pro.open("P_D");

    
    mt19937 semilla(time(NULL));
    uniform_real_distribution<double> numeroaleatorio_real(0.0,1.0);

    //Vamos a definir los numeros cero e i

    cero.r=0.0;
    cero.i=0.0;

    imaginario.r=0.0;
    imaginario.i=1.0;


    //Lo primero que tenemos que hacer, es generar todas estas variables en su instante inicial

    k=2*pi*nciclos/N;

    s=1./(4.*k*k);

    for(j=0; j<N; j++)
        V[j]=Potencial(j,k);
        

    for(m=0;m<1;m++)
    {
       
        condicion=0;


        //Calculamos la función phi en el primer instante del tiempo 

        phi[0]=cero;
        phi[N-1]=cero;

        norma=0.;
        
        for(j=1; j<N-1; j++)
        {    
            phi[j]=Cgauss((k*j),exp((-8.*(4.*j-N)*(4.*j-N))/(N*N)));
            norma=norma+Cabs(Cpow(phi[j],2));         
        }
        
        //Normalizamos la función de onda

           
        for(j=0;j<N;j++)
            phi[j]=RCmul(1./sqrt(norma),phi[j]);
               
        

        while(condicion==0)
        {

            //Calculamos alfa

            CalcularAlfa(s,V,gamma,alfa);
            

            //Comenzamos a iterar
            
            for(t=0; t<n_D;t++)
            {
                for(j=0; j<N; j++)
                    b[j]=Cmul(RCmul(4./s,imaginario),phi[j]);
                            
                
                //Calculamos los valores de beta

                CalcularBeta(gamma,b,beta);

                //Ahora toca calcular el vecor chi

                CalcularChi(alfa,beta,chi);

                //Finalmente, podemos calcular el nuevo valor de la funcion phi

                CalcularPhi(chi,phi);

                //Escribimos en el fichero

                for(j=0; j<N; j++)
                    sch<<j+1<<","<<Cabs(Cpow(phi[j],2))<<","<<V[j]<<endl; 
                sch<<endl;
               

            }

            //Calculamos P_D

            P_D=0.;

            for(j=(int)4*N/5; j<N; j++)
                P_D=P_D+Cabs(Cpow(phi[j],2));

            //Definimos un numero aleatorio x

            aleatorio=numeroaleatorio_real(semilla);
            x=aleatorio;

            //Probamos si x<P_D

            if(x<P_D)
            {
                m_T++;
                condicion=1;        
            }

            else
            {
                //Definimos la nueva función de onda 

                for(j=(int) 4*N/5; j<N; j++)
                    phi[j]=cero;
                
                norma=0.;
                
                for(j=0; j<N; j++)
                    norma=norma+Cabs(Cpow(phi[j],2));    
                
                for(j=0; j<N; j++)
                    phi[j]=RCmul(1./sqrt(norma),phi[j]);

                //Calculamos P_I

                P_I=0.;
            
                for(j=0; j<(int)N/5; j++)
                    P_I=P_I+Cabs(Cpow(phi[j],2));
        
                //Definimos un numero aleatorio x

                aleatorio=numeroaleatorio_real(semilla);
                x=aleatorio;

                //Comprobamos si x<P_I
                if(x>=P_I)
                {
                    for(j=0; j<(int)N/5; j++)
                        phi[j]=cero;
        
                    norma=0.;

                    for(j=0; j<N; j++)
                        norma=norma+Cabs(Cpow(phi[j],2));

                    for(j=0; j<N; j++)
                        phi[j]=RCmul(1./sqrt(norma),phi[j]);

                    condicion=0;
                }
                else
                    condicion=1;
            } 

        }
        for(j=0; j<N; j++)
            sch<<j+1<<","<<Cabs(Cpow(phi[j],2))<<","<<V[j]<<endl; 
        sch<<endl;

        
    }

    posicion=posicionEsp(phi);
    momento=momentoEsp(phi);

    posicionc=posicioncEsp(phi);
    momentoc=momentocEsp(phi);

    cout<<"COEFICIENTE DE TRANSMISIÓN:"<<endl;
    cout<<"K:  "<<(double)m_T/m<<endl;

    


    sch.close();
    pot.close();
    norm.close();
    pro.close();


    return 0;
}

double Potencial(int j,double k)
{
    int a, b;
    double Vol;

    a=(int)(2*N/5);
    b=(int)(3*N/5);

    if((j>=a)&&(j<=b))
        Vol=lambda*k*k;

    else
        Vol=0.0;

    return Vol;
}

//Función que me calcula el vector alpha

void CalcularAlfa(double s, double V[N],fcomplex gamma[N],fcomplex alfa[N])
{
    int j;
    fcomplex aux,A0[N],cero,uno,imaginario;

    cero.r=0.0;
    cero.i=0.0;

    uno.r=1.0;
    uno.i=0.0;

    imaginario.r=0.0;
    imaginario.i=1.0;

    alfa[N-1]=cero;

    for(j=N-1;j>=1;j--)
    {
        aux.r=V[j]+2.;
        aux.i=0.0;
        A0[j]=Csub(RCmul(2./s,imaginario),aux);
        gamma[j]=Cdiv(uno,Cadd(A0[j],alfa[j]));

        alfa[j-1].r=-gamma[j].r;
        alfa[j-1].i=-gamma[j].i;
       
    }
   

    return;
}

//Función que me calcula el vector beta

void CalcularBeta(fcomplex gamma[N],fcomplex b[N],fcomplex beta[N])
{
    int j;
    fcomplex cero;

    cero.r=0.0;
    cero.i=0.0;

    beta[N-1]=cero;

        for(j=N-1;j>=1;j--)
            beta[j-1]=Cmul(gamma[j],(Csub(b[j],beta[j])));

    return;
}

void CalcularChi(fcomplex alfa[N],fcomplex beta[N],fcomplex chi[N])
{
    int j;
    fcomplex cero;

    cero.r=0.0;
    cero.i=0.0;

    chi[0]=cero;

    for(j=0;j<N-1;j++)
        chi[j+1]=Cadd(Cmul(alfa[j],chi[j]),beta[j]);

    return;
}

void CalcularPhi(fcomplex chi[N],fcomplex phi[N])
{
    int j;

    for(j=0;j<N;j++)
    {
        phi[j]=Csub(chi[j],phi[j]);
        
    }
    

    return;
}

double posicionEsp(fcomplex phi[N])
{
    int j;
    double a;
    a=0.;
	
    for(j=0;j<N;j++) 
        a=a+j*(Cabs(phi[j])*Cabs(phi[j])); 
    
    return a;
}

double momentoEsp(fcomplex phi[N])
{
    int j;
    double a;
    fcomplex derivada[N];

    a=0.;
    derivada[0]=Complex(0.,0.);

    for(j=1; j<N; j++)
        derivada[j]=Csub(phi[j],phi[j-1]);

    for(j=0; j<N; j++)
        a=a+(Cabs(phi[j])*Cabs(Cmul(Complex(0.,-1.),derivada[j])));

    return a;
}

