#include "../includes/employes.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../includes/counters.h"


Employe* employes = NULL;
int nb_employes = 0;
int cap_employes = 0;

#define CAPACITE_INITIALE 10

void initialiser_employes() {
    employes = malloc(CAPACITE_INITIALE * sizeof(Employe));
    cap_employes = CAPACITE_INITIALE;
    nb_employes = 0;
}

void ajouter_employe(const char* cin, const char* nom, const char* prenom, const char* email, const char* telephone,Entreprise* entreprise, Role* role) {
    if (nb_employes >= cap_employes) {
        cap_employes++;
        Employe* new_tab = realloc(employes, cap_employes * sizeof(Employe));
        employes = new_tab;
    }

    employes[nb_employes].id = employe_id_counter++;
    employes[nb_employes].cin = strdup(cin);
    employes[nb_employes].nom = strdup(nom);
    employes[nb_employes].prenom = strdup(prenom);
    employes[nb_employes].email = strdup(email);
    employes[nb_employes].telephone = strdup(telephone);
    employes[nb_employes].entreprise = entreprise;  
    employes[nb_employes].role = role;             


    nb_employes++;
}

Employe* trouver_employe_par_id(int id) {
    for (int i = 0; i < nb_employes; i++) {
        if (employes[i].id == id) {
            return &employes[i];
        }
    }
    return NULL;
}

void supprimer_employe_de_table(int id) {
    for (int i = 0; i < nb_employes; i++) {
        if (employes[i].id == id) {
            free(employes[i].cin);
            free(employes[i].nom);
            free(employes[i].prenom);
            free(employes[i].email);
            free(employes[i].telephone);
            
            for (int j = i; j < nb_employes - 1; j++) {
                employes[j] = employes[j + 1];
            }
            nb_employes--;
            break;
        }
    }
}

void liberer_employes() {
    for (int i = 0; i < nb_employes; i++) {
        free(employes[i].cin);
        free(employes[i].nom);
        free(employes[i].prenom);
        free(employes[i].email);
        free(employes[i].telephone);
        // Note: entreprise and role pointers are not freed here
    }
    free(employes);
    employes = NULL;
    nb_employes = cap_employes = 0;
}




Employe* creer_employe(int id, const char* cin, const char* nom, const char* prenom,const char* email, const char* telephone,Entreprise* entreprise, Role* role) {Employe* emp = malloc(sizeof(Employe));
    if (emp) {
        emp->id = id;
        emp->cin = strdup(cin);
        emp->nom = strdup(nom);
        emp->prenom = strdup(prenom);
        emp->email = strdup(email);
        emp->telephone = strdup(telephone);
        emp->entreprise = entreprise;
        emp->role = role;
    }
    return emp;
}

void modifier_employe(Employe* emp, const char* nouveau_cin, const char* nouveau_nom,const char* nouveau_prenom, const char* nouveau_email,const char* nouveau_telephone, Entreprise* nouvelle_entreprise,Role* nouveau_role) {
    if (!emp) return;

    if (nouveau_cin) {
    free(emp->cin);
    emp->cin = strdup(nouveau_cin);
    }

    if (nouveau_nom) {
    free(emp->nom);
    emp->nom = strdup(nouveau_nom);
    }

    if (nouveau_prenom) {
    free(emp->prenom);
    emp->prenom = strdup(nouveau_prenom);
    }

    if (nouveau_email) {
    free(emp->email);
    emp->email = strdup(nouveau_email);
    }

    if (nouveau_telephone) {
    free(emp->telephone);
    emp->telephone = strdup(nouveau_telephone);
    }

    if (nouvelle_entreprise) emp->entreprise = nouvelle_entreprise;
    if (nouveau_role) emp->role = nouveau_role;
}

void afficher_employe(const Employe* emp) {
    if (emp) {
        printf("Employe [ID: %d]\nNom: %s %s\nCIN: %s\nEmail: %s\nTelephone: %s\n",
               emp->id, emp->prenom, emp->nom, emp->cin, emp->email, emp->telephone);
        if (emp->entreprise) printf("Entreprise: %s\n", emp->entreprise->nom);
        if (emp->role) printf("Role: %s\n", emp->role->nom);
    }
}

void supprimer_employe(Employe* emp) {
    if (emp) {
        free(emp->cin);
        free(emp->nom);
        free(emp->prenom);
        free(emp->email);
        free(emp->telephone);
        free(emp);
    }
}
void enregistrer_employes_dans_fichier(const char* nom_fichier) {
    FILE* fichier = fopen(nom_fichier, "w");
    if (!fichier) {
        perror("Erreur d'ouverture du fichier pour �criture");
        return;
    }

    for (int i = 0; i < nb_employes; i++) {
        fprintf(fichier, "%d;%s;%s;%s;%s;%s;%d;%d\n",
                employes[i].id,
                employes[i].cin,
                employes[i].nom,
                employes[i].prenom,
                employes[i].email,
                employes[i].telephone,
                employes[i].entreprise ? employes[i].entreprise->id : -1,
                employes[i].role ? employes[i].role->id : -1);
    }

    fclose(fichier);
}


void charger_employes_depuis_fichier(const char* nom_fichier) {
    FILE* fichier = fopen(nom_fichier, "r");
    if (!fichier) {
        perror("Erreur d'ouverture du fichier pour lecture");
        return;
    }

    initialiser_employes(); // reset

    int id, id_ent, id_role;
    char cin[100], nom[100], prenom[100], email[100], telephone[100];

    while (fscanf(fichier, "%d;%99[^;];%99[^;];%99[^;];%99[^;];%99[^;];%d;%d\n",
                  &id, cin, nom, prenom, email, telephone, &id_ent, &id_role) == 8) {

        Entreprise* e = trouver_entreprise_par_id(id_ent);
        Role* r = trouver_role_par_id(id_role);

        ajouter_employe(cin, nom, prenom, email, telephone, e, r);
        employes[nb_employes - 1].id = id;

        if (id >= employe_id_counter) {
            employe_id_counter = id + 1;
        }
    }

    fclose(fichier);
}



