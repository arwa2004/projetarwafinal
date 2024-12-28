#ifndef AGENT_H
#define AGENT_H
#include <gtk/gtk.h>
#include <stdio.h>
#define FILE_RESERVATION "reservation.txt"
#define file_agent "agent.txt"



typedef struct {
    int id;
    char nom[30];
    char prenom[50];
    char cin[30];
    int jour;
    char mois[20];
    int annee;
    char permis[30];
    char sexe[30];
}agent;


enum {
    ENOMr,
    EPRENOMr,
    ECINr,
    ENOM_PARKINGr,
    ETELEPHONEr,
    EIDr,
    EJOURr,
    EMOISr,
    EANNEEr,
    COLUMNSr
};
typedef struct {
    char nom[50];
    char prenom[50];
    char cin[20];
    char num_telephone[20];
} client_info_t;
typedef struct {
    int jour;
    int mois;
    int annee;
} date_reservation_t;
typedef struct {
    client_info_t client_info;
    char nom_parking[100];
    int id;
    date_reservation_t date_reservation;
} reservation;
// Déclaration des fonctions tache supp
int ajouter_reservation(char *file, reservation r);
void afficher_reservation(GtkWidget *liste);
// Déclaration des fonctions agent 
int ajouter_agent(char *file, agent a);
void rechercher_agent(const char* file, int id);
int modifier_agent(char *file, int id,agent a1);
int supprimer_agent(const char* file, int id);
void afficher_agent(GtkWidget *liste);
int rechercher_agentmod(const char* file, int id, agent *a);






#endif

