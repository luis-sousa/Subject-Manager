/* 
 * File:   myFunctions.h
 * Authores: 8090228 Luis Sousa
 *           8100158 Joel Babo
 *
 * Created on 14 de Dezembro de 2011, 20:45
 */

#include <stdlib.h>
#include <string.h>
#include "linked_list.h"
#include "util.h"

#define MESSAGE_START_PRINTING  "Start printing:\n"
#define MESSAGE_DONE            "\n...done!\n"
#define MESSAGE_EXIT_MENU       "****Deseja Sair?****\n* 1 -> Sim         *\n* 0 -> Nao         *\n********************\nOpçao: "
#define MESSAGE_INVALID_CHOICE  "Escolha Invalida!!!\n"
#define PERCENTAGE_TTP  0.40
#define PERCENTAGE_TP 0.60
#define NOTA_MIN_TTP 7.5
#define NOTA_MIN_TP 9.5
#define NOTA_MIN 9.5

/*
  Prototypes
 */
void insertAuto(UserPtr *userPtr); //
void menuInit(const UserPtr const HEAD_PTR); //
void menuLogin(const UserPtr const HEAD_PTR); //
void verifyLogin(const UserPtr const HEAD_PTR, const unsigned int NUMBER, const char PASSWORD[]); //
void menuStudent(const UserPtr HEAD_PTR, const UserPtr const STUDENT_PTR); //
void editUserBasic(const UserPtr const userPtr); //
void changeAvaliation(const UserPtr const STUDENT_PTR); //
void seeSituation(const UserPtr const STUDENT_PTR); //
void printAvContinuaSituation(const UserPtr const STUDENT_PTR); //
void printEpNormalSituation(const UserPtr const STUDENT_PTR); //
void printEpRecursoSituation(const UserPtr const STUDENT_PTR); //
void menuTeacher(UserPtr headPtr, const UserPtr const TEACHER_PTR);
void getUser(UserPtr *userPtr);
UserPtr findEditUser(const UserPtr const HEAD_PTR);
void editUser(const UserPtr const USER_PTR);
UserPtr sortNumber(UserPtr startPtr);
UserPtr sortName(UserPtr startPtr);
void printAllStudent(const UserPtr const ELEMENT_PTR);
void printPag(const UserPtr const ELEMENT_PTR, const unsigned int N_Pagination); //
void lancaNotas(const UserPtr const HEAD_PTR, const UserPtr TEACHER_PTR);
void lancaNotasContinua(const UserPtr const HEAD_PTR);
void updateAvContinuaSituation(const UserPtr const STUDENT_PTR);
void lancaNotasEpocaNormal(const UserPtr const HEAD_PTR);
void updateEpNormalSituation(const UserPtr const STUDENT_PTR);
void lancaNotasEpocaRecurso(const UserPtr const HEAD_PTR);
void verifyPreviousNotasTTP(const UserPtr const STUDENT_PTR);
void verifyPreviousNotasTP(const UserPtr const STUDENT_PTR);
void updateEpRecursoSituation(const UserPtr const STUDENT_PTR);
void numberStudentApprovedStatistics(const UserPtr const USER_PTR);

/* Funcao insertAuto serve para enviar os dados dos utilizadores para a funcao 
 * insertUser existente no ficheiro linked_list.h */
void insertAuto(UserPtr *userPtr) {
    insertUser(userPtr, 1111111, "123456", "Professor", docenteReg, 0, 0);
    insertUser(userPtr, 2222222, "123456", "HMP", docente, 0, 0);
    insertUser(userPtr, 3333333, "123456", "ECL", docente, 0, 0);
    insertUser(userPtr, 8090228, "123456", "Aluno Luis", aluno, final, avaliacaoCurso);
    insertUser(userPtr, 8100459, "123456", "Ana", aluno, final, avaliacaoCurso);
    insertUser(userPtr, 8100158, "123456", "Joel", aluno, final, avaliacaoCurso);
    insertUser(userPtr, 8100653, "123456", "Ramalho", aluno, final, avaliacaoCurso);
    insertUser(userPtr, 8100156, "123456", "Rompante", aluno, final, avaliacaoCurso);
    insertUser(userPtr, 8100454, "123456", "Rui", aluno, final, avaliacaoCurso);
    insertUser(userPtr, 8100456, "123456", "Ruda", aluno, final, avaliacaoCurso);
    insertUser(userPtr, 8100134, "123456", "David", aluno, final, avaliacaoCurso);
    insertUser(userPtr, 8100343, "123456", "Simao", aluno, final, avaliacaoCurso);
    insertUser(userPtr, 8100236, "123456", "Joao", aluno, final, avaliacaoCurso);
}

/* Menu inicial para os utilizadores poderem fazer login */
void menuInit(const UserPtr const HEAD_PTR) {
    short option;
    clearScreen();
    printf("1-Fazer Login \n");
    printf("0-Sair \n");
    printf("Introduza a sua opcao ");
    scanf("%hu", &option);
    switch (option) {
        case 1:
            clean();
            menuLogin(HEAD_PTR);
            break;
        case 0:
            clean();
            clearScreen();
            printf(MESSAGE_EXIT_MENU);
            scanf("%hu", &option);
            if (option == 1) {
                clearScreen();
                exit(0);
            } else {
                menuInit(HEAD_PTR);
            }
            break;
        default:
            clean();
            printf(MESSAGE_INVALID_CHOICE);
            wait(1);
            menuInit(HEAD_PTR);
    }
}

/* Menu Login*/
void menuLogin(const UserPtr const HEAD_PTR) {
    unsigned int number;
    char password[SIZEPASS];
    clearScreen();
    printf("Introduza o seu numero mecanografico ");
    scanf("%u", &number);
    clean();
    printf("Introduza a sua password ");
    scanf("%s", password);
    verifyLogin(HEAD_PTR, number, password);
}

/* Funcao para verificar se existe aquele login */
void verifyLogin(const UserPtr const HEAD_PTR, const unsigned int NUMBER, const char PASSWORD[]) {
    short verify = 0;
    UserPtr userPtr = HEAD_PTR;

    while (userPtr && verify != 1) {
        if ((userPtr->number == NUMBER) && (strcmp(userPtr->password, PASSWORD) == 0)) {
            verify = 1;
            printf("Login efetuado com sucesso!!!\n");
            wait(1);
            if (userPtr->typeUser == aluno) {
                menuStudent(HEAD_PTR, userPtr);
            } else {
                menuTeacher(HEAD_PTR, userPtr);
            }
        }
        userPtr = userPtr->nextPtr;
    }

    if (verify != 1) {
        printf("Dados errados\n");
        wait(1);
        menuInit(HEAD_PTR);
    }
}

