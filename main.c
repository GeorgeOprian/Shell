#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

char functiiExecutate[] = "cp mkdir ls cd du mv rm pwd exit cat echo rmdir help";


int argC;

char *shell_citeste_linie(void)
{
    char *linie = NULL;
    size_t bufsize = 0;
    getline(&linie, &bufsize, stdin);
    return linie;
}
char **shell_split_linie(char *linie)
{
    argC = 0;
    char **argv;
    char *word;
    int poz = 0;
    argv = (char **)malloc(100 * sizeof(char *));
    word = strtok(linie, " ");
    while (word)
    {
        argv[poz++] = word;
        argC++;
        word = strtok(NULL, " ");
    }
    argv[poz] = NULL;
    argv[poz - 1][strlen(argv[poz - 1]) - 1] = '\0';
    if (strstr(functiiExecutate, argv[0]) == NULL)
    {
        printf("Functia <%s> nu este implemtata!\n", argv[0]);
        return NULL;
    }
    return argv;
}

int shell_executa(char **args)
{
    pid_t pid;
    pid = fork();
    if (pid < 0)
    {
        printf("eroare fork");
    }
    if (pid == 0)
    {
        char cale[100];
        strcpy(cale, "/bin/");
        strcat(cale, args[0]);
    
        execve(cale, args, NULL);
    }
    else
    {
        wait(NULL);
    }
  return 1;
}
void shell_print_help (void){
    printf("Functii implementate:\n");
    printf("- cp copiaza un fisier sau director sursa in unul destinatie\n");
    printf("- mkdir creaza un director\n");
    printf("- ls afiseaza un director\n");
    printf("- rm sterge un fisier\n");
    printf("- pwd afiseaza calea absoluta a directorului curent\n");
    printf("- cat afiseaza continutul unui fiser in shell\n");
    printf("- rmdir sterge un folder\n");
    printf("- exit va opri executia shell-ului\n");

}
void shell_loop(void)
{
    char *linie;
    char **args;
    int status = 1;
    do
    {
        printf("$ ");
        linie = shell_citeste_linie();
        args = shell_split_linie(linie);

        if (strcmp(args[0], "help") == 0){
            shell_print_help();
        }

        if (strcmp(args[0], "exit") == 0){
            exit(0);
        }
        status = shell_executa(args);
        free(linie);
        free(args);
    } while (status);
    }

int main(int argc, char **argv)
{
    shell_loop();
    return 0;
}
