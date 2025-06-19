#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../includes/menu.h"
#include "../includes/gestion_reunions.h"
#include "../includes/entreprises.h"
#include "../includes/saisie.h"


void gerer_menu_principal() {
    int choix;
    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Gestion des Entreprises\n");
        printf("2. Gestion des Roles\n");
        printf("3. Gestion des Salles\n");
        printf("4. Gestion des Employes\n");
        printf("5. Gestion des Reunions\n");
        printf("6. Gestion des Documents\n");
        printf("7. Gestion des Notifications\n");
        printf("8. Gestion des Invitations\n");
        printf("9. Gestion des Ordres du Jour\n");
        printf("0. Quitter\n");
        choix = saisir_entier("Choix");
        
        
        switch(choix) {
            case 1: gerer_menu_entreprises(); break;
            case 2: gerer_menu_roles(); break;
            case 3: gerer_menu_salles(); break;
            case 4: gerer_menu_employes(); break;
            case 5: gerer_menu_reunions(); break;
            case 6: gerer_menu_documents(); break;
            case 7: gerer_menu_notifications(); break;
            case 8: gerer_menu_invitations(); break;
            case 9: gerer_menu_ordres_du_jour(); break;
            case 0: printf("Ferment le programme...\n"); break;
            default: printf("Choix invalide!\n");
        }
    } while(choix != 0);
}

void gerer_menu_entreprises() {
    int choix;
    
    do {
        printf("\n=== GESTION DES ENTREPRISES ===\n");
        printf("1. Ajouter une entreprise\n");
        printf("2. Modifier une entreprise\n");
        printf("3. Supprimer une entreprise\n");
        printf("4. Afficher toutes les entreprises\n");
        printf("5. Rechercher une entreprise\n");
        printf("0. Retour\n");
        choix = saisir_entier("Choix");
        
        switch(choix) {
            case 1: {
                Entreprise* ent = saisir_entreprise();
                ajouter_entreprise(ent->nom);
                free(ent->nom);
                free(ent);
                
                 enregistrer_entreprises_dans_fichier("stockage/entreprises.txt"); 

                 printf("Entreprise ajoutee avec succes!\n");
                break;
            }
            case 2: {
                int id = saisir_entier("ID de l'entreprise a modifier");
                Entreprise* ent = trouver_entreprise_par_id(id);
                if (ent) {
                    char* nouveau_nom = saisir_chaine("Nouveau nom", true);
                    modifier_entreprise(ent, nouveau_nom);
                    free(nouveau_nom);
                    enregistrer_entreprises_dans_fichier("stockage/entreprises.txt");
                    printf("Entreprise modifiee avec succes!\n");
                } else {
                    printf("Entreprise non trouvee!\n");
                }
                break;
            }
            case 3: {
                int id = saisir_entier("ID de l'entreprise a supprimer");
                Entreprise* ent = trouver_entreprise_par_id(id);
                if (ent) {
                    supprimer_entreprise_de_table(id);
                     enregistrer_entreprises_dans_fichier("stockage/entreprises.txt");
                    printf("Entreprise supprimee avec succes!\n");
                } else {
                    printf("Entreprise non trouvee!\n");
                }
                break;
            }
            case 4: afficher_toutes_entreprises(); break;
            case 5: {
                int id = saisir_entier("ID de l'entreprise a rechercher");
                Entreprise* ent = trouver_entreprise_par_id(id);
                if (ent) afficher_entreprise(ent);
                else printf("Entreprise non trouvee!\n");
                break;
            }
            case 0: break;
            default: printf("Choix invalide!\n");
        }
    } while(choix != 0);
}

void gerer_menu_roles() {
    int choix;
    
    do {
        printf("\n=== GESTION DES ROLES ===\n");
        printf("1. Ajouter un role\n");
        printf("2. Modifier un role\n");
        printf("3. Supprimer un role\n");
        printf("4. Afficher tous les roles\n");
        printf("5. Rechercher un role\n");
        printf("0. Retour\n");
        choix = saisir_entier("Choix");
        
        
        switch(choix) {
            case 1: {
                Role* role = saisir_role();
                ajouter_role(role->nom);
                free(role->nom);
                free(role);
                enregistrer_roles_dans_fichier("stockage/roles.txt");
                printf("Role ajoute avec succes!\n");
                break;
            }
            case 2: {
                int id = saisir_entier("ID du role a modifier");
                Role* role = trouver_role_par_id(id);
                if (role) {
                    char* nouveau_nom = saisir_chaine("Nouveau nom", true);
                    modifier_role(role, nouveau_nom);
                    free(nouveau_nom);
                    enregistrer_roles_dans_fichier("stockage/roles.txt");
                    printf("Role modifie avec succes!\n");
                } else {
                    printf("Role non trouve!\n");
                }
                break;
            }
            case 3: {
                int id = saisir_entier("ID du role a supprimer");
                Role* role = trouver_role_par_id(id);
                if (role) {
                    supprimer_role_de_table(id);
                    enregistrer_roles_dans_fichier("stockage/roles.txt");
                    printf("Role supprime avec succes!\n");
                } else {
                    printf("Role non trouve!\n");
                }
                break;
            }
            case 4: afficher_tous_roles(); break;
            case 5: {
                int id = saisir_entier("ID du role a rechercher");
                Role* role = trouver_role_par_id(id);
                if (role) afficher_role(role);
                else printf("Role non trouve!\n");
                break;
            }
            case 0: break;
            default: printf("Choix invalide!\n");
        }
    } while(choix != 0);
}

