#ifndef REUNIONS_DOCUMENTS_H
#define REUNIONS_DOCUMENTS_H

#include "reunions.h"
#include "documents.h"

typedef struct {
    Reunion *reunion;
    Document *document;
} ReunionDocument;


extern ReunionDocument* reunions_documents;
extern int nb_reunions_documents;
extern int cap_reunions_documents;


void initialiser_reunions_documents();
void ajouter_lien_reunion_document(Reunion *reunion, Document *document);
void supprimer_lien_reunion_document(Reunion *reunion, Document *document);
ReunionDocument* trouver_par_document_reunion(Document *doc, Reunion *reun);
void liberer_reunions_documents();


ReunionDocument* creer_reunion_document(Reunion* reunion, Document* document);
void afficher_reunion_document(const ReunionDocument* rd);
void supprimer_reunion_document(ReunionDocument* rd);
void enregistrer_reunions_documents_dans_fichier(const char* nom_fichier);
void charger_reunions_documents_depuis_fichier(const char* nom_fichier);


#endif
