# CStrikerPID

## Descripción
Este proyecto va orientado al control de velocidad de un router, en específico de una recortadora Makita sin control de velocidad, la finalidad principal fue sacar el máximo provecho al control de las revoluciones por minuto para realizar cortes en materiales con velocidades de cortes específicas.

## Funcionamiento
### Adquisión de la frecuencia
El funcionamiento de este proyecto consta de dos estapas, una que es la que se encarga de realizar toda la adquisición de los datos, y otra encargada de la selección de las RPM por parte del usuario. La lectura es realizada mediante un sensor optico que consta de un LED infrarrojo y un LED emisor de luz, esto colocada dentro de la recortadora, en la parte de un rodamiento, cada que pasa por una sección blanca del rodamiento (ya que es necesario colocar una marca para la correcta lectura), mandará un pulso al microcontrolador y mediante el TIM2 del microcontrolador realizará la lectura de la frecuencia.

### Selección de las velocidad
Para realizar la selección de la velocidad, es necesario insertar los valores mediante el sistema de control y despliegue del controlador PID, este consta de dos elementos, 5 displays de 7 segmentos que son controlados mediante un IC MAX7219, y la inserción de los valores que se realiza mediante tres botones, que tienen funciones de aumentar, disminuir y aceptar el valor actual, y funciones avanzadas como regresar al display anterior, pasar al display siguiente y regresar al menú de selección de los valores; todo esto es mas claro mediante la siguiente máquina de estados, en donde se mostrado el funcionamiento general del sistema.
![Segunda_funcion_ControlPID](https://user-images.githubusercontent.com/62403901/125179876-954cc300-e1b8-11eb-8f60-b029525a17b0.png)

![Maquina_estado_PID](https://user-images.githubusercontent.com/62403901/125179864-6b939c00-e1b8-11eb-97df-78c7d1a4eb67.png)

## Resultado final

![CStrikerPID_Control](https://user-images.githubusercontent.com/62403901/125179881-a8f82980-e1b8-11eb-9502-bee68d718904.jpg)

