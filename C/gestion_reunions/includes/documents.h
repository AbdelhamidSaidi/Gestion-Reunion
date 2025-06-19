#ifndef DOCUMENTS_H
#define DOCUMENTS_H

#include "date_heure.h"

typedef struct {
    int id;
    char *nom;
    char *type;//Compte Rendu, Ordre du jour, Annexe, Convocation, suivi (dakchi dial mn ba3d)
    char *extension_fichier;
    char *lien;
    Date_Heure date_creation;
} Document;


extern Document* documents;
extern int nb_documents;
extern int cap_documents;

void initialiser_documents();
void ajouter_document(const char* nom, const char* type, const char* extension_fichier, const char* lien, Date_Heure date_creation);
Document* trouver_document_par_id(int id);
void supprimer_document_de_table(int id);
void liberer_documents();


Document* creer_document(int id, const char* nom, const char* type, const char* extension_fichier, const char* lien, Date_Heure date_creation);
void afficher_document(const Document* doc);
void modifier_document(Document* doc, const char* nouveau_nom, const char* nouveau_type, const char* nouvelle_extension, const char* nouveau_lien, const Date_Heure* nouvelle_date);
void supprimer_document(Document* doc);
void enregistrer_documents_dans_fichier(const char* nom_fichier);
void charger_documents_depuis_fichier(const char* nom_fichier);
#endif
