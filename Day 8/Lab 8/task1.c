#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define ANIMAL_NODE 0
#define QUESTION_NODE 1

typedef struct zooNode {
    int type;
    char *animalName;
    char *questionText;
    struct zooNode *noAnimal;
    struct zooNode *yesAnimal;
} zooNode;

zooNode *topNode;

/* Remove the newline from the end of a string, if there is one */
void killNewline (char *str) {
    int len = strlen(str);

    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

zooNode *createAnimalNode (char *animalName) {

    zooNode *p = malloc(sizeof(zooNode));
    p->type = ANIMAL_NODE;
    p->animalName = strdup(animalName);
    p->questionText = NULL;
    p->noAnimal = NULL;
    p->yesAnimal = NULL;
    return p;

}

zooNode *createQuestionNode (char *questionText, zooNode *noAnimal, zooNode *yesAnimal) {

    zooNode *p = malloc(sizeof(zooNode));
    p->type = QUESTION_NODE;
    p->animalName = NULL;
    p->questionText = strdup(questionText);
    p->noAnimal = noAnimal;
    p->yesAnimal = yesAnimal;
    return p;

}

void interact (zooNode *node, zooNode *parent, int yesLink) {

    char inputBuffer[100];

    if (node->type == QUESTION_NODE) {

        printf("%s\n", node->questionText);
        fgets(inputBuffer,100,stdin);
        killNewline(inputBuffer); 

        if (strcmp(inputBuffer, "yes") == 0 || inputBuffer[0] == 'y') {

            interact(node->yesAnimal, node, 1);

        } else if(strcmp(inputBuffer, "no") == 0 || inputBuffer[0] == 'n')  {

            interact(node->noAnimal, node, 0);

        } else return;

    } else if (node->type == ANIMAL_NODE) {

        printf("Is it a %s?\n", node->animalName);
        fgets(inputBuffer,100,stdin);
        killNewline(inputBuffer);

        if (strcmp(inputBuffer, "yes") == 0 || inputBuffer[0] == 'y') {

            printf("I guessed your animal!\n");
            return;

        } else if(strcmp(inputBuffer, "no") == 0 || inputBuffer[0] == 'n')  {

            /* yesAnimal, noAnimal */
            /* is and has */
            char animalName[200];
            char difference[200];
            char questionStr[200];

            printf("What is your animal called?\n");
            fgets(animalName,100,stdin);
            killNewline(animalName);

            printf("How would you tell a %s from a %s?  A %s (has or is): \n",
            animalName, node->animalName, animalName);
            fgets(difference,100,stdin);
            killNewline(difference);

            if (strncmp(difference, "is ", 3) == 0) {

                sprintf(questionStr, "Is it %s?", difference + 3);
                
            } else if (strncmp(difference, "has ", 4) == 0) {

                sprintf(questionStr, "Does it have %s?", difference + 4);

            } else return;

            zooNode *newAnimal = createAnimalNode(animalName);
            zooNode *newQuestion = createQuestionNode(questionStr, node, newAnimal);

            if (parent == NULL) {
                topNode = newQuestion;
            } else if (yesLink) {
                parent->yesAnimal = newQuestion;
            } else {
                parent->noAnimal = newQuestion;
            }

            printf("Thanks for telling me about the %s.\n", animalName);

        } else return;

    }
}

int main () {
    topNode = createAnimalNode("Lion");

    while (1) {
        printf("\nThink of an animal.\n");
        interact(topNode, NULL, 0);
    }

    return 0;
}
