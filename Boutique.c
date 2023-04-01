#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<malloc.h>
#include<windows.h>
#include"Produit.h"

void esp_to_underscore(char T[])
	{
		int i=0;
		while(T[i]!='\0')
			{
				if(T[i]==' ')	T[i]='_';
				i++;
			}
	}
    
void add_fproduit(listeP *teteP)
	{
		FILE *fp;
		fp = fopen("Produit.txt","w+");
		if(fp==NULL)
			{
				printf("Le fichier ne peut pas etre ouvert \n");
				return;
			}
		if(teteP==NULL)	return;
		listeP *C;
		C=teteP;
		while(C!=NULL)
			{
				fprintf(fp,"%s\n%f\n",C->X.nomproduit,C->X.prix);
				C=C->s;
			}
        fclose(fp);
	}

produit creation_produit(produit X)
    {
    	getchar();
        printf("\tDescription du Produit: ");
        gets(X.nomproduit);
        esp_to_underscore(X.nomproduit);
        printf("\tPrix: ");
        scanf("%f",&X.prix);
        printf("\tNombre de pieces disponibles dans le stock: \n");
        	printf("\t\tSmall: ");
        	scanf("%d",&X.taille.S);
        	printf("\t\tMedium: ");
        	scanf("%d",&X.taille.M);
			printf("\t\tLarge: ");
			scanf("%d",&X.taille.L);
		printf("\tNombre de pieces selon la categorie des clients: \n");
        	printf("\t\tHommes: ");
        	scanf("%d",&X.M_F.M);
        	printf("\t\tFemmes: ");
        	scanf("%d",&X.M_F.F);
		return X;	
    }
    
listeP *ajout_produit(listeP *teteP, produit A)
	{
		listeP *N;
		listeP *C=teteP;
		N=(listeP*)malloc(sizeof(listeP));
		N->s=NULL;
		N->X=A;
		N->X.IDProduit=0;
		if(teteP==NULL)	
			{
				teteP=N;
				teteP->X.IDProduit=1;
			}
		else
			{
				while(C->s!=NULL)
					{
						C=C->s;
					}
				C->s=N;
				N->X.IDProduit=C->X.IDProduit+1;
			}
		return teteP;
	}
    
listeP *supp_produit(int IDP, listeP *teteP)
	{
		if(teteP==NULL)		
			{
				printf("Vous n'avez aucun produit a supprimer !!\n");
				return teteP;
			}
		else
			{
				listeP *C;
				C=teteP;
				while(C->s->X.IDProduit!=IDP)	C=C->s;
				listeP *P;
				P=C->s;
				C->s=P->s;
				free(P);
			}
		return teteP;
	}
    
int max_long_titre(listeP *teteP)
	{
		int M=strlen(teteP->X.nomproduit);
		listeP *C;
		C=teteP;
		while(C!=NULL)
			{
				if(M<strlen(C->X.nomproduit))	M=strlen(C->X.nomproduit);
				C=C->s;
			}
		return M;
	}
	
int max_ID(listeP *teteP)
	{
		return teteP->X.IDProduit;
	}	
	
void afficherP(listeP *teteP)
	{
		int M=max_long_titre(teteP), N=max_ID(teteP), K;
		M=M+4;
		int i;
		printf("\t");
		printf("ID:");		for(i=1;i<=5;i++)	printf(" ");	printf("| ");
		printf("Titre:");	for(i=7;i<=M;i++)	printf(" ");	printf("| ");
		printf("Prix:\n");
		printf("\t");		for(i=1;i<=21+M;i++)	printf("-");	printf("\n");
		listeP *C=teteP;
		while(C!=NULL)
			{
				printf("\t");
				if(C->X.IDProduit<10)	K=1;
				else if(C->X.IDProduit<100)	K=2;
				else if(C->X.IDProduit<1000)	K=3;
				else if(C->X.IDProduit<10000)	K=4;
				printf("%d",C->X.IDProduit); 	for(i=1;i<=8-K;i++)	printf(" ");	printf("| ");
				printf("%s",C->X.nomproduit);	for(i=1;i<=M-strlen(C->X.nomproduit);i++)	printf(" ");	printf("| ");
				printf("%.2f\n",C->X.prix);
				C=C->s;
			}
		return;
	}
	
listeP *modifyP(listeP *teteP, int IDP)
	{
		if(teteP==NULL)
			{
				printf("Vous n'avez aucun produit a modifier !!");
				return teteP;
			}
		listeP *C=teteP;
		while(C->s->X.IDProduit!=IDP)	C=C->s;
        printf("Mise a jour des donnees du produit Nr %d !! \n",IDP);
        C->X=creation_produit(C->X);
		
	}    

