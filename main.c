#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<malloc.h>
#include<windows.h>
#include"Boutique.h"
#include<time.h>



void menu()
    {
	time_t rawtime;
	struct tm * timeinfo;
	
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	printf ( "La date et l'heure actuelle: %s\n", asctime (timeinfo) );
		
    int C;  char A[30],B[30];   client t;
	client T,F;
	listeC *teteC=NULL;
	teteC=file_to_listeC(teteC);
	listeP *teteP=NULL;
	teteP=file_to_liste(teteP);
	listeCMD *teteCMD=NULL;
	teteCMD=file_to_listeCMD(teteCMD,teteC,teteP);
	listeSMS *teteSMS=NULL;
	teteSMS=file_to_listeSMS(teteSMS);
	
		
	do
	{
		C=accueil(C);
			if(C==1)
				{
					do
					{
						printf("\n\t**Laissez le champs du mot de passe vide si vous voulez revenir a l'accueil !!\n\n");
						t=connexion(t);
						t=check_compte(t,teteC);
						if(strlen(t.password)==0)	break;
						if(t.IDClient==-1)	printf("\t*Erreur: votre mail/mot de passe est incorrect !!");
						else	compteClMenu(teteC,teteP,teteCMD,teteSMS,t);
					}	
					while(t.IDClient==-1);	
				}
			else if(C==2)
				{
					t=creation(t);
					teteC=ajout_Nv_client(teteC,t);
					add_fclient(teteC);
					printf("\n\tVotre compte a ete bien ajoute !!\n");
				}
			else if(C==3)
				{
					F=initialiserCl1(F);
					compteClMenu(teteC,teteP,teteCMD,F);
				}
			else if(C==4)
				{
					nous();
				}
			
	} while((C>=1)&&(C<=4));

//	admin_home(teteC,teteP,teteCMD,X);
	




//	  
    return;
    }

main()
    {
        menu();
        return(0);
    }
