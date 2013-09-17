/*
* * professor: luizsantos@utfpr.edu.br
*
* - Programa que simula um painel de led
* - Entrada um arquivo chamado mensagem.txt com uma string que ser� apresentada no painel de led!
* - Saida mensagem (contida no arquivo mensagem.txt) que deve ser apresentada iniciando da direita e indo para a esquerda lentamentente tal como o painel de led da UTFPR-CM.
*
* - para compilar utilize o comando:
* gcc testencurses.c -o testencurses -lncurses
* 
* Esse programa est� utilizando ncurses! j� que o programa, anterior:
* 		(https://github.com/luizsantos/simuladorPainelLed-gtk-glade), com o ambiente gr�fico n�o estava executando em alguns Linux com gtk+glade 
* 		para interface gr�fica e pthread para executar c�digos em paralelo.
* 
* A dupla pode escolher fazer o painel de led com o exemplo desse c�digo usando ncurses ou fazer o primeiro programa proposto com gtk+glade+pthread! 
* Por�m quem escolher fazer o segundo com ncurses deve da mesmas forma explicar o gtk+glade+thread e explicar ncurses.
*
*
* Essa � a APS, que vale 2,0 na m�dia, deve ser fieta em DUPLA e ser� apresentada em data ainda a ser marcada em sala de aula!
*
* A dupla deve implementar o restante do programa para que o painel funcione corretamente apresentando a mensagem do arquivo.
*
* Al�m do programa deve ser entregue:
* - texto com teoria sobre interface gr�fica com o uso das bibliot�cas gtk e glade;
* - texto com teoria sobre o uso de threads;
* - texto com teoria/pr�tica sobre o ncurses;
* - relatos sobre problemas pr�ticos e suas solu��es encontradas durante o desenvolvimento do projeto;
* - texto explicando como o programa funciona;
* - c�digo fonte do programa;
* - refer�ncias bibliogr�ficas;
*
*
* ATEN��O - em qualquer tipo de pl�gio (c�pia) a APS receber� a nota ZERO!!!!
*
*
*/

#include <ncurses.h>			  
#include <string.h>

void amostra(char string[]);
void ledOn(int i,int y);
void ledOff(int i, int y);
void ligarTodosLeds();
void desligarTodosLeds();
void lerArquivo(char string[]);
 

// liga led tem que passar a posi��o linha,coluna onde vai ser ligado na tela
void ledOn(int i,int y)
{
 mvprintw(i,y,"%s","X");
 refresh();
}

// desliga led tem que passar a posi��o linha,coluna onde vai ser desligado na tela
void ledOff(int i, int y)
{
 mvprintw(i,y,"%s",".");
 refresh();
}

// liga todos os leds
void ligarTodosLeds()
{
 int i,j;
 for(i=0;i<5;i++)
  for(j=0;j<30;j++)
   ledOn(i,j);
}

// desliga todos os leds
void desligarTodosLeds()
{
 int i,j;
 for(i=0;i<5;i++)
  for(j=0;j<30;j++)
   ledOff(i,j);
}

// le do arquivo mensgem.txt a mensagem que deve ser apresentada no painel
void lerArquivo(char string[])
{
  // coloque o c�digo para ler o arquivo aqui!
  
  // um vetor � passado por referencia ent�o n�o precisa do return! o texto estar� na string!
  strcpy(string,"Ola mundo");
}


// um exemplo de como pode ser implementado!
void amostra(char string[])
{
  int i,j,row,col;
  getmaxyx(stdscr,row,col);
  printw("\n\nTexto do arquivo:\n\t%s\n",string);
  
 // liga todos mas com um tempo entre um led e outro
 for(i=0;i<5;i++)
  for(j=0;j<30;j++)
  {
    ledOn(i,j);
    usleep(10000);
  }
  
 for(i=0;i<5;i++)
  for(j=0;j<30;j++)
  {
    ledOff(i,j);
    usleep(10000);
  }
  refresh();
  //  mostra a letra O
  ledOn(0,3);
  ledOn(1,1);ledOn(1,5);
  ledOn(2,1);ledOn(2,5);
  ledOn(3,1);ledOn(3,5);
  ledOn(4,3);
  refresh();
 
}

// fun��o principal
int main()
{
 int row,col,i,j;				
 char string[50];
 
 
 initscr();			
 getmaxyx(stdscr,row,col);		

 // desliga todos os leds e apresenta o painel de led pela primeira vez!
 desligarTodosLeds();

 lerArquivo(string);
 amostra(string);
 
 // fica esperando o usu�rio digitar algo para terminar o programa e limpar a tela!
 getch();
 endwin();

 return 0;
}