int listeMenuP(listeP *teteP)
	{
		int choix;
		printf("Les Produits de Votre Boutique ! \n\n");
		afficherP(teteP);
		printf("\n\n");
        printf("\t");	printf("1- Ajouter un produit\n");
        printf("\t");	printf("2- Supprimer un produit\n");
        printf("\t");	printf("3- Modifier un produit\n");
        printf("\t");	printf("4- Enregistrer les modifications\n");
		printf("\n\tChoisissez le numero du choix que vous voulez (N'importe quelle valeur pour sortir du programme): ");
        scanf("%d",&choix);
        system("cls");
        if((choix<1)||(choix>4))    return 0;
        return choix;
	}
	
listeP *file_to_liste(listeP *teteP)
	{
		produit X;
		FILE *fp;
		fp = fopen("Produit.txt","r+");
		if(fp==NULL)
			{
				printf("Le fichier ne peut pas etre ouvert \n");
				return;
			}
		while(1)
			{
				fscanf(fp,"%s\n%f\n",&X.nomproduit,&X.prix);
				teteP=ajout_produit(teteP,X);
				if(feof(fp))	break;
			}
		fclose(fp);
		return teteP;
	}
	
int max_IDP(listeP *teteP)
	{
		listeP *C;
		C=teteP;
		while(C->s!=NULL)	C=C->s;
		return C->X.IDProduit;
	}

void MenuP()
	{
		produit X;
		listeP *teteP=NULL;
		int C,IDP;
		teteP=file_to_liste(teteP);
		do
			{
//			system("cls");
			C=listeMenuP(teteP);
			if(C==1)	
				{
					X=creation_produit(X);
					teteP=ajout_produit(teteP,X);
					printf("Le produit est ajoute !\n");
				}
			else if(C==2)
				{
					do
						{
							printf("Saisie l'ID du produit que vous voulez supprimer : ");	scanf("%d",&IDP);
						}	while((IDP<1)||(IDP>max_IDP(teteP)));
					teteP=supp_produit(IDP,teteP);
					printf("Le produit est supprime !\n");
				}
			else if(C==3)
				{
					do
						{
							printf("Saisie l'ID du produit que vous voulez modifier : ");	scanf("%d",&IDP);
						}	while((IDP<1)||(IDP>teteP->X.IDProduit));				
					modifyP(teteP,IDP);
					printf("Le produit est modifie !\n");
				}
			else if(C==4)
				{
					add_fproduit(teteP);
					printf("Tous les produits sont enregistres !\n");
				}
			}	while((C<5)&&(C>0));
	}


void underscore_to_esp(char T[])
	{
		int i=0;
		while(T[i]!='\0')
			{
				if(T[i]=='_')	T[i]=' ';
				i++;
			}
	}
	
client connexion(client X)
    {
        printf("\tEmail: ");
        scanf("%s",X.mail);
        printf("\tMot de passe: ");
        getchar();
        gets(X.password);
        X.IDClient=-1;
        system("cls");
        return X;
    }

int check_email1(char T[])
	{
		int i=0,K=0;
		while(T[i]!='\0')
			{
				if(T[i]=='@')	K++;
				i++;
			}
		if(K==1)	return 1;
		return 0;	
	}
	
int check_email2(char T[])
	{
		int i=0;
		while(T[i]!='\0')
			{
				if(T[i]==' ')	return 0;
				i++;
			}
		return 1;	
	}  
   
void add_fclient(listeC *teteC)
	{
		FILE *fp;
		fp = fopen("Client.txt","w+");
		if(fp==NULL)
			{
				printf("Le fichier ne peut pas etre ouvert \n");
				return;
			}
		if(teteC==NULL)	return;
		listeC *C;
		C=teteC;
		while(C!=NULL)
			{
				esp_to_underscore(C->X.nom);		
				esp_to_underscore(C->X.prenom);
				fprintf(fp,"%d\n%s\n%s\n%d %d %d\n%s\n%s\n",C->X.IDClient,C->X.nom,C->X.prenom,C->X.naissance.j,C->X.naissance.m,C->X.naissance.a,C->X.mail,C->X.password);
				C=C->s;
			}
        fclose(fp);
	}

client creation(client X)
    {
    	int e1,e2;
    	getchar();
    	printf("\n\t\tNom: ");
    	gets(X.nom);
    	esp_to_underscore(X.nom);
    	printf("\t\tPrenom: ");
    	gets(X.prenom);
    	esp_to_underscore(X.prenom);
    	do
			{
				printf("\t\tDate de naissance (JJ-MM-AAAA): ");
		    	scanf("%d%d%d",&X.naissance.j,&X.naissance.m,&X.naissance.a);   
    		} while(check_date(X.naissance)==0);
		getchar(); 	
        do
        	{
        		printf("\t\tEmail: ");
        		gets(X.mail);
        		e1=check_email1(X.mail);
        		e2=check_email2(X.mail);
			}	while( (e1!=1) || (e2!=1) );
        printf("\t\tMot de passe: ");
        gets(X.password);
        return X;
    }
    
listeC *ajout_Nv_client(listeC *teteC, client A)
	{
		listeC *N;
		listeC *C=teteC;
		N=(listeC*)malloc(sizeof(listeC));
		N->s=NULL;
		N->X=A;
		N->X.IDClient=1;
		if(teteC==NULL)  teteC=N;
		else
			{
				while(C->s!=NULL)	C=C->s;
				C->s=N;
				N->X.IDClient=C->X.IDClient+1;
			}
		return teteC;
	}
	
