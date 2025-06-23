
#include <stdio.h>
#include <string.h>

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct {
    char nomeDoCliente[50];
    char telefoneDoCliente[15];
    Data aniversario;
} Cliente;

typedef struct {
    Cliente cliente;
    char modelo[50];
    char placa[10];
    int anoFabricacao;
    float kilometragem;
} Carro;

typedef struct {
    int identificador;
    Data dataDoServico;
    Carro carro;
    int tipoDeServico;
    char pago;
} Servico;


int ValidarNome(char nome[50]);
int ValidarTelefone(char telefone[15]);
int ValidarData(Data dt);
void CadastrarCliente();
int anoBissexto(int ano);
int hasNum(char text[50]);
int isTotallyNum(char text[15]);

int qtdClientes = 0;
Cliente clientes[10];

int main()
{
    
    CadastrarCliente();
    
    return 0;
}

int ValidarNome(char nome[50]) {
    if(strlen(nome) > 5 && !hasNum(nome) && nome[0] != ' ') {
        return 1;
    } else {
        return 0;
    }
}

int ValidarTelefone(char telefone[15]) {
    if(telefone[0] == '0' && (strlen(telefone) == 11 || strlen(telefone) == 12) && isTotallyNum(telefone)) {
        return 1;
    } else {
        return 0;
    }
}

int ValidarData(Data dt){
    int diasEmCadaMesPadrao[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    int diasNoMes = diasEmCadaMesPadrao[dt.mes - 1]; // Atribui o número de dias no mês digitado
    
    if((dt.mes == 2) && anoBissexto(dt.ano)){ // Se for Fevereiro e for ano Bissexto, atribui 29 ao número de dias no mes
        diasNoMes = 29;
    }

    if((dt.dia < 1) || (dt.dia > diasNoMes)){ // Testando se o dia é Valido
        return 0;
    }

    if((dt.mes < 1) || (dt.mes > 12)){ // Testando se o mês é Valido
        return 0;
    }

    if((dt.ano < 1900) || (dt.ano > 2025)){ // Testando se o ano é Valido
        return 0;
    }
    
    if(dt.ano > 2025 || (dt.ano == 2025 && dt.dia > 23) || (dt.ano == 2025 && dt.mes > 6)) { // Testando se é posterior que a data de hoje
        return 0;
    }

    return 1; // Retornar verdadeiro(1) pois a data é Valida

}


//Falta validar os dados
void CadastrarCliente() {
    printf("Digite seu nome: ");
    fgets(clientes[qtdClientes].nomeDoCliente, 50, stdin);
    clientes[qtdClientes].nomeDoCliente[strlen(clientes[qtdClientes].nomeDoCliente) - 1] = '\0';
    
    printf("Digite seu telefone: ");
    fgets(clientes[qtdClientes].telefoneDoCliente, 15, stdin);
    clientes[qtdClientes].telefoneDoCliente[strlen(clientes[qtdClientes].telefoneDoCliente) - 1] = '\0';

    qtdClientes++;
}

int anoBissexto (int ano){ // Testando anos bissextos
    /* Testa se é divisivel por 4, e ao mesmo tempo, se é divisivel por 400 ou Não é divisivel por 100 */
    /* Retorna -- (1) Verdadeiro -- (0) Falso */
    return (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0));
}

int hasNum(char text[50]) {
    for(int i = 0; i < strlen(text); i++) {
        if((text[i] >= 65 && text[i] <= 90) && (text[i] >= 97 && text[i] <= 122)) {
           continue; 
        } else {
            return 0;
        }
    }
    
    return 1;
}

int isTotallyNum(char text[15]) {
    for(int i = 0; i < strlen(text); i++) {
        if(text[i] >= 48 && text[i] <= 57) {
            continue;
        } else {
            return 0;
        }
    }
    
    return 1;
}

