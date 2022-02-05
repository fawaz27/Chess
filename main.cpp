#include <iostream>
#include"Piece.h"
#include"Point.h"
#include <stdlib.h>
#include "termcolor.hpp"
#include <vector>


#define ligne 8
#define colonne 8
using namespace termcolor;
using namespace std;



string tab2[8][8]={
        "T","C","F","Q","K","F","C","T",
        "P","P","P","P","P","P","P","P",
        " "," "," "," "," "," "," "," ",
        " "," "," "," "," "," "," "," ",
        " "," "," "," "," "," "," "," ",
        " "," "," "," "," "," "," "," ",
        "P","P","P","P","P","P","P","P",
        "T","C","F","Q","K","F","C","T"};



string Noir="\033[0;30m",Blanc="\033[97m",Vert="\033[1;32m",Rouge= "\033[0;31m";




void initialisation(Piece tab[][colonne])//Cette fonction initialise le plateu de jeu
{

    for (int i = 0; i < ligne; i++)

    {
       for (int  j = 0; j < colonne; j++)
       {
           tab[i][j].setAbs(i);
           tab[i][j].setOrd(j);
           tab[i][j].setNomPiece(tab2[i][j]);
           if (i<2)
           {
                tab[i][j].setColor("black");

           }
           else if(i>5)
           {
                tab[i][j].setColor("white");
           }
           else
           {
                
           }
           
           
           
       }
       
    }
    


}





void affichage (Piece tab[][colonne])//Cette fonction se charge d'afficher le plateau à chaque mouvement de la partie 
{
        int i,j,k=0;
        cout<<Vert<<"\n\t  |-a---b---c---d---e---f---g---h-|\n\t" ;
     cout <<"  |-------------------------------|"<<Blanc<<"\n\t";
    for ( i = 0; i < 8; i++)
    { 
        cout<<Vert<<i+1<<" "<<Blanc;
        for ( j = 0; j < 8; j++)
        {k++;
               if (tab[i][j].getColor()=="black")
               {
                   cout<<Vert<<"| "<<Rouge<<tab[i][j].getNomPiece()<<Blanc<<" ";
               }
               else
               {
                    cout<<Vert<<"| "<<Blanc<<tab[i][j].getNomPiece()<<" ";
               }
               
               
             
             if(k%8==0)
             cout<<Vert<<"| "<<k/8<<Blanc<<"\n\t "<<Vert<< " |-------------------------------|\n\t"<<Blanc;
        }
       }
   
    cout<<Vert<<"  |-a---b---c---d---e---f---g---h-|"<<Blanc<<"\n" ;
    }





int Split(vector<string>& vecteur, string chaine, char separateur)// Cette fonction découpe une chaine de charactère suivant un séparateur
{
	vecteur.clear();

	string::size_type stTemp = chaine.find(separateur);
	
	while(stTemp != string::npos)
	{
		vecteur.push_back(chaine.substr(0, stTemp));
		chaine = chaine.substr(stTemp + 1);
		stTemp = chaine.find(separateur);
	}
	
	vecteur.push_back(chaine);

	return vecteur.size();
}




vector<int> decodage(string str)//Cette fonction décode le coup et renvoi une liste contenant les coordonnées de départ et d'arrivée
{

    vector<string> vecteur;
    int nb=Split(vecteur,str,'-');
    vector<int> r;
    r.clear();
    string chaine;
    for (int i = 0; i < nb; i++)
    {
        chaine=vecteur[i];
        r.push_back(chaine[0]-'a');
        r.push_back(chaine[1]-'1');
        

    }
    return r;

}




