#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agent.h"
#define file_agent "agent.txt"
#define FILE_RESERVATION "reservation.txt"


enum
{
    EID,
    ENOM,
    EPRENOM,
    ECIN,
    EJOUR,
    EMOIS,
    EANNEE,
    EPERMIS,
    ESEXE,
    COLUMNS,
};



//Ajouter

int id_existe(const char* file, int id) {
    FILE *f = fopen(file, "r");
    if (f == NULL) {
        return 0; 
    }
    agent a;
    while (fscanf(f,"%d %s %s %s %d %s %d %s %s \n ",&a.id,a.nom,a.prenom,a.cin,&a.jour,a.mois,&a.annee,a.permis,a.sexe)!=EOF) {
        if (a.id == id) {
            fclose(f);
            return 1; 
        }
    }
    fclose(f);
    return 0; 
}

int ajouter_agent(char *file, agent a){
	FILE * f=fopen(file,"a");
	if (f!=NULL){

	fprintf(f,"%d %s %s %s %d %s %d %s %s \n ",a.id,a.nom,a.prenom,a.cin,a.jour,a.mois,a.annee,a.permis,a.sexe);
	fclose(f);
	return 1; 
}
printf("impossible d'ouvrir le fichier"); 
return 0; 
} 

//Modifier

int modifier_agent(char *file, int id,agent a1){
    if (!id_existe(file, id)) {
        printf("Erreur : L'ID %d n'existe pas.\n", id);
        return 0; // ID non trouvé, arrêter la fonction
    }
agent a ;
int modif=0;
  FILE* f=fopen(file, "r");
  FILE* f2=fopen("marwamod.txt", "w");
  
   if (f == NULL || f2 == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier.\n");
        if (f) fclose(f);
        if (f2) fclose(f2);
        return 0;
    }	while(fscanf(f,"%d %s %s %s %d %s %d %s %s \n ",&a.id,a.nom,a.prenom,a.cin,&a.jour,a.mois,&a.annee,a.permis,a.sexe)!=EOF)
	{
		if(a.id == id)
  			{fprintf(f2,"%d %s %s %s %d %s %d %s %s \n ",a1.id,a1.nom,a1.prenom,a1.cin,a1.jour,a1.mois,a1.annee,a1.permis,a1.sexe);
			modif=1;}	
	else{
 		fprintf(f2,"%d %s %s %s %d %s %d %s %s \n ",a.id,a.nom,a.prenom,a.cin,a.jour,a.mois,a.annee,a.permis,a.sexe);
	}
  fclose(f);
  fclose(f2);
  remove(file);
  rename("marwamod.txt",file);
 }
return modif;
}



//supprimer

int supprimer_agent(const char* file, int id)
{
    	int modif = 0;
	agent a;     
	FILE * f=fopen(file,"r");
	FILE * f2=fopen("arwasupp.txt","w");
	if (f != NULL && f2 != NULL) {
		while (fscanf(f,"%d %s %s %s %d %s %d %s %s \n  ",&a.id,a.nom,a.prenom,a.cin,&a.jour,a.mois,&a.annee,a.permis,a.sexe)!=EOF){
			if(a.id == id){
         			modif = 1;
			}else{
 				 fprintf(f2,"%d %s %s %s %d %s %d %s %s \n  ",a.id,a.nom,a.prenom,a.cin,a.jour,a.mois,a.annee,a.permis,a.sexe);
			}
}}
 	fclose(f);
	fclose(f2);

	remove(file);
	rename("arwasupp.txt",file);

     return modif;
}



//rechercher 

void rechercher_agent(const char* file, int id) {
    FILE *f = fopen(file, "r");
    if (f == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier.\n");
        return;
    }
    agent a;
    int found = 0;
    // Parcourir le fichier pour trouver le service avec l'ID donné
    while (fscanf(f,"%d %s %s %s %d %s %d %s %s \n  ",&a.id,a.nom,a.prenom,a.cin,&a.jour,a.mois,&a.annee,a.permis,a.sexe)!=EOF) {
        if (a.id == id) {
            printf("agent avec ID %d trouvé.\n",a.id);
            found = 1;
            break;
        }
    }
    fclose(f);
    if (!found) {
        printf("agent avec ID %d non trouvé.\n", id);
    }
}



