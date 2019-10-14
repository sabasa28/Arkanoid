#include "states/game.h"

//CAMBIAR GETCENTERPOSITION A GETRECTANGLECENTER Y QUE TOME UN RECTANGULO
//TERMINAR DE PULIR COLISIONES
//INTENTAR CAMBIAR COLISION BOLA - PALETA se puede hacer lo mismo que en el pong
//REVISAR QUE TODO LO EXTERN SEA NECESARIO Y SINO QUE SEA STATIC, EJ OPCIONES EN MENU
//PONER TODO EN INGLES
//hacer consistente el codigo (mayus o minus en los structs)
//agregar getframetime()
//AL CAMBIAR PANTALLA DURANTE EL JEUGO PREGUNTAR "Hacer esto reiniciara tu juego s/n" o por lo menos poner un mensaje de aviso en general en pausa
//crear el modificador de multiplicador de ball.speed.x para la colision ball-player
//hacer constantes los dividers que no esten dentro de structs
//agregar lo de que se guarde el directorio de trabajo y lo de que se guarde el x86
//bloque con vida, bloque buff y bloque debuff
//controles
//namespace

void main()
{
	executeGame();
}