listeC *ajout_client(listeC *teteC, client A)
	{
		listeC *N;
		listeC *C=teteC;
		N=(listeC*)malloc(sizeof(listeC));
		N->s=NULL;
		N->X=A;
		if(teteC==NULL)  teteC=N;
		else
			{
				while(C->s!=NULL)	C=C->s;
				C->s=N;
			}
		return teteC;
	}
    
listeC *supp_client(int IDC, listeC *teteC)
	{
		if(teteC==NULL)		
			{
				printf("\n\t\tVous n'avez aucun client a supprimer !!\n");
				return teteC;
			}
		else
			{
				listeC *C;
				C=teteC;
				while(C->s->X.IDClient!=IDC)	C=C->s;
				listeC *P;
				P=C->s;
				C->s=P->s;
				free(P);
			}
		return teteC;
	}
    
int max_long_email(listeC *teteC)
	{
		int M=strlen(teteC->X.mail);
		listeC *C;
		C=teteC;
		while(C!=NULL)
			{
				if(M<strlen(C->X.mail))	M=strlen(C->X.mail);
				C=C->s;
			}
		return M;
	}
	
int max_long_nom(listeC *teteC)
	{
		int M=strlen(teteC->X.nom);
		listeC *C;
		C=teteC;
		while(C!=NULL)
			{
				if(M<strlen(C->X.nom))	M=strlen(C->X.nom);
				C=C->s;
			}
		return M;
	}
	
int max_long_prenom(listeC *teteC)
	{
		int M=strlen(teteC->X.prenom);
		listeC *C;
		C=teteC;
		while(C!=NULL)
			{
				if(M<strlen(C->X.prenom))	M=strlen(C->X.prenom);
				C=C->s;
			}
		return M;
	}
	
int max_IDC(listeC *teteC)
	{
		listeC *C;
		C=teteC;
		while(C->s!=NULL)	C=C->s;
		return C->X.IDClient;
	}	
	
void afficherC(listeC *teteC)
	{
		int M1=max_long_nom(teteC), M2=max_long_prenom(teteC), M3=max_long_email(teteC),  K;
		M1+=4;
		M2+=4;
		M3+=4;
		int i;
		printf("\t");
		printf("ID:");		for(i=1;i<=5;i++)	printf(" ");	printf("| ");
		printf("Nom:");		for(i=5;i<=M1;i++)	printf(" ");	printf("| ");
		printf("Prenom:");	for(i=8;i<=M2;i++)	printf(" ");	printf("| ");
		printf("Email:");	for(i=7;i<=M3;i++)	printf(" ");	printf("| ");
		printf("Date de naissance:");
		printf("\n\t");		for(i=8;i<=M1+M2+M3+53;i++)	printf("-");	printf("\n");
		listeC *C=teteC;
		while(C!=NULL)
			{
				printf("\t");
					if(C->X.IDClient<10)	K=1;
					else if(C->X.IDClient<100)	K=2;
					else if(C->X.IDClient<1000)	K=3;
					else if(C->X.IDClient<10000)	K=4;
				printf("%d",C->X.IDClient); 	for(i=1;i<=8-K;i++)	printf(" ");	printf("| ");
				
				printf("%s",C->X.nom);	for(i=1;i<=M1-strlen(C->X.nom);i++)	printf(" ");	printf("| ");
				printf("%s",C->X.prenom);	for(i=1;i<=M2-strlen(C->X.prenom);i++)	printf(" ");	printf("| ");
				printf("%s",C->X.mail);	for(i=1;i<=M3-strlen(C->X.mail);i++)	printf(" ");	printf("| ");
				printf (" ");
				if(C->X.naissance.j<10)	printf("0");	printf("%d -",C->X.naissance.j);
				if(C->X.naissance.m<10)	printf("0");	printf("%d -",C->X.naissance.m);
				printf(" %d\n",C->X.naissance.a);
				C=C->s;
			}
		return;
	}
	
listeC *reset_password(listeC *teteC, int IDC)
	{
		if(teteC==NULL)
			{
				printf("\n\t\tVous n'avez aucun compte client a modifier !!");
				return teteC;
			}
		client X;
		listeC *C=teteC;
		while(C->X.IDClient!=IDC)	C=C->s;
        printf("\n\t\tMise a jour des donnees du client Nr %d !! \n\n",IDC);
        printf("\n\t\t\tSaisie un nouveau de mot de passe pour ce compte client : ");
        scanf("%s",C->X.password);
		return teteC;	
	}    

