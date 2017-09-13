/* 
 * File:   linked_list.h
 * Authores: 8090228 Luis Sousa
 *           8100158 Joel Babo
 *
 * Created on 14 de Dezembro de 2011, 20:45
 */

#include <stdlib.h>
#include <string.h>

#define SIZEPASS 20
#define NAMESIZE 50

enum TypeUser {
    docenteReg=1, docente, aluno
};

enum Avaliation{
    continua=1, final
};

enum Situation {
    aprovado=1, reprovado, avaliacaoCurso
};

enum Epoca{
    normal=1, recurso
};

struct RecursoEpoca{
    float notaTTP;
    float notaTP;
    int notaTTPLancada; //1 lancada
    int notaTPLancada; //1 lancada
    enum Situation situation;
    float media;
};

struct NormalEpoca{
   float notaTTP;
    float notaTP;
    int notaTTPLancada; //1 lancada
    int notaTPLancada; //1 lancada
    enum Situation situation;
    float media;
};

struct FinalAvaliation{
    struct NormalEpoca normalEpoca;
    struct RecursoEpoca recursoEpoca;
};

struct ContinuaAvaliation{
    float notaTTP;
    float notaTP;
    int notaTTPLancada; //1 lancada
    int notaTPLancada; //1 lancada
    int continuaAvLancada; // 1 -> lancada a Nota TTP e do TP
    enum Situation situation;
    float media;
};

struct userAvaliation {
    enum Avaliation type; // avaliation continua ou exame final
    enum Situation situation; // aprovado ou reprovado ou avaliacao em curso
    float notaFinal;
};

struct user {
    unsigned int number;
    char password[SIZEPASS];
    char name[NAMESIZE];
    enum TypeUser  typeUser; // DocenteRegente ou Docente ou Aluno
    int firstlancamentoNotas; // 1 -> primeiro lancamento notas efetuado
    struct userAvaliation avaliation;
    struct ContinuaAvaliation continuaAvaliation;
    struct FinalAvaliation finalAvaliation;
    struct user *nextPtr;
};

/** Definição do tipo User */
typedef struct user User;
/** Definição do tipo User com um apontador para um User */
typedef User* UserPtr;


/* Prototypes */
void insertUser(UserPtr *sPtr, const unsigned int NUMBER, const char PASSWORD[],const char NAME[],
            const unsigned short int TYPE_USER, const unsigned short int TYPE_AVALIATION,
            const unsigned short SITUATION);
UserPtr removeUser(UserPtr sPtr, const unsigned int NUMBER_FIND);


//----------FUNCTIONS LISTA LIGADA----------------------------------------------------------------\\\

/**
 * Inserir um utilizador (aluno ou docente) na lista ligada
 */
void insertUser(UserPtr *sPtr, const unsigned int NUMBER, const char PASSWORD[],const char NAME[],
            const unsigned short int TYPE_USER, const unsigned short int TYPE_AVALIATION,
            const unsigned short SITUATION){
   UserPtr newPtr;      /* pointer to new node */
   UserPtr previousPtr; /* pointer to previous node in list */
   UserPtr currentPtr;  /* pointer to current node in list */
    newPtr = (UserPtr) malloc(sizeof (User));
    if (newPtr != NULL) {
        newPtr->number = NUMBER;
        strcpy(newPtr->password, PASSWORD);
        strcpy(newPtr->name, NAME);
        newPtr->typeUser = TYPE_USER;
        newPtr->avaliation.type = TYPE_AVALIATION;
        newPtr->avaliation.situation = SITUATION;
        /* is space available */
        newPtr->nextPtr = NULL;
        previousPtr = NULL;
        currentPtr = *sPtr;
        /* loop to find the correct location in the list */
        while (currentPtr != NULL && NUMBER > currentPtr->number) {
            previousPtr = currentPtr;
            currentPtr = currentPtr->nextPtr; /* ... next node */
        } /* end while */
        /* insert newPtr at beginning of list */
        if (previousPtr == NULL) {
            newPtr->nextPtr = *sPtr;
            *sPtr = newPtr;
        }/* end if */
        else { /* insert newPtr between previousPtr and currentPtr */
            previousPtr->nextPtr = newPtr;
            newPtr->nextPtr = currentPtr;
        } /* end else */
    }/* end if */
    else {

        printf("\nNao ha memoria disponivel");
    } /* end else */
} /* end function insert */


/**
 * Remover um utilizador (aluno ou docente) da lista ligada
 */
UserPtr removeUser(UserPtr sPtr, const unsigned int NUMBER_FIND) {
    UserPtr previousPtr; /* pointer to previous node in list */
    UserPtr currentPtr;  /* pointer to current node in list */
    UserPtr tempPtr;     /* temporary node pointer */
    
    /* delete first node */
    if (NUMBER_FIND == (sPtr)->number) {
        tempPtr = sPtr;
         sPtr = (sPtr)->nextPtr; /* de-thread the node */
        free(tempPtr); /* free the de-threaded node */
        return sPtr; /* return new head */
    }/* end if */
    else {
        previousPtr = sPtr;
        currentPtr = (sPtr)->nextPtr;
        /* loop to find the correct location in the list */
        while (currentPtr != NULL && currentPtr->number != NUMBER_FIND) {
            previousPtr = currentPtr;
            /* walk to ...
             */
            currentPtr = currentPtr->nextPtr; /* ... next node */
        } /* end while */
        /* delete node at currentPtr */
        if (currentPtr != NULL) {
            tempPtr = currentPtr;
            previousPtr->nextPtr = currentPtr->nextPtr;
            free(tempPtr);
        } /* end if */
    }
    return sPtr; /* return the same head that be received */
    /* end else */
} /* end function delete */


