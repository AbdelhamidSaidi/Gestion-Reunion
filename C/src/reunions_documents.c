#include "../includes/reunions_documents.h"
#include <stdlib.h>
#include <stdio.h>


ReunionDocument* reunions_documents = NULL;
int nb_reunions_documents = 0;
int cap_reunions_documents = 0;

#define CAPACITE_INITIALE 10

void initialiser_reunions_documents() {
    reunions_documents = malloc(CAPACITE_INITIALE * sizeof(ReunionDocument));
    cap_reunions_documents = CAPACITE_INITIALE;
    nb_reunions_documents = 0;
}

void ajouter_lien_reunion_document(Reunion *reunion, Document *document) {

    //si document deja lie au reunion quitter
    for (int i = 0; i < nb_reunions_documents; i++) {
        if (reunions_documents[i].reunion == reunion && 
            reunions_documents[i].document == document) {
            return; 
        }
    }

    if (nb_reunions_documents >= cap_reunions_documents) {
        cap_reunions_documents++;
        ReunionDocument* new_tab = realloc(reunions_documents, cap_reunions_documents * sizeof(ReunionDocument));

        reunions_documents = new_tab;
    }

    reunions_documents[nb_reunions_documents].reunion = reunion;
    reunions_documents[nb_reunions_documents].document = document;
    nb_reunions_documents++;
}

void supprimer_lien_reunion_document(Reunion *reunion, Document *document) {
    for (int i = 0; i < nb_reunions_documents; i++) {
        if (reunions_documents[i].reunion == reunion && 
            reunions_documents[i].document == document) {
            for (int j = i; j < nb_reunions_documents - 1; j++) {
                reunions_documents[j] = reunions_documents[j + 1];
            }
            nb_reunions_documents--;
            break;
        }
    }
}

ReunionDocument* trouver_par_document_reunion(Document *doc, Reunion *reun) {
    for (int i = 0; i < nb_reunions_documents; i++) {
        if (reunions_documents[i].document == doc && 
            reunions_documents[i].reunion == reun) {
            return &reunions_documents[i];
        }
    }
    return NULL;
}

void liberer_reunions_documents() {
    free(reunions_documents);
    reunions_documents = NULL;
    nb_reunions_documents = cap_reunions_documents = 0;
}



ReunionDocument* creer_reunion_document(Reunion* reunion, Document* document) {
    ReunionDocument* rd = malloc(sizeof(ReunionDocument));
    if (rd) {
        rd->reunion = reunion;
        rd->document = document;
    }
    return rd;
}

void afficher_reunion_document(const ReunionDocument* rd) {
    if (rd) {
        if (rd->reunion) printf("Reunion ID: %d\n", rd->reunion->id);
        if (rd->document) printf("Document: %s\n", rd->document->nom);
    }
}

void supprimer_reunion_document(ReunionDocument* rd) {
    free(rd);
}
void enregistrer_reunions_documents_dans_fichier(const char* nom_fichier) {
    FILE* fichier = fopen(nom_fichier, "w");
    if (!fichier) {
        perror("Erreur d'ouverture du fichier pour écriture");
        return;
    }

    for (int i = 0; i < nb_reunions_documents; i++) {
        fprintf(fichier, "%d;%d\n",
                reunions_documents[i].reunion ? reunions_documents[i].reunion->id : -1,
                reunions_documents[i].document ? reunions_documents[i].document->id : -1);
    }

    fclose(fichier);
}

void charger_reunions_documents_depuis_fichier(const char* nom_fichier) {
    FILE* fichier = fopen(nom_fichier, "r");
    if (!fichier) {
        perror("Erreur d'ouverture du fichier pour lecture");
        return;
    }

    initialiser_reunions_documents();

    int id_reunion, id_document;

    while (fscanf(fichier, "%d;%d\n", &id_reunion, &id_document) == 2) {
        Reunion* reunion = trouver_reunion_par_id(id_reunion);
        Document* document = trouver_document_par_id(id_document);

        if (reunion && document) {
            ajouter_lien_reunion_document(reunion, document);
        }
    }

    fclose(fichier);
}

