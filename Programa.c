
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
int VincularCliente(char nomeCliente[50]);
void buscarClientePeloNome(char nome[50]);
void buscarCarroPelaPlaca(char placa[15]);
int kilometragemCarros(float km);

void bancoDeDados(void);
void agruparPorAno(void);
void linha(void);

/**********************************************
        Declaração das variaveis Globais
**********************************************/

int g_qtdClientes = 3;
int g_qtdCarros = 2;
Cliente g_clientes[10];
Carro g_carros[10];



/**********************************************
                    Int main()
**********************************************/

int main()
{
    bancoDeDados();
    
    int quantidade = kilometragemCarros(5000);
    printf("Quantidade de carros que tem mais de 5000 km: %d\n", quantidade);

    agruparPorAno();

    /*linha();
    cadastrarCliente();
    linha();
    cadastrarCliente();
    linha();
    cadastrarCarro();
    linha();
    cadastrarCarro();
    linha();

    buscarClientePeloNome("ronaldo");
    buscarCarroPelaPlaca("opa123");
    linha();*/


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

    do
    {
        printf("Digite o nome do cliente: ");
        fgets(nome, 50, stdin);
        nome[strlen(nome) - 1] = '\0';

        validar = VincularCliente(nome);
        if(validar == (-1)) {
            printf("Cliente nao existe\n");
        }
    } while (validar == (-1));

    g_carros[g_qtdCarros].cliente = g_clientes[VincularCliente(nome)];
    
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
    for (i = 0; i < tam; i++)
    {
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

int VincularCliente(char nomeCliente[50])
{
    int pos = 0;
    for (pos = 0; pos < g_qtdClientes; pos++)
    {
        if (strcmp(nomeCliente, g_clientes[pos].nome) == 0)
        {
            return pos; // -- Retorna a possição do Cliente
        }
    }
    return (-1); // -- Cliente não encontrado
}

int anoBissexto(int ano)
{ // Testando anos bissextos
    /* Testa se é divisivel por 4, e ao mesmo tempo, se é divisivel por 400 ou Não é divisivel por 100 */
    return (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0));
    /* Retorna -- (1) Verdadeiro -- (0) Falso */
}

void buscarClientePeloNome(char nome[50]) {
    int cli_pos = 0;
    for (cli_pos = 0; cli_pos < g_qtdClientes; cli_pos++) {
        if (strcmp(nome, g_clientes[cli_pos].nome) == 0)
        {
            printf("Nome: %s\n", g_clientes[cli_pos].nome);
            printf("Telefone: %s\n", g_clientes[cli_pos].telefone);
            break;
        }
    }

    int car_pos = 0;
    for (car_pos = 0; car_pos < g_qtdCarros; car_pos++) {
        if (strcmp(nome, g_carros[car_pos].cliente.nome) == 0)
        {
            printf("Modelo do carro: %s\n", g_carros[car_pos].modelo);
            printf("Placa do carro: %s\n", g_carros[car_pos].placa);
            printf("Ano do carro: %d\n", g_carros[car_pos].anoFabricacao);
            printf("Kilometragem do carro: %.2f\n", g_carros[car_pos].kilometragem);
        }
    }
}

void buscarCarroPelaPlaca(char placa[15]) {
    int car_pos = 0;
    for (car_pos = 0; car_pos < g_qtdCarros; car_pos++) {
        if (strcmp(placa, g_carros[car_pos].placa) == 0)
        {
            printf("Modelo do carro: %s\n", g_carros[car_pos].modelo);
            printf("Placa do carro: %s\n", g_carros[car_pos].placa);
            printf("Ano do carro: %d\n", g_carros[car_pos].anoFabricacao);
            printf("Kilometragem do carro: %.2f\n", g_carros[car_pos].kilometragem);
            printf("Dono do carro: %s", g_carros[car_pos].cliente.nome);
            printf("Telefone do dono do carro: %s", g_carros[car_pos].cliente.telefone);
            break;
        }
    }  
}

int kilometragemCarros(float km) {
    int qtd = 0;
    int i = 0;


    for (i = 0; i < g_qtdCarros; i++)
    {
        if (g_carros[i].kilometragem > km)
        {
            qtd++;
        }
        
    }


    return qtd;
}


/*int buscarCarroPorCliente(char nomeCliente[50])
{
    int pos = 0;
    for (pos = 0; pos < g_qtdCarros; pos++)
    {
        if ()
        {
            return pos; // -- Retorna a possição do Cliente
        }
    }
    return (-1); // -- Cliente não encontrado
}*/


void bancoDeDados(void){

    strcpy(g_clientes[0].nome, "ronaldo");
    strcpy(g_clientes[0].telefone, "09090909090");

    strcpy(g_clientes[1].nome, "eduardo");
    strcpy(g_clientes[1].telefone, "018981101017");

    strcpy(g_clientes[2].nome, "gustavo");
    strcpy(g_clientes[2].telefone, "018991434719");

    g_carros[0].cliente = g_clientes[0];
    strcpy(g_carros[0].modelo, "Onix");
    strcpy(g_carros[0].placa, "ONX90");
    g_carros[0].anoFabricacao = 2019;
    g_carros[0].kilometragem = 10000;

    g_carros[1].cliente = g_clientes[2];
    strcpy(g_carros[1].modelo, "Opala");
    strcpy(g_carros[1].placa, "OPL40");
    g_carros[1].anoFabricacao = 1974;
    g_carros[1].kilometragem = 10000;
}

void agruparPorAno() {
    int i = 0;
    int j = 0;
    int ano = 0;

    for (i = 0; i < g_qtdCarros; i++)
    {   
        ano = g_carros[i].anoFabricacao;
        printf("%d\n", ano);
        /*for (j = i+1; i < g_qtdCarros; j++)
        {
            if (g_carros[j].anoFabricacao == g_carros[i].anoFabricacao)
            {
                
            }
            
        }*/
        
    }
    
}

void linha(void){
    printf("----------------------------------------\n");
}


void menu(void){
    printf("=====================================\n");
    printf("           MENU DE OPCOES            \n");
    printf("=====================================\n");
    printf("1 - Cadastrar Cliente\n");
    printf("2 - Cadastrar Carro\n");
    printf("3 - Buscar Cliente pelo Nome\n");
    printf("4 - Buscar Carro pela Placa\n");
    printf("5 - Contar Carros com Kilometragem Acima de um Valor\n");
    printf("0 - Sair\n");
    printf("=====================================\n");
    printf("Escolha uma opcao: ");
}