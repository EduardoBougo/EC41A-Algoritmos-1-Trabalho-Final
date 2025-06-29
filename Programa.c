
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/**********************************************
            Declara��o das structs
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
            Declara��o das fun��es
**********************************************/

void menu(void);
void mostrarMenu(void);
void cabecalho(char texto[50]);

void cadastrarCliente(void);
void cadastrarCarro(void);
void buscarClientePeloNome(char nome[50]);
void buscarCarroPelaPlaca(char placa[10]);
int kilometragemCarros(float km);
void agendarServico(void);
void valoresPendentes(void);
void registrarPagamento(void);
void servicoMaisUsado(void);
void promocaoAniversario(int dia, int mes);

int validarNome(char nome[50]);
int validarTelefone(char telefone[15]);
int validarData(Data dt);
int validarDataAnterior(Data dt);
int validarAnoFabricacao(int ano);
int contemSomenteLetras(char text[50]);
int contemSomenteNumeros(char text[15]);
int anoBissexto(int ano);

int VincularCliente(char nomeCliente[50]);
int VincularCarro(char modeloCarro[50], char placaCarro[15]);
void agruparPorAno(void);
void agruparOrdemAlfabetica(void);

void linha(void);
void bancoDeDados(void);
void enterParaContinuar(void);
void limparTela(void);


/**********************************************
        Declara��o das variaveis Globais
**********************************************/

/******************************
g_qtdClientes -- Contador de quantos clientes j� foram cadastrados
g_qtdCarros   -- Contador de quantos carros j� foram cadastrados
q_qtdServicos -- Contador de quantos servi?os j� foram agendados
g_id          --
---------------------------------------------------------------
g_Clientes    -- Vetor que armazena os dados de cada cliente em uma posi��o via struct
g_carros      -- Vetor que armazena os dados de cada carro em uma posi��o via struct
g_servicos    -- Vetor que armazena os dados de cada servi�o em uma posi��o via struct
******************************/

int g_qtdClientes = 3;
int g_qtdCarros = 3;
int g_qtdServicos = 0;
int g_id = 1;
Cliente g_clientes[10];
Carro g_carros[50];
Servico g_servicos[50];


/**********************************************
                    Int main()
**********************************************/

int main()
{
    // Acentua��o
    setlocale(LC_ALL, "Portuguese_Brazil");

    bancoDeDados();

    menu();

    return 0;
}

/*************************************************************************

                                FUN��ES

*************************************************************************/

/**********************************************
                Menu Interativo
**********************************************/

void menu(void)
{
    int op = 0;
    float kilometragem = 0;
    char nome[50],
         placa[10];
    Data niver;
    niver.dia = 0;
    niver.mes = 0;
    niver.ano = 2024;

    do
    {
        mostrarMenu();
        scanf("%d", &op);
        getchar();

        switch (op)
        {
        case 1:
            cabecalho("CADASTRAR NOVO CLIENTE");
            cadastrarCliente();
            break;

        case 2:
            cabecalho("CADASTRAR NOVO CARRO");
            cadastrarCarro();
            break;

        case 3:
            cabecalho("BUSCAR CLIENTE PELO NOME");
            printf("NOME: ");

            fgets(nome, 50, stdin);
            nome[strlen(nome) - 1] = '\0';
            buscarClientePeloNome(nome);

            enterParaContinuar();
            break;

        case 4:
            cabecalho("BUSCAR CARRO PELA PLACA");
            printf("PLACA: ");

            fgets(placa, 50, stdin);
            placa[strlen(placa) - 1] = '\0';
            buscarCarroPelaPlaca(placa);

            enterParaContinuar();
            break;

        case 5:
            cabecalho("QUANTIDADE DE CARROS COM A KILOMETRAGEM ACIMA");
            printf("KILOMETRAGEM: ");

            scanf("%f", &kilometragem);

            printf("\nExistem %d carros com kilometragem acima de %.2f cadastrados no sistema.\n", kilometragemCarros(kilometragem), kilometragem);
            getchar();

            enterParaContinuar();
            break;

        case 6:
            cabecalho("AGENDAR SERVI�OS");
            agendarServico();

            enterParaContinuar();
            break;

        case 7:
            cabecalho("CONSULTAR VALORES PENDENTES");
            valoresPendentes();
            enterParaContinuar();
            break;

        case 8:
            cabecalho("REGISTRAR PAGAMENTO");
            registrarPagamento();
            enterParaContinuar();
            break;

        case 9:
            cabecalho("SERVI�O MAIS SOLICITADO");
            servicoMaisUsado();
            enterParaContinuar();
            break;

        case 10:
            cabecalho("CONFERIR PROMO��O DE ANIVERS�RIO");
            do
            {
                printf("Dia: ");
                scanf("%d", &niver.dia);
                printf("M�s: ");
                scanf("%d", &niver.mes);
            } while (!validarData(niver));
            
            promocaoAniversario(niver.dia, niver.mes);
            enterParaContinuar();

            break;

        default:
            limparTela();
            break;
        }
    } while (op != 0);
}

