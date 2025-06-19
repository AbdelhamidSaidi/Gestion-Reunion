#include "../includes/documents.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../includes/counters.h"

Document* documents = NULL;
int nb_documents = 0;
int cap_documents = 0;

#define CAPACITE_INITIALE 10

void initialiser_documents() {
    documents = malloc(CAPACITE_INITIALE * sizeof(Document));
    cap_documents = CAPACITE_INITIALE;
    nb_documents = 0;
}

void ajouter_document(const char* nom, const char* type, const char* extension_fichier, const char* lien, Date_Heure date_creation) {

    if (nb_documents >= cap_documents) {
        cap_documents++;
        Document* new_tab = realloc(documents, cap_documents * sizeof(Document));
        documents = new_tab;
    }


    documents[nb_documents].id = document_id_counter++;
    documents[nb_documents].nom = strdup(nom);
    documents[nb_documents].type = strdup(type);
    documents[nb_documents].extension_fichier = strdup(extension_fichier);
    documents[nb_documents].lien = strdup(lien);
    documents[nb_documents].date_creation = date_creation;


    if (!documents[nb_documents].nom || 
        !documents[nb_documents].type ||
        !documents[nb_documents].extension_fichier ||
        !documents[nb_documents].lien) {
    }

    nb_documents++;
}

Document* trouver_document_par_id(int id) {
    for (int i = 0; i < nb_documents; i++) {
        if (documents[i].id == id) {
            return &documents[i];
        }
    }
    return NULL;
}

void supprimer_document_de_table(int id) {
    for (int i = 0; i < nb_documents; i++) {
        if (documents[i].id == id) {
            // Free all string fields
            free(documents[i].nom);
            free(documents[i].type);
            free(documents[i].extension_fichier);
            free(documents[i].lien);
            
            for (int j = i; j < nb_documents - 1; j++) {
                documents[j] = documents[j + 1];
            }
            nb_documents--;
            break;
        }
    }
}

void liberer_documents() {
    for (int i = 0; i < nb_documents; i++) {
        free(documents[i].nom);
        free(documents[i].type);
        free(documents[i].extension_fichier);
        free(documents[i].lien);
    }
    free(documents);
    documents = NULL;
    nb_documents = cap_documents = 0;
}




Document* creer_document(int id, const char* nom, const char* type, const char* extension_fichier, const char* lien, Date_Heure date_creation) {
    Document* doc = malloc(sizeof(Document));
    if (doc) {
        doc->id = id;
        doc->nom = strdup(nom);
        doc->type = strdup(type);
        doc->extension_fichier = strdup(extension_fichier);
        doc->lien = strdup(lien);
        doc->date_creation = date_creation;
    }
    return doc;
}


void modifier_document(Document* doc, const char* nouveau_nom, const char* nouveau_type, const char* nouvelle_extension, const char* nouveau_lien, const Date_Heure* nouvelle_date) {
    if (!doc) return;

    // Modifier le nom si fourni
    if (nouveau_nom) {
    free(doc->nom);
    doc->nom = strdup(nouveau_nom);
    }

    // Modifier le type si fourni
    if (nouveau_type) {
    free(doc->type);
    doc->type = strdup(nouveau_type);
    }

    // Modifier l'extension si fournie
    if (nouvelle_extension) {
    free(doc->extension_fichier);
    doc->extension_fichier = strdup(nouvelle_extension);
    }

    // Modifier le lien si fourni
    if (nouveau_lien) {
    free(doc->lien);
    doc->lien = strdup(nouveau_lien);
    }

    // Modifier la date si fournie
    if (nouvelle_date) {
    doc->date_creation = *nouvelle_date;
    }
}

void afficher_document(const Document* doc) {
    if (doc) {
        printf("Document [ID: %d]\nNom: %s\nType: %s\nExtension: %s\nLien: %s\n",
               doc->id, doc->nom, doc->type, doc->extension_fichier, doc->lien);
        printf("Date creation: ");
        afficher_date_heure(&doc->date_creation);
        printf("\n");
    }
}

void supprimer_document(Document* doc) {
    if (doc) {
        free(doc->nom);
        free(doc->type);
        free(doc->extension_fichier);
        free(doc->lien);
        free(doc);
    }
}
void enregistrer_documents_dans_fichier(const char* nom_fichier) {
    FILE* fichier = fopen(nom_fichier, "w");
    if (!fichier) {
        perror("Erreur d'ouverture du fichier pour écriture");
        return;
    }

    for (int i = 0; i < nb_documents; i++) {
        fprintf(fichier, "%d;%s;%s;%s;%s;%d-%02d-%02d;%02d:%02d\n",
                documents[i].id,
                documents[i].nom,
                documents[i].type,
                documents[i].extension_fichier,
                documents[i].lien,
                documents[i].date_creation.annee,
                documents[i].date_creation.mois,
                documents[i].date_creation.jour,
                documents[i].date_creation.hr,
                documents[i].date_creation.min);
    }

    fclose(fichier);
}

void charger_documents_depuis_fichier(const char* nom_fichier) {
    FILE* fichier = fopen(nom_fichier, "r");
    if (!fichier) {
        perror("Erreur d'ouverture du fichier pour lecture");
        return;
    }

    initialiser_documents();

    int id, annee, mois, jour, hr, min;
    char nom[100], type[100], extension[20], lien[256];

    while (fscanf(fichier, "%d;%99[^;];%99[^;];%19[^;];%255[^;];%d-%d-%d;%d:%d\n",
                  &id, nom, type, extension, lien, &annee, &mois, &jour, &hr, &min) == 10) {

        Date_Heure date;
        date.annee = annee;
        date.mois = mois;
        date.jour = jour;
        date.hr = hr;
        date.min = min;

        ajouter_document(nom, type, extension, lien, date);
        documents[nb_documents - 1].id = id;

        if (id >= document_id_counter) {
            document_id_counter = id + 1;
        }
    }

    fclose(fichier);
}