/* Menu com as funcionalidades dos utilizadores do tipo Aluno */
void menuStudent(const UserPtr HEAD_PTR, const UserPtr const STUDENT_PTR) {
    short option;
    clearScreen();

    printf("Bem Vindo %s\n\n", STUDENT_PTR->name);
    printf("1-Alterar Dados Proprios\n");
    printf("2-Escolher Avaliacao \n");
    printf("3-Consultar Situacao \n");
    printf("0-Logout \n");
    printf("Introduza a sua opcao ");
    scanf("%hu", &option);
    switch (option) {
        case 1:
            clean();
            editUserBasic(STUDENT_PTR);
            printf("Dados Editados com sucesso!!!\n");
            wait(1);
            menuStudent(HEAD_PTR, STUDENT_PTR);
            break;
        case 2:
            clean();
            changeAvaliation(STUDENT_PTR);
            menuStudent(HEAD_PTR, STUDENT_PTR);
            break;
        case 3:
            clean();
            seeSituation(STUDENT_PTR);
            menuStudent(HEAD_PTR, STUDENT_PTR);
            break;
        case 0:
            clean();
            clearScreen();
            printf(MESSAGE_EXIT_MENU);
            scanf("%hu", &option);
            if (option == 1) {
                menuInit(HEAD_PTR);
            } else {
                menuStudent(HEAD_PTR, STUDENT_PTR);
            }
            break;
        default:
            clean();
            printf(MESSAGE_INVALID_CHOICE);
            wait(1);
            menuStudent(HEAD_PTR, STUDENT_PTR);
    }
}

/* Funcao que permite alterar a password e o nome de um utilizador */
void editUserBasic(const UserPtr const userPtr) {
    char newPassword[SIZEPASS];
    char newName[NAMESIZE];
    clearScreen();
    printf("Introduza a sua nova password ");
    scanf("%s", newPassword);
    clean();
    printf("Introduza o seu novo nome ");
    scanf("%s", newName);
    clean();
    strcpy(userPtr->password, newPassword);
    strcpy(userPtr->name, newName);
}

/* Funcao que permite escolher a avaliacao de um Aluno*/
void changeAvaliation(const UserPtr const STUDENT_PTR) {
    short option;
    clearScreen();

    if (STUDENT_PTR->avaliation.type == continua || STUDENT_PTR->firstlancamentoNotas == 1) {
        printf("Aluno inscrito na Avaliacao Continua\n");
        printf("Nao pode alterar a avaliacao\n");
        pause();
    } else if (STUDENT_PTR->avaliation.type == final) {
        printf("Aluno inscrito na Avaliacao Final\n\n");
        do {
            printf("Insira { 1- Avaliacao Continua } ou { 2- Avaliacao Final } ? ");
            scanf("%hu", &option);
            clean();
        } while (option != 1 && option != 2);
        if (option == 1) {
            STUDENT_PTR->avaliation.type = continua;
            STUDENT_PTR->continuaAvaliation.situation = avaliacaoCurso;
        } else {
            STUDENT_PTR->avaliation.type = final;
            STUDENT_PTR->finalAvaliation.normalEpoca.situation = avaliacaoCurso;
        }
    }
}

/* Funcao que verifica o tipo de avaliacao do Aluno e reencaminha para a funcao 
 * printAvaliationSituation correspondente. 
 */
void seeSituation(const UserPtr const STUDENT_PTR) {
    clearScreen();
    if (STUDENT_PTR->avaliation.type == continua) {
        clearScreen();
        printAvContinuaSituation(STUDENT_PTR);
        printf("\n");
        pause();
    }
    if (STUDENT_PTR->avaliation.type == final) {
        clearScreen();
        printEpNormalSituation(STUDENT_PTR);
        printf("\n");
        pause();
    }
}

/* Funcao que imprime a situacao de um aluno inscrito em avaliacao continua */
void printAvContinuaSituation(const UserPtr const STUDENT_PTR) {
    // sem notas na avaliacao continua
    if (STUDENT_PTR->continuaAvaliation.notaTTPLancada != 1 && STUDENT_PTR->continuaAvaliation.notaTPLancada != 1) {
        if (STUDENT_PTR->continuaAvaliation.situation = avaliacaoCurso) {
            printf("\nAvaliacao Continua em curso");
        }
        // so nota TTP 
    } else if (STUDENT_PTR->continuaAvaliation.notaTTPLancada == 1 && STUDENT_PTR->continuaAvaliation.notaTPLancada != 1) {
        printf("\nNota TTP Avaliacao Continua = %0.2f", STUDENT_PTR->continuaAvaliation.notaTTP);
        if (STUDENT_PTR->continuaAvaliation.situation == avaliacaoCurso) {
            printf("\nAvaliacao Continua em curso");
        }
        // as 2 notas TTP e TP
    } else if (STUDENT_PTR->continuaAvaliation.notaTTPLancada == 1 && STUDENT_PTR->continuaAvaliation.notaTPLancada == 1) {
        printf("\nNota TTP Avaliacao Continua = %0.2f", STUDENT_PTR->continuaAvaliation.notaTTP);
        printf("\nNota TP  Avaliacao Continua = %0.2f", STUDENT_PTR->continuaAvaliation.notaTP);
        printf("\nMedia Avaliacao Continua = %0.2f", STUDENT_PTR->continuaAvaliation.media);
        if (STUDENT_PTR->continuaAvaliation.situation == aprovado) {
            printf("\nAluno %d aprovado na Avaliacao Continua", STUDENT_PTR->number);
            if (STUDENT_PTR->avaliation.situation == aprovado) {
                printf("\nAluno aprovado a LP!!! - Parabens!!!");
                printf("\nNota Final = %0.2f", STUDENT_PTR->avaliation.notaFinal);
            }
        }
        if (STUDENT_PTR->continuaAvaliation.situation == reprovado) {
            printf("\nAluno %d reprovado na Avaliacao Continua", STUDENT_PTR->number);
            printEpRecursoSituation(STUDENT_PTR);
        }
    }
}

