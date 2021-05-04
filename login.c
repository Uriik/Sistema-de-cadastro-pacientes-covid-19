#include <stdio.h>  // padrão
#include <stdlib.h> // padrão
#include <string.h> // Essa biblioteca serve para usar os structs e manipulação de strings
#include <conio.h>  // Usada para pausar o sistema
#include <time.h>   // biblioteca para pegar data e hora atuais
#include <locale.h>
#include <stdbool.h>

struct tm pegarDataSistema()
{
    time_t temp = time(NULL);

    struct tm dataAtual = *localtime(&temp);
    dataAtual.tm_year += 1900; // Compensa a forma como é contado o ano

    return dataAtual;
}

int calcularIdade(struct tm *dataAtual, struct tm *dataNascimento)
{
    int idade = dataAtual->tm_year - dataNascimento->tm_year;

    /*
     * Verifica as condições para determinar se já fez aniversário.
     * Caso não tenha feito ainda, decrementamos a idade para compensar.
     */
    if (dataAtual->tm_mon < dataNascimento->tm_mon)
    {
        idade -= 1;
    }
    else if (dataAtual->tm_mon == dataNascimento->tm_mon)
    {
        if (dataAtual->tm_mday < dataNascimento->tm_mday)
        {
            idade -= 1;
        }
    }

    return idade;
}

typedef struct
{
    char login[30]; // vetor login da struct pessoa
    char senha[30]; // vetor senha da struct pessoa
} pessoa;
pessoa p[1]; // diminuindo o nome da struct para "p" e o "[1]" é o máximo de pessoas com logins e senhas

struct cadastro
{
    char paciente[60];
    char cpf[12];
    char telefone[12];
    char endereco[30];
    int numero;
    char bairro[15];
    char cidade[15];
    char estado[15];
    int cep;
    struct tm nasc;
    char email[40];
    int diagnostico;
    char comorbidade[50];
};

struct cadastro CADASTRO;

char login[30]; // responsável por armazenar a senha inserida pelo usuário
char senha[30]; // responsável por armazenar a senha inserida pelo usuário

void cabecalho()
{

    printf("=========================================================\n");
    printf("           =SISTEMA DE CADASTRO COVID 19=                \n");
    printf("                 MINISTERIO DA SAUDE                     \n");
    printf("                      BEM VINDO                          \n");
    printf("=========================================================\n");
    printf("\n");
    printf("Data: %s..........Hora: %s", __DATE__, __TIME__);
    printf("\n \n");
}

void criarPaciente()
{
    system("cls");
    fflush(stdin);
    printf("NOME DO PACIENTE: ");
    gets(CADASTRO.paciente);
    fflush(stdin);
    printf("CPF: ");
    gets(CADASTRO.cpf);
    fflush(stdin);
    printf("Telefone: ");
    gets(CADASTRO.telefone);
    fflush(stdin);
    printf("Endereco: ");
    gets(CADASTRO.endereco);
    fflush(stdin);
    printf("Numero: ");
    scanf("%d", &CADASTRO.numero);
    fflush(stdin);
    printf("Bairro: ");
    gets(CADASTRO.bairro);
    fflush(stdin);
    printf("Cidade: ");
    gets(CADASTRO.cidade);
    fflush(stdin);
    printf("Estado: ");
    gets(CADASTRO.estado);
    fflush(stdin);
    printf("Cep: ");
    scanf("%d", &CADASTRO.cep);
    fflush(stdin);
    printf("Dia do Nascimento: ");
    scanf("%d", &CADASTRO.nasc.tm_mday);
    fflush(stdin);
    printf("Mes do Nascimento: ");
    scanf("%d", &CADASTRO.nasc.tm_mon);
    fflush(stdin);
    printf("Ano do Nascimento: ");
    scanf("%d", &CADASTRO.nasc.tm_year);
    fflush(stdin);
    printf("E-mail: ");
    gets(CADASTRO.email);
    fflush(stdin);
    printf("Data do diagnostico: ");
    scanf("%d", &CADASTRO.diagnostico);
    fflush(stdin);
    printf("O paciente possui alguma comorbidade (S/N)?");
    gets(CADASTRO.comorbidade);
    printf(CADASTRO.comorbidade);
    getch();

    //return CADASTRO;
    REGISTRO();
    REGISTRO_RISCO(&CADASTRO);
}