int listeMenuC(listeC *teteP)
	{
		int choix;
		printf("\n\tLes Clients de Votre Boutique ! \n\n\n");
		afficherC(teteP);
		printf("\n\n");
        printf("\t");	printf("1- Ajouter un compte\n");
        printf("\t");	printf("2- Supprimer un compte\n");
        printf("\t");	printf("3- Restaurer le mot de passe d'un compte client\n");
        printf("\t");	printf("4- Enregistrer les modifications\n");
		printf("\n\tChoisissez le numero du choix que vous voulez (N'importe quelle valeur pour sortir du programme): ");
        scanf("%d",&choix);
//        system("cls");
        if((choix<1)||(choix>4))    return 0;
        return choix;
	}
	
listeC *file_to_listeC(listeC *teteC)
	{
		client X;
		FILE *fp;
		fp = fopen("Client.txt","r+");
		if(fp==NULL)
			{
				printf("\n\tLe fichier ne peut pas etre ouvert \n");
				return;
			}
		while(1)
			{
				fscanf(fp,"%d\n%s\%s\n%d %d %d\n%s\n%s\n",&X.IDClient,&X.nom,&X.prenom,&X.naissance.j,&X.naissance.m,&X.naissance.a,&X.mail,&X.password);
				underscore_to_esp(X.nom);
				underscore_to_esp(X.prenom);
				teteC=ajout_client(teteC,X);
				if(feof(fp))	break;
			}
		fclose(fp);
		return teteC;
	}
	
int check_date(date X)
	{
		if( X.m<1 || X.m>12 || X.j<1 || X.j>31 || X.a<1900 || X.a>2013 )	return 0;
		return 1;
	}

void MenuC()
	{
		client X;
		listeC *teteC=NULL;
		int C,IDC;
		teteC=file_to_listeC(teteC);
		do
			{
			system("cls");
			C=listeMenuC(teteC);
			if(C==1)	
				{
					X=creation(X);
					teteC=ajout_Nv_client(teteC,X);
					printf("\n\tLe client est ajoute !\n");
				}
			else if(C==2)
				{
					do
						{
							printf("\n\tSaisie l'ID du client que vous voulez supprimer : ");	scanf("%d",&IDC);
						}	while((IDC<1)||(IDC>max_IDC(teteC)));
					teteC=supp_client(IDC,teteC);
					printf("\n\tLe client est supprime !\n");
				}
			else if(C==3)
				{
					do
						{
							printf("\n\tSaisie l'ID du compte client que vous voulez restaurer : ");	scanf("%d",&IDC);
						}	while((IDC<1)||(IDC>max_IDC(teteC)));				
					reset_password(teteC,IDC);
					printf("\n\tLe mot de passe du client est reinisialise !\n");
				}
			else if(C==4)
				{
					add_fclient(teteC);
					printf("\n\tTous les modifications sont enregistrees !\n");
				}
			}	while((C<5)&&(C>0));
	}

client check_compte(client X, listeC *teteC)
	{
		listeC *C=teteC;
		while(C!=NULL)
			{
				if(C->X.mail==X.mail && C->X.password==X.password)
					{	
						X=C->X;
						break;
					}
				C=C->s;
			}
		
		return X;
	}
	
void bienvenueTXT(client X)
	{
		printf("\n\tBonjour Mr %s !! On vous souhaite la bienvenue !!\n",X.prenom);
		return;
	}

void CompteClient(client X)
	{
		bienvenueTXT(X);
		
	}
	
	
	
	///////////////////////
	
	
	
	
	
void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
	{
        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
	}

int accueil(int choix)
    {
    	Color(15,0);
        printf("\n\n\t\tBienvenue dans votre Boutique ZARA ! \n\n");
        printf("\t1- Connexion\n");
        printf("\t2- Creer un compte\n");
        printf("\t3- Naviguer comme Anonyme\n");
        printf("\t4- Contactez-nous\n");
        Color(2,0);
        printf("\n\t\tSaisie le numero du choix que vous voulez (N'importe quelle valeur pour sortir du programme): ");
        Color(15,0);
        scanf("%d",&choix);
        system("cls");
        if((choix<1)||(choix>4))    return 0;
        return choix;
    }
    
void nous()
	{
		printf("\n\n\tComme Bershka, Stradivarius ou encore Massimo Dutti, Zara fait partie du groupe espagnol Inditex.\n");
		printf("\tZara est un magasin fast fashion créé en 1976 par Amancio Ortega et Rosalia Mera.\n");
		printf("\tLe magasin est présent partout dans le monde et emploie plus de 150 000 personnes.\n");
		Color(2,0);
		printf("\n\t\tCliquez sur n'importe bouton pour retourner vers le menu principal ! ");
		Color(15,0);
		getchar();
		getchar();
		system("cls");
	}

    
//int interface_Cl (client X)

    //////////////////////
    
    

listeCMD *ajout_Nv_CMD(listeCMD *teteCMD, cmd A)
	{
		listeCMD *N;
		N=(listeCMD*)malloc(sizeof(listeCMD));
		N->X=A;
		N->s=NULL;
		if(teteCMD==NULL)
			{
				teteCMD=N;
				teteCMD->X.IDCommande=1;
				return teteCMD;
			}
		listeCMD *C=teteCMD;
		while(C->s!=NULL)	C=C->s;
		C->s=N;
		N->X.IDCommande=C->X.IDCommande+1;
		return teteCMD;	
	}
	