/* Funcao que imprime a situacao de um aluno inscrito em avaliacao Final (Epoca Normal) */
void printEpNormalSituation(const UserPtr const STUDENT_PTR) {
    // sem notas na epoca normal
    if (STUDENT_PTR->finalAvaliation.normalEpoca.notaTTPLancada != 1 && STUDENT_PTR->finalAvaliation.normalEpoca.notaTPLancada != 1) {
        if (STUDENT_PTR->finalAvaliation.normalEpoca.situation = avaliacaoCurso) {
            printf("\nEpoca Normal em curso");
        }
        // so nota TTP 
    } else if (STUDENT_PTR->finalAvaliation.normalEpoca.notaTTPLancada == 1 && STUDENT_PTR->finalAvaliation.normalEpoca.notaTPLancada != 1) {
        printf("\nNota TTP Epoca Normal = %0.2f", STUDENT_PTR->finalAvaliation.normalEpoca.notaTTP);
        if (STUDENT_PTR->finalAvaliation.normalEpoca.situation == avaliacaoCurso) {
            printf("\nEpoca Normal em curso");
        }
        // as 2 notas TTP e TP
    } else if (STUDENT_PTR->finalAvaliation.normalEpoca.notaTTPLancada == 1 && STUDENT_PTR->finalAvaliation.normalEpoca.notaTPLancada == 1) {
        printf("\nNota TTP Epoca Normal = %0.2f", STUDENT_PTR->finalAvaliation.normalEpoca.notaTTP);
        printf("\nNota TP  Epoca Normal = %0.2f", STUDENT_PTR->finalAvaliation.normalEpoca.notaTP);
        printf("\nMedia Epoca Normal = %0.2f", STUDENT_PTR->finalAvaliation.normalEpoca.media);
        if (STUDENT_PTR->finalAvaliation.normalEpoca.situation == aprovado) {
            printf("\nAluno %d aprovado na Epoca Normal", STUDENT_PTR->number);
            if (STUDENT_PTR->avaliation.situation == aprovado) {
                printf("\nAluno aprovado a LP!!! - Parabens!!!");
                printf("\nNota Final = %0.2f", STUDENT_PTR->avaliation.notaFinal);
            }
        }
        if (STUDENT_PTR->finalAvaliation.normalEpoca.situation == reprovado) {
            printf("\nAluno %d reprovado na Epoca Normal", STUDENT_PTR->number);
            printEpRecursoSituation(STUDENT_PTR);
        }
    }
}

/* Funcao que imprime a situacao dos aluno reprovados nas avaliacoes anteriores (Epoca Recurso) */
void printEpRecursoSituation(const UserPtr const STUDENT_PTR) {
    // sem notas na epoca recurso
    if (STUDENT_PTR->finalAvaliation.recursoEpoca.notaTTPLancada != 1 && STUDENT_PTR->finalAvaliation.recursoEpoca.notaTPLancada != 1) {
        if (STUDENT_PTR->finalAvaliation.recursoEpoca.situation = avaliacaoCurso) {
            printf("\n\nEpoca Recurso em curso");
        }
        // so nota TTP 
    } else if (STUDENT_PTR->finalAvaliation.recursoEpoca.notaTTPLancada == 1 && STUDENT_PTR->finalAvaliation.recursoEpoca.notaTPLancada != 1) {
        printf("\n\nNota TTP Epoca Recurso = %0.2f", STUDENT_PTR->finalAvaliation.recursoEpoca.notaTTP);
        if (STUDENT_PTR->finalAvaliation.recursoEpoca.situation == avaliacaoCurso) {
            printf("\nEpoca Recurso em curso");
        }
        // as 2 notas TTP e TP
    } else if (STUDENT_PTR->finalAvaliation.recursoEpoca.notaTTPLancada == 1 && STUDENT_PTR->finalAvaliation.recursoEpoca.notaTPLancada == 1) {
        printf("\n\nNota TTP Epoca Recurso = %0.2f", STUDENT_PTR->finalAvaliation.recursoEpoca.notaTTP);
        printf("\nNota TP Epoca Recurso = %0.2f", STUDENT_PTR->finalAvaliation.recursoEpoca.notaTP);
        printf("\nMedia Epoca Recurso = %0.2f", STUDENT_PTR->finalAvaliation.recursoEpoca.media);
        if (STUDENT_PTR->finalAvaliation.recursoEpoca.situation == aprovado) {
            printf("\nAluno %d aprovado na epoca recurso", STUDENT_PTR->number);
            if (STUDENT_PTR->avaliation.situation == aprovado) {
                printf("\nNota Final = %0.2f", STUDENT_PTR->avaliation.notaFinal);
                printf("\nAluno aprovado a LP!!! - Parabens!!!");
            }
        }
        if (STUDENT_PTR->finalAvaliation.recursoEpoca.situation == reprovado) {
            printf("\nAluno %d reprovado na epoca recurso", STUDENT_PTR->number);
            if (STUDENT_PTR->avaliation.situation == reprovado) {
                printf("\nAluno reprovado a LP");
            }
        }
    }
}

/* Menu com as funcoes dos Utilizadores do tipo docente */
void menuTeacher(UserPtr headPtr, const UserPtr const TEACHER_PTR) {
    short option;
    unsigned int numberFind;
    unsigned int sort;
    unsigned int pagination;
    unsigned int nPagination = 0;
    clearScreen();

    printf("Bem Vindo %s\n\n", TEACHER_PTR->name);
    printf("1-Alterar Dados Proprios \n");
    printf("2-Inserir Utilizador \n");
    printf("3-Remover Utilizador \n");
    printf("4-Alterar Dados Utilizadores \n");
    printf("Ordenação:\n");
    printf("5-Listar alunos ordenados \n"); // perguntar por nome ou por numero
    printf("Paginação:\n");
    printf("6-Listar Alunos Paginacao \n"); // com ou sem paginação e nº alunos/pagina
    printf("7-Lancar Notas \n");
    printf("8-Estatisticas \n");
    printf("0-Logout \n");
    printf("Introduza a sua opcao ");
    scanf("%hu", &option);
    switch (option) {
        case 1:
            clean();
            editUserBasic(TEACHER_PTR);
            printf("Dados Editados com sucesso!!!\n");
            wait(1);
            menuTeacher(headPtr, TEACHER_PTR);
            break;
        case 2:
            clean();
            getUser(&headPtr);
            menuTeacher(headPtr, TEACHER_PTR);
            break;
        case 3:
            clean();
            clearScreen();
            printf("Introduza o numero do utilizador que deseja remover ");
            scanf("%u", &numberFind);
            clean();
            headPtr = removeUser(headPtr, numberFind);
            menuTeacher(headPtr, TEACHER_PTR);
            break;
        case 4:
            clean();
            editUser(findEditUser(headPtr));
            menuTeacher(headPtr, TEACHER_PTR);
            break;
        case 5:
            clean();
            clearScreen();
            printf("Ordenacao { 1- Numero ou 2- Name }");
            scanf("%u", &sort);
            if (sort == 1) {
                headPtr = sortNumber(headPtr);
            } else if (sort == 2) {
                headPtr = sortName(headPtr);
            } else {
                clean();
                printf(MESSAGE_INVALID_CHOICE);
                getchar();
            }
            menuTeacher(headPtr, TEACHER_PTR);
            break;
        case 6:
            clean();
            clearScreen();
            printf("Paginacao { 1- Sim ou 0-Nao }");
            scanf("%u", &pagination);
            if (pagination == 1) {
                do {
                    printf("Quantos alunos por pagina {1-5 alunos}");
                    scanf("%u", &nPagination);
                    clean();
                } while (nPagination <= 0 || nPagination > 5);
                printPag(headPtr, nPagination);
                pause();
            } else if (pagination == 0) {
                printAllStudent(headPtr);
                pause();
            } else {
                clean();
                printf(MESSAGE_INVALID_CHOICE);
                getchar();
            }
            menuTeacher(headPtr, TEACHER_PTR);
            break;
        case 7:
            clean();
            lancaNotas(headPtr, TEACHER_PTR);
            menuTeacher(headPtr, TEACHER_PTR);
            break;
        case 8:
            clean();
            numberStudentApprovedStatistics(headPtr);
            menuTeacher(headPtr, TEACHER_PTR);
            break;
        case 0:
            clean();
            clearScreen();
            printf(MESSAGE_EXIT_MENU);
            scanf("%hu", &option);
            if (option == 1) {
                menuInit(headPtr);
            } else {
                menuTeacher(headPtr, TEACHER_PTR);
            }
            menuTeacher(headPtr, TEACHER_PTR);
            break;
        default:
            clean();
            printf(MESSAGE_INVALID_CHOICE);
            wait(1);
            menuTeacher(headPtr, TEACHER_PTR);
    }
}

