#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<string.h>
#include<windows.h>
#include<time.h>
#include<conio.h>


typedef struct{

    int cod,qtd;
    char nome[30];
    char autor[20];
    char area[15];

}LIVROS;

typedef struct{

    int matricula;
    char nome[30];
    char cpf[20];

}ALUNOS;

typedef struct{

    int mat;
    int code;
    char name[30];
    char nomealuno[30];
    int day,month,year,diadev,mesdev,anodev;

}EMPRESTIMO;

void carregando(){
    system("cls");
    esp_tab(13,40);
    printf("C "); Sleep(50); printf("A "); Sleep(50); printf("R "); Sleep(50); printf("R "); Sleep(50); printf("E "); Sleep(50);
    printf("G "); Sleep(50); printf("A "); Sleep(50); printf("N "); Sleep(50); printf("D "); Sleep(50); printf("O"); Sleep(50);
    int i;
    for(i=0;i<5;i++){
        printf(".");
        Sleep(50);
    }
    system("cls");
}

dataint(char* x, int *dd, int *mm, int *aa)
{
    char numeros[10]={'0','1','2','3','4','5','6','7','8','9'};
    int i, j, v[6], count=0, dia, dia2, mes, mes2, ano, ano2;

    for(i=0;i<11;i++)
    {
        if(i!=2 && i!=5)
        {
            for(j=0;j<11;j++)
            {
                if(x[i]==numeros[j])
                {
                    v[count]=j;
                    count++;
                }
            }
        }
    }
    for(i=0;i<6;i++)
    {
        if(i%2==0)
        {
            if(i==0)
            {
                mes=(v[i]*10);
            }
            if(i==2)
            {
                dia=(v[i]*10);
            }
            if(i==4)
            {
                ano=(v[i]*10);
            }
        }
        if(i%2==1)
        {
            if(i==1)
            {
                mes2=v[i];
            }
            if(i==3)
            {
                dia2=v[i];
            }
            if(i==5)
            {
                ano2=v[i];
            }
        }
    }
    *dd=dia+dia2;
    *mm=mes+mes2;
    *aa=ano+ano2;
}

devolucao(int dia, int mes, int ano, int *diadev, int *mesdev, int *anodev)
{
    int v[12]={31,28,31,30,31,30,31,31,30,31,30,31}, i;
    for(i=0;i<12;i++)
    {
        if(mes==i+1)
        {
            if(dia+10<=v[i+1])
            {
                *diadev=dia+10;
                *mesdev=mes;
                *anodev=ano;
            }
            else
            {
                *mesdev=mes+1;
                *diadev=((dia+10)-v[i]);
                *anodev=ano;
                if(mes==12)
                {
                    *mesdev=1;
                    *anodev=ano+1;
                }
            }
        }
    }
}

void opcao_invalida(){
    system("cls");
    esp_tab(13,45);
    printf("OPÇÃO INVÁLIDA!");
    Sleep(1000);
    system("cls");
}

esp_tab (int quantesp, int quanttab){
    int i;
    for(i=0;i<quantesp;i++)
        puts("");
    for(i=0;i<quanttab;i++)
        printf(" ");
}

void cadastro_livro(){
    carregando();
    LIVROS cad;
    FILE *cadl = fopen("livros.txt","ab+");
    esp_tab(9,40);  printf("Nome do livro: "); fflush(stdin);
    gets(cad.nome);
    esp_tab(0,40);  printf("Autor principal: ");        fflush(stdin);
    gets(cad.autor);
    esp_tab(0,40);  printf("Área de conhecimento: ");   fflush(stdin);
    gets(cad.area);
    esp_tab(0,40);  printf("Exmplares disponíveis: ");     fflush(stdin);
    scanf("%d",&cad.qtd);
    esp_tab(0,40);  printf("Código do livro: ");
    scanf("%d",&cad.cod);
    fwrite(&cad,sizeof(LIVROS),1,cadl);
    fclose(cadl);
    system("cls");esp_tab(9,40);
    printf("CADASTRO REALIZADO\n");
    Sleep(1000);
    carregando();
    system("cls");
}