void gerer_menu_salles() {
    int choix;
    
    do {
        printf("\n=== GESTION DES SALLES ===\n");
        printf("1. Ajouter une salle\n");
        printf("2. Modifier une salle\n");
        printf("3. Supprimer une salle\n");
        printf("4. Afficher toutes les salles\n");
        printf("5. Rechercher une salle\n");
        printf("6. Reserver une salle pour une reunion\n");
        printf("0. Retour\n");
        choix = saisir_entier("Choix");
        
        
        switch(choix) {
            case 1: {
                Salle* salle = saisir_salle();
                ajouter_salle(salle->nom, salle->capacite, salle->disponible);
                free(salle->nom);
                free(salle);
                enregistrer_salles_dans_fichier("stockage/salles.txt");
                printf("Salle ajoutee avec succes!\n");
                break;
            }
            case 2: {
                int id = saisir_entier("ID de la salle a modifier");
                Salle* salle = trouver_salle_par_id(id);
                if (salle) {
                    char* nouveau_nom = saisir_chaine("Nouveau nom", true);
                    int nouvelle_cap = saisir_entier("Nouvelle capacite");
                    
                    char* disp = saisir_chaine("Disponible (O/N)", true);
                    
                    while (strlen(disp) != 1 || (tolower(disp[0]) != 'o' && tolower(disp[0]) != 'n')) {
                        printf("Option invalid!\n");
                        disp = saisir_chaine("Disponible (O/N)", true);
                    }

                    bool nouvelle_disp = (tolower(disp[0]) == 'o');
                    free(disp);
                    
                    modifier_salle(salle, nouveau_nom, nouvelle_cap, nouvelle_disp);
          
                    if (nouveau_nom) {
                        free(nouveau_nom);
                    }
                    enregistrer_salles_dans_fichier("stockage/salles.txt");
                    printf("Salle modifiee avec succes!\n");
                } else {
                    printf("Salle non trouvee!\n");
                }
                break;
            }  
            case 3: {
                int id = saisir_entier("ID de la salle a supprimer");
                Salle* salle = trouver_salle_par_id(id);
                if (salle) {
                    supprimer_salle_de_table(id);
                    enregistrer_salles_dans_fichier("stockage/salles.txt");
                    printf("Salle supprimee avec succes!\n");
                } else {
                    printf("Salle non trouvee!\n");
                }
                break;
            }
            case 4: afficher_toutes_salles(); break;
            case 5: {
                int id = saisir_entier("ID de la salle a rechercher");
                Salle* salle = trouver_salle_par_id(id);
                if (salle) afficher_salle(salle);
                else printf("Salle non trouvee!\n");
                break;
            }
            case 6: {
                int id_reunion = saisir_entier("ID de la reunion pour la reservation");
                Salle* salle = reserver_salle(id_reunion);
                break;
            }
            case 0: break;
            default: printf("Choix invalide!\n");
        }
    } while(choix != 0);
}
void gerer_menu_employes() {
    int choix;
    
    do {
        printf("\n=== GESTION DES EMPLOYES ===\n");
        printf("1. Ajouter un employe\n");
        printf("2. Modifier un employe\n");
        printf("3. Supprimer un employe\n");
        printf("4. Afficher tous les employes\n");
        printf("5. Rechercher un employe\n");
        printf("0. Retour\n");
        choix = saisir_entier("Choix");
        
        
        switch(choix) {
            case 1: {

                Employe* emp = malloc(sizeof(Employe));
                printf("\n=== Saisie Employe ===\n");
                
                // emp->id = employe_id_counter++;
                emp->cin = saisir_chaine("CIN", true);
                emp->nom = saisir_chaine("Nom", true);
                emp->prenom = saisir_chaine("Prenom", true);
                
                while (1) {
                    emp->email = saisir_chaine("Email", true);
                    if (est_email_valide(emp->email)) break;
                    printf("Email invalide (doit contenir @ et .)\n");
                    free(emp->email);
                }
                
                while (1) {
                    emp->telephone = saisir_chaine("Telephone", true);
                    bool valide = strlen(emp->telephone) >= 10;
                    for (int i = 0; valide && i < strlen(emp->telephone); i++) {
                        if (!isdigit(emp->telephone[i])) valide = false;
                    }
                    if (valide) break;
                    printf("Telephone invalide (10+ chiffres)\n");
                    free(emp->telephone);
                }
                
                do {
                    int id_entreprise = saisir_entier("\nEntreprise ID");
                    emp->entreprise = trouver_entreprise_par_id(id_entreprise);
                    if(!emp->entreprise) {
                        printf("Entreprise non trouvee!\n");
                    } 
                } while (!emp->entreprise);
                
                do {
                    int id_role = saisir_entier("\nRoles ID");
                    emp->role = trouver_role_par_id(id_role);
                    if(!emp->role) {
                        printf("Role non trouve!\n");
                    }   
                } while(!emp->role);

                
                ajouter_employe(emp->cin, emp->nom, emp->prenom, emp->email, 
                               emp->telephone, emp->entreprise, emp->role);
				enregistrer_employes_dans_fichier("stockage/employes.txt");
                free(emp->cin);
                free(emp->nom);
                free(emp->prenom);
                free(emp->email);
                free(emp->telephone);
                free(emp);

                printf("Employe ajoute avec succes!\n");
                break;
            }
            case 2: {
                int id = saisir_entier("ID de l'employe a modifier");
                Employe* emp = trouver_employe_par_id(id);
                if (emp) {



                    char* nouveau_cin = saisir_chaine("Nouveau CIN", true);
                    char* nouveau_nom = saisir_chaine("Nouveau nom", true);
                    char* nouveau_prenom = saisir_chaine("Nouveau prenom", true);

                    char* nouveau_email = NULL;
                
                    while (1) {
                        nouveau_email = saisir_chaine("Nouveau email", true);
                        if (est_email_valide(nouveau_email)) break;
                        printf("Email invalide (doit contenir @ et .)\n");
                        free(nouveau_email);
                    }

                    char* nouveau_tel = NULL;
                    
                    while (1) {
                        nouveau_tel = saisir_chaine("Nouveau telephone", true);
                        bool valide = strlen(nouveau_tel) >= 10;
                        for (int i = 0; valide && i < strlen(nouveau_tel); i++) {
                            if (!isdigit(nouveau_tel[i])) valide = false;
                        }
                        if (valide) break;
                        printf("Telephone invalide (10+ chiffres)\n");
                        free(nouveau_tel);
                    }
                    

                    char* rep = saisir_chaine("Modifier l entreprise ? (O/N)", true);
                    while(strlen(rep) != 1 || tolower(rep[0])!= 'o' && tolower(rep[0]) != 'n') {
                        free(rep);
                        printf("Option invalid!\n");
                        rep = saisir_chaine("Modifier l entreprise ? (O/N)", true);
                    }

                    if (tolower(rep[0]) == 'o') {
                        do {
                            int id_entreprise = saisir_entier("\nEntreprise ID");
                            emp->entreprise = trouver_entreprise_par_id(id_entreprise);
                            if(!emp->entreprise) {
                                printf("Entreprise non trouvee!\n");
                            } 
                        } while (!emp->entreprise);
                    }
                    
                    rep = saisir_chaine("Modifier le role ? (O/N)", true);
                    while(strlen(rep) != 1 || tolower(rep[0])!= 'o' && tolower(rep[0]) != 'n') {
                        free(rep);
                        printf("Option invalid!\n");
                        rep = saisir_chaine("Modifier le role? (O/N)", true);
                    }

                    if (tolower(rep[0]) == 'o') {
                        do {
                            int id_role = saisir_entier("\nRoles ID");
                            emp->role = trouver_role_par_id(id_role);
                            if(!emp->role) {
                                printf("Role non trouve!\n");
                            }   
                        } while(!emp->role);
                    }
         

                    
                    modifier_employe(emp, nouveau_cin, nouveau_nom, nouveau_prenom, 
                                   nouveau_email, nouveau_tel, emp->entreprise, emp->role);
                    enregistrer_employes_dans_fichier("stockage/employes.txt");
                    if (nouveau_cin) free(nouveau_cin);
                    if (nouveau_nom) free(nouveau_nom);
                    if (nouveau_prenom) free(nouveau_prenom);
                    if (nouveau_email) free(nouveau_email);
                    if (nouveau_tel) free(nouveau_tel);
                    
                    printf("Employe modifie avec succes!\n");
                } else {
                    printf("Employe non trouve!\n");
                }
                break;
            }
            case 3: {
                int id = saisir_entier("ID de l'employe a supprimer");
                Employe* emp = trouver_employe_par_id(id);
                if (emp) {
                    supprimer_employe_de_table(id);
                    enregistrer_employes_dans_fichier("stockage/employes.txt");
                    printf("Employe supprime avec succes!\n");
                } else {
                    printf("Employe non trouve!\n");
                }
                break;
            }
            case 4: afficher_tous_employes(); break;
            case 5: {
                int id = saisir_entier("ID de l'employe a rechercher");
                Employe* emp = trouver_employe_par_id(id);
                if (emp) afficher_employe(emp);
                else printf("Employe non trouve!\n");
                break;
            }
            case 0: break;
            default: printf("Choix invalide!\n");
        }
    } while(choix != 0);
}