/* Funcao pede os dados de um novo user e envia-o para a funcao insertUser onde 
 * é inserido
 */
void getUser(UserPtr *userPtr) {

    unsigned int number;
    char password[SIZEPASS];
    char name[NAMESIZE];
    short typeUser;
    short verify;
    clearScreen();
    printf("Introduza o numero mecanografico ");
    verify = scanf("%u", &number);
    while (!verify) {
        clean();
        printf("Erro - Introduza corretamente numero mecanografico ");
        if (scanf("%u", &number)) {
            verify = 1;
        }
    }
    printf("Introduza a password ");
    scanf("%s", password);
    clean();
    printf("Introduza o nome ");
    scanf("%s", name);
    clean();
    while ((typeUser != docenteReg) && (typeUser != docente) && (typeUser != aluno)) {
        printf("Introduza o tipo de utilizador {1-Docente Regente 2-Docente 3-Aluno} ");
        scanf("%hu", &typeUser);
        clean();
    }
    if (typeUser == aluno) {
        insertUser(userPtr, number, password, name, typeUser, final, avaliacaoCurso);
    } else {
        insertUser(userPtr, number, password, name, typeUser, 0, 0);
    }
}

/* Funcao serve para encontrar o user a editar */
UserPtr findEditUser(const UserPtr const HEAD_PTR) {
    UserPtr findUserPtr = HEAD_PTR;
    unsigned int numberFind;
    unsigned short int verify = 0;
    clearScreen();
    printf("Introduza o numero do utilizador que deseja editar ");
    scanf("%u", &numberFind);
    while (findUserPtr) {
        if (findUserPtr->number == numberFind) {
            verify = 1;
            printf("Encontrado!!!!");
            return findUserPtr;
        }
        findUserPtr = findUserPtr->nextPtr;
    }
    if (verify != 1) {
        clean();
        findEditUser(HEAD_PTR);
    }
}

/* Funcao serve para editar password e name de um utilizador */
void editUser(const UserPtr const USER_PTR) {
    clearScreen();
    editUserBasic(USER_PTR); //edit password and name
    printf("Dados Editados com sucesso!!!\n");
    wait(1);
}

/* Funcao serve para ordenar os users por numero */
UserPtr sortNumber(UserPtr startPtr) {
    UserPtr i = NULL;
    UserPtr j = NULL;
    UserPtr k = NULL;
    UserPtr l = NULL;
    UserPtr tmp = NULL;

    while (l != startPtr->nextPtr) {
        k = i = startPtr;
        j = i->nextPtr;
        while (i != l) {
            if (i->number > j->number) {
                if (i == startPtr) {
                    tmp = j->nextPtr;
                    j->nextPtr = i;
                    i->nextPtr = tmp;
                    startPtr = j;
                    k = j;
                } else {
                    tmp = j->nextPtr;
                    j->nextPtr = i;
                    i->nextPtr = tmp;
                    k->nextPtr = j;
                    k = j;
                }
            } else {
                k = i;
                i = i->nextPtr;
            }
            j = i->nextPtr;
            if (j == l)
                l = i;
        }
    }
    printAllStudent(startPtr);
    pause();
    return startPtr;
}

/* Funcao serve para ordenar os users por name */
UserPtr sortName(UserPtr startPtr) {
    UserPtr i = NULL;
    UserPtr j = NULL;
    UserPtr k = NULL;
    UserPtr l = NULL;
    UserPtr tmp = NULL;

    while (l != startPtr->nextPtr) {
        k = i = startPtr;
        j = i->nextPtr;
        while (i != l) {
            if (strcmp(i->name, j->name) > 0) {
                if (i == startPtr) {
                    tmp = j->nextPtr;
                    j->nextPtr = i;
                    i->nextPtr = tmp;
                    startPtr = j;
                    k = j;
                } else {
                    tmp = j->nextPtr;
                    j->nextPtr = i;
                    i->nextPtr = tmp;
                    k->nextPtr = j;
                    k = j;
                }
            } else {
                k = i;
                i = i->nextPtr;
            }
            j = i->nextPtr;
            if (j == l)
                l = i;
        }
    }
    printAllStudent(startPtr);
    pause();
    return startPtr;
}

/* Funcao serve para imprimir os alunos e suas respetivas informacoes */
void printAllStudent(const UserPtr const ELEMENT_PTR) {
    UserPtr userPtr = ELEMENT_PTR;
    printf("\n");
    while (userPtr) {
        if (userPtr->typeUser == aluno) {
            printf("%d | ", userPtr->number);
            printf("%s\n", userPtr->name);
            if (userPtr->avaliation.type == continua) {
                printf("Avaliacao Continua | ");
            } else if (userPtr->avaliation.type == final) {
                printf("Avaliacao Final | ");
            }
            if (userPtr->avaliation.situation == aprovado) {
                printf("Aprovado\n\n");
            } else if (userPtr->avaliation.situation == reprovado) {
                printf("Reprovado\n\n");
            } else if (userPtr->avaliation.situation == avaliacaoCurso) {
                printf("Avaliacao em curso\n");
            }
            if (userPtr->avaliation.type == continua) {
                printAvContinuaSituation(userPtr);
            } else if (userPtr->avaliation.type == final) {
                printEpNormalSituation(userPtr);
            }
            printf("\n________________________________________________________________________________\n\n");
        }
        userPtr = userPtr->nextPtr;
        if (userPtr == ELEMENT_PTR) {
            userPtr = NULL;
        }
    }
    getchar();
}

