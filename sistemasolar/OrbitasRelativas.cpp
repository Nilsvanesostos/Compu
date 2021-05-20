#include <iostream>
#include <cmath>
#include <fstream>

#define Msol 1.988e30
#define G 6.67e-11
#define c 1.496e11
#define N 10
#define h 0.01


using namespace std;
int main(void)
{
    double m[N],v[2][N], r[2][N], a[2][N], w[2][N], norma,t;
    int i,j,k,n;
    bool condicion[9];
    

    for(i=0; i<9; i++)
        condicion[i]=true;
    
    t=0.0;

    ifstream mi, vi, pi; //ficheros de masas velocidades y posiciones iniciales
    mi.open("masa");
    pi.open("posicion");
    vi.open("velocidad");

    ofstream re; //fichero donde vamos a escribir todas la posiciones de los planetas
    re.open("OrbitasRelativas");
    
    
    //Introducimos las masas a nuestro vector del fichero de datos    

    for(i=0; i<N; i++)
    {
        mi>>m[i];
        m[i]=m[i]/Msol;
          
    }  
    
    
    for(i=0; i<N; i++)
    {
        pi>>r[0][i]; //eje x
        r[0][i]=r[0][i]*1.1/c;
        r[1][i]=0.0; //eje y
        re<<r[0][i]<<", "<<r[1][i]<<endl;
    }  

    re<<endl;
    
    
    
    

    for(i=0; i<N; i++)
    {
        v[0][i]=0.0; //eje x
        vi>>v[1][i]; //eje y
        v[1][i]=v[1][i]*sqrt(c/(G*Msol));
    }  
    
    
    //Calculamos la aceleracion en un instante del tiempo

    for(i=0; i<N; i++)
    {
	    a[0][i]=0.0;
	    a[1][i]=0.0;

	    for(j=0; j<N; j++)
	    {
		    if(i!=j)
		    {	
			    norma=sqrt(((r[0][i]-r[0][j])*(r[0][i]-r[0][j]))+((r[1][i]-r[1][j])*(r[1][i]-r[1][j])));
			    a[0][i]=a[0][i]-((m[j]*(r[0][i]-r[0][j]))/(norma*norma*norma));
			    a[1][i]=a[1][i]-((m[j]*(r[1][i]-r[1][j]))/(norma*norma*norma));
		    }
	    }
    }			
			
    for(n=0; n<1000000;n++)
    { 
        //A continuación, calculamos las nuevas posiciones y omegas.

        r[0][0]=0.0;
        r[1][0]=0.0;
        
        for(i=1; i<N; i++)
        {
            r[0][i]=r[0][i]+(h*v[0][i])+(h*h*0.5*a[0][i]);
		    r[1][i]=r[1][i]+(h*v[1][i])+(h*h*0.5*a[1][i]);

		    w[0][i]=v[0][i]+(h*0.5*a[0][i]);
            w[1][i]=v[1][i]+(h*0.5*a[1][i]);
        }
        
        //Ahora calculamos la nueva aceleracion con la nueva posicion
        for(i=0; i<N; i++)
    	{
    
    		a[0][i]=0.0;
    		a[1][i]=0.0;
    
    		for(j=0; j<N; j++)
    		{							
    		    if(i!=j)
    		    {													       
    			    norma=sqrt(((r[0][i]-r[0][j])*(r[0][i]-r[0][j]))+((r[1][i]-r[1][j])*(r[1][i]-r[1][j])));												
    				a[0][i]=a[0][i]-((m[j]*(r[0][i]-r[0][j]))/(norma*norma*norma));
    				a[1][i]=a[1][i]-((m[j]*(r[1][i]-r[1][j]))/(norma*norma*norma));
    			}
    		}
    	}
  
        
        //Y finalmente, la nueva velocidad

        v[0][0]=0.0;
        v[1][0]=0.0;
        
        for(i=1; i<N; i++)
        {
            v[0][i]=w[0][i]+(h*0.5*a[0][i]);
		    v[1][i]=w[1][i]+(h*0.5*a[1][i]);
        }

        //Sumamos el paso al tiempo, y volvemos a espezar todo de nuevo 
        
        t=t+h;

        //Sacamos a un fichero de texto las nuevas posiciones de los planetas
	    
        for(i=0; i<N; i++)
        {
            re<<r[0][i]<<", "<<r[1][i]<<endl;
                               
        }
            
        re<<endl;
        
        
        //Comprobar si ha dado una vuelta, y en caso afirmativo los saco por pantalla

        if((r[1][1]<0.0)&&(condicion[0]==true))
        {
            condicion[0]=false;
            cout<<"MERCURIO: "<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<endl;        
        }
        
    
        if((r[1][2]<0.0)&&(condicion[1]==true))
        {
            condicion[1]=false;
            cout<<"VENUS: "<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<endl;        
        }  

        if((r[1][3]<0.0)&&(condicion[2]==true))
        {
            condicion[2]=false;
            cout<<"TIERRA: "<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<endl;        
        }    

        if((r[1][4]<0.0)&&(condicion[3]==true))
        {
            condicion[3]=false;
            cout<<"MARTE: "<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<endl;        
        }
    
        if((r[1][5]<0.0)&&(condicion[4]==true))
        {
            condicion[4]=false;
            cout<<"JUPITER: "<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<endl;        
        }  

        if((r[1][6]<0.0)&&(condicion[5]==true))
        {
            condicion[5]=false;
            cout<<"SATURNO: "<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<endl;        
        }

        if((r[1][7]<0.0)&&(condicion[6]==true))
        {
            condicion[6]=false;
            cout<<"URANO: "<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<endl;        
        }
    
        if((r[1][8]<0.0)&&(condicion[7]==true))
        {
            condicion[7]=false;
            cout<<"NEPTUNO: "<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<endl;        
        }  

        if((r[1][9]<0.0)&&(condicion[8]==true))
        {
            condicion[8]=false;
            cout<<"PLUTON: "<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<endl;        
        }

    }    
    
    mi.close(); 
    pi.close();
    vi.close();
    re.close();
    
    
    
    return 0;
}
