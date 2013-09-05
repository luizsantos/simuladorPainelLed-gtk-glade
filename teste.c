/*
 * * professor: luizsantos@utfpr.edu.br
 * 
 * - Programa que simula um painel de led
 * - Entrada um arquivo chamado mensagem.txt com uma string que será apresentada no painel de led! 
 * - Saida mensagem (contida no arquivo mensagem.txt) que deve ser apresentada iniciando da direita e indo para a esquerda lentamentente tal como o painel de led da UTFPR-CM.
 * 
 * - para compilar utilize o comando:
 * 	gcc -Wall -g -o teste teste.c -export-dynamic `pkg-config --cflags --libs gtk+-2.0` -lpthread
 * obs. no processo de compilação do projeto original vai dar um warning da pthread, mas o executável será criado!  ;-)
 * 
 * O programa está utilizando gtk+glade para interface gráfica e pthread para executar códigos em paralelo.
 * 
 *
 * Essa é a APS, que vale 2,0 na média, deve ser fieta em DUPLA e será apresentada em data ainda a ser marcada em sala de aula!
 * 
 * A dupla deve implementar o restante do programa para que o painel funcione corretamente apresentando a mensagem do arquivo.
 *  
 * Além do programa deve ser entregue:
 * - texto com teoria sobre interface gráfica com o uso das bibliotécas gtk e glade;
 * - texto com teoria sobre o uso de threads;
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

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <pthread.h>

// variáveis globais
 GtkWidget *window;
 GtkWidget *botao;
 GtkWidget *label; 
 GtkWidget *led[5][30];
 pthread_t thread1; 

// assinaturas de funções
 void ler (GtkWidget *widget, gpointer user_data);
 void sair (GtkObject *object, gpointer user_data);
 void iniciar_leds_desligados(GtkBuilder  *builder);
 void desligar_leds();
 void ligar_leds();
 void amostra();
 void *inicia_thread();


int main (int argc, char *argv[])
{
    // partes do main foram retiradas de: http://savebutton.wordpress.com/2011/06/19/interfaces-graficas-em-c-com-glade-e-gtk/
    GtkBuilder      *builder;

    gtk_init (&argc, &argv);

    builder = gtk_builder_new ();
    gtk_builder_add_from_file (builder, "tutorial.glade", NULL); //Carrega as informações do projeto glade para o GtkBuilder
    window = GTK_WIDGET(gtk_builder_get_object (builder, "window1"));   //Retorna o objeto Window, para mostrá-lo mais tarde


    gtk_builder_connect_signals (builder, NULL); //Conecta todos os eventos dentro do projeto do glade.


    iniciar_leds_desligados(builder);
    
    //label
    label =  GTK_WIDGET(gtk_builder_get_object (builder, "label1"));
    gtk_label_set_text(GTK_LABEL(label),"...");
 

    g_object_unref (G_OBJECT (builder)); //Exclui o GtkBuilder, pois não iremos mais usá-lo nesse exemplo.

    gtk_widget_show_all(window);   //Mostra a janela com seus objetos
    gtk_main ();

    return 0;
}

// função chamada quando o botao de ler é pressionado
void ler (GtkWidget *widget, gpointer user_data)
{
  
  printf(" Ola mundo \n"); 
  
  //label
  gtk_label_set_text(GTK_LABEL(label)," Ola Mundo ");
  
  //imagem
  //gtk_image_set_from_file(GTK_IMAGE(led[0][0]),"off.png");
  
  pthread_create(&thread1,NULL,inicia_thread,NULL);
  
}

// usado para liberar o botão de ler enquanto as funções de painel são executadas
void *inicia_thread()
{
  printf("Dentro da thread f1\n");
  
  // exemplo, retire quando criar o seu código...
  amostra();
  
  // coloque o seu código/função da APS aqui!!!!
  
    // código da aps
  
  // fim do código da APS
  
  pthread_exit(0);
}


// função chamada quando o botão de sair é pressionado
void sair (GtkObject *object, gpointer user_data)
{
   gtk_main_quit();
}

// relaciona as imagens da interface gráfica (gtk/glade) com uma matriz para ser utilizado nesse programa no C.
void iniciar_leds_desligados(GtkBuilder  *builder)
{
  int i,j,count=1;
  char imagem[11];
  for(i=0;i<5;i++)
    for(j=0;j<30;j++)
    {
      sprintf(imagem, "image%d",count++);
      //printf("%s,",imagem);
      led[i][j] = GTK_WIDGET(gtk_builder_get_object (builder, imagem));
      gtk_image_set_from_file(GTK_IMAGE(led[i][j]),"on.png"); 
    }  
}


// desliga todos leds
void desligar_leds()
{
  int i,j;
  for(i=0;i<5;i++)
  {
    for(j=0;j<30;j++)
    {
      gtk_image_set_from_file(GTK_IMAGE(led[i][j]),"off.png"); 
    } 
   // usleep(1000);
  }  
}

// liga todos os leds
void ligar_leds()
{
  int i,j;
  for(i=0;i<5;i++)
  {
    for(j=0;j<30;j++)
    {
      gtk_image_set_from_file(GTK_IMAGE(led[i][j]),"on.png"); 
    } 
   // usleep(1000);
  }  
}


// apenas uma amostra do que dá para fazer com os leds, desliga, liga, acente alguns, ola!
void amostra()
{
  int i,j,tempo=1000000;
  desligar_leds();
  usleep(tempo); // temporizador
  ligar_leds();
  usleep(tempo);
  desligar_leds();
  usleep(tempo);
  for(i=0;i<5;i=i+2)
  {
    for(j=0;j<30;j++)
    {
      gtk_image_set_from_file(GTK_IMAGE(led[i][j]),"on.png"); 
    } 
  }
  usleep(tempo);
  ligar_leds();
  usleep(tempo);
  desligar_leds();
  usleep(tempo);
  for(i=0;i<5;i++)
  {
    for(j=0;j<30;j=j+2)
    {
      gtk_image_set_from_file(GTK_IMAGE(led[i][j]),"on.png"); 
    } 
  }
  usleep(tempo);
  desligar_leds();
  usleep(tempo);
  gtk_image_set_from_file(GTK_IMAGE(led[0][3]),"on.png");
  gtk_image_set_from_file(GTK_IMAGE(led[1][2]),"on.png"); gtk_image_set_from_file(GTK_IMAGE(led[1][4]),"on.png");
  gtk_image_set_from_file(GTK_IMAGE(led[2][2]),"on.png"); gtk_image_set_from_file(GTK_IMAGE(led[2][4]),"on.png");
  gtk_image_set_from_file(GTK_IMAGE(led[3][2]),"on.png"); gtk_image_set_from_file(GTK_IMAGE(led[3][4]),"on.png");
  gtk_image_set_from_file(GTK_IMAGE(led[4][3]),"on.png");
  usleep(tempo);
  gtk_image_set_from_file(GTK_IMAGE(led[0][6]),"on.png");
  gtk_image_set_from_file(GTK_IMAGE(led[1][6]),"on.png"); 
  gtk_image_set_from_file(GTK_IMAGE(led[2][6]),"on.png"); 
  gtk_image_set_from_file(GTK_IMAGE(led[3][6]),"on.png"); 
  gtk_image_set_from_file(GTK_IMAGE(led[4][6]),"on.png"); gtk_image_set_from_file(GTK_IMAGE(led[4][7]),"on.png"); gtk_image_set_from_file(GTK_IMAGE(led[4][8]),"on.png");
  usleep(tempo);
  gtk_image_set_from_file(GTK_IMAGE(led[0][11]),"on.png");
  gtk_image_set_from_file(GTK_IMAGE(led[1][10]),"on.png"); gtk_image_set_from_file(GTK_IMAGE(led[1][12]),"on.png");
  gtk_image_set_from_file(GTK_IMAGE(led[2][10]),"on.png"); gtk_image_set_from_file(GTK_IMAGE(led[2][12]),"on.png");
  gtk_image_set_from_file(GTK_IMAGE(led[3][10]),"on.png"); gtk_image_set_from_file(GTK_IMAGE(led[2][11]),"on.png"); gtk_image_set_from_file(GTK_IMAGE(led[3][12]),"on.png");
  gtk_image_set_from_file(GTK_IMAGE(led[4][10]),"on.png"); gtk_image_set_from_file(GTK_IMAGE(led[4][12]),"on.png");
  usleep(tempo); 
}