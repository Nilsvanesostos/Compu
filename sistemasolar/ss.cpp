#include <iostream>
#include <cmath>
#include <fstream>

#define Msol 1.988e30
#define G 6.67e-11
#define c 1.496e11
#define N 10
#define h 0.001


using namespace std;
int main(void)
{
    long double masa[N],velocidad[2][N], posicion[2][N], aceleracion[2][N], omega[2][N], norma,t, energia;
    int i,j,k,n,contador,mercurio,venus,tierra,marte,jupiter,saturno,urano,neptuno,pluton;
    
    contador=0;
    
    mercurio=1;
    venus=1;
    tierra=1;
    marte=1;
    jupiter=1;
    saturno=1;
    urano=1;
    neptuno=1;
    pluton=1;
    
    
    n=0;
    t=0.0;

    ifstream mi, vi, pi; //ficheros de masas velocidades y posiciones iniciales
    mi.open("masa");
    pi.open("posicion");
    vi.open("velocidad");

    ofstream pf;
    pf.open("posicion_final");
    
    
    
    //Introducimos las masas a nuestro vector del fichero de datos    
    if(mi.is_open() ==true)
    {
        
        for(i=0; i<N; i++)
         {
            mi>>masa[i];
            masa[i]=masa[i]/Msol;
          
         }  
    
    }
 
    if(pi.is_open() ==true)
    {
       
        for(i=0; i<N; i++)
        {
            pi>>posicion[0][i]; //eje x
	        posicion[0][i]=posicion[0][i]/c;
            posicion[1][i]=0.0; //eje y
            pf<<posicion[0][i]<<"\t"<<posicion[1][i]<<"\t";
        }  

        pf<<endl;
    
    }
    
    if(vi.is_open() ==true)
    {
        
        for(i=0; i<N; i++)
        {
            velocidad[0][i]=0.0; //eje x
            vi>>velocidad[1][i]; //eje y
            velocidad[1][i]=velocidad[1][i]*sqrt(c/(G*Msol));
        }  
    
    }
    
    //Calculamos la aceleracion en un instante del tiempo

    for(i=0; i<N; i++)
    {
	    aceleracion[0][i]=0.0;
	    aceleracion[1][i]=0.0;

	    for(j=0; j<N; j++)
	    {
		    if(i!=j)
		    {	
			    norma=sqrt(((posicion[0][i]-posicion[0][j])*(posicion[0][i]-posicion[0][j]))+((posicion[1][i]-posicion[1][j])*(posicion[1][i]-posicion[1][j])));
			    aceleracion[0][i]=aceleracion[0][i]-((masa[j]*(posicion[0][i]-posicion[0][j]))/(norma*norma*norma));
			    aceleracion[1][i]=aceleracion[1][i]-((masa[j]*(posicion[1][i]-posicion[1][j]))/(norma*norma*norma));
		    }
	    }
    }			
			
    for(n=0; n<10000;n++)
    { 
        //A continuación, calculamos las nuevas posiciones y omegas.

        posicion[0][0]=0.0;
        posicion[1][0]=0.0;
        
        for(i=1; i<N; i++)
        {
            posicion[0][i]=posicion[0][i]+(h*velocidad[0][i])+(h*h*0.5*aceleracion[0][i]);
		    posicion[1][i]=posicion[1][i]+(h*velocidad[1][i])+(h*h*0.5*aceleracion[1][i]);

		    omega[0][i]=velocidad[0][i]+(h*0.5*aceleracion[0][i]);
            omega[1][i]=velocidad[1][i]+(h*0.5*aceleracion[1][i]);
        }
        
        //Ahora calculamos la nueva aceleracion con la nueva posicion
        for(i=0; i<N; i++)
    	{
    
    		aceleracion[0][i]=0.0;
    		aceleracion[1][i]=0.0;
    
    		for(j=0; j<N; j++)
    		{							
    		    if(i!=j)
    		    {													       
    			    norma=sqrt(((posicion[0][i]-posicion[0][j])*(posicion[0][i]-posicion[0][j]))+((posicion[1][i]-posicion[1][j])*(posicion[1][i]-posicion[1][j])));												
    				aceleracion[0][i]=aceleracion[0][i]-((masa[j]*(posicion[0][i]-posicion[0][j]))/(norma*norma*norma));
    				aceleracion[1][i]=aceleracion[1][i]-((masa[j]*(posicion[1][i]-posicion[1][j]))/(norma*norma*norma));
    			}
    		}
    	}
  
        
        //Y finalmente, la nueva velocidad

        velocidad[0][0]=0.0;
        velocidad[1][0]=0.0;
        
        for(i=1; i<N; i++)
        {
            velocidad[0][i]=omega[0][i]+(h*0.5*aceleracion[0][i]);
		    velocidad[1][i]=omega[1][i]+(h*0.5*aceleracion[1][i]);
        }
        
        
        //Sacamos a un fichero de texto las nuevas posiciones de los planetas
        t=t+h;
        


	    
        for(i=0; i<N; i++)
        {
            pf<<posicion[0][i]<<"\t"<<posicion[1][i]<<"\t";
                               
        }
            
        pf<<endl;
        
        contador++;
        
        //Calculamos la energia de la tierra 
        

        
        
        
        
        //Comprobar si ha dado una vuelta

        if((posicion[1][1]<0.0)&&(mercurio==1))
        {
            mercurio=2;
            cout<<"MERCURIO: "<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<endl;        
        }
        
    
        if((posicion[1][2]<0.0)&&(venus==1))
        {
            venus=2;
            cout<<"VENUS: "<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<endl;        
        }  

        if((posicion[1][3]<0.0)&&(tierra==1))
        {
            tierra=2;
            cout<<"TIERRA: "<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<endl;        
        }    

        if((posicion[1][4]<0.0)&&(marte==1))
        {
            marte=2;
            cout<<"MARTE: "<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<endl;        
        }
    
        if((posicion[1][5]<0.0)&&(jupiter==1))
        {
            jupiter=2;
            cout<<"JUPITER: "<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<endl;        
        }  

        if((posicion[1][6]<0.0)&&(saturno==1))
        {
            saturno=2;
            cout<<"SATURNO: "<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<endl;        
        }

        if((posicion[1][7]<0.0)&&(urano==1))
        {
            urano=2;
            cout<<"URANO: "<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<endl;        
        }
    
        if((posicion[1][8]<0.0)&&(neptuno==1))
        {
            neptuno=2;
            cout<<"NEPTUNO: "<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<endl;        
        }  

        if((posicion[1][9]<0.0)&&(pluton==1))
        {
            saturno=2;
            cout<<"PLUTON: "<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<endl;        
        }

    }    
    
    mi.close(); 
    pi.close();
    vi.close();
    pf.close();
    
    
    return 0;
}
        
        for(i=0; i<N; i++)
         {
            mi>>masa[i];
            masa[i]=masa[i]/Msol;
          
         }  
    
    }
 
    if(pi.is_open() ==true)
    {
       
        for(i=0; i<N; i++)
        {
            pi>>posicion[0][i]; //eje x
	        posicion[0][i]=posicion[0][i]/c;
            posicion[1][i]=0.0; //eje y
            pf<<posicion[0][i]<<"\t"<<posicion[1][i]<<"\t";
        }  

        pf<<endl;
    
    }
    
    if(vi.is_open() ==true)
    {
        
        for(i=0; i<N; i++)
        {
            velocidad[0][i]=0.0; //eje x
            vi>>velocidad[1][i]; //eje y
            velocidad[1][i]=velocidad[1][i]*sqrt(c/(G*Msol));
        }  
    
    }
    
    //Calculamos la aceleracion en un instante del tiempo

    for(i=0; i<N; i++)
    {
	    aceleracion[0][i]=0.0;
	    aceleracion[1][i]=0.0;

	    for(j=0; j<N; j++)
	    {
		    if(i!=j)
		    {	
			    norma=sqrt(((posicion[0][i]-posicion[0][j])*(posicion[0][i]-posicion[0][j]))+((posicion[1][i]-posicion[1][j])*(posicion[1][i]-posicion[1][j])));
			    aceleracion[0][i]=aceleracion[0][i]-((masa[j]*(posicion[0][i]-posicion[0][j]))/(norma*norma*norma));
			    aceleracion[1][i]=aceleracion[1][i]-((masa[j]*(posicion[1][i]-posicion[1][j]))/(norma*norma*norma));
		    }
	    }
    }			
			
    for(n=0; n<10000;n++)
    { 
        //A continuación, calculamos las nuevas posiciones y omegas.

        posicion[0][0]=0.0;
        posicion[1][0]=0.0;
        
        for(i=1; i<N; i++)
        {
            posicion[0][i]=posicion[0][i]+(h*velocidad[0][i])+(h*h*0.5*aceleracion[0][i]);
		    posicion[1][i]=posicion[1][i]+(h*velocidad[1][i])+(h*h*0.5*aceleracion[1][i]);

		    omega[0][i]=velocidad[0][i]+(h*0.5*aceleracion[0][i]);
            omega[1][i]=velocidad[1][i]+(h*0.5*aceleracion[1][i]);
        }
        
        //Ahora calculamos la nueva aceleracion con la nueva posicion
        for(i=0; i<N; i++)
    	{
    
    		aceleracion[0][i]=0.0;
    		aceleracion[1][i]=0.0;
    
    		for(j=0; j<N; j++)
    		{							
    		    if(i!=j)
    		    {													       
    			    norma=sqrt(((posicion[0][i]-posicion[0][j])*(posicion[0][i]-posicion[0][j]))+((posicion[1][i]-posicion[1][j])*(posicion[1][i]-posicion[1][j])));												
    				aceleracion[0][i]=aceleracion[0][i]-((masa[j]*(posicion[0][i]-posicion[0][j]))/(norma*norma*norma));
    				aceleracion[1][i]=aceleracion[1][i]-((masa[j]*(posicion[1][i]-posicion[1][j]))/(norma*norma*norma));
    			}
    		}
    	}
  
        
        //Y finalmente, la nueva velocidad

        velocidad[0][0]=0.0;
        velocidad[1][0]=0.0;
        
        for(i=1; i<N; i++)
        {
            velocidad[0][i]=omega[0][i]+(h*0.5*aceleracion[0][i]);
		    velocidad[1][i]=omega[1][i]+(h*0.5*aceleracion[1][i]);
        }
        
        
        //Sacamos a un fichero de texto las nuevas posiciones de los planetas
        t=t+h;
        


	    
        for(i=0; i<N; i++)
        {
            pf<<posicion[0][i]<<"\t"<<posicion[1][i]<<"\t";
                               
        }
            
        pf<<endl;
        
        contador++;
        
        //Calculamos la energia de la tierra 
        

        
        
        
        
        //Comprobar si ha dado una vuelta

        if((posicion[1][1]<0.0)&&(mercurio==1))
        {
            mercurio=2;
            cout<<"MERCURIO: "<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<endl;        
        }
        
    
        if((posicion[1][2]<0.0)&&(venus==1))
        {
            venus=2;
            cout<<"VENUS: "<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<endl;        
        }  

        if((posicion[1][3]<0.0)&&(tierra==1))
        {
            tierra=2;
            cout<<"TIERRA: "<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<endl;        
        }    

        if((posicion[1][4]<0.0)&&(marte==1))
        {
            marte=2;
            cout<<"MARTE: "<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<endl;        
        }
    
        if((posicion[1][5]<0.0)&&(jupiter==1))
        {
            jupiter=2;
            cout<<"JUPITER: "<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<endl;        
        }  

        if((posicion[1][6]<0.0)&&(saturno==1))
        {
            saturno=2;
            cout<<"SATURNO: "<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<endl;        
        }

        if((posicion[1][7]<0.0)&&(urano==1))
        {
            urano=2;
            cout<<"URANO: "<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<endl;        
        }
    
        if((posicion[1][8]<0.0)&&(neptuno==1))
        {
            neptuno=2;
            cout<<"NEPTUNO: "<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<endl;        
        }  

        if((posicion[1][9]<0.0)&&(pluton==1))
        {
            saturno=2;
            cout<<"PLUTON: "<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<endl;        
        }

    }    
    
    mi.close(); 
    pi.close();
    vi.close();
    pf.close();
    
    
    return 0;
}