void gerer_menu_reunions() {
    int choix;
    
    do {
        printf("\n=== GESTION DES REUNIONS ===\n");
        printf("1. Creer une reunion\n");
        printf("2. Modifier une reunion\n");
        printf("3. Supprimer une reunion\n");
        printf("4. Afficher toutes les reunions\n");
        printf("5. Rechercher une reunion\n");
        printf("6. Ajouter une session a une reunion\n");
        printf("7. Compter les invites d'une reunion\n");
        printf("0. Retour\n");
        choix = saisir_entier("Choix");
        
        
        switch(choix) {
            case 1: {
                Reunion* reunion = saisir_reunion();
                ajouter_reunion(reunion->date_debut, reunion->duree, reunion->lien,
                    reunion->type, reunion->organisateur, reunion->salle);

                free(reunion->lien);
                free(reunion->type);
                free(reunion);
                enregistrer_reunions_dans_fichier("stockage/reunions.txt");
                printf("Reunion creee avec succes!\n");
                break;
            }
            case 2: {
                int id = saisir_entier("ID de la reunion a modifier");
                Reunion* reunion = trouver_reunion_par_id(id);
                if (reunion) {
                    printf("Nouveaux details:\n");
                    Reunion* nv_reunion = saisir_reunion();
                    

                    modifier_reunion(reunion, &nv_reunion->date_debut, nv_reunion->duree, 
                                   nv_reunion->lien, nv_reunion->type, 
                                   reunion->organisateur, reunion->salle);
                    enregistrer_reunions_dans_fichier("stockage/reunions.txt");               
                    
                    supprimer_reunion(nv_reunion);
                    printf("Reunion modifiee avec succes!\n");
                } else {
                    printf("Reunion non trouvee!\n");
                }
                break;
            }
            case 3: {
                int id = saisir_entier("ID de la reunion a supprimer");
                Reunion* reunion = trouver_reunion_par_id(id);
                if (reunion) {
                    supprimer_reunion_et_sessions(id);
                    enregistrer_reunions_dans_fichier("stockage/reunions.txt");
                    printf("Reunion supprimee avec succes!\n");
                } else {
                    printf("Reunion non trouvee!\n");
                }
                break;
            }
            case 4: afficher_toutes_reunions(); break;
            case 5: {
                int id = saisir_entier("ID de la reunion a rechercher");
                Reunion* reunion = trouver_reunion_par_id(id);
                if (reunion) afficher_reunion(reunion);
                else printf("Reunion non trouvee!\n");
                break;
            }
            case 6: {
                int id = saisir_entier("ID de la reunion principale");
                Reunion *temp, *reunion = trouver_reunion_par_id(id);
                temp = reunion;
                if (reunion) {
                    printf("Nouvelle session pour la reunion %d:\n", id);

                    while (temp->suivante != NULL ) {
                        temp = temp->suivante;
                    }
                    
                    Date_Heure nouvelle_date = saisir_date_heure();
                    
                    Date_Heure date_fin_dernier_reunion = ajouter_date_duree(temp->date_debut, temp->duree);
                    
                    while(comparer_date_heure(&nouvelle_date, &date_fin_dernier_reunion) <= 0) {
                        printf("Date debut de reunion suivant doit etre apres dernier reunion!\n");
                        nouvelle_date = saisir_date_heure();
                    }

                    ajouter_session_reunion(reunion, nouvelle_date);
                    enregistrer_reunions_dans_fichier("stockage/reunions.txt");
                    printf("Session ajoutee avec succes!\n");
                } else {
                    printf("Reunion non trouvee!\n");
                }
                break;
            }
            case 7: {
                int id = saisir_entier("ID de la reunion");
                int nb_invites = compter_invites_par_reunion_id(id);
                int nb_presentiel = compter_invites_presentiel_par_reunion_id(id);
                printf("Nombre total d'invites: %d\n", nb_invites);
                printf("Nombre d'invites en presentiel: %d\n", nb_presentiel);
                printf("Nombre d'invites en ligne: %d\n", nb_invites - nb_presentiel);
                break;
            }
            case 0: break;
            default: printf("Choix invalide!\n");
        }
    } while(choix != 0);
}

