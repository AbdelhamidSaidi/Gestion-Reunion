#include <stdio.h>
#include "../includes/menu.h"
#include "../includes/counters.h"
#include "../includes/gestion_reunions.h"
#include "../includes/entreprises.h"
#include "../includes/roles.h"
#include "../includes/salles.h"
#include "../includes/reunions.h"
#include "../includes/documents.h"
#include "../includes/notifications.h"
#include "../includes/invitations.h"
#include "../includes/reunions_documents.h"
#include "../includes/notifications_invitations.h"


int main() {
    
    init_counters();
    
    initialiser_entreprises();
    initialiser_roles();
    initialiser_salles();
    initialiser_employes();
    initialiser_reunions();
    initialiser_documents();
    initialiser_notifications();
    initialiser_invitations();
    initialiser_ordres_du_jour();
    initialiser_reunions_documents();
    initialiser_notifications_invitations();

     charger_entreprises_depuis_fichier("stockage/entreprises.txt");
     charger_roles_depuis_fichier("stockage/roles.txt");
     charger_employes_depuis_fichier("stockage/employes.txt");
     charger_salles_depuis_fichier("stockage/salles.txt");
     charger_reunions_depuis_fichier("stockage/reunions.txt");
     charger_ordres_du_jour_depuis_fichier("stockage/ordres_du_jour.txt");
     charger_documents_depuis_fichier("stockage/documents.txt");
     charger_reunions_documents_depuis_fichier("stockage/reunions_documents.txt");
     charger_notifications_depuis_fichier("stockage/notifications.txt");
     charger_notifications_invitations_depuis_fichier("stockage/notifications_invitations.txt");
	 charger_invitations_depuis_fichier("stockage/invitations.txt");

    gerer_menu_principal();


    enregistrer_entreprises_dans_fichier("stockage/entreprises.txt");
    enregistrer_roles_dans_fichier("stockage/roles.txt");
    enregistrer_employes_dans_fichier("stockage/employes.txt");
    enregistrer_salles_dans_fichier("stockage/salles.txt");
    enregistrer_reunions_dans_fichier("stockage/reunions.txt");
    enregistrer_ordres_du_jour_dans_fichier("stockage/ordres_du_jour.txt");
    enregistrer_documents_dans_fichier("stockage/documents.txt");
    enregistrer_notifications_dans_fichier("stockage/notifications.txt");
    enregistrer_invitations_dans_fichier("stockage/invitations.txt");
    enregistrer_reunions_documents_dans_fichier("stockage/reunions_documents.txt");
    enregistrer_notifications_invitations_dans_fichier("stockage/notifications_invitations.txt");


    liberer_entreprises();
    liberer_roles();
    liberer_salles();
    liberer_employes();
    liberer_reunions();
    liberer_documents();
    liberer_notifications();
    liberer_invitations();
    liberer_ordres_du_jour();
    liberer_reunions_documents();
    liberer_notifications_invitations();

    printf("Au revoir!\n");
    return 0;
}
