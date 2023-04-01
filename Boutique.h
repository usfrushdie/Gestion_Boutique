typedef struct size	
	{	
		int S;	
		int M;	
		int L;
	}	size;   
	
typedef struct gender
	{
		int M;
		int F;
	} 	gender;
	
typedef struct date    
	{	
		int j;	
		int m;	
		int a;	
	}	date;

typedef struct produit
	{	
		int IDProduit;
		char nomproduit[50];
		float prix;
		size taille;
		gender M_F;	
	}	produit;
	
typedef struct client	
	{	
		int IDClient;
		char nom[50];
		char prenom[50];
		date naissance;	
		char mail[40];	
		char password[30];	
	} 	client;

typedef struct commandes	
	{	
		int IDCommande;
		client X;
		produit Y;
	} 	cmd;
	
typedef struct listeCMD	
	{	
		cmd X;	
		struct listeCMD *s;	
	}	listeCMD;
	
typedef struct listeP
	{	
		produit X;
		struct listeP *s;
	} 	listeP;
	
typedef struct listeC	
	{	
		client X;	
		struct listeC *s;	
	}	listeC;

typedef struct message
	{
		char TXT[500];
		char EXP[50];
		char EMAILEXP[50];
		int IDC;
	}	message;

typedef struct listeSMS
	{
		int IDSMS;
		message X;
		struct listeSMS *s;
	}	listeSMS;

void add_fproduit(listeP *teteP);

produit creation_produit(produit X);
    
listeP *ajout_produit(listeP *teteP, produit A);
    
listeP *supp_produit(int IDP, listeP *teteP);
    
int max_long_titre(listeP *teteP);
	
int max_ID(listeP *teteP);
	
void afficherP(listeP *teteP);
    
listeP *modifyP(listeP *teteP, int IDP);
    
int listeMenuP(listeP *teteP);

listeP *file_to_liste(listeP *teteP);

void MenuP();

///
listeCMD *ajout_Nv_CMD(listeCMD *teteCMD, cmd A);
	
listeCMD *ajout_CMD(listeCMD *teteCMD, cmd A);

cmd complete(listeC *teteC, listeP *teteP, int A, int B);

listeCMD *file_to_listeCMD(listeCMD *teteCMD, listeC *teteC, listeP *teteP);

void add_fcommande(listeCMD *teteCMD);
	
int max_long_titreCMD(listeCMD *teteCMD);

int max_long_prenomCMD(listeCMD *teteCMD);
	
int max_IDCMD1(listeCMD *teteCMD);
	
int max_IDCMD2(listeCMD *teteCMD);
	
int max_IDCMD3(listeCMD *teteCMD);

int max_long_emailCMD(listeCMD *teteCMD);
	
int max_long_nomCMD(listeCMD *teteCMD);
	
void afficherCMD(listeCMD *teteCMD, listeC *teteC, listeP *teteP);
	
void listeMenuCMD(listeCMD *teteCMD, listeC *teteC, listeP *teteP);

///




void underscore_to_esp(char T[]);

int max_long_email(listeC *teteC);
	
int max_long_nom(listeC *teteC);
	
int max_long_prenom(listeC *teteC);
	
int max_IDC(listeC *teteC);
	
client connexion (client X);

int check_email1(char T[]);
	
int check_email2(char T[]);
   
void add_fclient(listeC *teteC);

client creation(client X);
    
listeC *ajout_Nv_client(listeC *teteC, client A);

listeC *ajout_client(listeC *teteC, client A);
    
listeC *supp_client(int IDC, listeC *teteC);
	
void afficherC(listeC *teteC);
	
listeC *reset_password(listeC *teteC, int IDC);

int listeMenuC(listeC *teteP);
	
listeC *file_to_listeC(listeC *teteC);

int check_date(date X);

void MenuC();

client check_compte(client X, listeC *teteC);

client initialiserCl1(client A);

/////


void Color(int ,int );
int accueil(int );
void nous();