void mostrarMenu(void)
{
    limparTela();

    printf(" |-------------------------------------------------|\n");
    printf(" |                MENU DE OP��ES                   |\n");
    printf(" |-------------------------------------------------|\n");
    printf(" | 1  - Cadastrar Cliente                          |\n");
    printf(" | 2  - Cadastrar Carro                            |\n");
    printf(" | 3  - Buscar Cliente pelo Nome                   |\n");
    printf(" | 4  - Buscar Carro pela Placa                    |\n");
    printf(" | 5  - Quantidade de Carros com Kilometragem Acima|\n");
    printf(" | 6  - Agendar servi�o                            |\n");
    printf(" | 7  - Consultar valores pendentes                |\n");
    printf(" | 8  - Registrar pagamento                        |\n");
    printf(" | 9  - Mostrar o servi�o mais solicitado          |\n");
    printf(" | 10 - Conferir promo��o de anivers�rio           |\n");
    printf(" | 0 - Sair                                        |\n");
    printf(" |-------------------------------------------------|\n");
    printf(" Escolha uma op�ao: ");
}

void cabecalho(char texto[50])
{ // Imprime um cabe�alho personalizado
    int tam = strlen(texto),
        qtdEspacos = ((50 - tam) / 2), // Conta quantos espa�os ter� antes e depois do texto -- Centralizando
        i = 0;

    limparTela();
    printf(" |--------------------------------------------------|\n");
    printf(" |");

    for (i = 0; i < qtdEspacos; i++)
    { // Imprime os espa�os antes do texto
        printf(" ");
    }

    printf("%s", texto); // Imprime o texto

    if ((tam % 2) == 1)
    { // Caso a qtd de espa�os seja impar -- Soma 1
        qtdEspacos++;
    }

    for (i = 0; i < qtdEspacos; i++)
    { // Imprime os espa�os depois do texto
        printf(" ");
    }

    printf("|\n");
    printf(" |--------------------------------------------------|\n");
    printf("\n\n");
}

/**********************************************
                Fun��es do Menu
**********************************************/

