#ifndef MENU_H
#define MENU_H

#include "gestion_reunions.h"

// Main menu functions
void gerer_menu_principal(void);
void gerer_menu_entreprises(void);
void gerer_menu_roles(void);
void gerer_menu_salles(void);
void gerer_menu_employes(void);
void gerer_menu_reunions(void);
void gerer_menu_documents(void);
void gerer_menu_notifications(void);
void gerer_menu_invitations(void);
void gerer_menu_ordres_du_jour(void);

// Utility functions
void afficher_toutes_entreprises(void);
void afficher_tous_roles(void);
void afficher_toutes_salles(void);
void afficher_tous_employes(void);
void afficher_toutes_reunions(void);
void afficher_tous_documents(void);
void afficher_toutes_notifications(void);
void afficher_toutes_invitations(void);
void afficher_tous_ordres_du_jour(void);

#endif