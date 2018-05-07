#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
int main (void)
{
    char caminho[]="FlashBD.txt", linha[125], linhaComparar[125], respostaUsuario[117], senhaUsuario[8], cpf[11];
    int linNum = 0, qtdUsers, escolha;
    bool login = false, errorLogin = false;
    FILE *arq;

    arq = fopen(caminho, "r"); //r + = Abre um arquivo para atualizar leitura e grava��o. O arquivo deve existir.

	if(arq == NULL)
    {
        printf("Erro, nao foi possivel abrir o arquivo\n");
        return 0;
    }
    fscanf(arq, "%i", &qtdUsers);
    qtdUsers --;
    char usuarios[qtdUsers][255];
    printf("numero de usuarios cadastrados: %i \nConectando com o Banco de dados...", qtdUsers);
    fgets(&linha, &linNum, arq);
    while (linNum <= qtdUsers)
    {
        linNum++;
		fgets(&usuarios[linNum-1], &linNum, arq);
    }
    printf("OK\n");
    fclose(arq);
    printf("Escolha entre uma das opcoes: \n1-Login \n2-Cadastro \n3-Sair \nResposta: ");
    scanf("%d", &escolha);
    switch (escolha)
    {
        case 1:
            naoExisteUser:
            if (errorLogin == true)
                printf("Usuario ou Senha errados, tente novamente\n");
            printf("Digite o nome do Usuario: ");
            scanf("%s", &respostaUsuario);
            printf("Digite sua senha: ");
            scanf("%s", &senhaUsuario);
            strcpy(linhaComparar, respostaUsuario);
            strcat(linhaComparar, " ");
            strcat(linhaComparar, senhaUsuario);
            strcat(linhaComparar, "\n");

            if ((strcmp(usuarios[0],linhaComparar) > 0) || (strcmp(usuarios[qtdUsers],linhaComparar) < 0))
            {
                printf("linha 1: %s\n", usuarios[0]);
                printf("linha ultimo: %s\n", usuarios[qtdUsers]);
                printf("linha comp: %s\n", linhaComparar);
                errorLogin = true;
                goto naoExisteUser;
            }
            int ponteiro = (qtdUsers)/2;
            int max_elem = qtdUsers;
            int min_elem = 0;
            int cont = 0;
            printf("Consultando base de dados...");
            do
            {
                int result =strcmp(usuarios[ponteiro],linhaComparar);
                printf("%s, %s\n", usuarios[ponteiro], linhaComparar);
                if (result < 0)
                    min_elem = ponteiro + 1;
                else if(result > 0)
                    max_elem = ponteiro;
                else
                {
                    errorLogin = false;
                    login = true;
                    goto logou;
                }
                ponteiro = (min_elem + (max_elem/2));
                printf("min :%i, max: %i, ponteiro: %i\n", min_elem, max_elem, ponteiro);
            }while(ponteiro >= min_elem && ponteiro <= max_elem);

            printf("OK\n");
            errorLogin = true;
            goto naoExisteUser;
            break;
        case 2:
            retornarCadastro:
            printf("Digite seu CPF (Sem pontos ou espacos): ");
            scanf("%s", cpf);
            strcat(cpf, "\n");
            if (strlen(cpf)<11)
            {
                printf("CPF invalido por nao possuir numeros suficientes \n");
                goto retornarCadastro;
            }
            //if(validaCPF(cpf))
            arq = fopen("ValidaCPF.txt", "r+");
            if(arq == NULL)
            {
                printf("Erro, nao foi possivel abrir o arquivo de CPF\n");
                return 0;
            }
            printf("Consultando o Banco de dados...");
            bool existe = false;
            bool parar = false;
            fscanf(arq, "%i", &qtdUsers);
            char cpfs[qtdUsers+1][11];
            linNum = 1;
            //fgets(&linha, &linNum, arq);
            do
            {
                linNum++;
                fgets(&cpfs[linNum-2], &linNum, arq);
                //printf("\n%s", cpfs[linNum-2]);
                int cmp = strcmp(cpfs[linNum-2], cpf);
                if(cmp == 0)
                    existe = true;
                else if(cmp > 0)
                    parar = true;
            }while (linNum <= qtdUsers && (existe == false && parar == false));
            printf("OK\n");
            if(existe == true)
            {
                printf("Usuario ja existe, tente novamente\n");
                goto retornarCadastro;
            }
            printf("OK\n");
            nomeInv:
            printf("Escolha um nome de usuario [At� 117 caracteres]: ");
            scanf("%s", &respostaUsuario);
            //if(nomeJ�Existe);
            if(strlen(respostaUsuario)==0)
            {
                 printf("Nome invalido, tente novamente");
                 goto nomeInv;
            }
            printf("Digite sua senha [Exatamente 8 caracteres]: ");
            scanf("%s", &senhaUsuario);
            strcpy(linhaComparar, respostaUsuario);
            strcat(linhaComparar, " ");
            strcat(linhaComparar, senhaUsuario);
            strcat(linhaComparar, "\n");
            fclose(arq);

            break;
//        default:
            printf("Saindo... OK");
            //return 0;
    }
    logou:
    if(login == true)
        printf("\nSeja Bem vindo\n");


    return 1;
}
/* Valida��o de CPF
inline bool validaCPF(const int * const cpf)
{
    int digito1,
        digito2,
        temp = 0;

    for(char i = 0; i < 9; i++)
        temp += (cpf[i] * (10 - i));

    temp %= 11;

    if(temp < 2)
        digito1 = 0;
    else
        digito1 = 11 - temp;

    temp = 0;
    for(char i = 0; i < 10; i++)
        temp += (cpf[i] * (11 - i));

    temp %= 11;

    if(temp < 2)
        digito2 = 0;
    else
        digito2 = 11 - temp;

    if(digito1 == cpf[9] && digito2 == cpf[10])
        return true;
    else
        return false;
}
*/