/* Funcao serve para imprimir os alunos com paginacao */
void printPag(const UserPtr const HEAD_PTR, const unsigned int N_Pagination) {
    UserPtr userPtr = HEAD_PTR;
    unsigned int ct = 0;
    clearScreen();
    while (userPtr && ct != N_Pagination) {
        if (userPtr->typeUser == aluno) {
            // print the information about the users
            printf("%d | ", userPtr->number);
            printf("%s | ", userPtr->password);
            printf("%s\n", userPtr->name);
            printf("Aluno | ");
            if (userPtr->avaliation.type == continua) {
                printf("Avaliacao Continua | ");
            } else if (userPtr->avaliation.type == final) {
                printf("Avaliacao Final | ");
            }
            if (userPtr->avaliation.situation == aprovado) {
                printf("Aprovado\n\n");
            } else if (userPtr->avaliation.situation == reprovado) {
                printf("Reprovado\n\n");
            } else if (userPtr->avaliation.situation == avaliacaoCurso) {
                printf("Avaliacao em curso\n\n");
            }
            if (userPtr->avaliation.type == continua) {
                printAvContinuaSituation(userPtr);
            } else if (userPtr->avaliation.type == final) {
                printEpNormalSituation(userPtr);
            }
            printf("\n________________________________________________________________________________\n\n");
            ct = ct + 1;
        }
        // move forward to the next element
        userPtr = userPtr->nextPtr;
    }
    if (ct == N_Pagination) {
        printf("Prima qualquer tecla para continuar a imprimir...");
        getchar();
        printPag(userPtr, N_Pagination);
    }
}

/* Funcao que reencaminha para as funcoes de lancar notas correspondentes*/
void lancaNotas(const UserPtr const HEAD_PTR, const UserPtr TEACHER_PTR) {
    unsigned int avaliationInput = 0;
    unsigned int epoca = 0;
    clearScreen();
    if (TEACHER_PTR->typeUser == docenteReg) {
        do {
            printf("Deseja lancar notas na avaliacao {1-Continua ou 2-Final}");
            scanf("%u", &avaliationInput);
            clean();
        } while (avaliationInput != 1 && avaliationInput != 2);
        if (avaliationInput == continua) {
            lancaNotasContinua(HEAD_PTR); // avaliacao continua
        }
        if (avaliationInput == final) {
            clearScreen();
            do {
                printf("Deseja lancar notas na {1-Epoca normal ou 2-Recurso}");
                scanf("%u", &epoca);
                clean();
            } while (epoca != 1 && epoca != 2);
            if (epoca == 1) { // epoca normal
                lancaNotasEpocaNormal(HEAD_PTR);
            } else { // epoca recurso
                lancaNotasEpocaRecurso(HEAD_PTR);
            }
        }
    } else {
        printf("Nao pode inserir notas\n");
        wait(1);
    }
}

/* Funcao serve para lancar notas na Avaliacao Continua */
void lancaNotasContinua(const UserPtr const HEAD_PTR) {
    UserPtr userPtr = HEAD_PTR;
    unsigned int evaluationNumber = 0;
    float nota;
    clearScreen();
    do {
        printf("Deseja lancar notas do {1-TTP ou 2-TP}");
        scanf("%u", &evaluationNumber);
        clean();
    } while (evaluationNumber != 1 && evaluationNumber != 2);
    while (userPtr) {
        if (evaluationNumber == 1 &&
                userPtr->typeUser == aluno &&
                userPtr->avaliation.type == continua &&
                userPtr->continuaAvaliation.notaTTPLancada != 1) {
            do {
                printf("Introduza a nota do teste TP para o aluno %d\n"
                        , userPtr->number);
                scanf("%f", &nota);
                clean();
            } while (nota < 0 || nota > 20);
            userPtr->continuaAvaliation.notaTTP = nota;
            userPtr->continuaAvaliation.notaTTPLancada = 1;
            updateAvContinuaSituation(userPtr);
        }
        if (evaluationNumber == 2 && // TP
                userPtr->typeUser == aluno &&
                userPtr->avaliation.type == continua &&
                userPtr->continuaAvaliation.notaTTPLancada == 1 && // se nota 1ºteste lancada
                userPtr->continuaAvaliation.notaTPLancada != 1) {
            do {
                printf("Introduza a nota do TP para o aluno %d\n"
                        , userPtr->number);
                scanf("%f", &nota);
                clean();
            } while (nota < 0 || nota > 20);
            userPtr->continuaAvaliation.notaTP = nota;
            userPtr->continuaAvaliation.notaTPLancada = 1;
            updateAvContinuaSituation(userPtr);
        }
        if (evaluationNumber == 1) {
            userPtr->firstlancamentoNotas = 1; // primeiro lancamento notas efetuado   
        }
        if (evaluationNumber == 2) {
            userPtr->continuaAvaliation.continuaAvLancada = 1; // avaliacao continua lancada 
        }
        userPtr = userPtr->nextPtr;
    }
}

/* Funcao que serve para fazer update as notas e situacao de um determinado aluno com avaliacao continua*/
void updateAvContinuaSituation(const UserPtr const STUDENT_PTR) {
    if ((STUDENT_PTR->continuaAvaliation.notaTTPLancada == 1) && (STUDENT_PTR->continuaAvaliation.notaTPLancada == 1)) {
        STUDENT_PTR->continuaAvaliation.media = STUDENT_PTR->continuaAvaliation.notaTTP * PERCENTAGE_TTP + STUDENT_PTR->continuaAvaliation.notaTP * PERCENTAGE_TP;
        if (STUDENT_PTR->continuaAvaliation.notaTTP >= NOTA_MIN_TTP && STUDENT_PTR->continuaAvaliation.notaTP >= NOTA_MIN_TP) {
            if (STUDENT_PTR->continuaAvaliation.media >= NOTA_MIN) {
                STUDENT_PTR->continuaAvaliation.situation = aprovado;
                STUDENT_PTR->avaliation.situation = aprovado;
                STUDENT_PTR->avaliation.notaFinal = STUDENT_PTR->continuaAvaliation.media;
            } else {
                STUDENT_PTR->continuaAvaliation.situation = reprovado;
                STUDENT_PTR->finalAvaliation.recursoEpoca.situation = avaliacaoCurso;
            }
        } else {
            STUDENT_PTR->continuaAvaliation.situation = reprovado; //reprovado da continua 
            STUDENT_PTR->finalAvaliation.recursoEpoca.situation = avaliacaoCurso;
        }
    } else {
        STUDENT_PTR->continuaAvaliation.situation = avaliacaoCurso;
        STUDENT_PTR->avaliation.situation = avaliacaoCurso;
    }
}