void editar_livro(){
    LIVROS cad;
    FILE *cadl;
    char nome[40];
    int o,codigo,k=0;

    cadl = fopen("livros.txt","r+b");

    if(cadl==NULL){
        printf(" ERRO: arquivo nao encontrado\n");Sleep(1500);
        system("cls");
        return;
    }
    system("cls");
    esp_tab(9,40);
    printf(" 1 - BUSCAR POR NOME");esp_tab(1,40);
    printf(" 2 - BUSCAR POR CODIGO ");esp_tab(1,40);
    o = getch();
    switch(o){
        case '1':
            system("cls");
            esp_tab(9,40);
            printf("DIGITE O NOME DO LIVRO: ");
            gets(nome);
            while(fread(&cad,sizeof(LIVROS),1,cadl)==1){

                if(strcmp(nome,cad.nome)==0){
                    k++;

                    EMPRESTIMO ep;
                    FILE *emp = fopen("emprestimos.txt","rb");

                    while(fread(&ep,sizeof(EMPRESTIMO),1,emp)==1){
                        if(strcmp(nome,ep.name)==0){
                            fclose(cadl);
                            system("cls");esp_tab(9,40);
                            printf("LIVRO NAO PODE SER EDITADO\n\n");Sleep(1500);
                            system("cls");
                            return;
                        }
                    }
                    fclose(emp);
                    esp_tab(1,40);
                    printf("LIVRO ENCONTRADO\n");
                    esp_tab(1,40);
                    printf("Digite o novo nome do livro: ");fflush(stdin);
                    gets(cad.nome);esp_tab(1,40);
                    printf("Digite o novo autor: ");fflush(stdin);
                    gets(cad.autor);esp_tab(1,40);
                    printf("Digite a area de conhecimento: ");fflush(stdin);
                    gets(cad.area);esp_tab(1,40);
                    printf("Digite codigo do livro: ");
                    scanf("%d",&cad.cod);esp_tab(1,40);
                    printf("Digite a quantidade de exemplares: ");
                    scanf("%d",&cad.qtd);esp_tab(1,40);
                    fseek(cadl,ftell(cadl)-sizeof(LIVROS),0);
                    fwrite(&cad,sizeof(LIVROS),1,cadl);
                    fclose(cadl);
                    system("cls");esp_tab(9,40);
                    printf("LIVRO EDITADO COM SUCESSO\n");Sleep(1500);
                    system("cls");
                }

            }

            if(k==0){
                fclose(cadl);
                system("cls");esp_tab(9,40);
                printf("LIVRO NAO ENCONTRADO\n");Sleep(1500);
                system("cls");
                break;
            }

        break;

        case '2':

            printf("DIGITE O CODIGO DO LIVRO: ");
            scanf("%d",&codigo);
            while(fread(&cad,sizeof(LIVROS),1,cadl)==1){

                if(codigo==cad.cod){
                    k++;
                    EMPRESTIMO ep;
                    FILE *emp = fopen("emprestimos.txt","rb");

                    while(fread(&ep,sizeof(EMPRESTIMO),1,emp)==1){
                        if(codigo==ep.code){
                            fclose(cadl);
                            system("cls");esp_tab(9,40);
                            printf("LIVRO NAO PODE SER EDITADO\n\n");Sleep(1500);
                            system("cls");
                            return;
                        }
                    }
                    fclose(emp);
                    esp_tab(1,40);
                    printf("LIVRO ENCONTRADO\n");
                    printf("Digite o novo nome do livro: ");fflush(stdin);
                    gets(cad.nome);
                    printf("Digite o novo autor: ");fflush(stdin);
                    gets(cad.autor);
                    printf("Digite a area de conhecimento: ");fflush(stdin);
                    gets(cad.area);
                    printf("Digite codigo do livro: ");
                    scanf("%d",&cad.cod);
                    printf("Digite a quantidade de exemplares: ");
                    scanf("%d",&cad.qtd);
                    fseek(cadl,ftell(cadl)-sizeof(LIVROS),0);
                    fwrite(&cad,sizeof(LIVROS),1,cadl);
                    fclose(cadl);
                    system("cls");esp_tab(9,40);
                    printf("LIVRO EDITADO COM SUCESSO\n");Sleep(1500);
                    system("cls");
                }
            }
            if(k==0){
                fclose(cadl);
                system("cls");esp_tab(9,40);
                printf("LIVRO NAO ENCONTRADO\n");Sleep(1500);
                system("cls");
                break;
            }

        break;
    }
}