void REGISTRO_RISCO(struct cadastro *pacienteP)
{
    struct tm dataAtual = pegarDataSistema();
    int idade = calcularIdade(&dataAtual, (&pacienteP->nasc));
    bool comorbidade = (strcmp(pacienteP->comorbidade, "S") == 0);
    bool shouldWrite = idade >= 65 || comorbidade;
    if (!shouldWrite)
    {
        printf("A IDADE É: %d", idade);
        getch();
        return;
    }

    FILE *r;
    r = fopen("PACIENTES NO GRUPO DE RISCO.txt", "a");
    if (r == NULL)
    {
        printf("ERRO DE ABERTURA DO ARQUIVO\n");
        exit(1);
    }
    fprintf(r, "%d", pacienteP->cep);
    fprintf(r, " \n ");
    fprintf(r, "%d", idade);
    fprintf(r, " \n ");
    fprintf(r, "------------------------------------------------------------\n");
    fclose(r);
    printf("\n\n");
}

void REGISTRO()
{
    FILE *r;

    r = fopen("REGISTRO DE PACIENTES.txt", "a");
    if (r == NULL)
    {
        printf("ERRO DE ABERTURA DO ARQUIVO\n");
        exit(1);
    }

    fputs(CADASTRO.paciente, r);
    fprintf(r, " \n ");
    fputs(CADASTRO.cpf, r);
    fprintf(r, " \n ");
    fputs(CADASTRO.telefone, r);
    fprintf(r, " \n ");
    fputs(CADASTRO.endereco, r);
    fprintf(r, " \n ");
    fprintf(r, "%d", CADASTRO.numero);
    fprintf(r, " \n ");
    fputs(CADASTRO.bairro, r);
    fprintf(r, " \n ");
    fputs(CADASTRO.cidade, r);
    fprintf(r, " \n ");
    fputs(CADASTRO.estado, r);
    fprintf(r, " \n ");
    fprintf(r, "%d", CADASTRO.cep);
    fprintf(r, " \n ");
    fprintf(r, "%d", CADASTRO.nasc.tm_mday);
    fprintf(r, " \n ");
    fprintf(r, "%d", CADASTRO.nasc.tm_mon);
    fprintf(r, " \n ");
    fprintf(r, "%d", CADASTRO.nasc.tm_year);
    fprintf(r, " \n ");
    fputs(CADASTRO.email, r);
    fprintf(r, " \n ");
    fprintf(r, "%d", CADASTRO.diagnostico);
    fprintf(r, " \n ");
    fputs(CADASTRO.comorbidade, r);
    fprintf(r, " \n ");
    fprintf(r, "------------------------------------------------------------\n");
    fclose(r);
    printf("\n\n");
}

int main()
{

    char login[30]; // responsável por armazenar a senha inserida pelo usuário
    char senha[30]; // responsável por armazenar a senha inserida pelo usuário

    strcpy(p[0].login, "admin"); // Definindo o login "admin" na struct
    strcpy(p[0].senha, "123");   // Definindo a senha "123"  na struct

    int logged = 0;

    do
    {

        system("cls");
        cabecalho();

        printf("\nLOGIN: ");
        scanf("%s", login); // armazenando os dados inseridos pelo usuário para o vetor login que está dentro da função main

        printf("\nSENHA: ");
        scanf("%s", senha); // armazenando os dados inseridos pelo usuário para o vetor senha que está dentro da função main

        logged = ((strcmp(login, p[0].login) == 0) && (strcmp(senha, p[0].senha) == 0)); // A função strcmp é responsável por comparar string com string

    } while (!logged); // se os vetores de dentro da struct tiver os mesmos dados do vetor interno da função main, usuário será logado.

    setlocale(LC_ALL, "Portuguese");
    int opcao;

    do
    {
        system("cls");
        cabecalho();
        printf("1- CADASTRAR PACIENTES\n");
        printf("2- SAIR\n");
        printf("\n\n");
        printf("DIGITE A OPCAO DESEJADA: ");
        scanf("%d", &opcao);

        switch (opcao)
        {

        case 1:
            printf("\n\n");
            criarPaciente();
            break;

        case 2:
            printf("OBRIGADO POR SUA VISITA!!!");
            getch();
            break;

        default:
            printf("OPCAO INVALIDA!\n");
            getch();
            break;
        }

    } while (opcao != 2);
}