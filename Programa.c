
#include <stdio.h>
#include <string.h>

/**********************************************
            Declaração das structs
**********************************************/

typedef struct
{
    int dia;
    int mes;
    int ano;
} Data;

typedef struct
{
    char nome[50];
    char telefone[15];
    Data aniversario;
} Cliente;

typedef struct
{
    Cliente cliente;
    char modelo[50];
    char placa[10];
    int anoFabricacao;
    float kilometragem;
} Carro;

typedef struct
{
    int identificador; // valor sempre crescente (nunca repete) ("auto_incremental")
    Data dataDoServico;
    Carro carro;
    int tipoDeServico;
    char pago;
} Servico;

/**********************************************
            Declaração das funções
**********************************************/

void cadastrarCliente(void);
void cadastrarCarro(void);

int validarNome(char nome[50]);
int contemSomenteLetras(char text[50]);

int validarTelefone(char telefone[15]);
int contemSomenteNumeros(char text[15]);

int validarAnoFabricacao(int ano);
int validarData(Data dt);
int anoBissexto(int ano);
Cliente VincularCliente(char nomeCliente[50]);

/**********************************************
        Declaração das variaveis Globais
**********************************************/

int g_qtdClientes = 0;
int g_qtdCarros = 0;
Cliente g_clientes[10];
Carro g_carros[10];

/**********************************************
                    Int main()
**********************************************/

int main()
{

    cadastrarCliente();
    cadastrarCarro();
    cadastrarCarro();

    int i = 0;
    for(i = 0; i < g_qtdCarros; i++) {
        printf("%s\n", g_carros[i].cliente.nome);
    }

    return 0;
}

/**********************************************
                    Funções
**********************************************/

void cadastrarCliente(void)
{
    int validar = 0;
    do // Loop. Recebe o nome e checa se é Válido
    {
        printf("Digite seu nome: ");
        fgets(g_clientes[g_qtdClientes].nome, 50, stdin);
        g_clientes[g_qtdClientes].nome[strlen(g_clientes[g_qtdClientes].nome) - 1] = '\0';

        validar = validarNome(g_clientes[g_qtdClientes].nome);
        if (!validar)
        {
            printf(">>>Nome Invalido<<<\n");
        }

    } while (!validar);

    do // Loop. Recebe o telefone e checa se é Válido
    {
        printf("Digite seu telefone: ");
        fgets(g_clientes[g_qtdClientes].telefone, 15, stdin);
        g_clientes[g_qtdClientes].telefone[strlen(g_clientes[g_qtdClientes].telefone) - 1] = '\0';

        validar = validarTelefone(g_clientes[g_qtdClientes].telefone);
        if (!validar)
        {
            printf(">>>Telefone Invalido<<<\n");
        }

    } while (!validar);

    g_qtdClientes++; // (+ 1) toda vez que um cliente é cadastrado. Evitando que os dados de novos clientes sejam sobreponham os dados dos clientes antigos.
}

void cadastrarCarro(void)
{
    int validar = 0;
    char nome[50];

    printf("Digite o nome do cliente: ");
    fgets(nome, 50, stdin);
    nome[strlen(nome) - 1] = '\0';
    g_carros[g_qtdCarros].cliente = VincularCliente(nome);

    printf("Digite o modelo do carro: ");
    fgets(g_carros[g_qtdCarros].modelo, 50, stdin);
    g_carros[g_qtdCarros].modelo[strlen(g_carros[g_qtdCarros].modelo) - 1] = '\0';

    printf("Digite a placa do carro: ");
    fgets(g_carros[g_qtdCarros].placa, 10, stdin);
    g_carros[g_qtdCarros].placa[strlen(g_carros[g_qtdCarros].placa) - 1] = '\0';


    printf("Digite a kilometragem do carro: ");
    scanf("%f", &g_carros[g_qtdCarros].kilometragem);

    do // Loop. Recebe o ano e checa se é Válido
    {
        printf("Digite o ano de fabricacao do carro: ");
        scanf("%d", &g_carros[g_qtdCarros].anoFabricacao);
        getchar();

        validar = validarAnoFabricacao(g_carros[g_qtdCarros].anoFabricacao);
        if (!validar)
        {
            printf(">>>Ano posterior ao desse<<<");
        }

    } while (!validar);

    g_qtdCarros++; // (+ 1) toda vez que um carro é cadastrado. Evitando que os dados de novos clientes sejam sobreponham os dados dos clientes antigos.
}
int validarNome(char nome[50])
{ // (1) Verdadeiro -- (0) Falso
    if ((strlen(nome) > 5) && contemSomenteLetras(nome) && (nome[0] != ' '))
    {
        return 1; // -- Nome Válido
    }
    else
    {
        return 0; // -- Nome Inválido
    }
}

int contemSomenteLetras(char text[50])
{ // (1) Verdadeiro -- (0) Falso

    int tam = strlen(text);
    int i = 0;
    for (i = 0; i < tam; i++) {
        if ((65 <= text[i] && text[i] <= 90) || (97 <= text[i] && text[i] <= 122))
        {
            continue;
        }
        else
        {
            return 0; // -- Outros Caracteres
        }
    }
    return 1; // -- Somente Letras
}

int validarTelefone(char telefone[15])
{ // (1) Verdadeiro -- (0) Falso
    if (telefone[0] == '0' && (strlen(telefone) == 11 || strlen(telefone) == 12) && contemSomenteNumeros(telefone))
    {
        return 1; // -- Telefone Válido
    }
    else
    {
        return 0; // -- Telefone Inválido
    }
}

int contemSomenteNumeros(char text[15])
{

    int tam = strlen(text);
    int i = 0;
    for (i = 0; i < tam; i++)
    {
        if (48 <= text[i] && text[i] <= 57)
        {
            continue;
        }
        else
        {
            return 0; // -- Outros Caracteres
        }
    }
    return 1; // -- Somente Números
}

int validarAnoFabricacao(int ano)
{
    if (ano > 2025)
    {
        return 0;
    }

    return 1;
}

int validarData(Data dt)
{
    int diasEmCadaMesPadrao[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int diasNoMes = diasEmCadaMesPadrao[dt.mes - 1]; // Atribui o número de dias no mês digitado

    if ((dt.mes == 2) && anoBissexto(dt.ano))
    { // Se for Fevereiro e for ano Bissexto, atribui 29 ao número de dias no mes
        diasNoMes = 29;
    }

    if ((dt.dia < 1) || (dt.dia > diasNoMes))
    { // Testando se o dia é Valido
        return 0;
    }

    if ((dt.mes < 1) || (dt.mes > 12))
    { // Testando se o mês é Valido
        return 0;
    }

    if ((dt.ano < 1900) || (dt.ano > 2025))
    { // Testando se o ano é Valido
        return 0;
    }

    if (dt.ano > 2025 || (dt.ano == 2025 && dt.dia > 23) || (dt.ano == 2025 && dt.mes > 6))
    { // Testando se é posterior que a data de hoje
        return 0;
    }

    return 1; // Retornar verdadeiro(1) pois a data é Valida
}

Cliente VincularCliente(char nomeCliente[50])
{

    int i = 0;
    for (i = 0; i < g_qtdClientes; i++)
    {
        if (strcmp(nomeCliente, g_clientes[i].nome) == 0)
        {
            return g_clientes[i];
        }
    }
}

int anoBissexto(int ano)
{ // Testando anos bissextos
    /* Testa se é divisivel por 4, e ao mesmo tempo, se é divisivel por 400 ou Não é divisivel por 100 */
    return (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0));
    /* Retorna -- (1) Verdadeiro -- (0) Falso */
}
