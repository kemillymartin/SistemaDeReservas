//Bruna Campos Santana
//Kemilly Martin Ramalho
//Livia Fabrin Somera

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

int tam = 100; //tamanho do vetor que armazenar� o cadastro dos clientes
int tam_atual = 0; //tamanho atualizado do vetor
char assentos[43]; // vetor que armazena os assentos do �nibus

//struct para armazenar os dados do cliente
struct Cliente
{
    char nome [80];
    char cpf [12];
    int assento;
    int usado;
};

//prot�tipo das fun��es
void cadastrarCliente(struct Cliente vet[]); //fun��o 01
void excluirCadastro(struct Cliente vet[]); //fun��o 02
void pesquisarPorCpf(struct Cliente vet[]); //fun��o 03
void pesquisarPorNome(struct Cliente vet[]); //fun��o 04
void imprimirCadastros(struct Cliente vet[]); //fun��o 05
void reservarAssento(struct Cliente vet[]); //fun��o 06
void venderAssento(struct Cliente vet[]); //fun��o 07
void alterarReserva(struct Cliente vet[]); //fun��o 08
void alterarVenda(struct Cliente vet[]); //fun��o 09
void desfazerReserva(struct Cliente vet[]); //fun��o 10
void consultarStatus(); //fun��o 11
int validarCliente(struct Cliente vet[], char cliente_cpf[]); //fun��o para validar o CPF do cliente
int arquivoExiste(char *fnome);
void salva(struct Cliente cli[], int tamCli, char assentos[], int tamA) ;
void carrega(struct Cliente cli[], int tamCli, char assentos[], int tamA) ;
int contaArquivo(char *nome);

int main()
{
    setlocale(LC_ALL, "Portuguese");

    int opcao; //selecionar a op��o do menu
    struct Cliente vet[tam];

    if(arquivoExiste("clientes.bin") && arquivoExiste("assentos.bin"))
    {
        tam_atual = contaArquivo("clientes.bin");
        carrega(vet, tam_atual, assentos, 43);
    }
    else
    {
        //la�o para garantir que todas as posi��es do vetor para armazenar clientes estar�o zeradas
        for(int i=0; i<tam; i++)
        {
            vet[i].usado = 0;
        }

        //la�o para garantir que todas as posi��es do vetor para armazenar assentos do cliente estar�o zeradas
        for(int i=0; i<tam; i++)
        {
            vet[i].assento = 0;
        }

        //la�o para garantir que todas as posi��es do vetor assento receber�o 1, que significa que o assento est� dispon�vel
        for(int i=0; i<43; i++)
        {
            assentos[i] = '1';
        }
    }

    //menu de op��es
    while(1)
    {
        printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
        printf("           MENU INICIAL\n");
        printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
        printf("1- CADASTRAR CLIENTE\n");
        printf("2- EXCLUIR UM CADASTRO\n");
        printf("3- PESQUISAR CLIENTE POR CPF\n");
        printf("4- PESQUISAR CLIENTE POR NOME\n");
        printf("5- IMPRIMIR CLIENTES CADASTRADOS\n");
        printf("6- RESERVAR ASSENTO\n");
        printf("7- VENDER ASSENTO\n");
        printf("8- ALTERAR ASSENTO RESERVADO\n");
        printf("9- ALTERAR ASSENTO VENDIDO\n");
        printf("10-DESFAZER RESERVA\n");
        printf("11-CONSULTAR STATUS DAS POLTRONAS\n");
        printf("0- SALVAR A��ES\n");
        printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
        printf("\n");
        scanf("%d", &opcao);
        printf("\n");

        switch (opcao)
        {
        case 0:
            salva(vet, tam_atual, assentos, 43); //quando o usu�rio seleciona essa op��o, o arquivo � salvo
            exit(0);

        case 1:
            cadastrarCliente(vet);
            break;

        case 2:
            excluirCadastro(vet);
            break;

        case 3:
            pesquisarPorCpf(vet);
            break;

        case 4:
            pesquisarPorNome(vet);
            break;

        case 5:
            imprimirCadastros(vet);
            break;

        case 6:
            reservarAssento(vet);
            break;

        case 7:
            venderAssento(vet);
            break;

        case 8:
            alterarReserva(vet);
            break;

        case 9:
            alterarVenda(vet);
            break;

        case 10:
            desfazerReserva(vet);
            break;

        case 11:
            consultarStatus();
            break;
        }
    }
    return 0;
}