void remover_livro(){
    carregando();
    LIVROS cad;
    int o,k=0,c=0,r=0;
    char nome[30];


    FILE *cadl = fopen("livros.txt","rb");
    FILE *cadl2 = fopen("auxiliar.txt","wb");
    esp_tab(9,40);
    printf("1 - REMOVER POR NOME\n");     esp_tab(1,40);
    printf("2 - REMOVER POR CÓDIGO\n");   esp_tab(1,40);
    printf("OPÇÃO: ");
    o = getch();
    switch(o){
        case '1':
            if(cadl==NULL){
                system("cls");esp_tab(9,40);
                printf("ERRO: Arquivo não encontrado ");Sleep(1500);
                fclose(cadl2);
                remove("auxiliar.txt");
                system("cls");
                return;
            }
            system("cls");
            esp_tab(9,40);
            printf("DIGITE O NOME DO LIVRO: "); fflush(stdin);
            gets(nome);


                while(fread(&cad,sizeof(LIVROS),1,cadl)==1){
                    if(strcmp(nome,cad.nome)==0){
                    k++;esp_tab(1,40);
                    printf("LIVRO ENCONTRADO\n\n");
                    //---------------------------------------------------------
                    EMPRESTIMO ep;
                    FILE *emp = fopen("emprestimos.txt","rb");

                    while(fread(&ep,sizeof(EMPRESTIMO),1,emp)==1){
                        if(strcmp(nome,ep.name)==0){
                            fclose(emp);
                            fclose(cadl2);
                            remove("auxiliar.txt");
                            fclose(cadl);
                            system("cls");esp_tab(9,40);
                            printf("LIVRO NAO PODE SER REMOVIDO\n\n");Sleep(1500);
                            system("cls");
                            return;
                        }
                    }
                    fclose(emp);
                    //-------------------------------------------------------------

                    }else{
                        fwrite(&cad,sizeof(LIVROS),1,cadl2);
                    }
                }
                if(k==0){
                    fclose(cadl2);
                    remove("auxiliar.txt");
                    fclose(cadl);
                    system("cls");
                    esp_tab(9,40);
                    printf("LIVRO NÃO ENCONTRADO\n");Sleep(1500);
                    system("cls");
                    break;
                }
                else{
                fclose(cadl);
                remove("livros.txt");
                fclose(cadl2);
                rename("auxiliar.txt","livros.txt");
                system("cls");
                esp_tab(9,40);
                printf("LIVRO REMOVIDO COM SUCESSO\n\n\n");Sleep(1500);
                system("cls");
                break;
                }

        break;

        case '2':
            if(cadl==NULL){
                system("cls");esp_tab(9,40);
                printf("ERRO: Arquivo não encontrado");Sleep(1500);
                fclose(cadl2);
                remove("auxiliar.txt");
                carregando();
                return;
            }
            system("cls");
            esp_tab(9,40);
            printf("DIGITE O CODIGO DO LIVRO: ");esp_tab(1,40);
            scanf("%d",&c);
            while(fread(&cad,sizeof(LIVROS),1,cadl)==1){
                if(c==cad.cod){
                k++;esp_tab(1,40);
                printf("LIVRO ENCONTRADO\n");
                EMPRESTIMO ep;
                FILE *emp = fopen("emprestimos.txt","rb");

                while(fread(&ep,sizeof(EMPRESTIMO),1,emp)==1){
                    if(strcmp(nome,ep.name)==0){
                        fclose(emp);
                        fclose(cadl2);
                        remove("auxiliar.txt");
                        fclose(cadl);
                        system("cls");esp_tab(9,40);
                        printf("LIVRO NAO PODE SER REMOVIDO\n\n");Sleep(1500);
                        system("cls");
                        return;
                        }
                    }
                fclose(emp);
                }else{
                    fwrite(&cad,sizeof(LIVROS),1,cadl2);
                }
            }
            if(k==0){
                fclose(cadl2);
                remove("auxiliar.txt");
                fclose(cadl);
                system("cls");esp_tab(9,40);
                printf("LIVRO NÃO ENCONTRADO\n");Sleep(1500);
                system("cls");
                break;
            }
            else{
            fclose(cadl);
            remove("livros.txt");
            fclose(cadl2);
            rename("auxiliar.txt","livros.txt");
            system("cls");esp_tab(9,40);
            printf("LIVRO REMOVIDO COM SUCESSO\n\n\n");Sleep(1500);
            system("cls");
            break;
            }
        break;

        default:
            opcao_invalida();
            break;
    }

}

void listar_livros(){
    carregando();
    LIVROS cad;
    FILE* cadl = fopen("livros.txt","rb");
    if(cadl==NULL){
        printf("\nERRO: Arquivo não encontrado\n");
        system("\npause");
        carregando();
        return;
    }

            rewind(cadl);
            if(fgetc(cadl)==EOF){
                system("cls");
                esp_tab(9,40);
                printf("NENHUM LIVRO ENCONTRADO\n");Sleep(1500);
                carregando();
                return;
            }
            rewind(cadl);

    while(fread(&cad,sizeof(LIVROS),1,cadl)==1 ){
        printf("NOME: %s\n",cad.nome);
        printf("AUTOR: %s\n",cad.autor);
        printf("AREA: %s\n",cad.area);
        printf("QUANTIDADE: %d\n",cad.qtd);
        printf("CÓDIGO: %d\n\n",cad.cod);
    }

    fclose(cadl);
    system("\npause");
    system("cls");
}

void cadastro_aluno(){
    carregando();
    ALUNOS al;
    FILE* alun = fopen("alunos.txt","ab+");
    esp_tab(9,40);
    printf("Digite o nome do aluno: ");fflush(stdin);
    gets(al.nome);esp_tab(0,40);
    printf("Matricula: ");
    scanf("%d",&al.matricula);esp_tab(0,40);
    printf("CPF: ");fflush(stdin);
    gets(al.cpf);
    fwrite(&al,sizeof(ALUNOS),1,alun);
    fclose(alun);
    esp_tab(9,40);
    printf("CADASTRO REALIZADO\n");
    Sleep(800);
    carregando();
    system("cls");
}