void cadastrarCliente(void)
{
    int validar = 0;
    Data tempData;
    do // Loop. Recebe o nome e checa se � V�lido
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

    do // Loop. Recebe o telefone e checa se � V�lido
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

    do // Loop. Recebe a data de aniversario e checa se � V�lido
    {
        printf("Digite o dia de seu nascimento: ");
        scanf("%d", &tempData.dia);
        printf("Digite o mes de seu nascimento: ");
        scanf("%d", &tempData.mes);
        printf("Digite o ano de seu nascimento: ");
        scanf("%d", &tempData.ano);

        if (!validarData(tempData))
        {
            printf(">>>Data inv�lida<<<\n");
        }
    } while (!validarData(tempData));

    g_clientes[g_qtdClientes].aniversario = tempData;

    g_qtdClientes++; // (+ 1) toda vez que um cliente � cadastrado. Evitando que os dados de novos clientes sejam sobreponham os dados dos clientes antigos.
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
        if (validar == (-1))
        {
            printf("Cliente n�o existe\n");
        }
    } while (validar == (-1));

    g_carros[g_qtdCarros].cliente = g_clientes[VincularCliente(nome)];

    printf("Digite o modelo do carro: ");
    fgets(g_carros[g_qtdCarros].modelo, 50, stdin);
    g_carros[g_qtdCarros].modelo[strlen(g_carros[g_qtdCarros].modelo) - 1] = '\0';

    printf("Digite a placa do carro: ");
    fgets(g_carros[g_qtdCarros].placa, 10, stdin);
    g_carros[g_qtdCarros].placa[strlen(g_carros[g_qtdCarros].placa) - 1] = '\0';
    g_carros[g_qtdCarros].modelo[0] = toupper(g_carros[g_qtdCarros].modelo[0]);

    printf("Digite a kilometragem do carro: ");
    scanf("%f", &g_carros[g_qtdCarros].kilometragem);

    do // Loop. Recebe o ano e checa se � V�lido
    {
        printf("Digite o ano de fabrica��o do carro: ");
        scanf("%d", &g_carros[g_qtdCarros].anoFabricacao);
        getchar();

        validar = validarAnoFabricacao(g_carros[g_qtdCarros].anoFabricacao);
        if (!validar)
        {
            printf(">>>Ano posterior ao desse<<<");
        }

    } while (!validar);

    g_qtdCarros++; // (+ 1) toda vez que um carro � cadastrado. Evitando que os dados de novos clientes sejam sobreponham os dados dos clientes antigos.
}

void buscarClientePeloNome(char nome[50])
{

    int cli_pos = 0;
    int encontrado = 0;
    for (cli_pos = 0; cli_pos < g_qtdClientes; cli_pos++)
    {
        if (strcmp(nome, g_clientes[cli_pos].nome) == 0)
        {
            printf("Nome: %s\n", g_clientes[cli_pos].nome);
            printf("Telefone: %s\n", g_clientes[cli_pos].telefone);
            encontrado = 1;
            break;
        }
    }

    int car_pos = 0;
    if (encontrado == 1)
    {
        for (car_pos = 0; car_pos < g_qtdCarros; car_pos++)
        {
            if (strcmp(nome, g_carros[car_pos].cliente.nome) == 0)
            {
                printf("Modelo do carro: %s\n", g_carros[car_pos].modelo);
                printf("Placa do carro: %s\n", g_carros[car_pos].placa);
                printf("Ano do carro: %d\n", g_carros[car_pos].anoFabricacao);
                printf("Kilometragem do carro: %.2f\n", g_carros[car_pos].kilometragem);
            }
        }
    } else {
        printf("N�o foi encontrado o cliente com nome %s", nome);
    }
}