int si_coup_possible(int x1,int y1 ,int x2,int y2,int joueur,Piece tab[][colonne])//Cette fonction vérifie si un coup est possible et renvoie 1 si c'est possible et 0 sinon
{
    
    int result=0,i,j;
    
    if (joueur==1)//Blancs
    {
        if (tab[x1][y1].getNomPiece()=="P")//Pion
        {
            
            if (tab[x2][y2].getNomPiece()==" ")
            {
                
                if (y1==y2)
                {
                    if (x1==6)
                    {
                        if ((x1-x2)==1)
                            {
                             result=1;   
                            }
                            
                        else if ((x1-x2)==2)
                            {
                                i = x1-1;
                                
                                for ( i = x1-1; tab[i][y1].getNomPiece()==" " && i>x2; i--);

                                if (i==x2)
                                    {
                                        result=1;
                                    }
                                

                            }
                            
                    }
                    else
                    {
                        if ((x1-x2)==1)
                        {
                            result=1;
                        }
                        
                    }
                    
                    
                }
                
            }
            else if(tab[x2][y2].getNomPiece()!=" " && tab[x2][y2].getColor()=="black" && tab[x2][y2].getNomPiece()!="K")
            {
                if ((x2==x1-1 && y2==y1+1)||(x2==x1-1 && y2==y1-1))
                {
                   result=1;
                }
                
            }
            
            
        }
        else if(tab[x1][y1].getNomPiece()=="T")//Tour
        {
            if (tab[x2][y2].getNomPiece()==" ")
            {
                if (y1==y2)
                {
                    if (x1>x2)
                    {
                        for ( i = x1-1; tab[i][y1].getNomPiece()==" " && i>x2; i--);

                                    if (i==x2)
                                        {
                                            result=1;
                                        }
                    }
                    else if(x1<x2)
                    {
                        for ( i = x1+1; tab[i][y1].getNomPiece()==" " && i<x2; i++);

                                    if (i==x2)
                                        {
                                            result=1;
                                        }
                    }
                }
                else if(x1==x2)
                {
                
                    if (y1>y2)
                    {
                        for ( i = y1-1; tab[x1][i].getNomPiece()==" " && i>y2; i--);

                                    if (i==y2)
                                        {
                                            result=1;
                                        }
                    }
                    else if(y1<y2)
                    {
                        for ( i = y1+1; tab[x1][i].getNomPiece()==" " && i<y2; i++);

                                    if (i==y2)
                                        {
                                            result=1;
                                        }
                    }
                
                }
                
                
            }
            else if(tab[x2][y2].getNomPiece()!=" " && tab[x2][y2].getColor()=="black" && tab[x2][y2].getNomPiece()!="K")
            {
                if (y1==y2)
                {
                    if (x1>x2)
                    {
                        for ( i = x1-1; tab[i][y1].getNomPiece()==" " && i>x2; i--);

                                    if (i==x2)
                                        {
                                            result=1;
                                        }
                    }
                    else if(x1<x2)
                    {
                        for ( i = x1+1; tab[i][y1].getNomPiece()==" " && i<x2; i++);

                                    if (i==x2)
                                        {
                                            result=1;
                                        }
                    }
                }
                else if(x1==x2)
                {
                
                    if (y1>y2)
                    {
                        for ( i = y1-1; tab[x1][i].getNomPiece()==" " && i>y2; i--);

                                    if (i==y2)
                                        {
                                            result=1;
                                        }
                    }
                    else if(y1<y2)
                    {
                        for ( i = y1+1; tab[x1][i].getNomPiece()==" " && i<y2; i++);

                                    if (i==y2)
                                        {
                                            result=1;
                                        }
                    }
                
                }
                
            }
            
            
            
        }
        else if(tab[x1][y1].getNomPiece()=="F")// Fou
        {
            if (tab[x2][y2].getNomPiece()==" ")
            {
                
                if (abs((x2-x1))==abs((y2-y1)))
                {
                    
                    if (x1>x2)
                    {
                        if (y1<y2)
                        {
                            for ( i = x1-1,j=y1+1; i >x2 && tab[i][j].getNomPiece()==" "; i--,j++);                         
                            if (i==x2)
                            {
                                result=1;
                            }
                            
                        }
                        else if(y1>y2)
                        {
                            for ( i = x1-1,j=y1-1; i >x2 && tab[i][j].getNomPiece()==" "; i--,j--);                         
                            if (i==x2)
                            {
                                result=1;
                            }
                        }
                        
                        
                    }

                    else if(x1<x2)
                    {
                        if (y1<y2)
                        {
                            for ( i = x1+1,j=y1+1; i <x2 && tab[i][j].getNomPiece()==" "; i++,j++);                         
                            if (i==x2)
                            {
                                result=1;
                            }
                            
                        }
                        else if(y1>y2)
                        {
                            for ( i = x1+1,j=y1-1; i <x2 && tab[i][j].getNomPiece()==" "; i++,j--);                         
                            if (i==x2)
                            {
                                result=1;
                            }
                        }
                    }
                    
                }
                
            }
            else if(tab[x2][y2].getNomPiece()!=" " && tab[x2][y2].getColor()=="black" && tab[x2][y2].getNomPiece()!="K")
            {
                if (abs((x2-x1))==abs((y2-y1)))
                {
                    
                    if (x1>x2)
                    {
                        if (y1<y2)
                        {
                            for ( i = x1-1,j=y1+1; i >x2 && tab[i][j].getNomPiece()==" "; i--,j++);                         
                            if (i==x2)
                            {
                                result=1;
                            }
                            
                        }
                        else if(y1>y2)
                        {
                            for ( i = x1-1,j=y1-1; i >x2 && tab[i][j].getNomPiece()==" "; i--,j--);                         
                            if (i==x2)
                            {
                                result=1;
                            }
                        }
                        
                        
                    }

                    else if(x1<x2)
                    {
                        if (y1<y2)
                        {
                            for ( i = x1+1,j=y1+1; i <x2 && tab[i][j].getNomPiece()==" "; i++,j++);                         
                            if (i==x2)
                            {
                                result=1;
                            }
                            
                        }
                        else if(y1>y2)
                        {
                            for ( i = x1+1,j=y1-1; i <x2 && tab[i][j].getNomPiece()==" "; i++,j--);                         
                            if (i==x2)
                            {
                                result=1;
                            }
                        }
                    }
                    
                }

            }
            

        }
        else if(tab[x1][y1].getNomPiece()=="K")// Roi
        {
            if (tab[x2][y2].getNomPiece()==" ")
            {
                if (y1==y2)
                {
                    if (abs(x2-x1)==1)
                    {
                        result=1;
                    }
                    
                    
                }
                else if(x1==x2)
                {
                    if (abs(y2-y1)==1)
                    {
                        result=1;
                    }
                   
                }
                else
                {
                    if (abs(x2-x1)==1 && abs(y2-y1)==1)
                    {
                      result=1;
                    }
                    
                }
                
            }
            else if(tab[x2][y2].getNomPiece()!=" " && tab[x2][y2].getColor()=="black" && tab[x2][y2].getNomPiece()!="K")
            {
                if (y1==y2)
                {
                    if (abs(x2-x1)==1)
                    {
                        result=1;
                    }
                    
                    
                }
                else if(x1==x2)
                {
                    if (abs(y2-y1)==1)
                    {
                        result=1;
                    }
                   
                }
                else
                {
                    if (abs(x2-x1)==1 && abs(y2-y1)==1)
                    {
                      result=1;
                    }
                    
                }
            }

            
        }
        else if(tab[x1][y1].getNomPiece()=="C")//Cavalier
        {
            if (tab[x2][y2].getNomPiece()==" ")
            {
                
                if (x1>x2)
                {
                   if (y1<y2)
                   {
                       if ( (x2==x1-2) && (y2==y1+1) )
                       {
                           result=1;
                       }
                       else if( (x2==x1-1) && (y2==y1+2) )
                       {
                           result=1;
                       }
                    }
                   else if(y1>y2)
                   {
                       if ( (x2==x1-2) && (y2==y1-1) )
                       {
                           result=1;
                       }
                       else if( (x2==x1-1) && (y2==y1-2) )
                       {
                           result=1;
                       }
                    }
                   
                   
                }
                else if(x1<x2)
                {
                    if (y1<y2)
                    {
                       if ( (x2==x1+2) && (y2==y1+1) )
                       {
                           result=1;
                       }
                       else if( (x2==x1+1) && (y2==y1+2) )
                       {
                           result=1;
                       }
                    }
                   else if(y1>y2)
                    {
                       if ( (x2==x1+2) && (y2==y1-1) )
                       {
                           result=1;
                       }
                       else if( (x2==x1+1) && (y2==y1-2) )
                       {
                           result=1;
                       }
                    }
                    
                }
                
                
            }
            else if(tab[x2][y2].getNomPiece()!=" " && tab[x2][y2].getColor()=="black" && tab[x2][y2].getNomPiece()!="K")
            {
                if (x1>x2)
                {
                   if (y1<y2)
                   {
                       if ( (x2==x1-2) && (y2==y1+1) )
                       {
                           result=1;
                       }
                       else if( (x2==x1-1) && (y2==y1+2) )
                       {
                           result=1;
                       }
                    }
                   else if(y1>y2)
                   {
                       if ( (x2==x1-2) && (y2==y1-1) )
                       {
                           result=1;
                       }
                       else if( (x2==x1-1) && (y2==y1-2) )
                       {
                           result=1;
                       }
                    }
                   
                   
                }
                else if(x1<x2)
                {
                    if (y1<y2)
                    {
                       if ( (x2==x1+2) && (y2==y1+1) )
                       {
                           result=1;
                       }
                       else if( (x2==x1+1) && (y2==y1+2) )
                       {
                           result=1;
                       }
                    }
                   else if(y1>y2)
                    {
                       if ( (x2==x1+2) && (y2==y1-1) )
                       {
                           result=1;
                       }
                       else if( (x2==x1+1) && (y2==y1-2) )
                       {
                           result=1;
                       }
                    }
                    
                }
            }
        }
        else if(tab[x1][y1].getNomPiece()=="Q") //Reine
        {
            if (tab[x2][y2].getNomPiece()==" ")
            {
                /*------------Dépalacement Roi ------------------*/
                if (y1==y2)
                {
                    if (abs(x2-x1)==1)
                    {
                        result=1;
                    }
                    
                    
                }
                else if(x1==x2)
                {
                    if (abs(y2-y1)==1)
                    {
                        result=1;
                    }
                   
                }
                else
                {
                    if (abs(x2-x1)==1 && abs(y2-y1)==1)
                    {
                      result=1;
                    }
                    
                }
                /*------------Dépalacement Fou ------------------*/
                if (abs((x2-x1))==abs((y2-y1)))
                {
                    
                    if (x1>x2)
                    {
                        if (y1<y2)
                        {
                            for ( i = x1-1,j=y1+1; i >x2 && tab[i][j].getNomPiece()==" "; i--,j++);                         
                            if (i==x2)
                            {
                                result=1;
                            }
                            
                        }
                        else if(y1>y2)
                        {
                            for ( i = x1-1,j=y1-1; i >x2 && tab[i][j].getNomPiece()==" "; i--,j--);                         
                            if (i==x2)
                            {
                                result=1;
                            }
                        }
                        
                        
                    }

                    else if(x1<x2)
                    {
                        if (y1<y2)
                        {
                            for ( i = x1+1,j=y1+1; i <x2 && tab[i][j].getNomPiece()==" "; i++,j++);                         
                            if (i==x2)
                            {
                                result=1;
                            }
                            
                        }
                        else if(y1>y2)
                        {
                            for ( i = x1+1,j=y1-1; i <x2 && tab[i][j].getNomPiece()==" "; i++,j--);                         
                            if (i==x2)
                            {
                                result=1;
                            }
                        }
                    }
                    
                }

                /*------------Dépalacement Tour ------------------*/
                if (y1==y2)
            {
                if (tab[x2][y2].getNomPiece()==" ")
                {
                    if (x1>x2)
                    {
                        for ( i = x1-1; tab[i][y1].getNomPiece()==" " && i>x2; i--);

                                    if (i==x2)
                                        {
                                            result=1;
                                        }
                    }
                    else if(x1<x2)
                    {
                        for ( i = x1+1; tab[i][y1].getNomPiece()==" " && i<x2; i++);

                                    if (i==x2)
                                        {
                                            result=1;
                                        }
                    }
                }
                
                
            }
                else if(x1==x2)
            {
                if (tab[x2][y2].getNomPiece()==" ")
                {
                    if (y1>y2)
                    {
                        for ( i = y1-1; tab[x1][i].getNomPiece()==" " && i>y2; i--);

                                    if (i==y2)
                                        {
                                            result=1;
                                        }
                    }
                    else if(y1<y2)
                    {
                        for ( i = y1+1; tab[x1][i].getNomPiece()==" " && i<y2; i++);

                                    if (i==y2)
                                        {
                                            result=1;
                                        }
                    }
                }
                
                
            }

            }
            else if(tab[x2][y2].getNomPiece()!=" " && tab[x2][y2].getColor()=="black" && tab[x2][y2].getNomPiece()!="K")
            {
                 /*------------Dépalacement Roi ------------------*/
                if (y1==y2)
                {
                    if (abs(x2-x1)==1)
                    {
                        result=1;
                    }
                    
                    
                }
                else if(x1==x2)
                {
                    if (abs(y2-y1)==1)
                    {
                        result=1;
                    }
                   
                }
                else
                {
                    if (abs(x2-x1)==1 && abs(y2-y1)==1)
                    {
                      result=1;
                    }
                    
                }
                /*------------Dépalacement Fou ------------------*/
                if (abs((x2-x1))==abs((y2-y1)))
                {
                    
                    if (x1>x2)
                    {
                        if (y1<y2)
                        {
                            for ( i = x1-1,j=y1+1; i >x2 && tab[i][j].getNomPiece()==" "; i--,j++);                         
                            if (i==x2)
                            {
                                result=1;
                            }
                            
                        }
                        else if(y1>y2)
                        {
                            for ( i = x1-1,j=y1-1; i >x2 && tab[i][j].getNomPiece()==" "; i--,j--);                         
                            if (i==x2)
                            {
                                result=1;
                            }
                        }
                        
                        
                    }

                    else if(x1<x2)
                    {
                        if (y1<y2)
                        {
                            for ( i = x1+1,j=y1+1; i <x2 && tab[i][j].getNomPiece()==" "; i++,j++);                         
                            if (i==x2)
                            {
                                result=1;
                            }
                            
                        }
                        else if(y1>y2)
                        {
                            for ( i = x1+1,j=y1-1; i <x2 && tab[i][j].getNomPiece()==" "; i++,j--);                         
                            if (i==x2)
                            {
                                result=1;
                            }
                        }
                    }
                    
                }

                /*------------Dépalacement Tour ------------------*/
                if (y1==y2)
            {
                if (tab[x2][y2].getNomPiece()==" ")
                {
                    if (x1>x2)
                    {
                        for ( i = x1-1; tab[i][y1].getNomPiece()==" " && i>x2; i--);

                                    if (i==x2)
                                        {
                                            result=1;
                                        }
                    }
                    else if(x1<x2)
                    {
                        for ( i = x1+1; tab[i][y1].getNomPiece()==" " && i<x2; i++);

                                    if (i==x2)
                                        {
                                            result=1;
                                        }
                    }
                }
                
                
            }
                else if(x1==x2)
            {
                if (tab[x2][y2].getNomPiece()==" ")
                {
                    if (y1>y2)
                    {
                        for ( i = y1-1; tab[x1][i].getNomPiece()==" " && i>y2; i--);

                                    if (i==y2)
                                        {
                                            result=1;
                                        }
                    }
                    else if(y1<y2)
                    {
                        for ( i = y1+1; tab[x1][i].getNomPiece()==" " && i<y2; i++);

                                    if (i==y2)
                                        {
                                            result=1;
                                        }
                    }
                }
                
                
            }

            
            }
            
        }
        else
        {
            cout<<" Pièce sans nom"<<endl;
        }
        

    }
    else if (joueur==2)//Noir
    {
        if (tab[x1][y1].getNomPiece()=="P") //Pion
        {
            if (tab[x2][y2].getNomPiece()==" ")
            {
                if (y1==y2)
                {
                    if (x1==1)
                    {
                        
                        if (abs(x1-x2)==1)
                            {
                             result=1;   
                            }
                            
                        else if (abs(x1-x2)==2)
                            {
                                for ( i = x1+1; tab[i][y1].getNomPiece()==" " && i<x2; i++);
                            
                                if (i==x2)
                                    {
                                        result=1;
                                    }
                                

                            }
                            
                    }
                    else
                    {
                        
                        if (abs(x1-x2)==1)
                        {
                            result=1;
                        }
                        
                    }
                    
                    
                }
                
            }
            else if(tab[x2][y2].getNomPiece()!=" " && tab[x2][y2].getColor()=="white" && tab[x2][y2].getNomPiece()!="K")
            {
                if ((x2==x1+1 && y2==y1+1)||(x2==x1+1 && y2==y1-1))
                {
                   result=1;
                }
                
            }
            
        }
        else if(tab[x1][y1].getNomPiece()=="T")//Tour
        {
            if (tab[x2][y2].getNomPiece()==" ")
            {
                if (y1==y2)
                {
                    if (x1>x2)
                    {
                        for ( i = x1-1; tab[i][y1].getNomPiece()==" " && i>x2; i--);

                                    if (i==x2)
                                        {
                                            result=1;
                                        }
                    }
                    else if(x1<x2)
                    {
                        for ( i = x1+1; tab[i][y1].getNomPiece()==" " && i<x2; i++);

                                    if (i==x2)
                                        {
                                            result=1;
                                        }
                    }
                }
                else if(x1==x2)
                {
                
                    if (y1>y2)
                    {
                        for ( i = y1-1; tab[x1][i].getNomPiece()==" " && i>y2; i--);

                                    if (i==y2)
                                        {
                                            result=1;
                                        }
                    }
                    else if(y1<y2)
                    {
                        for ( i = y1+1; tab[x1][i].getNomPiece()==" " && i<y2; i++);

                                    if (i==y2)
                                        {
                                            result=1;
                                        }
                    }
                
                }
                
                
            }
            else if(tab[x2][y2].getNomPiece()!=" " && tab[x2][y2].getColor()=="white" && tab[x2][y2].getNomPiece()!="K")
            {
                if (y1==y2)
                {
                    if (x1>x2)
                    {
                        for ( i = x1-1; tab[i][y1].getNomPiece()==" " && i>x2; i--);

                                    if (i==x2)
                                        {
                                            result=1;
                                        }
                    }
                    else if(x1<x2)
                    {
                        for ( i = x1+1; tab[i][y1].getNomPiece()==" " && i<x2; i++);

                                    if (i==x2)
                                        {
                                            result=1;
                                        }
                    }
                }
                else if(x1==x2)
                {
                
                    if (y1>y2)
                    {
                        for ( i = y1-1; tab[x1][i].getNomPiece()==" " && i>y2; i--);

                                    if (i==y2)
                                        {
                                            result=1;
                                        }
                    }
                    else if(y1<y2)
                    {
                        for ( i = y1+1; tab[x1][i].getNomPiece()==" " && i<y2; i++);

                                    if (i==y2)
                                        {
                                            result=1;
                                        }
                    }
                
                }
            }
            
        }
        else if(tab[x1][y1].getNomPiece()=="F") //Fou
        {
            if (tab[x2][y2].getNomPiece()==" ")
            {
                
                if (abs((x2-x1))==abs((y2-y1)))
                {
                    
                    if (x1>x2)
                    {
                        if (y1<y2)
                        {
                            for ( i = x1-1,j=y1+1; i >x2 && tab[i][j].getNomPiece()==" "; i--,j++);                         
                            if (i==x2)
                            {
                                result=1;
                            }
                            
                        }
                        else if(y1>y2)
                        {
                            for ( i = x1-1,j=y1-1; i >x2 && tab[i][j].getNomPiece()==" "; i--,j--);                         
                            if (i==x2)
                            {
                                result=1;
                            }
                        }
                        
                        
                    }

                    else if(x1<x2)
                    {
                        if (y1<y2)
                        {
                            for ( i = x1+1,j=y1+1; i <x2 && tab[i][j].getNomPiece()==" "; i++,j++);                         
                            if (i==x2)
                            {
                                result=1;
                            }
                            
                        }
                        else if(y1>y2)
                        {
                            for ( i = x1+1,j=y1-1; i <x2 && tab[i][j].getNomPiece()==" "; i++,j--);                         
                            if (i==x2)
                            {
                                result=1;
                            }
                        }
                    }
                    
                }
                
            }
            else if(tab[x2][y2].getNomPiece()!=" " && tab[x2][y2].getColor()=="white" && tab[x2][y2].getNomPiece()!="K")
            {
                if (abs((x2-x1))==abs((y2-y1)))
                {
                    
                    if (x1>x2)
                    {
                        if (y1<y2)
                        {
                            for ( i = x1-1,j=y1+1; i >x2 && tab[i][j].getNomPiece()==" "; i--,j++);                         
                            if (i==x2)
                            {
                                result=1;
                            }
                            
                        }
                        else if(y1>y2)
                        {
                            for ( i = x1-1,j=y1-1; i >x2 && tab[i][j].getNomPiece()==" "; i--,j--);                         
                            if (i==x2)
                            {
                                result=1;
                            }
                        }
                        
                        
                    }

                    else if(x1<x2)
                    {
                        if (y1<y2)
                        {
                            for ( i = x1+1,j=y1+1; i <x2 && tab[i][j].getNomPiece()==" "; i++,j++);                         
                            if (i==x2)
                            {
                                result=1;
                            }
                            
                        }
                        else if(y1>y2)
                        {
                            for ( i = x1+1,j=y1-1; i <x2 && tab[i][j].getNomPiece()==" "; i++,j--);                         
                            if (i==x2)
                            {
                                result=1;
                            }
                        }
                    }
                    
                }
            }
            
            
        }
        else if(tab[x1][y1].getNomPiece()=="K") //Roi
        {
           if (tab[x2][y2].getNomPiece()==" ")
            {
                if (y1==y2)
                {
                    if (abs(x2-x1)==1)
                    {
                        result=1;
                    }
                    
                    
                }
                else if(x1==x2)
                {
                    if (abs(y2-y1)==1)
                    {
                        result=1;
                    }
                   
                }
                else
                {
                    if (abs(x2-x1)==1 && abs(y2-y1)==1)
                    {
                      result=1;
                    }
                    
                }
                
            } 
            else if(tab[x2][y2].getNomPiece()!=" " && tab[x2][y2].getColor()=="white" && tab[x2][y2].getNomPiece()!="K")
            {
                if (y1==y2)
                {
                    if (abs(x2-x1)==1)
                    {
                        result=1;
                    }
                    
                    
                }
                else if(x1==x2)
                {
                    if (abs(y2-y1)==1)
                    {
                        result=1;
                    }
                   
                }
                else
                {
                    if (abs(x2-x1)==1 && abs(y2-y1)==1)
                    {
                      result=1;
                    }
                    
                }
                
            }
        }
        else if(tab[x1][y1].getNomPiece()=="C") //Cavalier
        {
           
            if (tab[x2][y2].getNomPiece()==" ")
            {
                
                if (x1>x2)
                {
                   if (y1<y2)
                   {
                       if ( (x2==x1-2) && (y2==y1+1) )
                       {
                           result=1;
                       }
                       else if( (x2==x1-1) && (y2==y1+2) )
                       {
                           result=1;
                       }
                    }
                   else if(y1>y2)
                   {
                       if ( (x2==x1-2) && (y2==y1-1) )
                       {
                           result=1;
                       }
                       else if( (x2==x1-1) && (y2==y1-2) )
                       {
                           result=1;
                       }
                    }
                   
                   
                }
                else if(x1<x2)
                {
                    if (y1<y2)
                    {
                       if ( (x2==x1+2) && (y2==y1+1) )
                       {
                           result=1;
                       }
                       else if( (x2==x1+1) && (y2==y1+2) )
                       {
                           result=1;
                       }
                    }
                   else if(y1>y2)
                    {
                       if ( (x2==x1+2) && (y2==y1-1) )
                       {
                           result=1;
                       }
                       else if( (x2==x1+1) && (y2==y1-2) )
                       {
                           result=1;
                       }
                    }
                    
                }
                
                
            }
            else if(tab[x2][y2].getNomPiece()!=" " && tab[x2][y2].getColor()=="white" && tab[x2][y2].getNomPiece()!="K")
            {
                if (x1>x2)
                {
                   if (y1<y2)
                   {
                       if ( (x2==x1-2) && (y2==y1+1) )
                       {
                           result=1;
                       }
                       else if( (x2==x1-1) && (y2==y1+2) )
                       {
                           result=1;
                       }
                    }
                   else if(y1>y2)
                   {
                       if ( (x2==x1-2) && (y2==y1-1) )
                       {
                           result=1;
                       }
                       else if( (x2==x1-1) && (y2==y1-2) )
                       {
                           result=1;
                       }
                    }
                   
                   
                }
                else if(x1<x2)
                {
                    if (y1<y2)
                    {
                       if ( (x2==x1+2) && (y2==y1+1) )
                       {
                           result=1;
                       }
                       else if( (x2==x1+1) && (y2==y1+2) )
                       {
                           result=1;
                       }
                    }
                   else if(y1>y2)
                    {
                       if ( (x2==x1+2) && (y2==y1-1) )
                       {
                           result=1;
                       }
                       else if( (x2==x1+1) && (y2==y1-2) )
                       {
                           result=1;
                       }
                    }
                    
                }
                
                
            }
            
        }
        else if(tab[x1][y1].getNomPiece()=="Q") //Reine
        {
            if (tab[x2][y2].getNomPiece()==" ")
            {
            /*------------Dépalacement Roi ------------------*/
                if (y1==y2)
                {
                    if (abs(x2-x1)==1)
                    {
                        result=1;
                    }
                    
                    
                }
                else if(x1==x2)
                {
                    if (abs(y2-y1)==1)
                    {
                        result=1;
                    }
                   
                }
                else
                {
                    if (abs(x2-x1)==1 && abs(y2-y1)==1)
                    {
                      result=1;
                    }
                    
                }
                /*------------Dépalacement Fou ------------------*/
                if (abs((x2-x1))==abs((y2-y1)))
                {
                    
                    if (x1>x2)
                    {
                        if (y1<y2)
                        {
                            for ( i = x1-1,j=y1+1; i >x2 && tab[i][j].getNomPiece()==" "; i--,j++);                         
                            if (i==x2)
                            {
                                result=1;
                            }
                            
                        }
                        else if(y1>y2)
                        {
                            for ( i = x1-1,j=y1-1; i >x2 && tab[i][j].getNomPiece()==" "; i--,j--);                         
                            if (i==x2)
                            {
                                result=1;
                            }
                        }
                        
                        
                    }

                    else if(x1<x2)
                    {
                        if (y1<y2)
                        {
                            for ( i = x1+1,j=y1+1; i <x2 && tab[i][j].getNomPiece()==" "; i++,j++);                         
                            if (i==x2)
                            {
                                result=1;
                            }
                            
                        }
                        else if(y1>y2)
                        {
                            for ( i = x1+1,j=y1-1; i <x2 && tab[i][j].getNomPiece()==" "; i++,j--);                         
                            if (i==x2)
                            {
                                result=1;
                            }
                        }
                    }
                    
                }

                /*------------Dépalacement Tour ------------------*/
                if (y1==y2)
            {
                if (tab[x2][y2].getNomPiece()==" ")
                {
                    if (x1>x2)
                    {
                        for ( i = x1-1; tab[i][y1].getNomPiece()==" " && i>x2; i--);

                                    if (i==x2)
                                        {
                                            result=1;
                                        }
                    }
                    else if(x1<x2)
                    {
                        for ( i = x1+1; tab[i][y1].getNomPiece()==" " && i<x2; i++);

                                    if (i==x2)
                                        {
                                            result=1;
                                        }
                    }
                }
                
                
            }
                else if(x1==x2)
            {
                if (tab[x2][y2].getNomPiece()==" ")
                {
                    if (y1>y2)
                    {
                        for ( i = y1-1; tab[x1][i].getNomPiece()==" " && i>y2; i--);

                                    if (i==y2)
                                        {
                                            result=1;
                                        }
                    }
                    else if(y1<y2)
                    {
                        for ( i = y1+1; tab[x1][i].getNomPiece()==" " && i<y2; i++);

                                    if (i==y2)
                                        {
                                            result=1;
                                        }
                    }
                }
                
                
            }
            }
            else if(tab[x2][y2].getNomPiece()!=" " && tab[x2][y2].getColor()=="white" && tab[x2][y2].getNomPiece()!="K")
            {
                /*------------Dépalacement Roi ------------------*/
                if (y1==y2)
                {
                    if (abs(x2-x1)==1)
                    {
                        result=1;
                    }
                    
                    
                }
                else if(x1==x2)
                {
                    if (abs(y2-y1)==1)
                    {
                        result=1;
                    }
                   
                }
                else
                {
                    if (abs(x2-x1)==1 && abs(y2-y1)==1)
                    {
                      result=1;
                    }
                    
                }
                /*------------Dépalacement Fou ------------------*/
                if (abs((x2-x1))==abs((y2-y1)))
                {
                    
                    if (x1>x2)
                    {
                        if (y1<y2)
                        {
                            for ( i = x1-1,j=y1+1; i >x2 && tab[i][j].getNomPiece()==" "; i--,j++);                         
                            if (i==x2)
                            {
                                result=1;
                            }
                            
                        }
                        else if(y1>y2)
                        {
                            for ( i = x1-1,j=y1-1; i >x2 && tab[i][j].getNomPiece()==" "; i--,j--);                         
                            if (i==x2)
                            {
                                result=1;
                            }
                        }
                        
                        
                    }

                    else if(x1<x2)
                    {
                        if (y1<y2)
                        {
                            for ( i = x1+1,j=y1+1; i <x2 && tab[i][j].getNomPiece()==" "; i++,j++);                         
                            if (i==x2)
                            {
                                result=1;
                            }
                            
                        }
                        else if(y1>y2)
                        {
                            for ( i = x1+1,j=y1-1; i <x2 && tab[i][j].getNomPiece()==" "; i++,j--);                         
                            if (i==x2)
                            {
                                result=1;
                            }
                        }
                    }
                    
                }

                /*------------Dépalacement Tour ------------------*/
                if (y1==y2)
            {
                if (tab[x2][y2].getNomPiece()==" ")
                {
                    if (x1>x2)
                    {
                        for ( i = x1-1; tab[i][y1].getNomPiece()==" " && i>x2; i--);

                                    if (i==x2)
                                        {
                                            result=1;
                                        }
                    }
                    else if(x1<x2)
                    {
                        for ( i = x1+1; tab[i][y1].getNomPiece()==" " && i<x2; i++);

                                    if (i==x2)
                                        {
                                            result=1;
                                        }
                    }
                }
                
                
            }
                else if(x1==x2)
            {
                if (tab[x2][y2].getNomPiece()==" ")
                {
                    if (y1>y2)
                    {
                        for ( i = y1-1; tab[x1][i].getNomPiece()==" " && i>y2; i--);

                                    if (i==y2)
                                        {
                                            result=1;
                                        }
                    }
                    else if(y1<y2)
                    {
                        for ( i = y1+1; tab[x1][i].getNomPiece()==" " && i<y2; i++);

                                    if (i==y2)
                                        {
                                            result=1;
                                        }
                    }
                }
                
                
            }
           
            }
        }
        else
        {
            cout<<" Pièce sans nom"<<endl;
        }
    }
    
    
return result;
    
}