listeCMD *ajout_CMD(listeCMD *teteCMD, cmd A)
	{
		listeCMD *N;
		N=(listeCMD*)malloc(sizeof(listeCMD));
		N->X=A;
		N->s=NULL;
		if(teteCMD==NULL)
			{
				teteCMD=N;
				return teteCMD;
			}
		listeCMD *C=teteCMD;
		while(C->s!=NULL)	C=C->s;
		C->s=N;
		return teteCMD;	
	}

cmd complete(listeC *teteC, listeP *teteP, int A, int B)
	{
		listeC *C1=teteC;
		while(C1->X.IDClient!=A)	C1=C1->s;
		listeP *C2=teteP;
		while(C2->X.IDProduit!=B)	C2=C2->s;
		cmd N;
		N.X=C1->X;
		N.Y=C2->X;	
		return N;	
	}

listeCMD *file_to_listeCMD(listeCMD *teteCMD, listeC *teteC, listeP *teteP)
	{
		cmd A;
		int K;
		FILE *fp;
		fp = fopen("Commandes.txt","r+");
		if(fp==NULL)
			{
				printf("Le fichier ne peut pas etre ouvert \n");
				return;
			}
		while(1)
			{
				fscanf(fp,"%d - %d - %d\n",&K,&A.X.IDClient,&A.Y.IDProduit);
				A=complete(teteC,teteP,A.X.IDClient,A.Y.IDProduit);
				A.IDCommande=K;
				teteCMD=ajout_CMD(teteCMD,A);
				if(feof(fp))	break;
			}
		fclose(fp);
		return teteCMD;
	}

void add_fcommande(listeCMD *teteCMD)
	{
		FILE *fp;
		fp = fopen("Commandes.txt","w+");
		if(fp==NULL)
			{
				printf("Le fichier ne peut pas etre ouvert \n");
				return;
			}
		if(teteCMD==NULL)	return;
		listeCMD *C;
		C=teteCMD;
		while(C!=NULL)
			{
				fprintf(fp,"%d - %d - %d\n",C->X.IDCommande,C->X.X.IDClient,C->X.Y.IDProduit);
				C=C->s;
			}
        fclose(fp);
	}
	
int max_long_titreCMD(listeCMD *teteCMD)
	{
		int M=strlen(teteCMD->X.Y.nomproduit);
		listeCMD *C;
		C=teteCMD;
		while(C!=NULL)
			{
				if(M<strlen(C->X.Y.nomproduit))	M=strlen(C->X.Y.nomproduit);
				C=C->s;
			}
		return M;
	}

int max_long_prenomCMD(listeCMD *teteCMD)
	{
		int M=strlen(teteCMD->X.X.prenom);
		listeCMD *C;
		C=teteCMD;
		while(C!=NULL)
			{
				if(M<strlen(C->X.X.prenom))		M=strlen(C->X.X.prenom);
				C=C->s;
			}
		return M;
	}
	
int max_IDCMD1(listeCMD *teteCMD)
	{
		listeCMD *C;
		C=teteCMD;
		while(C->s!=NULL)	C=C->s;
		return C->X.IDCommande;
	}	
	
int max_IDCMD2(listeCMD *teteCMD)
	{
		listeCMD *C;
		C=teteCMD;
		while(C->s!=NULL)	C=C->s;
		return C->X.X.IDClient;
	}
	
int max_IDCMD3(listeCMD *teteCMD)
	{
		listeCMD *C;
		C=teteCMD;
		while(C->s!=NULL)	C=C->s;
		return C->X.Y.IDProduit;
	}

int max_long_emailCMD(listeCMD *teteCMD)
	{
		int M=strlen(teteCMD->X.X.mail);
		listeCMD *C;
		C=teteCMD;
		while(C!=NULL)
			{
				if(M<strlen(C->X.X.mail))	M=strlen(C->X.X.mail);
				C=C->s;
			}
		return M;
	}
	
int max_long_nomCMD(listeCMD *teteCMD)
	{
		int M=strlen(teteCMD->X.X.nom);
		listeCMD *C;
		C=teteCMD;
		while(C!=NULL)
			{
				if(M<strlen(C->X.X.nom))	M=strlen(C->X.X.nom);
				C=C->s;
			}
		return M;
	}
	