void remover_aluno(){
    carregando();
    ALUNOS al;
    system("cls");
    int o,k=0,c;
    char nomeal[30];
    FILE *aluno = fopen("alunos.txt","rb");
    FILE *aluno2 = fopen("alaux.txt","ab+");
    esp_tab(9,40);
    printf("1 - NOME\n");esp_tab(1,40);
    printf("2 - MATRICULA ");
    o = getch();
    switch(o){
        case '1':
            if(aluno==NULL){
                system("cls");esp_tab(9,40);
                printf("ERRO: Arquivo não encontrado");Sleep(1500);
                fclose(aluno2);
                remove("alaux.txt");
                system("cls");
                break;
            }
            system("cls");esp_tab(9,40);
            printf("DIGITE O NOME DO ALUNO: ");fflush(stdin);
            gets(nomeal);
            while(fread(&al,sizeof(ALUNOS),1,aluno)==1){
                if(strcmp(nomeal,al.nome)==0){
                k++;esp_tab(1,40);
                printf("ALUNO: %s\n\n",al.nome);
                //------------------------------------------------------
                EMPRESTIMO ep;
                    FILE *emp = fopen("emprestimos.txt","rb");

                    while(fread(&ep,sizeof(EMPRESTIMO),1,emp)==1){
                        if(strcmp(nomeal,ep.nomealuno)==0){
                            fclose(emp);
                            fclose(aluno2);
                            fclose(aluno);
                            remove("alaux.txt");
                            system("cls");esp_tab(9,40);
                            printf("ALUNO NAO PODE SER REMOVIDO\n\n");Sleep(1500);
                            system("cls");
                            return;
                        }
                    }
                    fclose(emp);
                //----------------------------------------------------------
                }else{
                    fwrite(&al,sizeof(ALUNOS),1,aluno2);
                }
            }
            if(k==0){
                fclose(aluno2);
                fclose(aluno);
                remove("alaux.txt");
                system("cls");esp_tab(9,40);
                printf("ALUNO NÃO ENCONTRADO\n");Sleep(1500);
                system("cls");
                break;
            }
            else{
            fclose(aluno2);
            fclose(aluno);
            remove("alunos.txt");
            rename("alaux.txt","alunos.txt");
            system("cls");esp_tab(9,40);
            printf("ALUNO REMOVIDO COM SUCESSO\n");Sleep(1500);
            system("cls");
            break;
            }
        break;

        case '2':

            if(aluno==NULL){
                system("cls");esp_tab(9,40);
                printf("ERRO: Arquivo não encontrado");Sleep(1500);
                fclose(aluno2);
                remove("alaux.txt");
                system("\n\n\npause");
                carregando();
                break;
            }
            system("cls");esp_tab(9,40);
            printf("DIGITE A MATRICULA DO ALUNO ");
            scanf("%d",&c);
            while(fread(&al,sizeof(ALUNOS),1,aluno)==1){
                if(c==al.matricula){
                k++;esp_tab(1,40);
                printf("ALUNO: %s\n\n",al.nome);

                EMPRESTIMO ep;
                FILE *emp = fopen("emprestimos.txt","rb");

                while(fread(&ep,sizeof(EMPRESTIMO),1,emp)==1){
                    if(c==ep.mat){
                    system("cls");esp_tab(9,40);
                    printf("ALUNO NAO PODE SER REMOVIDO\n\n");Sleep(1500);
                    carregando();
                    return;
                    }
                }
                fclose(emp);
                }else{
                    fwrite(&al,sizeof(ALUNOS),1,aluno2);
                }
            }
            if(k==0){
                fclose(aluno2);
                fclose(aluno);
                remove("alaux.txt");
                system("cls");esp_tab(9,40);
                printf("ALUNO NÃO ENCONTRADO\n");Sleep(1500);
                system("cls");
                break;
            }
            else{
            fclose(aluno2);
            fclose(aluno);
            remove("alunos.txt");
            rename("alaux.txt","alunos.txt");
            system("cls");esp_tab(9,40);
            printf("ALUNO REMOVIDO COM SUCESSO\n");Sleep(1500);
            system("cls");
            break;
            }

        break;

        default:
            opcao_invalida();
            break;
    }

}