/* Funcao que serve para lancar as notas de alunos Epoca Normal*/
void lancaNotasEpocaNormal(const UserPtr const HEAD_PTR) {
    UserPtr userPtr = HEAD_PTR;
    unsigned int evaluationNumber = 0;
    float nota;
    clearScreen();
    do {
        printf("Deseja lancar notas do {1-TTP ou 2-TP}");
        scanf("%u", &evaluationNumber);
        clean();
    } while (evaluationNumber != 1 && evaluationNumber != 2);
    while (userPtr) {
        if (evaluationNumber == 1 &&
                userPtr->typeUser == aluno &&
                userPtr->avaliation.type == final &&
                userPtr->continuaAvaliation.continuaAvLancada == 1 &&
                userPtr->finalAvaliation.normalEpoca.notaTTPLancada != 1) {
            do {
                printf("Introduza a nota do teste TP para o aluno %d\n"
                        , userPtr->number);
                scanf("%f", &nota);
                clean();
            } while (nota < 0 || nota > 20);
            userPtr->finalAvaliation.normalEpoca.notaTTP = nota;
            userPtr->finalAvaliation.normalEpoca.notaTTPLancada = 1;
            updateEpNormalSituation(userPtr);
        }
        if (evaluationNumber == 2 &&
                userPtr->typeUser == aluno &&
                userPtr->avaliation.type == final &&
                userPtr->finalAvaliation.normalEpoca.notaTTPLancada == 1 &&
                userPtr->finalAvaliation.normalEpoca.notaTPLancada != 1) {
            do {
                printf("Introduza a nota do TP para o aluno %d\n"
                        , userPtr->number);
                scanf("%f", &nota);
                clean();
            } while (nota < 0 || nota > 20);
            userPtr->finalAvaliation.normalEpoca.notaTP = nota;
            userPtr->finalAvaliation.normalEpoca.notaTPLancada = 1;
            updateEpNormalSituation(userPtr);
        }
        userPtr = userPtr->nextPtr;
    }
}

/* Funcao que serve para fazer update as notas e situacao de um determinado aluno 
 * com avaliacao final (Epoca Normal) */
void updateEpNormalSituation(const UserPtr const STUDENT_PTR) {
    if ((STUDENT_PTR->finalAvaliation.normalEpoca.notaTTPLancada == 1) && (STUDENT_PTR->finalAvaliation.normalEpoca.notaTPLancada == 1)) {
        STUDENT_PTR->finalAvaliation.normalEpoca.media = STUDENT_PTR->finalAvaliation.normalEpoca.notaTTP * PERCENTAGE_TTP + STUDENT_PTR->finalAvaliation.normalEpoca.notaTP * PERCENTAGE_TP;
        if (STUDENT_PTR->finalAvaliation.normalEpoca.notaTTP >= NOTA_MIN_TTP && STUDENT_PTR->finalAvaliation.normalEpoca.notaTP >= NOTA_MIN_TP) {
            if (STUDENT_PTR->finalAvaliation.normalEpoca.media >= NOTA_MIN) {
                STUDENT_PTR->finalAvaliation.normalEpoca.situation = aprovado;
                STUDENT_PTR->avaliation.situation = aprovado;
                STUDENT_PTR->avaliation.notaFinal = STUDENT_PTR->finalAvaliation.normalEpoca.media;
            } else {
                STUDENT_PTR->finalAvaliation.normalEpoca.situation = reprovado;
                STUDENT_PTR->finalAvaliation.recursoEpoca.situation = avaliacaoCurso;
            }
        } else {
            STUDENT_PTR->finalAvaliation.normalEpoca.situation = reprovado;
            STUDENT_PTR->finalAvaliation.recursoEpoca.situation = avaliacaoCurso;
        }
    } else {
        STUDENT_PTR->finalAvaliation.normalEpoca.situation = avaliacaoCurso;
        STUDENT_PTR->avaliation.situation = avaliacaoCurso;
    }
}

/* Funcao serve para lancar notas na Epoca de Recurso */
void lancaNotasEpocaRecurso(const UserPtr const HEAD_PTR) {
    UserPtr userPtr = HEAD_PTR;
    unsigned int evaluationNumber = 0;
    clearScreen();
    do {
        printf("Deseja lancar notas do {1-TTP ou 2-TP}");
        scanf("%u", &evaluationNumber);
        clean();
    } while (evaluationNumber != 1 && evaluationNumber != 2);
    while (userPtr) {
        if (evaluationNumber == 1 && // teste TP (TTP)
                userPtr->typeUser == aluno &&
                (userPtr->continuaAvaliation.situation == reprovado ||
                userPtr->finalAvaliation.normalEpoca.situation == reprovado) &&
                userPtr->finalAvaliation.recursoEpoca.notaTTPLancada != 1) {
            verifyPreviousNotasTTP(userPtr);
        }
        if (evaluationNumber == 2 && // trabalho Pratico (TP)
                userPtr->typeUser == aluno &&
                (userPtr->continuaAvaliation.situation == reprovado ||
                userPtr->finalAvaliation.normalEpoca.situation == reprovado) &&
                userPtr->finalAvaliation.recursoEpoca.notaTTPLancada == 1 &&
                userPtr->finalAvaliation.recursoEpoca.notaTPLancada != 1) {
            verifyPreviousNotasTP(userPtr);
        }
        userPtr = userPtr->nextPtr;
    }
}

/* Funcao serve para verificar notas anteriores do TTP de um determinando aluno
 * com a finalidade de verificar se o mesmo tem notas minimas e tambem
 * lancar notas na epoca de recurso para o TTP
 */