void afficherCMD(listeCMD *teteCMD, listeC *teteC, listeP *teteP)
	{		
		int i,K,N,M1,M2,M3,M4;

		if(teteCMD==NULL)
			{
				printf("\t\tAucune commande n'est effectuee pour l'afficher !!\n");
				return;
			}

		M1=max_long_nomCMD(teteCMD)+4; 
		M2=max_long_prenomCMD(teteCMD)+4; 
		M3=max_long_emailCMD(teteCMD)+4; 
		M4=max_long_titreCMD(teteCMD)+4;

		printf("\t");
		printf("ID Commande");	printf(" ");	printf("| ");
		printf("ID Client");	printf(" ");	printf("| ");
		printf("Nom:");			for(i=5;i<=M1;i++)	printf(" ");	printf("| ");
		printf("Prenom:");		for(i=8;i<=M2;i++)	printf(" ");	printf("| ");
		printf("Email:");		for(i=7;i<=M3;i++)	printf(" ");	printf("| ");
		printf("ID Produit");	printf(" ");	printf("| ");
		printf("Titre:");		for(i=7;i<=M4;i++)	printf(" ");	printf("| ");
		printf("Prix:");		
		printf("\n\t");		for(i=8;i<=M1+M2+M3+M4+60;i++)	printf("-");	printf("\n");
		
		listeCMD *C=teteCMD;

		while(C!=NULL)
			{
				printf("\t");
				
					if(C->X.IDCommande<10)	K=1;
					else if(C->X.IDCommande<100)	K=2;
					else if(C->X.IDCommande<1000)	K=3;
					else if(C->X.IDCommande<10000)	K=4;
				printf("%d",C->X.IDCommande);	for(i=1;i<=12-K;i++)								printf(" ");	printf("| ");
				
					if(C->X.X.IDClient<10)	K=1;
					else if(C->X.X.IDClient<100)	K=2;
					else if(C->X.X.IDClient<1000)	K=3;
					else if(C->X.X.IDClient<10000)	K=4;
				printf("%d",C->X.X.IDClient); 	for(i=1;i<=10-K;i++)								printf(" ");	printf("| ");
				printf("%s",C->X.X.nom);		for(i=1;i<=M1-strlen(C->X.X.nom);i++)				printf(" ");	printf("| ");
				printf("%s",C->X.X.prenom);		for(i=1;i<=M2-strlen(C->X.X.prenom);i++)			printf(" ");	printf("| ");
				printf("%s",C->X.X.mail);		for(i=1;i<=M3-strlen(C->X.X.mail);i++)				printf(" ");	printf("| ");
				
					if(C->X.Y.IDProduit<10)	K=1;
					else if(C->X.Y.IDProduit<100)	K=2;
					else if(C->X.Y.IDProduit<1000)	K=3;
					else if(C->X.Y.IDProduit<10000)	K=4;
				printf("%d",C->X.Y.IDProduit); 	for(i=1;i<=11-K;i++)								printf(" ");	printf("| ");
				printf("%s",C->X.Y.nomproduit);	for(i=1;i<=M4-strlen(C->X.Y.nomproduit);i++)		printf(" ");	printf("| ");
				printf("%.2f\n",C->X.Y.prix);
				
				C=C->s;
			}	
		return;
	}
	
int menuCMD()
	{
		int choix;
        printf("\t");	printf("1- Supprimer une commande\n");
        printf("\t");	printf("2- Enregistrer les modifications\n");
		printf("\n\tChoisissez le numero du choix que vous voulez (N'importe quelle valeur pour sortir du programme): ");
        scanf("%d",&choix);
        if((choix<1)||(choix>4))    return 0;
        return choix;
	}
	
listeCMD *suppCMD(listeCMD *teteCMD)
	{
		int F;
		printf("Saisir l'ID de la commande que vous voulez supprimer : ");
		scanf("%d",&F);
		listeCMD *C=teteCMD;
		if(teteCMD->X.IDCommande==F)
			{
				listeCMD *N;
				N=teteCMD->s;
				free(teteCMD);
				teteCMD=N;
				return teteCMD;
			}
		while(C->s->X.IDCommande!=F)	C=C->s;
		if(C==NULL)	return teteCMD;
		listeCMD *N=C->s->s;
		free(C->s);
		C->s=N;
		return teteCMD;
	}
	
void listeMenuCMD(listeCMD *teteCMD, listeC *teteC, listeP *teteP)
	{
		int choix;
		do
			{
				printf("\n\tLes Commandes de Vos Clients ! \n\n");
				afficherCMD(teteCMD,teteC,teteP);
				printf("\n\n");
				choix=menuCMD();
				if(choix==1)	teteCMD=suppCMD(teteCMD);
				else if(choix==2)	add_fcommande(teteCMD);
				else break;
				system("cls");
			}	while(choix==1 || choix==2);
		
	}

void admin_home(listeC *teteC, listeP *teteP, listeCMD *teteCMD, int C)
	{
		do
		{
			if(C==1)	listeMenuCMD(teteCMD,teteC,teteP);
			if(C==2)    MenuP();
		    if(C==3)	MenuC();
		}	while(C==1 || C==2 ||C==3);
	}
	
int MenuCl(int choix, client N)
	{
        printf("\n\n\t\tBienvenue Mme/Mr %s %s !! \n\n",N.prenom,N.nom);
        printf("\t1- Effectuer une commande\n");
        printf("\t2- Voir mon historique de commandes\n");
        printf("\t3- modifier les information de mon profil\n");
        printf("\t4- Envoyer un message a l'administration\n");
        Color(2,0);
        printf("\n\t\tSaisie le numero du choix que vous voulez (N'importe quelle valeur pour sortir du programme): ");
        Color(15,0);
        scanf("%d",&choix);
        system("cls");
        if((choix<1)||(choix>4))    return 0;
        return choix;
	}
	
