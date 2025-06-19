#ifndef ROLES_H
#define ROLES_H

typedef struct {
    int id;
    char *nom;
} Role;

extern Role* roles;
extern int nb_roles;
extern int cap_roles;

void initialiser_roles();
void ajouter_role(const char* nom);
Role* trouver_role_par_id(int id);
void supprimer_role_de_table(int id);
void liberer_roles();


Role* creer_role(int id, const char* nom);
void afficher_role(const Role* role);
void modifier_role(Role* role, const char* nouveau_nom);
void supprimer_role(Role* role);
void enregistrer_roles_dans_fichier(const char* nom_fichier);
void charger_roles_depuis_fichier(const char* nom_fichier);

#endif
