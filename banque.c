#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "banque.h"

void global(void)
{
	int nE, nS, tmax,retour;
	float tabE[50], tabS[50], base, totaux, totalE, totalS;
	char infoE[50][14], infoS[50][14];
	charg(tabE,tabS,infoE,infoS,&base,&nE,&nS);
	total(tabE,nE,tabS,nS,base,&totaux,&totalE,&totalS);
	retour = affichMenu();
	while(retour < 9)
	{
		if (retour==1)
		{
			affichCompte(tabE,tabS,infoE,infoS,base,nE,nS,totaux, totalS, totalE);
		}
		if (retour==2)
		{
			ajoutS(tabS,infoS,&nS);
			total(tabE,nE,tabS,nS,base,&totaux,&totalE,&totalS);
		}
		if (retour==3)
		{
			ajoutE(tabE,infoE,&nE);
			total(tabE,nE,tabS,nS,base,&totaux,&totalE,&totalS);
		}
		if (retour==4)
		{
			empty(tabE,tabS,infoE,infoS,&nE,&nS,&base,totaux);
			enregistr(tabE,infoE,tabS,infoS,nE,nS,base);
		}
		if (retour==5)
		{
			enregistr(tabE,infoE,tabS,infoS,nE,nS,base);
		}
		if(retour==6)
			economie(totaux);
		retour = affichMenu();
	}
}

void charg(float tabE[], float tabS[],char infoE[][14],char infoS[][14],float* base, int* nE, int* nS)
{
	FILE* flot;
	int i=0;
	float entree, sortie;
	char info[50];

	flot=fopen("base.don","r");
	if (flot==NULL) exit(1);
	fscanf(flot,"%f",base);
	fclose(flot);

	flot=fopen("entree.don","r");
	if (flot==NULL) exit(1);
	fscanf(flot,"%*c%s %f",info,&entree);
	while(!feof(flot))
	{
		tabE[i]=entree;
		strcpy(infoE[i],info);
		fscanf(flot,"%*c%s %f",info, &entree);
		i++;
	}
	*nE=i;
	fclose(flot);
	i=0;

	flot=fopen("sortie.don","r");
	if (flot==NULL) exit(1);
	fscanf(flot,"%s %f",info,&sortie);
	while(!feof(flot))
	{
		tabS[i]=sortie;
		strcpy(infoS[i], info);
		fscanf(flot,"%s %f",info,&sortie);
		i++;
	}
	*nS=i;
	fclose(flot);
}

void total(float tabE[],int nE, float tabS[],int nS, float base,float* totaux,float* totalE,float* totalS)
{
	*totalE=0;*totalS=0;*totaux=0;
	for(int i=0; i < nE ; i++)
		*totalE=*totalE + tabE[i];
	for(int i=0; i < nS ; i++)
		*totalS=*totalS + tabS[i];
	*totaux= base + *totalE - *totalS;
}

int affichMenu(void)
{
	int retour;
	printf("\n\n\n*************************************************************\n");
	printf("Differentes Actions:\n");
	printf("\t1\tVoir Mes Mouvements Recents\n");
	printf("\t2\tAjouter des Dépenses\n");
	printf("\t3\tAjouter des Entrées\n");
	printf("\t4\tRéinitialiser Pour le Début du Mois\n");
	printf("\t5\tEnregistrer les Modifications\n");
	printf("\t6\tProposition d'économie\n");
	printf("\t9\tQUITTER\nChoix:");
	scanf("%d",&retour);
	printf("*************************************************************\n\n\n\n");
	
	return retour;
}

void affichCompte(float tabE[],float tabS[],char infoE[][14],char infoS[][14],float base,int nE,int nS,float totaux, float totalS, float totalE)
{
	printf("La Base du mois fut de:\033[1;32m %.2f \033[0m\n\n",base);
	printf("\t\tEntree\tSortie\tTotal\n");
	printf("Total:\t\t%.2f\t%.2f\t%.2f\n",totalE,totalS,totaux );
	printf("\nTableau des entrees:\n");
	if (nE==0)
	{
		printf("\tPas encore d'Entrées\n");
	}
	else
	{
		for(int i=0; i < nE; i++)
			{
				printf("\t%s\t\t\t\033[1;36m%.2f\033[0m",infoE[i],tabE[i]);
				printf("\n");
			}
	}

	printf("\nTableau des Sorties:\n");
	if (nS==0)
	{
		printf("\tPas encore de Sorties\n");
	}
	else
	{
		for(int i=0; i < nS; i++)
		{
			if(strlen(infoS[i])>8)
				printf("\t%s\t\t\033[1;31m%.2f\033[0m",infoS[i],tabS[i]);
			else
				printf("\t%s\t\t\t\033[1;31m%.2f\033[0m",infoS[i],tabS[i]);
			printf("\n");
		}
	}
	printf("\n\nArgent Actuellement Disponible:\033[1;32m %.2f \033[0m\n", totaux);
}

void ajoutS(float tabS[], char infoS[][14],int* nS)
{
	char info[14];
	float cout;
	printf("Veuillez donnez le nom de la Dépenses(-de 12char)\n");
	scanf("%s",info);
	printf("Veuillez indiquez le montant de la Dépenses\n");
	scanf("%f",&cout);
	tabS[*nS]=cout;
	strcpy(infoS[*nS],info);
	*nS=*nS+1;
}

void ajoutE(float tabE[], char infoE[][14],int* nE)
{
	char info[14];
	float cout;
	printf("Veuillez donnez le nom de l'Apport(-de 12char)\n");
	scanf("%s",info);
	printf("Veuillez indiquez le montant de l'Apport\n");
	scanf("%f",&cout);
	tabE[*nE]=cout;
	strcpy(infoE[*nE],info);
	*nE=*nE+1;
}

void enregistr(float tabE[], char infoE[][14], float tabS[], char infoS[][14], int nE, int nS, float base)
{
	FILE* flot;
	char info[14];
	float cout;

	flot=fopen("base.don","w");
	if(flot==NULL) exit(1);
	fprintf(flot, "%.2f\n", base);
	fclose(flot);

	flot=fopen("sortie.don","w");
	if (flot==NULL) exit(1);
	for (int i = 0; i < nS; ++i)
	{
		cout=tabS[i]; strcpy(info,infoS[i]);
		fprintf(flot, "%s %.2f\n",infoS[i], tabS[i]);
	}
	fclose(flot);

	flot=fopen("entree.don","w");
	if (flot==NULL) exit(1);
	for (int i = 0; i < nE; ++i)
	{	
		cout=tabE[i]; strcpy(info,infoE[i]);
		fprintf(flot, "%s %.2f\n",infoE[i], tabE[i]);
	}
	fclose(flot);
}

void empty(float tabE[], float tabS[], char infoE[][14], char infoS[][14], int* nE, int* nS, float* base, float nBase)
{
	float emptyF[50];
	char emptyC[50][14];
	for (int i = 0; i < *nE; ++i)
	{
		tabE[i]=emptyF[i];
		infoE[i][14]=emptyC[i][14];
	}
	for (int i = 0; i < *nS; ++i)
	{
		tabS[i]=emptyF[i];
		infoS[i][14]=emptyC[i][14];
	}
	*base=nBase;
	*nE=0; *nS=0;

	system("./move.sh");
}

void economie(float totaux)
{
	float val;
	if(totaux<250)
	{
		printf("Cela risque d'etre compliqué ce mois-ci!\n");
	}
	else
	{
		val=((totaux-250)/2);
		printf("Ce mois-ci, je te conseille de mettre %.2f sur ton livret A en guise d'économie\n", val);
	}
}