int check_IDP(listeP *teteP, int K)
	{
		listeP *C=teteP;
		while(C!=NULL)
			{
				if(C->X.IDProduit==K)	return 1;
				C=C->s;
			}
		return 0;
	}
	
produit completePr(listeP *teteP, produit A)
	{
		listeP *C=teteP;
		while(C->s->X.IDProduit!=A.IDProduit)	C=C->s;
		A=C->X;
		return A;
	}
	
int Nv_ID_CMD(listeCMD *teteCMD)
	{
		listeCMD *C=teteCMD;
		while(C->s!=NULL)	C=C->s;
		return C->X.IDCommande+1;
	}

void afficherCMD_Cl(listeCMD *teteCMD, listeP *teteP, client N)
	{		
		int i,K,M1,M2,M3,M4;

		if(teteCMD==NULL)
			{
				printf("\t\tAucune commande n'est effectuee pour l'afficher !!\n");
				return;
			}

		M4=max_long_titreCMD(teteCMD)+4;

		printf("\t");
		printf("ID Commande");	printf(" ");	printf("| ");
		printf("ID Produit");	printf(" ");	printf("| ");
		printf("Titre:");		for(i=7;i<=M4;i++)	printf(" ");	printf("| ");
		printf("Prix:");		
		printf("\n\t");		for(i=8;i<=M4+34;i++)	printf("-");	printf("\n");
		
		listeCMD *C=teteCMD;

		while(C!=NULL)
			{
				if(C->X.X.IDClient==N.IDClient)
				printf("\t");
				
					if(C->X.IDCommande<10)	K=1;
					else if(C->X.IDCommande<100)	K=2;
					else if(C->X.IDCommande<1000)	K=3;
					else if(C->X.IDCommande<10000)	K=4;
				printf("%d",C->X.IDCommande);	for(i=1;i<=12-K;i++)								printf(" ");	printf("| ");
				
					if(C->X.X.IDClient<10)	K=1;
					else if(C->X.X.IDClient<100)	K=2;
					else if(C->X.X.IDClient<1000)	K=3;
					else if(C->X.X.IDClient<10000)	K=4;
				printf("%d",C->X.X.IDClient); 	for(i=1;i<=10-K;i++)								printf(" ");	printf("| ");
				printf("%s",C->X.X.nom);		for(i=1;i<=M1-strlen(C->X.X.nom);i++)				printf(" ");	printf("| ");
				printf("%s",C->X.X.prenom);		for(i=1;i<=M2-strlen(C->X.X.prenom);i++)			printf(" ");	printf("| ");
				printf("%s",C->X.X.mail);		for(i=1;i<=M3-strlen(C->X.X.mail);i++)				printf(" ");	printf("| ");
				
					if(C->X.Y.IDProduit<10)	K=1;
					else if(C->X.Y.IDProduit<100)	K=2;
					else if(C->X.Y.IDProduit<1000)	K=3;
					else if(C->X.Y.IDProduit<10000)	K=4;
				printf("%d",C->X.Y.IDProduit); 	for(i=1;i<=11-K;i++)								printf(" ");	printf("| ");
				printf("%s",C->X.Y.nomproduit);	for(i=1;i<=M4-strlen(C->X.Y.nomproduit);i++)		printf(" ");	printf("| ");
				printf("%.2f\n",C->X.Y.prix);
				
				C=C->s;
			}	
		return;
	}
	
void modifyProfile(client *X)
	{
		char T[40];
		printf("\n\n\tVous etes sur le point de modifier vos informations!\n");
		printf("\n\n\tSi vous voulez ne pas changer l'information d'un champ donne, veuillez cliquez sur le bouton 'Entrer' !!\n\n");
		int e1,e2;
    	getchar();
    	printf("\n\t\tNom: ");
    	gets(T);
    	if(strlen(T)!=0)	strcpy(X->nom,T);
    	esp_to_underscore(X->nom);
    	printf("\t\tPrenom: ");
    	gets(T);
    	if(strlen(T)!=0)	strcpy(X->prenom,T);
    	esp_to_underscore(X->prenom);
		getchar(); 	
        do
        	{
        		printf("\t\tEmail: ");
        		gets(T);
    			if(strlen(T)==0)	break;
        		strcpy(X->mail,T);
        		e1=check_email1(X->mail);
        		e2=check_email2(X->mail);
			}	while( (e1!=1) || (e2!=1) );
        printf("\t\tMot de passe: ");
    	gets(T);
    	if(strlen(T)!=0)	strcpy(X->password,T);
    	printf("\t\tVos modifications sont enregistres ! Cliquez sur n'importe quel bouton pour revenir a l'accueil ... ");
    	getchar();
    	system("cls");
	}
	