void gerer_menu_documents() {
    int choix;
    
    do {
        printf("\n=== GESTION DES DOCUMENTS ===\n");
        printf("1. Ajouter un document\n");
        printf("2. Modifier un document\n");
        printf("3. Supprimer un document\n");
        printf("4. Afficher tous les documents\n");
        printf("5. Rechercher un document\n");
        printf("6. Lier un document a une reunion\n");
        printf("0. Retour\n");
        choix = saisir_entier("Choix");
        
        
        switch(choix) {
            case 1: {
                Document* doc = saisir_document();
                ajouter_document(doc->nom, doc->type, doc->extension_fichier, 
                               doc->lien, doc->date_creation);
                free(doc->nom);
                free(doc->type);
                free(doc->extension_fichier);
                free(doc->lien);
                free(doc);
                enregistrer_documents_dans_fichier("stockage/documents.txt");
                printf("Document ajoute avec succes!\n");
                break;
            }
            case 2: {
                int id = saisir_entier("ID du document a modifier");
                Document* doc = trouver_document_par_id(id);
                if (doc) {      
                    char* nouveau_nom = saisir_chaine("Nouveau nom", true);

                    char* nouveau_type = saisir_chaine("Nouveau type Document (Compte rendu / Ordre du jour / Annexe/ Convocation / Suivi)", true);
                    while(strcmp(nouveau_type, "Compte rendu") && strcmp(nouveau_type, "Ordre du jour") && strcmp(nouveau_type, "Annexe") && strcmp(nouveau_type, "Convocation") && strcmp(nouveau_type, "Suivi")) {
                    
                        free(nouveau_type);
                        printf("Veuillez saisir les types affiches!\n");
                        nouveau_type = saisir_chaine("Type Document (Compte rendu / Ordre du jour / Annexe/ Convocation / Suivi)", true);

                    }
      
                    char* nouvelle_ext = NULL;
                    while (1) {
                        nouvelle_ext = saisir_chaine("Nouvelle extension (.pdf,.docx)", true);
                        if (!strcmp(nouvelle_ext, ".pdf") || !strcmp(nouvelle_ext, ".docx")) break;
                        printf("Extension saisie invalid!\n");
                        free(nouvelle_ext);
                    }

                    char* nouveau_lien = saisir_chaine("Nouveau lien", true);
                    //MARK: HERE
                    Date_Heure nouvelle_date;
                    char* rep = saisir_chaine("Modifier la date de creation? (O/N)", true);
                    while(strlen(rep) != 1 || tolower(rep[0])!= 'o' && tolower(rep[0]) != 'n') {
                        free(rep);
                        printf("Option invalid!\n");
                        rep = saisir_chaine("Modifier la date de creation? (O/N)", true);
                    }

                    if (tolower(rep[0]) == 'o') {
                        nouvelle_date = saisir_date_heure();
                        modifier_document(doc, nouveau_nom, nouveau_type, nouvelle_ext, 
                                        nouveau_lien, &nouvelle_date);
                        enregistrer_documents_dans_fichier("stockage/documents.txt");                
                    } else {
                        modifier_document(doc, nouveau_nom, nouveau_type, nouvelle_ext, 
                                        nouveau_lien, NULL);
                    }
                    
                    if (nouveau_nom) free(nouveau_nom);
                    if (nouveau_type) free(nouveau_type);
                    if (nouvelle_ext) free(nouvelle_ext);
                    if (nouveau_lien) free(nouveau_lien);
                    
                    printf("Document modifie avec succes!\n");
                } else {
                    printf("Document non trouve!\n");
                }
                break;
            }
            case 3: {
                int id = saisir_entier("ID du document a supprimer");
                Document* doc = trouver_document_par_id(id);
                if (doc) {
                    supprimer_document_de_table(id);
                    enregistrer_documents_dans_fichier("stockage/documents.txt");
                    printf("Document supprime avec succes!\n");
                } else {
                    printf("Document non trouve!\n");
                }
                break;
            }
            case 4: afficher_tous_documents(); break;
            case 5: {
                int id = saisir_entier("ID du document a rechercher");
                Document* doc = trouver_document_par_id(id);
                if (doc) afficher_document(doc);
                else printf("Document non trouve!\n");
                break;
            }
            case 6: {
                int id_reunion = saisir_entier("ID de la reunion");
                int id_doc = saisir_entier("ID du document");
                
                Reunion* reunion = trouver_reunion_par_id(id_reunion);
                Document* doc = trouver_document_par_id(id_doc);
                
                if (reunion && doc) {
                    ajouter_lien_reunion_document(reunion, doc);
                    enregistrer_reunions_documents_dans_fichier("reunions_documents.txt");
                    printf("Document lie a la reunion avec succes!\n");
                } else {
                    if (!reunion) printf("Reunion non trouvee!\n");
                    if (!doc) printf("Document non trouve!\n");
                }
                break;
            }
            case 0: break;
            default: printf("Choix invalide!\n");
        }
    } while(choix != 0);
}