void buscarCarroPelaPlaca(char placa[10])
{
    int car_pos = 0;
    int encontrado = 0;
    for (car_pos = 0; car_pos < g_qtdCarros; car_pos++)
    {
        if (strcmp(placa, g_carros[car_pos].placa) == 0)
        {
            printf("Modelo do carro: %s\n", g_carros[car_pos].modelo);
            printf("Placa do carro: %s\n", g_carros[car_pos].placa);
            printf("Ano do carro: %d\n", g_carros[car_pos].anoFabricacao);
            printf("Kilometragem do carro: %.2f\n", g_carros[car_pos].kilometragem);
            printf("Dono do carro: %s\n", g_carros[car_pos].cliente.nome);
            printf("Telefone do dono do carro: %s\n", g_carros[car_pos].cliente.telefone);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
    {
        printf("N�o foi encontrado nenhum carro com placa %s", placa);
    }
    
}

int kilometragemCarros(float km)
{
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

void agendarServico()
{
    int validar = 0;
    int tipo = 0;
    char modelo[50];
    char placa[15];
    Data tempData;

    do
    {
        printf("Digite o modelo do carro que deseja agendar o servi�o: ");
        fgets(modelo, 50, stdin);
        modelo[strlen(modelo) - 1] = '\0';
        printf("Digite a placa do carro: ");
        fgets(placa, 15, stdin);
        placa[strlen(placa) - 1] = '\0';

        validar = VincularCarro(modelo, placa);
        if (validar == -1)
        {
            printf("Carro n�o encontrado.\n");
        }
    } while (validar == -1);

    g_servicos[g_qtdServicos].carro = g_carros[VincularCarro(modelo, placa)];
    linha();

    do
    {
        printf("Digite o dia do servi�o: ");
        scanf("%d", &tempData.dia);
        printf("Digite o m�s do servi�o: ");
        scanf("%d", &tempData.mes);
        printf("Digite o ano do servi�o: ");
        scanf("%d", &tempData.ano);

        if (!validarDataAnterior(tempData))
        {
            printf("Data inv�lida\n");
        }

    } while (!validarDataAnterior(tempData));

    g_servicos[g_qtdServicos].dataDoServico = tempData;
    linha();

    do
    {
        printf("Digite o tipo de servi�o que deseja fazer:\n");
        printf("1 - Revisao b�sica - R$750.00\n");
        printf("2 - Troca de �leo - R$190.00\n");
        printf("3 - Alinhamento e balanceamento - R$120.00\n");
        printf("4 - Higieniza��o - R$90.00\n");
        scanf("%d", &tipo);
        getchar();

        if (tipo != 1 && tipo != 2 && tipo != 3 && tipo != 4)
        {
            printf("Tipo inv�lido.\n");
        }

    } while (tipo != 1 && tipo != 2 && tipo != 3 && tipo != 4);

    g_servicos[g_qtdServicos].tipoDeServico = tipo;

    g_servicos[g_qtdServicos].pago = 'N';

    g_servicos[g_qtdServicos].identificador = g_id;
    g_id++;

    g_qtdServicos++;

    printf("Servico agendado!\n");
    linha();
}

void valoresPendentes(void)
{
    int i = 0;
    int j = 0;
    int encontrouServico = 0;
    for (i = 0; i < g_qtdCarros; i++)
    {
        Carro carroAtual = g_carros[i];
        printf("Carro: %s | Placa %s\n", carroAtual.modelo, carroAtual.placa);
        encontrouServico = 0;

        for (j = 0; j < g_qtdServicos; j++)
        {
            if (strcmp(carroAtual.placa, g_servicos[j].carro.placa) == 0)
            {
                encontrouServico = 1;
                if (g_servicos[j].pago == 'N')
                {
                    int tipo = g_servicos[j].tipoDeServico;
                    switch (tipo)
                    {
                    case 1:
                        printf("Servi�o de Revis�o b�sica (750,0) - n�o pago\n");
                        break;
                    case 2:
                        printf("Servi�o de Troca de �leo (190,0) - n�o pago\n");
                        break;
                    case 3:
                        printf("Servi�o de Alinhamento e balanceamento (120,0) - n�o pago\n");
                        break;
                    case 4:
                        printf("Servi�o de Higieniza��o (90,0) - n�o pago\n");
                        break;
                    }
                }
            }
        }

        if (!encontrouServico)
        {
            printf("N�o possui servi�o no momento.\n");
        }

        linha();
    }
}

void registrarPagamento(void) {
    int i = 0;
    int input = 0;
    int maiorId = 0;
    char servicos[4][50] = {"Revis�o b�sica", "Troca de �leo", "Alinhamento e balanceamento", "Higieniza��o"};

    for (i = 0; i < g_qtdServicos; i++)
    {   
        printf("Identificador do servi�o: %d\n", g_servicos[i].identificador);
        printf("Carro: %s\n", g_servicos[i].carro.modelo);
        printf("Placa do carro: %s\n", g_servicos[i].carro.placa);
        printf("Servi�o: %s\n", servicos[g_servicos[i].tipoDeServico - 1]);
        printf("Situa��o do pagamento: %s\n", g_servicos[i].pago == 'N' ? "Pendente\n" : "Conclu�do\n");

        if(g_servicos[i].identificador > maiorId) {
            maiorId = g_servicos[i].identificador;
        }
    }

    linha();

    do
    {
        printf("Digite o identificador do servi�o que deseja pagar: ");
        scanf("%d", &input);

        if (input == 0)
        {
            printf("Inv�lido\n");
        }
        
    } while (input == 0);
    
    if (input <= maiorId)
    {
        g_servicos[input - 1].pago = 'S';
        printf("O servi�o %s, vinculado ao carro com placa %s foi conclu�do!\n", servicos[g_servicos[input - 1].tipoDeServico - 1], g_servicos[input - 1].carro.placa);
    } else {
        printf("Nao ha um servi�o com este identificador!");
    }

    linha();
}

void servicoMaisUsado(void)
{
    int i = 0;
    int cont[4] = {0, 0, 0, 0};
    int id_Servico = 0;
    int maiorQtd = 0;

    if (g_qtdServicos == 0)
    { // Caso n�o haja nenhum servi�o registrado ainda
        printf("\nNenhum servi�o registrado ainda\n");
        return;
    }

    for (i = 0; i < g_qtdServicos; i++) // Contador de quantas vezes o servi�o foi pedido
    {
        id_Servico = g_servicos[i].tipoDeServico;
        cont[id_Servico - 1]++;
    }

    for (i = 0; i < 4; i++)
    {
        if (cont[i] > maiorQtd)
        { // Compara os valores e identifica a maior quantidades de pedidos de um servi�o
            maiorQtd = cont[i];
        }
    }

    printf("Servi�o(s) mais pedido(s): \n");
    for (i = 0; i < 4; i++)
    {
        if (cont[i] == maiorQtd)
        { // Mostrar o(s) servi�o(s) mais usado(s)
            switch (i + 1)
            {
            case 1:
                printf("- Revis�o b�sica\n");
                break;
            case 2:
                printf("- Troca de �leo\n");
                break;

            case 3:
                printf("- Alinhamento e balanceamento\n");
                break;

            case 4:
                printf("- Higieniza��o \n");
                break;

            default:
                break;
            }
        }
    }
}

void promocaoAniversario(int dia, int mes) {
    int i = 0;
    for (i = 0; i < g_qtdClientes; i++)
    {
        if (g_clientes[i].aniversario.mes == mes && (g_clientes[i].aniversario.dia >= dia && g_clientes[i].aniversario.dia <= (dia + 7)))
        {
            printf("O cliente %s foi selecionado para a promo��o!\n", g_clientes[i].nome);
        }
    }
    getchar();
}


/**********************************************
              Valida��o de Dados
**********************************************/

int validarNome(char nome[50])
{ // (1) Verdadeiro -- (0) Falso
    if ((strlen(nome) > 5) && contemSomenteLetras(nome) && (nome[0] != ' '))
    {
        return 1; // -- Nome V�lido
    }
    else
    {
        return 0; // -- Nome Inv�lido
    }
}

int validarTelefone(char telefone[15])
{ // (1) Verdadeiro -- (0) Falso
    if (telefone[0] == '0' && (strlen(telefone) == 11 || strlen(telefone) == 12) && contemSomenteNumeros(telefone))
    {
        return 1; // -- Telefone V�lido
    }
    else
    {
        return 0; // -- Telefone Inv�lido
    }
}

int validarData(Data dt)
{
    int diasEmCadaMesPadrao[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int diasNoMes = diasEmCadaMesPadrao[dt.mes - 1]; // Atribui o n�mero de dias no m�s digitado

    if ((dt.mes == 2) && anoBissexto(dt.ano))
    { // Se for Fevereiro e for ano Bissexto, atribui 29 ao n�mero de dias no mes
        diasNoMes = 29;
    }

    if ((dt.dia < 1) || (dt.dia > diasNoMes))
    { // Testando se o dia � Valido
        return 0;
    }

    if ((dt.mes < 1) || (dt.mes > 12))
    { // Testando se o m�s � Valido
        return 0;
    }

    if ((dt.ano < 1900) || (dt.ano > 2025))
    { // Testando se o ano � Valido
        return 0;
    }

    if (dt.ano > 2025 || (dt.ano == 2025 && dt.dia > 30) || (dt.ano == 2025 && dt.mes > 6))
    { // Testando se � posterior que a data de hoje
        return 0;
    }

    return 1; // Retornar verdadeiro(1) pois a data � Valida
}

int validarDataAnterior(Data dt)
{
    int diasEmCadaMesPadrao[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int diasNoMes = diasEmCadaMesPadrao[dt.mes - 1]; // Atribui o n�mero de dias no m�s digitado

    if ((dt.mes == 2) && anoBissexto(dt.ano))
    { // Se for Fevereiro e for ano Bissexto, atribui 29 ao n�mero de dias no m�s
        diasNoMes = 29;
    }

    if ((dt.dia < 1) || (dt.dia > diasNoMes))
    { // Testando se o dia � Valido
        return 0;
    }

    if ((dt.mes < 1) || (dt.mes > 12))
    { // Testando se o m�s � Valido
        return 0;
    }

    if (dt.ano < 2025 || (dt.ano == 2025 && dt.mes < 6) || (dt.ano == 2025 && dt.mes == 6 && dt.dia < 30))
    { // Testando se � anterior que a data de hoje
        return 0;
    }

    return 1; // Retornar verdadeiro(1) pois a data � Valida
}

int validarAnoFabricacao(int ano)
{
    if (ano > 2025)
    {
        return 0;
    }

    return 1;
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
    return 1; // -- Somente N�meros
}

int anoBissexto(int ano)
{ // Testando anos bissextos
    /* Testa se � divisivel por 4, e ao mesmo tempo, se � divisivel por 400 ou N�o � divisivel por 100 */
    return (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0));
    /* Retorna -- (1) Verdadeiro -- (0) Falso */
}

/**********************************************
             Vincula��o de Dados
**********************************************/

int VincularCliente(char nomeCliente[50])
{
    int pos = 0;
    for (pos = 0; pos < g_qtdClientes; pos++)
    {
        if (strcmp(nomeCliente, g_clientes[pos].nome) == 0)
        {
            return pos; // -- Retorna a posi��o do Cliente
        }
    }
    return (-1); // -- Cliente n�o encontrado
}

int VincularCarro(char modeloCarro[50], char placaCarro[15])
{
    int pos = 0;
    for (pos = 0; pos < g_qtdCarros; pos++)
    {
        if (strcmp(modeloCarro, g_carros[pos].modelo) == 0 && strcmp(placaCarro, g_carros[pos].placa) == 0)
        {
            return pos; // -- Retorna a posi��o do Carro
        }
    }
    return (-1); // -- Carro n�o encontrado
}

void agruparPorAno()
{
    int i = 0;
    int j = 0;

    for (int i = 0; i < g_qtdCarros; i++)
    {
        for (j = (i + 1); j < g_qtdCarros; j++)
        {
            if (g_carros[i].anoFabricacao > g_carros[j].anoFabricacao)
            {
                // Trocar os carros, ordenando por ano de fabrica��o
                Carro temp = g_carros[i];
                g_carros[i] = g_carros[j];
                g_carros[j] = temp;
            }
        }
    }

    int anoAtual = 0;
    for (i = 0; i < g_qtdCarros; i++)
    {
        // Se o ano de fabrica��o n�o for igual ao da vari�vel anoAtual, essa vari�vel ir� receber outro ano.
        if (g_carros[i].anoFabricacao != anoAtual)
        {
            printf("%d\n", g_carros[i].anoFabricacao);
            anoAtual = g_carros[i].anoFabricacao;
        }

        printf("Modelo: %s\n", g_carros[i].modelo);
        printf("Placa: %s\n", g_carros[i].placa);
        printf("Kilometragem: %.2f\n", g_carros[i].kilometragem);
        printf("Dono: %s\n", g_carros[i].cliente.nome);
        printf("Telefone do Dono: %s\n", g_carros[i].cliente.telefone);
        linha();
    }
}

void agruparOrdemAlfabetica() { // Ordena e lista os carros por ordem alfabetica dos modelos
    int i = 0;
    int j = 0;
    Carro tempCarro;

    for (i = 0; i < g_qtdCarros; i++)
    {
        for (j = i+1; j < g_qtdCarros; j++)
        {
            if (strcmp(g_carros[i].modelo, g_carros[j].modelo) > 0)
            {
                tempCarro = g_carros[i];
                g_carros[i] = g_carros[j];
                g_carros[j] = tempCarro;
            }
            
        }
        
    }

    printf("| %-20s | %-10s | %-5s | %-12s | %-20s | %-15s |\n",
             "Modelo", "Placa", "Ano", "Kilometragem", "Dono do carro", "Telefone");

    for (i = 0; i < g_qtdCarros; i++)
    {
        printf("| %-20s | %-10s | %-5d | %-12.2f | %-20s | %-15s |\n",
               g_carros[i].modelo,
               g_carros[i].placa,
               g_carros[i].anoFabricacao,
               g_carros[i].kilometragem,
               g_carros[i].cliente.nome,
               g_carros[i].cliente.telefone);
    }
}

/**********************************************
                Fun��es Internas
**********************************************/

void linha(void)
{
    printf("----------------------------------------\n");
}

void bancoDeDados(void)
{
    // Cliente 1
    strcpy(g_clientes[0].nome, "ronaldo");
    strcpy(g_clientes[0].telefone, "09090909090");
    g_clientes[0].aniversario.dia = 12;
    g_clientes[0].aniversario.mes = 2;
    g_clientes[0].aniversario.ano = 2005;

    // Cliente 2
    strcpy(g_clientes[1].nome, "eduardo");
    strcpy(g_clientes[1].telefone, "018981101017");
    g_clientes[1].aniversario.dia = 20;
    g_clientes[1].aniversario.mes = 2;
    g_clientes[1].aniversario.ano = 2005;

    // Cliente 3
    strcpy(g_clientes[2].nome, "gustavo");
    strcpy(g_clientes[2].telefone, "018991434719");
    g_clientes[0].aniversario.dia = 23;
    g_clientes[0].aniversario.mes = 4;
    g_clientes[0].aniversario.ano = 2001;


    // Carro 1
    g_carros[0].cliente = g_clientes[0];
    strcpy(g_carros[0].modelo, "Onix");
    strcpy(g_carros[0].placa, "ONX90");
    g_carros[0].anoFabricacao = 2019;
    g_carros[0].kilometragem = 10000;

    // Carro 2
    g_carros[1].cliente = g_clientes[2];
    strcpy(g_carros[1].modelo, "Opala");
    strcpy(g_carros[1].placa, "OPL40");
    g_carros[1].anoFabricacao = 1974;
    g_carros[1].kilometragem = 10000;

    // Carro 3
    g_carros[2].cliente = g_clientes[1];
    strcpy(g_carros[2].modelo, "Opala2");
    strcpy(g_carros[2].placa, "OPA40");
    g_carros[2].anoFabricacao = 2019;
    g_carros[2].kilometragem = 10000;
}

void enterParaContinuar(void)
{
    printf("\n>>> Precione a tecla Enter para continuar <<<\n");
    getchar();
}

void limparTela(void)
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/************************************************************************************/