void editar_aluno(){
    ALUNOS al;
    FILE *alun;
    char nome[40];
    int o,mat,k=0;

    alun = fopen("alunos.txt","r+b");

    if(alun==NULL){
        system("cls");esp_tab(9,40);
        printf("ERRO: arquivo nao encontrado\n\n\n");Sleep(1500);
        system("cls");
        return;
    }
    system("cls");esp_tab(9,40);
    printf(" 1 - BUSCAR POR NOME");esp_tab(1,40);
    printf(" 2 - BUSCAR POR MATRICULA ");esp_tab(1,40);
    o = getch();
    switch(o){
        case '1':
            system("cls");
            esp_tab(9,40);
            printf("DIGITE O NOME DO ALUNO: ");fflush(stdin);
            gets(nome);
            while(fread(&al,sizeof(ALUNOS),1,alun)==1){

                if(strcmp(nome,al.nome)==0){
                    k++;

                    EMPRESTIMO ep;
                    FILE *emp = fopen("emprestimos.txt","rb");

                    while(fread(&ep,sizeof(EMPRESTIMO),1,emp)==1){
                        if(strcmp(nome,ep.nomealuno)==0){
                            fclose(emp);
                            fclose(alun);
                            system("cls");esp_tab(9,40);
                            printf("ALUNO NAO PODE SER EDITADO\n\n");Sleep(1500);
                            system("cls");
                            return;
                        }
                    }
                    fclose(emp);

                    esp_tab(1,40);
                    printf("Digite o novo nome do aluno: ");fflush(stdin);
                    gets(al.nome);esp_tab(1,40);
                    printf("Digite o novo CPF: ");fflush(stdin);
                    gets(al.cpf);esp_tab(1,40);
                    printf("Digite a nova matricula: ");fflush(stdin);
                    scanf("%d",&al.matricula);esp_tab(1,40);
                    fseek(alun,ftell(alun)-sizeof(ALUNOS),0);
                    fwrite(&al,sizeof(ALUNOS),1,alun);
                    fclose(alun);
                    system("cls");esp_tab(9,40);
                    printf("ALUNO EDITADO COM SUCESSO\n");Sleep(1500);
                    system("cls");

                }

            }

            if(k==0){
                fclose(alun);
                system("cls");esp_tab(9,40);
                printf("ALUNO NAO ENCONTRADO\n");Sleep(1500);
                system("cls");
                break;
            }

        break;

        case '2':

            printf("DIGITE A MATRICULA DO ALUNO: ");
            scanf("%d",&mat);
            while(fread(&al,sizeof(ALUNOS),1,alun)==1){

                if(mat==al.matricula){
                    k++;

                    EMPRESTIMO ep;
                    FILE *emp = fopen("emprestimos.txt","rb");

                    while(fread(&ep,sizeof(EMPRESTIMO),1,emp)==1){
                        if(mat==ep.mat){
                            fclose(emp);
                            fclose(alun);
                            system("cls");esp_tab(9,40);
                            printf("ALUNO NAO PODE SER EDITADO\n\n");Sleep(1500);
                            return;
                        }
                    }
                    fclose(emp);
                    esp_tab(1,40);
                    printf("Digite o novo nome do aluno: ");fflush(stdin);
                    gets(al.nome);esp_tab(1,40);
                    printf("Digite o novo CPF: ");fflush(stdin);
                    gets(al.cpf);esp_tab(1,40);
                    printf("Digite a nova matricula: ");
                    scanf("%d",&al.matricula);esp_tab(1,40);
                    fseek(alun,ftell(alun)-sizeof(ALUNOS),0);
                    fwrite(&al,sizeof(ALUNOS),1,alun);
                    fclose(alun);
                    system("cls");esp_tab(9,40);
                    printf("ALUNO EDITADO COM SUCESSO\n");Sleep(1500);
                    system("cls");
                }
            }
            if(k==0){
                fclose(alun);
                system("cls");esp_tab(9,40);
                printf("ALUNO NAO ENCONTRADO\n");Sleep(1500);
                system("cls");
                break;
            }
        break;
    }
}

void listar_aluno(){
    carregando();
    ALUNOS al;
    FILE* alun = fopen("alunos.txt","rb");
    if(alun == NULL){
        printf("\nERRO: Arquivo não encontrado\n");
        system("\npause");
        carregando();
        return;
    }

    rewind(alun);
    if(fgetc(alun)==EOF){
        system("cls");
        esp_tab(9,40);
        printf("NENHUM ALUNO ENCONTRADO\n");Sleep(1500);
        carregando();
        return;
    }
    rewind(alun);

    while(fread(&al,sizeof(ALUNOS),1,alun) == 1){
        printf("ALUNO: %s\n",al.nome);
        printf("MATRICULA: %d\n",al.matricula);
        printf("CPF: %s\n\n",al.cpf);
    }
    fclose(alun);
    system("\npause");
    carregando();
}