void gerer_menu_notifications() {
    int choix;
    
    do {
        printf("\n=== GESTION DES NOTIFICATIONS ===\n");
        printf("1. Creer une notification\n");
        printf("2. Modifier une notification\n");
        printf("3. Supprimer une notification\n");
        printf("4. Afficher toutes les notifications\n");
        printf("5. Rechercher une notification\n");
        printf("6. Envoyer une notification d'invitation\n");
        printf("0. Retour\n");
        choix = saisir_entier("Choix");
        
        
        switch(choix) {
            case 1: {
                Notification* notif = saisir_notification();
                ajouter_notification(notif->type, notif->sujet, notif->message);
                free(notif->type);
                free(notif->sujet);
                free(notif->message);
                free(notif);
                enregistrer_notifications_dans_fichier("stockage/notifications.txt");
                enregistrer_notifications_invitations_dans_fichier("stockage/notifications_invitations.txt");

                printf("Notification creee avec succes!\n");
                break;
            }
            case 2: {
                int id = saisir_entier("ID de la notification a modifier");
                Notification* notif = trouver_notification_par_id(id);
                if (notif) {

                    char* nouveau_type = NULL;
                    while (1) {
                    nouveau_type = saisir_chaine("Type (Rappel/Alerte/Annulation/Invitation)", true);
                    if (strcmp(nouveau_type, "Rappel") == 0 || 
                        strcmp(nouveau_type, "Alerte") == 0 ||
                        strcmp(nouveau_type, "Annulation") == 0 ||
                        strcmp(nouveau_type, "Invitation") == 0) break;
                        printf("Type doit etre: Rappel, Alerte, Annulation ou Invitation\n");
                        free(nouveau_type);
                    }
                    
                    char* nouveau_sujet = saisir_chaine("Nouveau sujet", true);
                    char* nouveau_msg = saisir_chaine("Nouveau message", true);
        

                    modifier_notification(notif, nouveau_type, nouveau_sujet, nouveau_msg);
                    enregistrer_notifications_dans_fichier("stockage/notifications.txt");
                    enregistrer_notifications_invitations_dans_fichier("stockage/notifications_invitations.txt");                    
                    if (nouveau_type) free(nouveau_type);
                    if (nouveau_sujet) free(nouveau_sujet);
                    if (nouveau_msg) free(nouveau_msg);
                    
                    printf("Notification modifiee avec succes!\n");
                } else {
                    printf("Notification non trouvee!\n");
                }
                break;
            }
            case 3: {
                int id = saisir_entier("ID de la notification a supprimer");
                Notification* notif = trouver_notification_par_id(id);
                if (notif) {
                    supprimer_notification_de_table(id);
                    enregistrer_notifications_dans_fichier("stockage/notifications.txt");
                    enregistrer_notifications_invitations_dans_fichier("stockage/notifications_invitations.txt");
                    printf("Notification supprimee avec succes!\n");
                } else {
                    printf("Notification non trouvee!\n");
                }
                break;
            }
            case 4: afficher_toutes_notifications(); break;
            case 5: {
                int id = saisir_entier("ID de la notification a rechercher");
                Notification* notif = trouver_notification_par_id(id);
                if (notif) afficher_notification(notif);
                else printf("Notification non trouvee!\n");
                break;
            }
            case 6: {
                NotificationInvitation* ni = saisir_notification_invitation();
                ajouter_notification_invitation(ni->date_envoi, ni->statut, ni->employe, 
                                              ni->reunion, ni->notification);
                free(ni->statut);
                free(ni);
                printf("Notification d'invitation envoyee avec succes!\n");
                break;
            }
            case 0: break;
            default: printf("Choix invalide!\n");
        }
    } while(choix != 0);
}