client initialiserCl1(client A)
	{
		getchar();
		A.IDClient=0;
		printf("Saisie un Prenom : ");
		gets(A.prenom);
		printf("Saisie un Nom : ");
		gets(A.nom);
		A.naissance.a=2000;
		A.naissance.j=1;
		A.naissance.m=1;
		return A;
	}
	
listeSMS *ajout_Nv_SMS(listeSMS *teteSMS, message M)
	{
		listeSMS *N;
		N=(listeSMS*)malloc(sizeof(listeSMS));
		N->s=NULL;
		N->X=M;
		if(teteSMS==NULL)
			{
				N->IDSMS=1;
				teteSMS=N;
				return teteSMS;
			}
		listeSMS *C=teteSMS;
		while(C->s!=NULL)	C=C->s;
		C->s=N;
		N->IDSMS=C->IDSMS+1;
		return teteSMS;
	}
	
listeSMS *sendMessage(listeSMS *teteSMS, client N)
	{
		getchar();
		message M;
		printf("Saisie votre Message :\n");
		gets(M.TXT);
		M.IDC=N.IDClient;
		strcpy(M.EXP,N.nom);
		strcat(M.EXP," ");
		strcat(M.EXP,N.prenom);
		strcpy(M.EMAILEXP,N.mail);
		teteSMS=ajout_Nv_SMS(teteSMS,M);
		return teteSMS;
	}
	
listeSMS *ajout_fSMS(listeSMS *teteSMS, message M, int K)
	{
		listeSMS *N;
		N=(listeSMS*)malloc(sizeof(listeSMS));
		N->X=M;
		N->s=NULL;
		N->IDSMS=K;
		if(teteSMS==NULL)
			{
				teteSMS=N;
				return teteSMS;
			}
		listeSMS *C=teteSMS;
		while(C->s!=NULL)	C=C->s;
		C->s=N;
		return teteSMS;
	}
	
listeSMS *file_to_listeSMS(listeSMS *teteSMS)
	{
		message X;
		int K;
		FILE *fp;
		fp = fopen("Messages.txt","r+");
		if(fp==NULL)
			{
				printf("\n\tLe fichier ne peut pas etre ouvert \n");
				return;
			}
		while(1)
			{
				fscanf(fp,"%d\n%s\n%s\n%s\n",&K,&X.EXP,&X.EMAILEXP,&X.TXT);
				underscore_to_esp(X.EXP);
				underscore_to_esp(X.TXT);
				teteSMS=ajout_fSMS(teteSMS,X,K);
				if(feof(fp))	break;
			}
		fclose(fp);
		return teteSMS;
	}

void add_fSMS(listeSMS *teteSMS)
	{
		FILE *fp;
		fp = fopen("Messages.txt","w+");
		if(fp==NULL)
			{
				printf("Le fichier ne peut pas etre ouvert \n");
				return;
			}
		if(teteSMS==NULL)	return;
		listeSMS *C;
		C=teteSMS;
		while(C!=NULL)
			{
				esp_to_underscore(C->X.EXP);
				esp_to_underscore(C->X.TXT);
				fprintf(fp,"%d\n%s\n%s\n%s\n",C->IDSMS,C->X.EXP,C->X.EMAILEXP,C->X.TXT);
				C=C->s;
			}
        fclose(fp);
	}
	

void compteClMenu(listeC *teteC, listeP *teteP, listeCMD *teteCMD, listeSMS *teteSMS, client N)
	{
		int C,K;
		produit Pr;
		cmd CMD;
		listeC *C1;
		do
		{
			C=MenuCl(C,N);
			if(C==1)
				{
					do
					{
						afficherP(teteP);
						printf("\n\tSaisir l'ID du produit que vous voulez acheter : ");
						scanf("%d",&Pr.IDProduit);
						if(check_IDP(teteP,Pr.IDProduit)==0)	printf("\n\t-- Cet ID ne convient a aucun produit !!");
						else
							{
								Pr=completePr(teteP,Pr);
								CMD.X=N;
								CMD.Y=Pr;
								CMD.IDCommande=Nv_ID_CMD(teteCMD);
								teteCMD=ajout_Nv_CMD(teteCMD,CMD);
							}
						system("cls");
					}	while(check_IDP(teteP,K)==0);	
				}
			if(C==2)
				{
					afficherCMD_Cl(teteCMD,teteP,N);
					printf("Cliquez sur n'importe quel bouton pour revenir en arrière !!");
					getchar();
					system("cls");
				}
			if(C==3)
				{
					C1=teteC;
					while(C1->s->X.IDClient!=N.IDClient)	C1=C1->s;	
					modifyProfile(&N);
					system("cls");
				}
			if(C==4)
				{
					teteSMS=sendMessage(teteSMS,N);
					add_fSMS(teteSMS);
					printf("\n\tVotre message est envoye !!\n\tCliquez sur n'importe quel bouton pour revenir vers l'acceuil !\n");
					getchar();
					system("cls");
				}
		} while(C>0);
	}
















    