void novo_emprestimo(){
    FILE *cadl,*emp,*alun;
    LIVROS cad;
    ALUNOS al;
    EMPRESTIMO ep;
    int mat,o,codigo,k=0,l=0,opk;
    char nome[30];
    system("cls");
    esp_tab(9,40);
    printf("1 - BUSCAR POR CODIGO DO LIVRO");esp_tab(1,40);
    printf("2 - BUSCAR POR NOME DO LIVRO ");
    o = getch();
    switch(o){
        case '1':

            cadl = fopen("livros.txt","rb");
            if(cadl==NULL){
                printf("\nERRO: Arquivo não encontrado\n");
                getch();
            exit(1);
            }
            esp_tab(1,40);
            printf("\nDigite o codigo do livro: ");
            scanf("%d",&codigo);

            while(fread(&cad,sizeof(LIVROS),1,cadl) == 1){

                if(codigo==cad.cod){
                    k++;esp_tab(1,40);
                    printf("Livro encontrado");esp_tab(1,40);
                    printf("NOME: %s",cad.nome);esp_tab(1,40);
                    printf("CÓDIGO: %d",cad.cod);esp_tab(1,40);
                    printf("Digite sua matricula: ");
                    scanf("%d",&mat);

                    alun = fopen("alunos.txt","rb");
                    while(fread(&al,sizeof(ALUNOS),1,alun) == 1){

                        if(mat==al.matricula){
                            l++;
                            emp = fopen("emprestimos.txt","ab+");
                            strcpy(ep.name,cad.nome);
                            ep.code=cad.cod;
                            ep.mat=al.matricula;
                            strcpy(ep.nomealuno,al.nome);
                        //-----------------------------------------------------------
                            int dia=0,mes=0,ano=0, diadev=0, mesdev=0, anodev=0;
                            char data[9];
                            _strdate(data);
                            dataint(data,&dia, &mes, &ano);
                            ep.day = dia;
                            ep.month = mes;
                            ep.year = ano;
                            devolucao(dia, mes, ano, &diadev, &mesdev, &anodev);
                            ep.diadev = diadev;
                            ep.mesdev = mesdev;
                            ep.anodev = anodev;

                        //---------------------------------------------------------
                            fwrite(&ep,sizeof(EMPRESTIMO),1,emp);

                        }
                    }
                    fclose(alun);

                }
            }
            if(k==0 || l==0){
                fclose(cadl);
                system("cls");esp_tab(9,20);
                printf("NÃO FOI POSSÍVEL REALIZAR O EMPRÉSTIMO, MATRÍCULA OU LIVRO NÃO CADASTRADOS\n");
                system("\npause");
                break;
            }
       system("cls");
        esp_tab(9,40);
       printf("LIVRO EMPRESTADO COM SUCESSO\n");Sleep(1500);
       fclose(cadl);
       fclose(alun);
       fclose(emp);

       cadl = fopen("livros.txt","r+b");
        while(fread(&cad,sizeof(LIVROS),1,cadl) == 1){
            if(codigo==cad.cod){
                strcpy(cad.nome,cad.nome);
                strcpy(cad.area,cad.area);
                strcpy(cad.autor,cad.autor);
                cad.cod=cad.cod;
                cad.qtd = cad.qtd - 1;
                fseek(cadl,ftell(cadl)-sizeof(LIVROS),0);
                fwrite(&cad,sizeof(LIVROS),1,cadl);
                fclose(cadl);
            }
        }
       carregando();
       break;

        case '2':

            cadl = fopen("livros.txt","rb");
            if(cadl==NULL){
                printf("\nERRO: Arquivo não encontrado\n");
                getch();
            exit(1);
            }
            system("cls");esp_tab(9,40);
            printf("Digite nome do livro: ");fflush(stdin);
            gets(nome);


            while(fread(&cad,sizeof(LIVROS),1,cadl) == 1){

                if(strcmp(nome,cad.nome)==0){
                    k++;esp_tab(1,40);
                    printf("Livro encontrado");esp_tab(1,40);
                    printf("NOME: %s",cad.nome);esp_tab(1,40);
                    printf("CÓDIGO: %d",cad.cod);esp_tab(1,40);
                    printf("Digite sua matricula: ");
                    scanf("%d",&mat);
                    alun = fopen("alunos.txt","rb");

                    while(fread(&al,sizeof(ALUNOS),1,alun) == 1){

                        if(mat==al.matricula){
                            l++;
                            emp = fopen("emprestimos.txt","ab+");
                            strcpy(ep.name,cad.nome);
                            ep.code=cad.cod;
                            ep.mat=al.matricula;
                            strcpy(ep.nomealuno,al.nome);

                            //-----------------------------------------------------------
                            int dia=0,mes=0,ano=0, diadev=0, mesdev=0, anodev=0;
                            char data[9];
                            _strdate(data);
                            dataint(data,&dia, &mes, &ano);
                            ep.day = dia;
                            ep.month = mes;
                            ep.year = ano;
                            devolucao(dia, mes, ano, &diadev, &mesdev, &anodev);
                            ep.diadev = diadev;
                            ep.mesdev = mesdev;
                            ep.anodev = anodev;

                        //---------------------------------------------------------

                            fwrite(&ep,sizeof(EMPRESTIMO),1,emp);
                        }
                    }
                    fclose(alun);
                }
            }

            if(k==0 || l==0){
                fclose(cadl);
                system("cls");esp_tab(9,20);
                printf("NÃO FOI POSSÍVEL REALIZAR O EMPRÉSTIMO, MATRÍCULA OU LIVRO NÃO CADASTRADOS\n");
                system("\npause");
                carregando();
                break;
            }else{

            system("cls");
            esp_tab(9,40);
            printf("LIVRO EMPRESTADO COM SUCESSO\n");Sleep(1500);
            fclose(cadl);
            fclose(alun);
            fclose(emp);

            cadl = fopen("livros.txt","r+b");
            while(fread(&cad,sizeof(LIVROS),1,cadl) == 1){

                if(strcmp(nome,cad.nome)==0){
                    strcpy(nome,cad.nome);
                    strcpy(cad.area,cad.area);
                    strcpy(cad.autor,cad.autor);
                    cad.cod=cad.cod;
                    cad.qtd = cad.qtd - 1;
                    fseek(cadl,ftell(cadl)-sizeof(LIVROS),0);
                    fwrite(&cad,sizeof(LIVROS),1,cadl);
                    fclose(cadl);
                }
            }
            fclose(cadl);
            carregando();
            break;
            }

    }

}