void gerer_menu_invitations() {
    int choix;
    
    do {
        printf("\n=== GESTION DES INVITATIONS ===\n");
        printf("1. Creer une invitation\n");
        printf("2. Modifier une invitation\n");
        printf("3. Supprimer une invitation\n");
        printf("4. Afficher toutes les invitations\n");
        printf("5. Rechercher une invitation\n");
        printf("6. Mettre a jour le statut d'une invitation\n");
        printf("0. Retour\n");
        choix = saisir_entier("Choix");
        
        
        switch(choix) {
            case 1: {
                Invitation* inv = saisir_invitation();
                ajouter_invitation(inv->disponibilite, inv->presence, inv->type, 
                                 inv->invite, inv->reunion);
                enregistrer_invitations_dans_fichier("stockage/invitations.txt");
                free(inv->disponibilite);
                free(inv->presence);
                free(inv);
                printf("Invitation creee avec succes!\n");
                break;
            }
            case 2: {

                int id_emp = saisir_entier("ID de l'employe invite");
                Employe* emp = trouver_employe_par_id(id_emp);

                while(1) {
                    if(emp) {
                        printf("Employee trouve!\n");
                        break;
                    }
                    printf("Employe avec ID %d non trouve\n", id_emp);
                    id_emp = saisir_entier("ID de l'employe invite");
                    emp = trouver_employe_par_id(id_emp);
                }
                
                int id_reunion = saisir_entier("ID de la reunion");
                Reunion* reunion = trouver_reunion_par_id(id_reunion);

                while(1) {
                    if(reunion) {
                        printf("Reunion trouve!\n");
                        break;
                    }
                    printf("Reunion avec ID %d non trouve\n", id_reunion);
                    id_reunion = saisir_entier("Saisir ID de reunion");
                    reunion = trouver_reunion_par_id(id_reunion);
                }
                
                if (emp && reunion) {
                    Invitation* inv = trouver_invitation_par_employe_et_reunion(emp, reunion);
                    if (inv) {
                        char* nouvelle_dispo;
                        
                        while (1) {
                            nouvelle_dispo = saisir_chaine("Nouvelle disponibilite (Disponible/Indisponible)", true);
                            if (strcmp(nouvelle_dispo, "Disponible") == 0 || 
                            strcmp(nouvelle_dispo, "Indisponible") == 0) break;
                            printf("Doit etre 'Disponible' ou 'Indisponible'\n");
                            free(nouvelle_dispo);
                        }

                        char* nouvelle_presence;

                        while (1) {
                            nouvelle_presence = saisir_chaine("Presence (Present/Absent/En attente)", true);
                            if (strcmp(nouvelle_presence, "Present") == 0 || 
                                strcmp(nouvelle_presence, "Absent") == 0 ||
                                strcmp(nouvelle_presence, "En attente") == 0) break;
                            printf("Doit etre 'Present', 'Absent' ou 'En attente'\n");
                            free(nouvelle_presence);
                        }
                        
                        
                        char* type = saisir_chaine("Nouveau type (P=Presentiel, L=En ligne)", true);

                        while(1) {
                            if(strlen(type) == 1 && (tolower(type[0]) == 'p' || tolower(type[0] == 'l'))) break;
                            printf("Veuillez saisir type affiche!\n");
                            free(type);
                            type = saisir_chaine("Nouveau type (P=Presentiel, L=En ligne)", true);
                        }

                        inv->type = (tolower(type[0]) == 'l');//si type == 0, presentiel si type == 1 en ligne
                        free(type);


                        bool nouveau_type = inv->type;
        
                        
                        modifier_invitation(inv, nouvelle_dispo, nouvelle_presence, 
                                          nouveau_type, inv->invite, inv->reunion);
                        enregistrer_invitations_dans_fichier("stockage/invitations.txt");
                        if (nouvelle_dispo) free(nouvelle_dispo);
                        if (nouvelle_presence) free(nouvelle_presence);
                        
                        printf("Invitation modifiee avec succes!\n");
                    } else {
                        printf("Invitation non trouvee!\n");
                    }
                } else {
                    if (!emp) printf("Employe non trouve!\n");
                    if (!reunion) printf("Reunion non trouvee!\n");
                }
                break;
            }
            case 3: {
                int id_emp = saisir_entier("ID de l'employe invite");
                int id_reunion = saisir_entier("ID de la reunion");
                
                Employe* emp = trouver_employe_par_id(id_emp);
                Reunion* reunion = trouver_reunion_par_id(id_reunion);
                
                if (emp && reunion) {
                    Invitation* inv = trouver_invitation_par_employe_et_reunion(emp, reunion);
                    if (inv) {
                        supprimer_invitation_de_table(inv);
                        enregistrer_invitations_dans_fichier("stockage/invitations.txt");
                        printf("Invitation supprimee avec succes!\n");
                    } else {
                        printf("Invitation non trouvee!\n");
                    }
                } else {
                    if (!emp) printf("Employe non trouve!\n");
                    if (!reunion) printf("Reunion non trouvee!\n");
                }
                break;
            }
            case 4: afficher_toutes_invitations(); break;
            case 5: {
                int id_emp = saisir_entier("ID de l'employe invite");
                int id_reunion = saisir_entier("ID de la reunion");
                
                Employe* emp = trouver_employe_par_id(id_emp);
                Reunion* reunion = trouver_reunion_par_id(id_reunion);
                
                if (emp && reunion) {
                    Invitation* inv = trouver_invitation_par_employe_et_reunion(emp, reunion);
                    if (inv) afficher_invitation(inv);
                    else printf("Invitation non trouvee!\n");
                } else {
                    if (!emp) printf("Employe non trouve!\n");
                    if (!reunion) printf("Reunion non trouvee!\n");
                }
                break;
            }
            case 6: {
                int id_emp = saisir_entier("ID de l'employe invite");
                int id_reunion = saisir_entier("ID de la reunion");
                
                Employe* emp = trouver_employe_par_id(id_emp);
                Reunion* reunion = trouver_reunion_par_id(id_reunion);
                
                if (emp && reunion) {
                    Invitation* inv = trouver_invitation_par_employe_et_reunion(emp, reunion);
                    if (inv) {
                        char* nouvelle_dispo;
                        
                        while (1) {
                            nouvelle_dispo = saisir_chaine("Nouvelle disponibilite (Disponible/Indisponible)", true);
                            if (strcmp(nouvelle_dispo, "Disponible") == 0 || 
                            strcmp(nouvelle_dispo, "Indisponible") == 0) break;
                            printf("Doit etre 'Disponible' ou 'Indisponible'\n");
                            free(nouvelle_dispo);
                        }
                
                        char* nouvelle_presence;

                        while (1) {
                            nouvelle_presence = saisir_chaine("Presence (Present/Absent/En attente)", true);
                            if (strcmp(nouvelle_presence, "Present") == 0 || 
                                strcmp(nouvelle_presence, "Absent") == 0 ||
                                strcmp(nouvelle_presence, "En attente") == 0) break;
                            printf("Doit etre 'Present', 'Absent' ou 'En attente'\n");
                            free(nouvelle_presence);
                        }

                        mettre_a_jour_statut_invitation(inv, nouvelle_dispo, nouvelle_presence);
                        
                        free(nouvelle_dispo);
                        free(nouvelle_presence);
                        
                        printf("Statut d'invitation mis a jour avec succes!\n");
                    } else {
                        printf("Invitation non trouvee!\n");
                    }
                } else {
                    if (!emp) printf("Employe non trouve!\n");
                    if (!reunion) printf("Reunion non trouvee!\n");
                }
                break;
            }
            case 0: break;
            default: printf("Choix invalide!\n");
        }
    } while(choix != 0);
}