//01 fun��o para cadastrar novo cliente
void cadastrarCliente(struct Cliente vet[])
{
    int n;//vari�vel pra receber o tamanho do cpf
    char nome[80], cpf[12];

    if(tam_atual<tam)  //receber os dados do cliente para valida��o do cpf - verifica se h� espa�o para cadastrar novo cliente
    {
        printf("Digite o nome do cliente: ");
        scanf("%s", nome);
        printf("Digite o CPF do cliente: ");
        scanf("%s", cpf);

        for(int i=0; i<tam_atual; i++)
        {
            if(strcmp(vet[i].cpf, cpf)==0) // verifica se o cpf digitado j� foi cadastrado e retorna sem salvar o novo cadastrado
            {
                printf("Erro! CPF j� cadastrado!\n\n");
                return;
            }
        }
        n = strlen(cpf); //caso o cpf n�o tenha sido cadastrado ainda, verifica se o cpf � valido

        if(n == 11)  //se o cpf � v�lido, prossegue com o cadastro
        {
            for(int i=0; i<tam; i++)
            {
                if(vet[i].usado==0)  //verifica se a posi��o est� dispon�vel no vetor de cadastro e se estiver, prossegue
                {
                    strcpy(vet[i].nome, nome); //recebe o nome inserido
                    strcpy(vet[i].cpf, cpf); //recebe o cpf inserido

                    vet[i].usado = 1;//atribui 1 para indicar que essa posi��o do vetor est� sendo usada
                    tam_atual++; //atualiza o tamanho do vetor
                    break;
                }
            }
            printf("Cliente cadastrado com sucesso!\n"); //cliente cadastrado
        }
        else
        {
            printf("Informe um CPF v�lido!\n"); //cpf inv�lido - menos ou mais de 11 n�meros
        }
    }

    else
    {
        printf("Espa�o insuficiente para novo cadastro!\n"); //vetor de cadastro j� est� cheio
    }
    printf("\n");
}

//02 fun��o para excluir cliente
void excluirCadastro(struct Cliente vet[])
{
    char cliente_cpf[12];
    int retorno=0, resultado=0;

    printf("Informe o CPF do cliente que deseja exluir: ");
    scanf("%s", cliente_cpf);

    //retorno recebe a resposta da fun��o que verifica o cpf
    retorno = validarCliente(vet, cliente_cpf);

    if(retorno == 1) //se o cpf for v�lido, retorno ser� 1 e ent�o entra no if
    {
        for(int i=0; i<tam_atual; i++)
        {
            if(strcmp(vet[i].cpf, cliente_cpf)==0) //se o cpf da struct na posi��o i for igual ao cpf digitado
            {
                if(vet[i].assento == 0)
                {
                    //.usado recebe 0 (torna a posi��o i da struct dispon�vel para receber um novo cliente)
                    vet[i].usado=0;
                    resultado = 1; //indica que um cliente foi exclu�do
                }
                else
                {
                    printf("Cliente tem reserva ou compra de assento registrada! \n Favor desfazer a opera��o antes de excluir o cadastro.");
                }
            }
        }
    }
    if(resultado == 1) //como o cliente foi exclu�do, exibe mensagem de sucesso
    {
        printf("Cliente exclu�do com sucesso!\n\n");
    }

}