void verifyPreviousNotasTTP(const UserPtr const STUDENT_PTR) {
    float nota;
    short option;
    // suas notas da avaliacao continua ( se tem nota minima no TTP)
    if (STUDENT_PTR->avaliation.type == continua && STUDENT_PTR->continuaAvaliation.notaTTP >= NOTA_MIN_TTP) {
        printf("\nO aluno %d ja teve nota minima no TTP em epoca continua\n", STUDENT_PTR->number);
        printf("Teve %0.2f\n", STUDENT_PTR->continuaAvaliation.notaTTP);
        do { // se aluno reprovado tentou alterar nota TTP
            printf("Deseja alterar a sua nota nesta parte do exame recurso{ 1-Sim 0-Nao } ");
            scanf("%hu", &option);
            clean();
        } while (option != 1 && option != 0);

        if (option == 1) {
            do {
                printf("Introduza a nova nota do TTP para o aluno %d\n", STUDENT_PTR->number);
                scanf("%f", &nota);
                clean();
            } while (nota < 0 || nota > 20);
            STUDENT_PTR->finalAvaliation.recursoEpoca.notaTTP = nota;
            STUDENT_PTR->finalAvaliation.recursoEpoca.notaTTPLancada = 1;
            updateEpRecursoSituation(STUDENT_PTR);
        } else {
            //vai ficar com a nota do TTP da epoca continua na nota do TTP na epoca recurso
            STUDENT_PTR->finalAvaliation.recursoEpoca.notaTTP = STUDENT_PTR->continuaAvaliation.notaTTP;
            STUDENT_PTR->finalAvaliation.recursoEpoca.notaTTPLancada = 1;
            updateEpRecursoSituation(STUDENT_PTR);
        }
        // suas notas da Epoca Normal ( se tem nota minima no TTP)
    } else if (STUDENT_PTR->avaliation.type == final && STUDENT_PTR->finalAvaliation.normalEpoca.notaTTP >= NOTA_MIN_TTP) {
        printf("\nO aluno %d ja teve nota minima no TTP em epoca normal\n", STUDENT_PTR->number);
        printf("Teve %0.2f\n", STUDENT_PTR->finalAvaliation.normalEpoca.notaTTP);
        do {// se aluno reprovado e tentou alterar nota TTP
            printf("Deseja alterar a sua nota nesta parte do exame recurso{ 1-Sim 0-Nao } ");
            scanf("%hu", &option);
            clean();
        } while (option != 1 && option != 0);

        if (option == 1) {
            do {
                printf("Introduza a nova nota do TTP para o aluno %d\n"
                        , STUDENT_PTR->number);
                scanf("%f", &nota);
                clean();
            } while (nota < 0 || nota > 20);
            STUDENT_PTR->finalAvaliation.recursoEpoca.notaTTP = nota;
            STUDENT_PTR->finalAvaliation.recursoEpoca.notaTTPLancada = 1;
            updateEpRecursoSituation(STUDENT_PTR);
        } else {
            //vai ficar com a nota do teste TTP da epoca normal na nota do TTP na epoca recurso
            STUDENT_PTR->finalAvaliation.recursoEpoca.notaTTP = STUDENT_PTR->finalAvaliation.normalEpoca.notaTTP;
            STUDENT_PTR->finalAvaliation.recursoEpoca.notaTTPLancada = 1;
            updateEpRecursoSituation(STUDENT_PTR);
        }
    } else { // se nao tem notas minimas 
        do {
            printf("\nIntroduza a nota do teste TP para o aluno %d\n"
                    , STUDENT_PTR->number);
            scanf("%f", &nota);
            clean();
        } while (nota < 0 || nota > 20);
        STUDENT_PTR->finalAvaliation.recursoEpoca.notaTTP = nota;
        STUDENT_PTR->finalAvaliation.recursoEpoca.notaTTPLancada = 1;
        updateEpRecursoSituation(STUDENT_PTR);
    }
}

/* Funcao serve para verificar notas anteriores do TP de um determinando aluno
 * com a finalidade de verificar se o mesmo tem notas minimas e tambem
 * lancar notas na epoca de recurso para o TP
 */
void verifyPreviousNotasTP(const UserPtr const STUDENT_PTR) {
    float nota;
    int option;
    // na avaliacao continua
    if (STUDENT_PTR->avaliation.type == continua && STUDENT_PTR->continuaAvaliation.notaTP >= NOTA_MIN_TP) {
        printf("\nO aluno %d ja teve nota minima nesta parte em epoca continua\n", STUDENT_PTR->number);
        printf("Teve %0.2f\n", STUDENT_PTR->continuaAvaliation.notaTP);
        do { // se aluno reprovado tentou alterar nota TP
            printf("Deseja alterar a sua nota nesta parte do exame recurso{ 1-Sim 0-Nao } ");
            scanf("%d", &option);
        } while (option != 1 && option != 0);
        if (option == 1) {
            do {
                printf("Introduza a nova nota do TP para o aluno %d\n", STUDENT_PTR->number);
                scanf("%f", &nota);
            } while (nota < 0 || nota > 20);
            STUDENT_PTR->finalAvaliation.recursoEpoca.notaTP = nota;
            STUDENT_PTR->finalAvaliation.recursoEpoca.notaTPLancada = 1;
            updateEpRecursoSituation(STUDENT_PTR);
        } else {
            //vai ficar com a nota do TP da epoca continua na nota do TP na epoca recurso
            STUDENT_PTR->finalAvaliation.recursoEpoca.notaTP = STUDENT_PTR->continuaAvaliation.notaTP;
            STUDENT_PTR->finalAvaliation.recursoEpoca.notaTPLancada = 1;
            updateEpRecursoSituation(STUDENT_PTR);
        }
        // na avaliacao final epoca normal
    } else if (STUDENT_PTR->avaliation.type == final && STUDENT_PTR->finalAvaliation.normalEpoca.notaTP >= NOTA_MIN_TP) {
        printf("\nO aluno %d ja teve nota minima nesta parte em epoca normal\n", STUDENT_PTR->number);
        printf("Teve %0.2f\n", STUDENT_PTR->finalAvaliation.normalEpoca.notaTP);
        do { // se aluno reprovado e tentou alterar nota TP
            printf("Deseja alterar a sua nota nesta parte do exame recurso{ 1-Sim 0-Nao } ");
            scanf("%d", &option);
        } while (option != 1 && option != 0);

        if (option == 1) {
            do {
                printf("Introduza a nova nota do TP para o aluno %d\n", STUDENT_PTR->number);
                scanf("%f", &nota);
            } while (nota < 0 || nota > 20);
            STUDENT_PTR->finalAvaliation.recursoEpoca.notaTP = nota;
            STUDENT_PTR->finalAvaliation.recursoEpoca.notaTPLancada = 1;
            updateEpRecursoSituation(STUDENT_PTR);
        } else {
            //vai ficar com a nota do teste TP da epoca normal na nota do TP na epoca recurso
            STUDENT_PTR->finalAvaliation.recursoEpoca.notaTP = STUDENT_PTR->finalAvaliation.normalEpoca.notaTP;
            STUDENT_PTR->finalAvaliation.recursoEpoca.notaTPLancada = 1;
            updateEpRecursoSituation(STUDENT_PTR);
        }
    } else {
        do {
            printf("\nIntroduza a nota do TP para o aluno %d\n"
                    , STUDENT_PTR->number);
            scanf("%f", &nota);
        } while (nota < 0 || nota > 20);
        STUDENT_PTR->finalAvaliation.recursoEpoca.notaTP = nota;
        STUDENT_PTR->finalAvaliation.recursoEpoca.notaTPLancada = 1;
        updateEpRecursoSituation(STUDENT_PTR);
    }
}