void gerer_menu_ordres_du_jour() {
    int choix;
    
    do {
        printf("\n=== GESTION DES ORDRES DU JOUR ===\n");
        printf("1. Ajouter un ordre du jour\n");
        printf("2. Modifier un ordre du jour\n");
        printf("3. Supprimer un ordre du jour\n");
        printf("4. Afficher tous les ordres du jour\n");
        printf("5. Rechercher un ordre du jour\n");
        printf("6. Rechercher par reunion\n");
        printf("7. Rechercher par presentateur\n");
        printf("0. Retour\n");
        choix = saisir_entier("Choix");
        
        
        switch(choix) {
            case 1: {
                OrdreDuJour* ordre = saisir_ordre_du_jour();
                ajouter_ordre_du_jour(ordre->sujet, ordre->presentateur, ordre->reunion);
                free(ordre->sujet);
                free(ordre);
                enregistrer_ordres_du_jour_dans_fichier("stockage/ordres_du_jour.txt");
                printf("Ordre du jour ajoute avec succes!\n");
                break;
            }
            case 2: {
                int id = saisir_entier("ID de l'ordre du jour a modifier");
                OrdreDuJour* ordre = trouver_ordre_par_id(id);
                if (ordre) {
                    char* nouveau_sujet = saisir_chaine("Nouveau sujet: ", true);
                    
                    modifier_ordre_du_jour(ordre, nouveau_sujet, ordre->presentateur, ordre->reunion);
                    
                    if (nouveau_sujet) free(nouveau_sujet);
                    enregistrer_ordres_du_jour_dans_fichier("stockage/ordres_du_jour.txt");
                    printf("Ordre du jour modifie avec succes!\n");
                } else {
                    printf("Ordre du jour non trouve!\n");
                }
                break;
            }
            case 3: {
                int id = saisir_entier("ID de l'ordre du jour a supprimer");
                OrdreDuJour* ordre = trouver_ordre_par_id(id);
                if (ordre) {
                    supprimer_ordre_du_jour_de_table(id);
                    enregistrer_ordres_du_jour_dans_fichier("stockage/ordres_du_jour.txt");
                    printf("Ordre du jour supprime avec succes!\n");
                } else {
                    printf("Ordre du jour non trouve!\n");
                }
                break;
            }
            case 4: afficher_tous_ordres_du_jour(); break;
            case 5: {
                int id = saisir_entier("ID de l'ordre du jour a rechercher");
                OrdreDuJour* ordre = trouver_ordre_par_id(id);
                if (ordre) afficher_ordre_du_jour(ordre);
                else printf("Ordre du jour non trouve!\n");
                break;
            }
            case 6: {
                int id_reunion = saisir_entier("ID de la reunion");
                Reunion* reunion = trouver_reunion_par_id(id_reunion);
                if (reunion) {
                    OrdreDuJour* ordre = trouver_ordres_par_reunion(reunion);
                    if (ordre) afficher_ordre_du_jour(ordre);
                    else printf("Aucun ordre du jour trouve pour cette reunion!\n");
                } else {
                    printf("Reunion non trouvee!\n");
                }
                break;
            }
            case 7: {
                int id_emp = saisir_entier("ID du presentateur");
                Employe* emp = trouver_employe_par_id(id_emp);
                if (emp) {
                    OrdreDuJour* ordre = trouver_ordres_par_presentateur(emp);
                    if (ordre) afficher_ordre_du_jour(ordre);
                    else printf("Aucun ordre du jour trouve pour ce presentateur!\n");
                } else {
                    printf("Employe non trouve!\n");
                }
                break;
            }
            case 0: break;
            default: printf("Choix invalide!\n");
        }
    } while(choix != 0);
}