void cancelar_emprestimo(){
    carregando();
    int o,k=0;
    char nomeal[30],nomeli[40];
    EMPRESTIMO ep;LIVROS cad;
    FILE *emp = fopen("emprestimos.txt","rb");
    FILE *emp2 = fopen("epaux.txt","ab+");
    FILE *cadl;

            if(emp==NULL){
                system("cls");
                esp_tab(9,40);
                printf("ERRO: Arquivo não encontrado\n\n");
                fclose(emp2);
                fclose(emp);
                remove("epaux.txt");
                system("pause");
                system("cls");
                return;
            }
            esp_tab(9,40);
            printf("Digite o nome do livro: "); fflush(stdin);
            gets(nomeli);

            while(fread(&ep,sizeof(EMPRESTIMO),1,emp)==1){
                if(strcmp(nomeli,ep.name)==0){
                k++;
                esp_tab(1,40);
                printf("EMPRESTIMO ENCONTRADO\n");
                }else{
                    fwrite(&ep,sizeof(EMPRESTIMO),1,emp2);
                }
            }
            if(k==0){
                esp_tab(1,40);
                printf("EMPRESTIMO NÃO ENCONTRADO\n");
                remove("epaux.txt");
                fclose(emp2);
                fclose(emp);
                system("\npause");
                carregando();
                return;
            }
            else{
            fclose(emp2);
            fclose(emp);
            remove("emprestimos.txt");
            rename("epaux.txt","emprestimos.txt");esp_tab(1,40);
            printf("EMPRESTIMO CANCELADO COM SUCESSO\n");Sleep(1500);


        //-------------------------------------------------------------
            cadl = fopen("livros.txt","r+b");
            while(fread(&cad,sizeof(LIVROS),1,cadl) == 1){
                if(strcmp(nomeli,cad.nome)==0){
                    strcpy(cad.nome,cad.nome);
                    strcpy(cad.area,cad.area);
                    strcpy(cad.autor,cad.autor);
                    cad.cod=cad.cod;
                    cad.qtd = cad.qtd + 1;
                    fseek(cadl,ftell(cadl)-sizeof(LIVROS),0);
                    fwrite(&cad,sizeof(LIVROS),1,cadl);
                    fclose(cadl);
                }
            }
            fclose(cadl);
        //-------------------------------------------------------------


            carregando();
            return;

            }

}

void lista_emprestimo(){
    system("cls");
    EMPRESTIMO ep;
    int k=0,o;
    char livro[30],aluno[30];
    FILE *emp = fopen("emprestimos.txt","rb");

    if(emp==NULL){
        printf("ERRO: Arquivo não encontrado\n");
        system("pause");
        carregando();
        return;
    }
    carregando();
    esp_tab(9,40);
    printf("1 - LISTAR TODOS");esp_tab(1,40);
    printf("2 - LISTAR POR LIVRO");esp_tab(1,40);
    printf("3 - LISTAR POR ALUNO\n");esp_tab(1,40);
    printf("OPCAO ");
    o = getch();
    carregando();

    switch(o){
        case '1':
            rewind(emp);
            if(fgetc(emp)==EOF){
                system("cls");
                esp_tab(9,40);
                printf("NENHUM EMPRESTIMO ENCONTRADO\n");Sleep(1500);
                fclose(emp);
                carregando();
                break;
            }
            rewind(emp);
            while(fread(&ep,sizeof(EMPRESTIMO),1,emp)==1){
                printf("\nMATRICULA: %d\nNOME DO LIVRO: %s\nCÓDIGO DO LIVRO: %d\nEMPRESTIMO EM: %.2d/%.2d/%.2d ",ep.mat,ep.name,ep.code,ep.day,ep.month,ep.year);
                printf(" | DEVOLUÇÃO ATÉ: %.2d/%.2d/%.2d\n",ep.diadev,ep.mesdev,ep.anodev);
            }

            esp_tab(9,40);
            fclose(emp);
            system("\npause");
            carregando();
            break;
        break;

        case '2':
            esp_tab(1,40);
            printf("Digite o nome do livro: ");fflush(stdin);
            gets(livro);
            rewind(emp);
            if(fgetc(emp)==EOF){
                system("cls");
                esp_tab(9,40);
                printf("NENHUM EMPRESTIMO ENCONTRADO\n");Sleep(1500);
                fclose(emp);
                carregando();
                break;
            }
            rewind(emp);
            while(fread(&ep,sizeof(EMPRESTIMO),1,emp)==1){

                if(strcmp(livro,ep.name)==0){
                    k++;
                    printf("NOME DO LIVRO: %s\nCÓDIGO DO LIVRO: %d\nEMPRESTADO A: %s\nEMPRETIMO EM: %.2d/%.2d/%.2d ",ep.name,ep.code,ep.nomealuno,ep.day,ep.month,ep.year);
                    printf(" | DEVOLUÇÃO ATÉ: %.2d/%.2d/%.2d\n\n",ep.diadev,ep.mesdev,ep.anodev);

                }
            }
            if(k==0){
                esp_tab(1,40);
                printf("O livro não foi emprestado\n");
            }
            fclose(emp);
            system("\npause");
            carregando();
            break;
        break;

        case '3':
            esp_tab(1,40);
            printf("Digite o nome do aluno: ");fflush(stdin);
            gets(aluno);
            rewind(emp);
            if(fgetc(emp)==EOF){
                system("cls");
                esp_tab(9,40);
                printf("NENHUM EMPRESTIMO ENCONTRADO\n");Sleep(1500);
                fclose(emp);
                carregando();
                break;
            }
            rewind(emp);
            while(fread(&ep,sizeof(EMPRESTIMO),1,emp)==1){

                if(strcmp(aluno,ep.nomealuno)==0){
                    k++;
                    printf("ALUNO: %s\nNOME DO LIVRO: %s\nCÓDIGO DO LIVRO: %d\nEMPRESTIMO EM: %.2d/%.2d/%.2d",ep.nomealuno,ep.name,ep.code,ep.day,ep.month,ep.year);
                    printf(" | DEVOLUÇÃO ATÉ: %.2d/%.2d/%.2d\n\n",ep.diadev,ep.mesdev,ep.anodev);
                }
            }
            if(k==0){
                esp_tab(1,40);
                printf("Aluno sem emprestimos\n");
            }
            fclose(emp);
            system("\npause");
            carregando();
            break;

        break;
    }
}

