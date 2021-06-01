//EJERCICIO OBLIGATORIO DE LA NAVE
//PROGRAMA DE LA NAVE PARA H FIJA 

#include <iostream>
#include <cmath>
#include <fstream>

#define G 6.67e-11			
#define MT 5.9736e24
#define ML 0.07349e24		
#define dTL 3.844e8			
#define w 2.6617e-6			
#define RT 6.378160e6		
#define RL 1.7374e6			      	
#define h 0.8	
#define teta 0.78       //Angulo fancy 0.78 radianes (45 grados)
#define v 11090.0      //velocidad fancy 11090.0

double f(double r, double phi, double pr, double pfi, double t, int i);

using namespace std;

int main()
{
    int i,j,k,contador;
	double cohete[4],luna [2];			
	double k1[4],k2[4],k3[4],k4[4],t,rLuna,H,p_phi,p_r,r,phi;	

    ofstream ch,lu;

    ch.open("datos_cohete");
    lu.open("datos_luna");

    //Introducimos las condiciones iniciales del problema

    cohete[0]=RT;//posicion
	cohete[1]=0.3;//phi
    cohete[2]=v*cos(teta-cohete[1]);		//	momento radial
    cohete[3]=RT*v*sin(teta-cohete[1]);		//	momento angular

    //Ahora las reescalamos 

    cohete[0]=cohete[0]/dTL;
	cohete[1]=cohete[1];
	cohete[2]=cohete[2]/dTL;
	cohete[3]=cohete[3]/(dTL*dTL);

    //Escribimos también las condiciones de la luna ya reescaladas

    luna[0]=(RT+RL+dTL)/dTL;
    luna[1]=0.0;
    contador=0;

    t=0.;

    for(k=0; k<1000000; k++)
    {
        //Escribimos en nuestro fichero

        if(contador==1000)
        {
            ch<<cohete[0]*cos(cohete[1])<<","<<cohete[0]*sin(cohete[1])<<endl;
		    ch<<luna[0]*cos(w*t)<<","<<luna[0]*sin(w*t)<<endl<<endl;
            contador=0;        
        }
        //Aplicamos el algoritmo Runge-Kutta

	    	for(j=0;j<4;j++)
       		k1[j]=h*f(cohete[0],cohete[1],cohete[2],cohete[3],t,j); 		      	
	    
        for(j=0;j<4;j++)
            k2[j]=h*f(cohete[0]+(k1[0]/2.0),cohete[1]+(k1[1]/2.0),cohete[2]+(k1[2]/2.0),cohete[3]+(k1[3]/2.0),t+(h/2.0),j);

        for(j=0;j<4;j++)
            k3[j]=h*f(cohete[0]+(k2[0]/2.0),cohete[1]+(k2[1]/2.0),cohete[2]+(k2[2]/2.0),cohete[3]+(k2[3]/2.0),t+(h/2.0),j);

        for(j=0;j<4;j++)
            k4[j]=h*f(cohete[0]+k3[0],cohete[1]+k3[1],cohete[2]+k3[2],cohete[3]+k3[3],t+h,j);


        //Calculamos ahora las nuevas coordenadas

        for(j=0;j<4;j++)				
			cohete[j]=cohete[j]+((1.0/6.0)*(k1[j]+(2.0*k2[j])+(2.0*k3[j])+k4[j]));

        //Reescalamos de nuevo a las coordenadas originales

        r=cohete[0]*dTL;

        phi=cohete[1];
        
        p_r=cohete[2]*dTL;
        
        p_phi=cohete[3]*dTL*dTL;

        //Calculamos el Hamiltoniano del sistema y lo escribimos por pantalla para comprobar que H' es constante de movimiento

        rLuna=sqrt((r*r)+(dTL*dTL)-(2.*r*dTL*cos(phi-(w*t))));

        H=(p_r*p_r/2.)+((p_phi*p_phi)/(2.*r*r))-(G*MT/r)-(G*ML/rLuna);

        cout<<H-(w*p_phi)<<endl;

        //Aplicamos el paso al tiempo 

        t=t+h;
        contador++;

    }

    ch.close();
    lu.close();



    return 0;
}

double f(double r, double phi, double pr, double pfi, double t, int i)
{
	double derivada,rp,mu,delta;
	
	rp=sqrt(1.0+(r*r)-(2.0*r*cos(phi-w*t)));
    mu=ML/MT;
    delta=G*MT/(dTL*dTL*dTL);

	if(i==0)
		derivada=pr;

	else if(i==1)
		derivada=pfi/(r*r);
	
	else if(i==2)
		derivada=((pfi*pfi)/(r*r*r))-(delta*((1.0/(r*r))+((mu/(rp*rp*rp))*(r-cos(phi-(w*t))))));
	
	else if(i==3)
		derivada=-((delta*mu*r*sin(phi-(w*t)))/(rp*rp*rp));
	
	
	return derivada;
}
