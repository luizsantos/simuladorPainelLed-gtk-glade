/*
* * professor: luizsantos@utfpr.edu.br
*
* - Programa que simula um painel de led
* - Entrada um arquivo chamado mensagem.txt com uma string que será apresentada no painel de led!
* - Saida mensagem (contida no arquivo mensagem.txt) que deve ser apresentada iniciando da direita e indo para a esquerda lentamentente tal como o painel de led da UTFPR-CM.
*
* - para compilar utilize o comando:
* gcc testencurses.c -o testencurses -lncurses
* 
* Esse programa está utilizando ncurses! já que o programa, anterior:
* 		(https://github.com/luizsantos/simuladorPainelLed-gtk-glade), com o ambiente gráfico não estava executando em alguns Linux com gtk+glade 
* 		para interface gráfica e pthread para executar códigos em paralelo.
* 
* A dupla pode escolher fazer o painel de led com o exemplo desse código usando ncurses ou fazer o primeiro programa proposto com gtk+glade+pthread! 
* Porém quem escolher fazer o segundo com ncurses deve da mesmas forma explicar o gtk+glade+thread e explicar ncurses.
*
*
* Essa é a APS, que vale 2,0 na média, deve ser fieta em DUPLA e será apresentada em data ainda a ser marcada em sala de aula!
*
* A dupla deve implementar o restante do programa para que o painel funcione corretamente apresentando a mensagem do arquivo.
*
* Além do programa deve ser entregue:
* - texto com teoria sobre interface gráfica com o uso das bibliotécas gtk e glade;
* - texto com teoria sobre o uso de threads;
* - texto com teoria/prática sobre o ncurses;
* - relatos sobre problemas práticos e suas soluções encontradas durante o desenvolvimento do projeto;
* - texto explicando como o programa funciona;
* - código fonte do programa;
* - referências bibliográficas;
*
*
* ATENÇÃO - em qualquer tipo de plágio (cópia) a APS receberá a nota ZERO!!!!
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
 

// liga led tem que passar a posição linha,coluna onde vai ser ligado na tela
void ledOn(int i,int y)
{
 mvprintw(i,y,"%s","X");
 refresh();
}

// desliga led tem que passar a posição linha,coluna onde vai ser desligado na tela
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
  // coloque o código para ler o arquivo aqui!
  
  // um vetor é passado por referencia então não precisa do return! o texto estará na string!
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

// função principal
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
 
 // fica esperando o usuário digitar algo para terminar o programa e limpar a tela!
 getch();
 endwin();

 return 0;
}