vector <Point> trajectoire(Piece tmp,int joueur)
{
    int i,j,k,l;
    vector<Point> tableau;
    string str=tmp.getNomPiece();
    

    if (tmp.getNomPiece()=="K") //Roi
    {
        tableau.push_back(Point (tmp.getAbs()+1,tmp.getOrd()) );
        tableau.push_back(Point (tmp.getAbs()-1,tmp.getOrd()) );
        tableau.push_back(Point (tmp.getAbs(),tmp.getOrd()+1) );
        tableau.push_back(Point (tmp.getAbs(),tmp.getOrd()-1) );
        tableau.push_back(Point (tmp.getAbs()-1,tmp.getOrd()-1) );
        tableau.push_back(Point (tmp.getAbs()+1,tmp.getOrd()+1) );
        tableau.push_back(Point (tmp.getAbs()+1,tmp.getOrd()-1) );
        tableau.push_back(Point (tmp.getAbs()-1,tmp.getOrd()+1) );
    }
    else if(tmp.getNomPiece()=="Q")//Reine
    {
        //----------------Dépalcement Roi----------------------
        tableau.push_back(Point (tmp.getAbs()+1,tmp.getOrd()) );
        tableau.push_back(Point (tmp.getAbs()-1,tmp.getOrd()) );
        tableau.push_back(Point (tmp.getAbs(),tmp.getOrd()+1) );
        tableau.push_back(Point (tmp.getAbs(),tmp.getOrd()-1) );
        tableau.push_back(Point (tmp.getAbs()-1,tmp.getOrd()-1) );
        tableau.push_back(Point (tmp.getAbs()+1,tmp.getOrd()+1) );
        tableau.push_back(Point (tmp.getAbs()+1,tmp.getOrd()-1) );
        tableau.push_back(Point (tmp.getAbs()-1,tmp.getOrd()+1) );

        //----------------Dépalcement Tour----------------------

        for ( j = 0; j < 8; j++)
        {
            tableau.push_back(Point (tmp.getAbs(),j));
            
        }
        for ( i = 0; i < 8; i++)
        {
            tableau.push_back(Point (i,tmp.getOrd()));
        }
        

        //----------------Dépalcement Fou----------------------

        for ( i = tmp.getAbs()-1,j=tmp.getOrd()+1; i >=0 && j<8; i--,j++){
            tableau.push_back(Point (i,j) );
            
            
        }
        for ( i = tmp.getAbs()-1,j=tmp.getOrd()-1; i >=0 && j>=0; i--,j--){
            tableau.push_back(Point (i,j) );
            
            
        }
        for ( i = tmp.getAbs()+1,j=tmp.getOrd()+1; i <8 && j<8; i++,j++){
            tableau.push_back(Point (i,j) );
            
            
        }
        for ( i = tmp.getAbs()+1,j=tmp.getOrd()-1; i <8 && j>0; i++,j--){
            tableau.push_back(Point (i,j) );
            
            
        }
        
    }
    else if(tmp.getNomPiece()=="P") //Pion
    {
        if (joueur==1)
        {
            tableau.push_back(Point (tmp.getAbs()-1,tmp.getOrd()+1) );
            tableau.push_back(Point (tmp.getAbs()-1,tmp.getOrd()-1) );

            
        }
        else if(joueur==2)
        {
            tableau.push_back(Point (tmp.getAbs()+1,tmp.getOrd()+1) );
            tableau.push_back(Point (tmp.getAbs()+1,tmp.getOrd()-1) );
        }
    }
    else if(tmp.getNomPiece()=="T") //Tour
    {
        for ( j = 0; j < 8; j++)
        {
            tableau.push_back(Point (tmp.getAbs(),j));
            
        }
        for ( i = 0; i < 8; i++)
        {
            tableau.push_back(Point (i,tmp.getOrd()));
        }
    }
    else if(tmp.getNomPiece()=="F") //Fou
    {
        for ( i = tmp.getAbs()-1,j=tmp.getOrd()+1; i >=0 && j<8; i--,j++){
            tableau.push_back(Point (i,j) );
            
            
        }
        for ( i = tmp.getAbs()-1,j=tmp.getOrd()-1; i >=0 && j>=0; i--,j--){
            tableau.push_back(Point (i,j) );
            
            
        }
        for ( i = tmp.getAbs()+1,j=tmp.getOrd()+1; i <8 && j<8; i++,j++){
            tableau.push_back(Point (i,j) );
            
            
        }
        for ( i = tmp.getAbs()+1,j=tmp.getOrd()-1; i <8 && j>0; i++,j--){
            tableau.push_back(Point (i,j) );
            
            
        }
    }
    else if(tmp.getNomPiece()=="C") //Cavalier
    {
        tableau.push_back(Point(tmp.getAbs()+2,tmp.getOrd()-1));
        tableau.push_back(Point(tmp.getAbs()+1,tmp.getOrd()-2));
        tableau.push_back(Point(tmp.getAbs()+2,tmp.getOrd()+1));
        tableau.push_back(Point(tmp.getAbs()+1,tmp.getOrd()+2));
        tableau.push_back(Point(tmp.getAbs()-2,tmp.getOrd()-1));
        tableau.push_back(Point(tmp.getAbs()-1,tmp.getOrd()-2));
        tableau.push_back(Point(tmp.getAbs()-2,tmp.getOrd()+1));
        tableau.push_back(Point(tmp.getAbs()-1,tmp.getOrd()+2));
    }
    else 
    {
        
    }
    
    
    
    



return tableau;

}

