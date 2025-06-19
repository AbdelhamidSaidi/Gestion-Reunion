#ifndef ENTREPRISES_H
#define ENTREPRISES_H

typedef struct {
    int id;
    char *nom;
} Entreprise;


extern Entreprise* entreprises; 
extern int nb_entreprises;      
extern int cap_entreprises;     

void initialiser_entreprises();
void ajouter_entreprise(const char* nom);
Entreprise* trouver_entreprise_par_id(int id);
void supprimer_entreprise_de_table(int id);
void liberer_entreprises();


Entreprise* creer_entreprise(int id, const char* nom);
void afficher_entreprise(const Entreprise* ent);
void modifier_entreprise(Entreprise* ent, const char* nouveau_nom);
void supprimer_entreprise(Entreprise* ent);
void enregistrer_entreprises_dans_fichier(const char* nom_fichier);
void charger_entreprises_depuis_fichier(const char* nom_fichier);
#endif