void afficher_toutes_entreprises() {
    printf("\n=== LISTE DES ENTREPRISES ===\n");
    for (int i = 0; i < nb_entreprises; i++) {
        afficher_entreprise(&entreprises[i]);
        printf("----------------------------\n");
    }
}

void afficher_tous_roles() {
    printf("\n=== LISTE DES ROLES ===\n");
    for (int i = 0; i < nb_roles; i++) {
        afficher_role(&roles[i]);
        printf("----------------------------\n");
    }
}

void afficher_toutes_salles() {
    printf("\n=== LISTE DES SALLES ===\n");
    for (int i = 0; i < nb_salles; i++) {
        afficher_salle(&salles[i]);
        printf("----------------------------\n");
    }
}

void afficher_tous_employes() {
    printf("\n=== LISTE DES EMPLOYES ===\n");
    for (int i = 0; i < nb_employes; i++) {
        afficher_employe(&employes[i]);
        printf("----------------------------\n");
    }
}

void afficher_toutes_reunions() {
    printf("\n=== LISTE DES REUNIONS ===\n");
    for (int i = 0; i < nb_reunions; i++) {
        Reunion* current = &reunions[i];
        while (current != NULL) {
            afficher_reunion(current);
            printf("----------------------------\n");
            current = current->suivante;
        }
    }
}

void afficher_tous_documents() {
    printf("\n=== LISTE DES DOCUMENTS ===\n");
    for (int i = 0; i < nb_documents; i++) {
        afficher_document(&documents[i]);
        printf("----------------------------\n");
    }
}

void afficher_toutes_notifications() {
    printf("\n=== LISTE DES NOTIFICATIONS ===\n");
    for (int i = 0; i < nb_notifications; i++) {
        afficher_notification(&notifications[i]);
        printf("----------------------------\n");
    }
}

void afficher_toutes_invitations() {
    printf("\n=== LISTE DES INVITATIONS ===\n");
    for (int i = 0; i < nb_invitations; i++) {
        afficher_invitation(&invitations[i]);
        printf("----------------------------\n");
    }
}

void afficher_tous_ordres_du_jour() {
    printf("\n=== LISTE DES ORDRES DU JOUR ===\n");
    for (int i = 0; i < nb_ordres_du_jour; i++) {
        afficher_ordre_du_jour(&ordres_du_jour[i]);
        printf("----------------------------\n");
    }
}