Point searchKing(Piece tab[][colonne],int joueur ){
    int i,j;
    Point king;
    if (joueur==1)
    {
       for ( i = 0; i < ligne; i++)
       {
           for (int j = 0; i < colonne; j++)
           {
              if (tab[i][j].getColor()=="white" && tab[i][j].getNomPiece()=="K")
              {
                  king=Point(i,j);
              }
               
           }
           
       }
       
    }
    else if(joueur==2)
    {
        for ( i = 0; i < ligne; i++)
       {
           for (int j = 0; i < colonne; j++)
           {
              if (tab[i][j].getColor()=="black" && tab[i][j].getNomPiece()=="K")
              {
                  king=Point(i,j);
              }
               
           }
           
       }
    }
    
    
    return king;
}

int search (vector<Point> vecteur , Point cood){
int result=0;

    for (int i = 0; i < vecteur.size(); i++)
    {
        if (vecteur[i].getAbs()==cood.getAbs() && vecteur[i].getOrd()==cood.getOrd())
        {
            result=1;
        }
    
    }
return result;

}

int si_echec(Piece tab[][colonne],int joueur){
    int result=0 ,i,j ;
    vector <Point> coup_possible;
    coup_possible.clear();
    Point king=searchKing(tab,joueur);

    for ( i = 0; i < ligne; i++)
    {
       for ( j = 0; j< colonne; j++)
       {
           coup_possible=trajectoire(tab[i][j],joueur);

            if (search(coup_possible,king)==1)
            {
                result=1;
            }
            
       }
       
    }
    
    

    return result;
}