main(){
    setlocale(LC_ALL,"");
    int o,o1,o2,o3;
    system("color F0");
    while(o){
        esp_tab(9,40);
        printf("BIBLIOTECA UEPB\n\n");      esp_tab(1,40);
        printf("1 - LIVROS\n");             esp_tab(1,40);
        printf("2 - ALUNOS \n");            esp_tab(1,40);
        printf("3 - EMPRÉSTIMOS\n");        esp_tab(1,40);
        printf("4 - SAIR\n");               esp_tab(1,40);
        printf("OPÇÃO: ");
        o = getch();
        switch(o){
            case '1':
                carregando();
                esp_tab(9,40);
                printf("ACERVO DE LIVROS\n\n");             esp_tab(1,40);
                printf("1 - Cadastrar Livro\n");            esp_tab(1,40);
                printf("2 - Editar Livro\n");               esp_tab(1,40);
                printf("3 - Remover Livro\n");              esp_tab(1,40);
                printf("4 - Listar Livros Cadastrados\n");  esp_tab(1,40);
                printf("5 - Voltar\n");                      esp_tab(1,40);
                printf("OPCÃO: ");
                o1 = getch();
                switch(o1){

                    case '1':
                        cadastro_livro();
                    break;
                    case '2':
                        editar_livro();
                    break;
                    case '3':
                        remover_livro();
                    break;
                    case '4':
                        listar_livros();
                    break;
                    case '5':
                        carregando();
                        main();
                    break;
                    default:
                        opcao_invalida();
                    break;
                }
                break;

            case '2':
                carregando();
                esp_tab(9,48);
                printf("ALUNOS\n\n");                       esp_tab(1,40);
                printf("1 - Cadastrar Aluno\n");            esp_tab(1,40);
                printf("2 - Editar Dados de um Aluno\n");   esp_tab(1,40);
                printf("3 - Remover Aluno\n");              esp_tab(1,40);
                printf("4 - Listar Alunos Cadastrados\n");  esp_tab(1,40);
                printf("5 - Voltar\n");                     esp_tab(1,40);
                printf("OPÇÃO: ");
                o2 = getch();
                switch(o2){

                    case '1':
                        cadastro_aluno();
                    break;
                    case '2':
                        editar_aluno();
                    break;
                    case '3':
                        remover_aluno();
                    break;
                    case '4':
                        listar_aluno();
                    break;
                    case '5':
                        carregando();
                        main();
                    break;
                    default:
                        opcao_invalida();
                        break;
                }
                break;

            case '3':
                carregando();
                esp_tab(9,45);
                printf("EMPRÉSTIMOS\n\n");              esp_tab(1,40);
                printf("1 - Novo Empréstimo\n");        esp_tab(1,40);
                printf("2 - Cancelar Empréstimo\n");    esp_tab(1,40);
                printf("3 - Listar Empréstimos\n");     esp_tab(1,40);
                printf("4 - Voltar\n");                 esp_tab(1,40);
                printf("OPÇÃO: ");
                o3 = getch();
                switch(o3){
                    case '1':
                        novo_emprestimo();
                    break;
                    case '2':
                        cancelar_emprestimo();
                    break;
                    case '3':
                        lista_emprestimo();
                    break;
                    case '4':
                        carregando();
                        main();
                    break;
                    default:
                        opcao_invalida();
                    break;
                }
                break;

            case '4':
                carregando();
                esp_tab(9,33);
                printf("Desenvolvido por: Mateus Cavalcante Honorato %c",169);  esp_tab(2,38);
                printf("Email: mateuscavalcanteh@gmail.com");                   esp_tab(2,43);
                printf("Contato: (83)98649-6139");                              esp_tab(9,35);
                exit(1);
                break;

            default:
                opcao_invalida();
                break;
        }
    }
}