//03 fun��o para pesquisar cliente por CPF
void pesquisarPorCpf(struct Cliente vet[])
{
    char cliente_cpf[12], nome[80], cpf[12];
    int retorno=0;

    printf("Informe o CPF do cliente que deseja pesquisar: ");
    scanf("%s", cliente_cpf);

    //retorno recebe a resposta da fun��o que verifica o cpf
    retorno = validarCliente(vet, cliente_cpf);

    if(retorno == 1) //se o cpf for v�lido, retorno ser� 1 e ent�o entra no if
    {
        for(int i=0; i<tam_atual; i++)
        {
            if(strcmp (vet[i].cpf, cliente_cpf)==0) //verifica se o cpf digitado � igual a algum j� inserido
            {
                //caso encontre um cpf igual ao inserido, copia o nome e o cpf para as vari�veis auxiliares
                printf("Nome: %s\n", vet[i].nome);
                printf("CPF: %s\n", vet[i].cpf);
            }
        }
    }

}

//04 fun��o para pesquisar cliente por nome
void pesquisarPorNome(struct Cliente vet[])
{
    char cliente_nome[80], nome[80], cpf[12];
    int resultado =0;

    if(tam_atual>0) //verifica se a lista j� est� criada
    {
        printf("Informe o nome do cliente que deseja pesquisar: "); //informa o nome que deseja pesquisar
        scanf("%s", cliente_nome);

        for(int i=0; i<tam_atual; i++) //la�o para percorrer o vetor de cadastro e verificar se algum nome corresponde ao nome pesquisado
        {
            if(strcmp (vet[i].nome, cliente_nome)==0) //caso encontre uma correspond�ncia, salva o nome e cpf nas vari�veis auxiliares
            {
                resultado = 1;
                strcpy(nome, vet[i].nome);
                strcpy(cpf, vet[i].cpf);
            }
        }
        if(resultado == 1) //caso seja encontrado um cpf igual ao digitado, exibe na tela o nome e cpf salvos nas vair�veis auxiliares
        {
            printf("Nome: %s\n", nome);
            printf("CPF: %s\n", cpf);
        }
        else
        {
            printf("Cliente n�o encontrado!"); // caso n�o encontre um cpf, exibe mensagem de erro
        }
    }
    else
    {
        printf("N�o h� nenhum cliente cadastrado! \n"); //caso a lista ainda n�o exista, exibe mensagem de ero
    }
    printf("\n");
}

//05 fun��o para imprimir clientes cadastrados
void imprimirCadastros(struct Cliente vet[])
{
    if(tam_atual>0) //verifica se a lista de clientes j� existe
    {
        printf("Clientes cadastrados: \n\n");

        for(int i =0; i<tam_atual; i++) //caso a lista exista, percorre todo o vetor
        {
            if(vet[i].usado==1) //verifica se a posi��o do vetor est� sendo usada
            {
                printf("Nome: %s\n", vet[i].nome); //caso encontre uma posi��o usada, exibe o nome e o cpf
                printf("CPF: %s\n", vet[i].cpf);
                printf("\n");
            }
        }
    }
    else
    {
        printf("N�o h� nenhum cliente cadastrado!\n"); //caso a lista n�o tenha sido criada, exibe mensagem de erro
    }
    printf("\n");
}

//06 fun��o para reservar assentos
void reservarAssento(struct Cliente vet[])
{
    char cliente_cpf[12];
    int assentoEscolhido, retorno=0;

    //recebe o numero do assento desejado que coincide com a posi��o no vetor
    printf("Informe o assento desejado: ");
    scanf("%d", &assentoEscolhido);

    //verifica se o assento escolhido est� dispon�vel
    if(assentos[assentoEscolhido] == '1')
    {
        printf("Informe o CPF do cliente que deseja reservar o assento: "); //se o assento est� dispon�vel, insere o cpf do cliente
        scanf("%s", cliente_cpf);

        retorno = validarCliente(vet, cliente_cpf); //verifica se o cpf � v�lido e se for, busca o cpf do cliente

        if(retorno == 1) //caso o cliente esteja cadastrado, procura o cadastrado do mesmo e efetua a reserva
        {
            for(int i=0; i<tam_atual; i++)
            {
                if(strcmp (vet[i].cpf, cliente_cpf)==0) //busca cadastro
                {
                    if(vet[i].assento==0)
                    {
                        vet[i].assento = assentoEscolhido; //associa o assento escolhido ao cadastro do cliente
                        assentos[assentoEscolhido] = 'R'; //assinala o assento escolhido como vendido
                        printf("Assento reservado com sucesso!\n\n"); //exibe mensagem de sucesso
                        return;
                    }
                    else
                    {
                        printf("O CPF informado j� possui uma poltrona!\n");
                    }
                }
            }
        }
    }
    else
    {
        printf("O assento n�o est� dispon�vel!\nVolte ao MENU e consulte o status das poltronas.\n\n"); //mensagem de erro caso o assento escolhido esteja indispon�vel
    }
}