void deplacement(string str,Piece tab[][colonne]){
vector<int>  vect1=decodage(str);
int possible=3;
int y1=vect1[0],y2=vect1[2],x1=vect1[1],x2=vect1[3];
int joueur ;
Piece tmp=Piece();

if (tab[x1][y1].getColor()=="white")
{
    joueur=1;
    cout<<"C'est le joueur 1"<<endl;
}
else if(tab[x1][y1].getColor()=="black")
{
    joueur=2;
    cout<<"C'est le joueur 2"<<endl;
}
else
{
    joueur=0;
    cout<<"Pas de pièce à cet emplacement"<<endl;
}



/* 
x1 == x de départ
y1 == y de départ
x2 == x d'arrivée
y2 == y d'arrivée
*/

if (x1>-1 && x1<8 && y1>-1 && y1<8 && x2>-1 && x2<8 && y2>-1 && y2<8 && joueur!=0)
    {
    




        possible=si_coup_possible(x1,y1,x2,y2,joueur,tab);
       

        if (possible==1)
        {

            tab[x2][y2].setNomPiece(tab[x1][y1].getNomPiece());
            tab[x2][y2].setColor(tab[x1][y1].getColor());
            tab[x1][y1].setNomPiece(" ");
        }
        else
        {
            cout<<"Coup invalide\n"<<endl;

        }

    }
else
    {
    cout<<"Vous vous etes trompé de coordonnées!\n "<<endl;
    }



//system("clear");
affichage(tab);


}








int main(int argc, char const *argv[])
{

   Piece a ,tab[ligne][colonne];
   string str;
   string str1="a7-a5";
   string str2="d2-d4";
   string str3="b8-c6";
   
   vector <Point> essai(4);

   
   
   
   
   initialisation(tab);
   tab[3][4].setColor("black");
    tab[3][4].setNomPiece("Q");
    tab[2][5].setColor("black");
    tab[2][5].setNomPiece("T");
   affichage(tab);
   
  /* essai=trajectoire(tab[3][4],2);

   for (int i = 0; i < essai.size(); i++)
   {
       essai[i].info();
   }
   */
   
    /*cout<<"\n\n"<<endl;
   deplacement(str1,tab);
   cout<<"\n\n"<<endl;
   deplacement(str2,tab);
   cout<<"\n\n"<<endl;
   deplacement(str3,tab);
   cout<<"\n\n"<<endl;
*/
    while (str!="0")
    {
        cout<<"\n\tQue jouez vous?";
            getline(cin, str);
            deplacement(str,tab);
    }
    
   
   
    return 0;
}