/* Funcao que serve para fazer update as notas e situacao de um determinado aluno 
 * na Epoca Recurso */
void updateEpRecursoSituation(const UserPtr const STUDENT_PTR) {
    if ((STUDENT_PTR->finalAvaliation.recursoEpoca.notaTTPLancada == 1) && (STUDENT_PTR->finalAvaliation.recursoEpoca.notaTPLancada == 1)) {
        STUDENT_PTR->finalAvaliation.recursoEpoca.media = STUDENT_PTR->finalAvaliation.recursoEpoca.notaTTP * PERCENTAGE_TTP + STUDENT_PTR->finalAvaliation.recursoEpoca.notaTP * PERCENTAGE_TP;
        if (STUDENT_PTR->finalAvaliation.recursoEpoca.notaTTP >= NOTA_MIN_TTP && STUDENT_PTR->finalAvaliation.recursoEpoca.notaTP >= NOTA_MIN_TP) {
            if (STUDENT_PTR->finalAvaliation.recursoEpoca.media >= NOTA_MIN) {
                STUDENT_PTR->finalAvaliation.recursoEpoca.situation = aprovado;
                STUDENT_PTR->avaliation.situation = aprovado; // situacao final de todo ano a LP
                STUDENT_PTR->avaliation.notaFinal = STUDENT_PTR->finalAvaliation.recursoEpoca.media;
            } else {
                STUDENT_PTR->finalAvaliation.recursoEpoca.situation = reprovado;
                STUDENT_PTR->avaliation.situation = reprovado; // situacao final de todo ano a LP
                STUDENT_PTR->avaliation.notaFinal = STUDENT_PTR->finalAvaliation.recursoEpoca.media;
            }
        } else {
            STUDENT_PTR->finalAvaliation.recursoEpoca.situation = reprovado; //reprovado em recurso
            STUDENT_PTR->avaliation.situation = reprovado; /// situacao final de todo ano a LP
            STUDENT_PTR->avaliation.notaFinal = STUDENT_PTR->finalAvaliation.recursoEpoca.media;
        }
    } else {
        STUDENT_PTR->finalAvaliation.recursoEpoca.situation = avaliacaoCurso;
        STUDENT_PTR->avaliation.situation = avaliacaoCurso;
    }
}

/* Funcao serve para apresentar estatisticas em relacao aos alunos*/
void numberStudentApprovedStatistics(const UserPtr const USER_PTR) {
    UserPtr userPtr = USER_PTR;
    clearScreen();
    unsigned int numberApprovedAvContinua = 0;
    unsigned int numberStudentsAvContinua = 0;
    float percentageApprovedStudentContinua = 0;
    unsigned int numberApprovedEpNormal = 0;
    unsigned int numberStudentsEpNormal = 0;
    float percentageApprovedStudentEpNormal = 0;
    unsigned int numberApprovedEpRecurso = 0;
    unsigned int numberStudentsEpRecurso = 0;
    float percentageApprovedStudentEpRecurso = 0;
    unsigned int continuaStatisticsExist = 0;
    unsigned int normalStatisticsExist = 0;
    unsigned int recursoStatisticsExist = 0;

    while (userPtr) {
        if (userPtr->typeUser == aluno) {
            if (userPtr->avaliation.type == continua &&
                    userPtr->continuaAvaliation.notaTTPLancada == 1 &&
                    userPtr->continuaAvaliation.notaTPLancada == 1) {
                numberStudentsAvContinua++;
                continuaStatisticsExist = 1;
                if (userPtr->continuaAvaliation.situation == aprovado) {
                    numberApprovedAvContinua++;
                }
            } else if (userPtr->avaliation.type == final &&
                    userPtr->finalAvaliation.normalEpoca.notaTTPLancada == 1 &&
                    userPtr->finalAvaliation.normalEpoca.notaTPLancada == 1) {
                numberStudentsEpNormal++;
                normalStatisticsExist = 1;
                if (userPtr->finalAvaliation.normalEpoca.situation == aprovado) {
                    numberApprovedEpNormal++;
                }
            }

            if (userPtr->finalAvaliation.recursoEpoca.notaTTPLancada == 1 &&
                    userPtr->finalAvaliation.recursoEpoca.notaTPLancada == 1) {
                numberStudentsEpRecurso++;
                recursoStatisticsExist = 1;
                if (userPtr->finalAvaliation.recursoEpoca.situation == aprovado) {
                    numberApprovedEpRecurso++;
                }
            }
        }
        userPtr = userPtr->nextPtr;
    }

    if (continuaStatisticsExist == 0 && normalStatisticsExist == 0 && recursoStatisticsExist == 0) {
        printf("Sem estatisticas de momento\n");
    } else {
        if (continuaStatisticsExist == 1) {
            printf("Numero aprovados Avaliacao Continua -> %u\n", numberApprovedAvContinua);
            percentageApprovedStudentContinua = (numberApprovedAvContinua * 100) / numberStudentsAvContinua;
            printf("Percentagem aprovados Avaliacao Continua -> %0.2f\n", percentageApprovedStudentContinua);
        }
        if (normalStatisticsExist == 1) {
            printf("Numero aprovados Epoca Normal -> %u\n", numberApprovedEpNormal);
            percentageApprovedStudentEpNormal = (numberApprovedEpNormal * 100) / numberStudentsEpNormal;
            printf("Percentagem aprovados Epoca Normal-> %0.2f\n", percentageApprovedStudentEpNormal);
        }
        if (recursoStatisticsExist == 1) {
            printf("Numero aprovados Epoca Recurso -> %u\n", numberApprovedEpRecurso);
            percentageApprovedStudentEpRecurso = (numberApprovedEpRecurso * 100) / numberStudentsEpRecurso;
            printf("Percentagem aprovados Epoca Recurso-> %0.2f\n", percentageApprovedStudentEpRecurso);
        }
    }
    pause();
}