//07 fun��o para vender assento
void venderAssento(struct Cliente vet[])
{
    char cliente_cpf[12];
    int assentoEscolhido, retorno=0;

    //recebe o numero do assento desejado que coincide com a posi��o no vetor
    printf("Informe o assento desejado: ");
    scanf("%d", &assentoEscolhido);

    if(assentos[assentoEscolhido] == '1')
    {
        printf("Informe o CPF do cliente que deseja comprar o assento: "); //se o assento est� dispon�vel, insere o cpf do cliente
        scanf("%s", cliente_cpf);

        retorno = validarCliente(vet, cliente_cpf); //verifica se o cpf � v�lido e se for, busca o cpf do cliente

        if(retorno == 1) //verifica se o cpf � v�lido e procura o cadastrado do cliente
        {
            for(int i=0; i<tam_atual; i++)
            {
                if(strcmp (vet[i].cpf, cliente_cpf)==0) //busca cadastro do cliente
                {

                    if(vet[i].assento==0)
                    {
                        vet[i].assento = assentoEscolhido; //associa o assento escolhido ao cadastro do cliente
                        assentos[assentoEscolhido] = 'V'; //assinala o assento escolhido como vendido
                        printf("Assento vendido com sucesso!\n\n"); //exibe mensagem de sucesso
                        return;
                    }
                    else
                    {
                        printf("O CPF informado j� possui uma poltrona!\n");
                    }
                }
            }
        }
        printf("\n");
    }
    else
    {
        printf("O assento n�o est� dispon�vel!\nVolte ao MENU e consulte o status das poltronas.\n\n"); //mensagem de erro caso o assento escolhido esteja indispon�vel
    }
}