/*
// Function to set up the TreeView
void vider(GtkWidget *liste) {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkListStore *store;
    GtkTreeIter iter;
	int id;
    	char nom[30];
    	char prenom[50];
    	char cin[30];
    	int jour;
    	char mois[20];
    	int annee;
    	char permis[30];
    	char sexe[30];
    	store = NULL;
	FILE *f;
	store=gtk_tree_view_get_model(liste);
  	if (store == NULL) {
        // Create and set up renderers and columns for the TreeView
	renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("id", renderer, "text", 0, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("nom", renderer, "text", 1, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("prenom", renderer, "text", 2, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("cin", renderer, "text", 3, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("jour", renderer, "text", 4, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("mois", renderer, "text", 5, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

	renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("annee", renderer, "text", 6, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

	renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("permis", renderer, "text", 7, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

	renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("sexe", renderer, "text", 8, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        store = gtk_list_store_new(COLUMNS, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_STRING, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING); 

        gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));


        g_object_unref(store);}}
    

*/
int rechercher_agentmod(const char* file, int id, agent *a) {
    FILE *f = fopen(file, "r");
    if (f == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier.\n");
        return 0;
    }

    while (fscanf(f,"%d %s %s %s %d %s %d %s %s \n", &a->id, a->nom, a->prenom,a->cin,&a->jour,a->mois,&a->annee,a->permis,a->sexe) != EOF) {
        if (a->id == id) {
            fclose(f);
            return 1; // Agent found
        }
    }

    fclose(f);
    return 0; // Agent not found
}



void afficher_agent(GtkWidget *liste){
	GtkCellRenderer *renderer;
    	GtkTreeViewColumn *column;
    	GtkTreeIter iter;
    	GtkListStore *store;

    	int id;
    	char nom[30];
    	char prenom[50];
    	char cin[30];
    	int jour;
    	char mois[20];
    	int annee;
    	char permis[30];
    	char sexe[30];
    	store = NULL;
	FILE *f;
	store=gtk_tree_view_get_model(liste);
	agent a;
    // Ajouter les colonnes si elles n'existent pas
    	if (store == NULL)
   	 {
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("id", renderer, "text", EID, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("nom", renderer, "text", ENOM, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("prenom", renderer, "text", EPRENOM, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("cin", renderer, "text", ECIN, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Jour", renderer, "text", EJOUR, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("mois", renderer, "text", EMOIS, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("annee", renderer, "text", EANNEE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("permis", renderer, "text", EPERMIS, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("sexe", renderer, "text", ESEXE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
    }

    store = gtk_list_store_new(COLUMNS, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,G_TYPE_INT, G_TYPE_STRING, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING);

    f = fopen("agent.txt", "r");
    if (f == NULL)
        {return;}
    else{
	f = fopen("agent.txt", "a+");
    	// Lecture et ajout des données dans le modèle
    	while (fscanf(f, "%d %s %s %s %d %s %d %s %s",&id, nom, prenom, cin, &jour, mois, &annee, permis, sexe) != EOF)
    {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,EID, id,ENOM, nom,EPRENOM, prenom,ECIN, cin,EJOUR, jour,EMOIS, mois,EANNEE, annee,EPERMIS, permis,ESEXE, sexe,-1);
    }
    fclose(f);


    // Mettre à jour le modèle du TreeView
    gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
    g_object_unref(store);
}
	

}

int ajouter_reservation(char *file, reservation r) {
    FILE *f = fopen(file, "a");
    if (f == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 0;
    }
    fprintf(f, "%s %s %s %s %s %d %d %d %d\n",
            r.client_info.nom, r.client_info.prenom, r.client_info.cin, r.nom_parking,
            r.client_info.num_telephone, r.id, r.date_reservation.jour,
            r.date_reservation.mois, r.date_reservation.annee);
    fclose(f);
    return 1;
}
void afficher_reservation(GtkWidget *liste) {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;
    reservation r;
    
    store = NULL;
    FILE *f;
    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));
    
    if (store == NULL) {
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("nom", renderer, "text", ENOMr, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("prenom", renderer, "text", EPRENOMr, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("cin", renderer, "text", ECINr, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("nom_parking", renderer, "text", ENOM_PARKINGr, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("telephone", renderer, "text", ETELEPHONEr, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("id", renderer, "text", EIDr, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("jour", renderer, "text", EJOURr, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("mois", renderer, "text", EMOISr, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("annee", renderer, "text", EANNEEr, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
    }
    
    store = gtk_list_store_new(COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT);
    
    f = fopen("reservation.txt", "r");
    if (f == NULL) {
        return;
    } else {
        while (fscanf(f, "%s %s %s %s %s %d %d %d %d\n",
                      r.client_info.nom, r.client_info.prenom, r.client_info.cin,
                      r.nom_parking, r.client_info.num_telephone, &r.id,
                      &r.date_reservation.jour, &r.date_reservation.mois,
                      &r.date_reservation.annee) != EOF) {
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter, ENOMr, r.client_info.nom, EPRENOMr, r.client_info.prenom, ECINr, r.client_info.cin, ENOM_PARKINGr, r.nom_parking,
                               ETELEPHONEr, r.client_info.num_telephone, EIDr, r.id, EJOURr, r.date_reservation.jour, EMOISr, r.date_reservation.mois, EANNEEr, r.date_reservation.annee, -1);
        }
        fclose(f);
    }
    
    gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
    g_object_unref(store);
}