//08 fun��o para alterar reserva
void alterarReserva(struct Cliente vet[])
{
    int aux, retorno = 0, assento;
    char cliente_cpf[12];
    char cpf[12];

    printf("Informe o CPF do cliente que deseja alterar a reserva: "); //insere o cpf que deseja ter a reserva alterada
    scanf("%s", cliente_cpf);

    retorno = validarCliente(vet, cliente_cpf); //verifica se o cpf � v�lido e se o cliente est� cadastrado


    if(retorno == 1) //caso o cliente esteja cadastrado, procura o cadastrado do mesmo
    {
        for(int i=0; i<tam_atual; i++)
        {
            if(strcmp (vet[i].cpf, cliente_cpf)==0) //verifica se o cliente tem um assento vendido, e caso tenha, n�o executa a opera��o
            {
                if(vet[i].assento != 0)
                {
                    for(int j=1; j<43; j++)
                    {
                        if(j == vet[i].assento)
                        {
                            if(assentos[j]=='V')
                            {
                                printf("Opera��o inv�lida!\nCliente possui um assento vendido.\n");
                            }
                            else if(assentos[j]=='R')
                            {
                                printf("Informe o assento desejado: "); //solicita o novo assento desejado
                                scanf("%d", &assento);

                                for(int i=1; i<43; i++) //verifica se o assento solicitado est� dispon�vel
                                {
                                    if(i == assento)
                                    {
                                        if(assentos[i] == 'R')
                                        {
                                            printf("O assento j� est� reservado!\n\n");
                                        }
                                        else if(assentos[i] == 'V')
                                        {
                                            printf("O assento est� vendido!\n\n");
                                        }
                                        else if(assentos[i] == '1') //se o assento estiver dispon�vel, realiza a troca
                                        {
                                            assentos[i] = 'R';
                                            for(int j=0; j<tam_atual; j++)
                                            {
                                                if(strcmp (vet[j].cpf, cliente_cpf)==0) //busca cadastro do cliente
                                                {
                                                    aux = vet[j].assento; //o aux recebe o n�mero do assento anteriormente solicitado
                                                    vet[j].assento = assento; //.assento(a atribui��o na estrutura cliente) recebe o novo assento
                                                    assentos[aux] = '1'; //o vetor de assentos na posi��o aux(o assento anterior) recebe 1 que significa dispon�vel
                                                }
                                            }
                                            printf("Assento reservado com sucesso!\n\n");
                                            return;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

//09 fun��o para alterar uma venda
void alterarVenda(struct Cliente vet[])
{
    int aux, retorno = 0, assento;
    char cliente_cpf[12];
    char cpf[12];

    printf("Informe o CPF do cliente: "); //insere o cpf que deseja ter a venda alterada
    scanf("%s", cliente_cpf);

    retorno = validarCliente(vet, cliente_cpf); //verifica se o cpf � v�lido e se o cliente est� cadastrado

    if(retorno == 1) //caso o cliente esteja cadastrado, procura o cadastrado do mesmo
    {
        for(int i=0; i<tam_atual; i++)
        {
            if(strcmp (vet[i].cpf, cliente_cpf)==0) //verifica se o cliente tem um assento reservado, e caso tenha, n�o executa a opera��o
            {
                if(vet[i].assento != 0)
                {
                    for(int j=1; j<43; j++)
                    {
                        if(j == vet[i].assento)
                        {
                            if(assentos[j]=='R')
                            {
                                printf("Opera��o inv�lida!\nCliente possui um assento reservado.\n");
                            }
                            else if(assentos[j]=='V')
                            {
                                printf("Informe o assento desejado: "); //solicita o novo assento desejado
                                scanf("%d", &assento);

                                for(int i=1; i<43; i++) //verifica se o assento solicitado est� dispon�vel
                                {
                                    if(i == assento)
                                    {
                                        if(assentos[i] == 'R')
                                        {
                                            printf("O assento j� est� reservado!\n\n");
                                        }
                                        else if(assentos[i] == 'V')
                                        {
                                            printf("O assento est� vendido!\n\n");
                                        }
                                        else if(assentos[i] == '1') //se o assento estiver dispon�vel, realiza a venda
                                        {
                                            assentos[i] = 'V'; //o assento escolhido � marcado como vendido
                                            for(int j=0; j<tam_atual; j++)
                                            {
                                                if(strcmp (vet[j].cpf, cliente_cpf)==0) //busca cadastro do cliente
                                                {
                                                    aux = vet[j].assento; //o aux recebe o n�mero do assento anteriormente solicitado
                                                    vet[j].assento = assento; //.assento(a atribui��o na estrutura cliente) recebe o novo assento
                                                    assentos[aux] = '1'; //o vetor de assentos na posi��o aux(o assento anterior) recebe 1 que significa dispon�vel
                                                }
                                            }
                                            printf("Assento vendido com sucesso!\n\n");
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

//10 fun��o para desfazer reserva
                        void desfazerReserva(struct Cliente vet[])
                        {
                            int aux, retorno = 0;
                            char cliente_cpf[12];
                            char cpf[12];

                            printf("Informe o CPF do cliente que deseja desfazer a reserva: "); //insere o cpf que deseja ter a reserva desfeita
                            scanf("%s", cliente_cpf);

                            retorno = validarCliente(vet, cliente_cpf); //verifica se o cpf � v�lido e se o cliente est� cadastrado

                            if(retorno == 1) //caso o cliente esteja cadastrado, procura o cadastrado do mesmo
                            {
                                for(int i=0; i<tam_atual; i++)
                                {
                                    if(strcmp (vet[i].cpf, cliente_cpf)==0) //busca cadastro do cliente
                                    {
                                        if(assentos[(vet[i].assento)] == 'R') //verifica se o cadastro tem uma reserva
                                        {
                                            aux = vet[i].assento; //aux recebe o assento reservado
                                            vet[i].assento = 0; //a reserva do cliente � cancelada
                                            assentos[aux] = '1'; //o assento reservado se torna dispon�vel novamente
                                            printf("Reserva cancelada com sucesso!\n\n");
                                        }
                                        else if(assentos[(vet[i].assento)] == 'V')
                                        {
                                            printf("Este assento foi vendido e a opera��o n�o pode ser cancelada.\n\n");
                                        }
                                        else
                                        {
                                            printf("Este assento n�o foi reservado.\n\n");
                                        }
                                    }
                                }
                            }
                        }

//11 fun��o para consultar o status das poltronas
                        void consultarStatus()
                        {

                            printf ("**STATUS DAS POLTRONAS**\n\n");
                            for(int i=1; i<43; i++)
                            {
                                if(assentos[i] == '1') //verifica se o assento est� dispon�vel e imprime o n�mero da poltrona
                                {
                                    printf("%.2d ", i);
                                }
                                else
                                {
                                    if(assentos[i] == 'R') //verifica se o assento est� reservado e imprime AR
                                    {
                                        printf("AR ");
                                    }
                                    else if(assentos[i] == 'V') //verifica se o assento est� vendido e imprime AV
                                    {
                                        printf("AV ");
                                    }
                                }
                                if(i % 2 == 0) //formata��o
                                {
                                    printf("  ");
                                }
                                if(i % 4 == 0) //formata��o
                                {
                                    printf("\n");
                                }
                            }
                            printf("\n");
                        }

//fun��o para validar o CPF do cliente e para verificar se a lista de clientes j� est� criada ou n�o
                        int validarCliente(struct Cliente vet[], char cliente_cpf[])
                        {
                            int n, aux=0;
                            if(tam_atual>0)
                            {
                                n = strlen(cliente_cpf);
                                if(n == 11)
                                {
                                    for(int i=0; i<tam_atual; i++)
                                    {
                                        if(strcmp (vet[i].cpf, cliente_cpf)==0)
                                        {
                                            return 1;
                                            aux = 1;
                                        }
                                    }
                                    if(aux!=1)
                                    {
                                        printf("Cliente n�o encontrado!\n");
                                        return;
                                    }
                                }
                                else
                                {
                                    printf("Informe um CPF v�lido!\n\n");
                                    return;
                                }
                            }
                            else
                            {
                                printf("N�o h� nenhum cliente cadastrado!\n\n");
                                return;
                            }
                        }

//verifica se o arquivo j� existe
                        int arquivoExiste(char *fnome)
                        {
                            FILE *file;
                            if ((file = fopen(fnome, "r")))
                            {
                                fclose(file);
                                return 1;
                            }
                            return 0;
                        }

//caso o arquivo n�o exista, ele � criado
                        void salva(struct Cliente cli[], int tamCli, char assentos[], int tamA)
                        {
                            FILE *arqClientes = fopen("clientes.bin","wb");
                            FILE *arqAssentos = fopen("assentos.bin","wb");

                            fwrite(cli, sizeof(struct Cliente), tamCli, arqClientes);
                            fwrite(assentos, sizeof(char), tamA, arqAssentos);

                            fclose(arqClientes);
                            fclose(arqAssentos);
                        }

//caso o arquivo j� exista, ele � aberto para leitura
                        void carrega(struct Cliente cli[], int tamCli, char assentos[], int tamA)
                        {
                            FILE *arqClientes = fopen("clientes.bin","rb");
                            FILE *arqAssentos = fopen("assentos.bin","rb");

                            fread(cli, sizeof(struct Cliente), tamCli, arqClientes);
                            fread(assentos, sizeof(char), tamA, arqAssentos);

                            fclose(arqClientes);
                            fclose(arqAssentos);
                        }

//verifica quantos cadastros foram inseridos
                        int contaArquivo(char *nome)
                        {
                            int count=0;
                            if(arquivoExiste(nome))
                            {
                                FILE *arq = fopen(nome,"r+b");

                                fseek(arq, 0, SEEK_END);
                                count = ftell(arq) / sizeof(struct Cliente);

                                fclose(arq);
                            }

                            return count;
                        }



