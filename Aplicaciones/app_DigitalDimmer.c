/*
 * app_DigitalDimmer.c
 *
 *  Created on: 9 jul. 2020
 *      Author: dario
 */

/* Libreria principal */

#include "app_DigitalDimmer.h"

TIM_HandleTypeDef htim2;

uint16_t Tiempo_activacion = 0, Angulo = 0;
//float Tiempo_activacion = 0, Angulo = 0;
float RPM_cal = 0;
uint16_t Boton[3] = {0x1000, 0x2000, 0x4000};
uint8_t Bandera = 0;

void app_CruceCero(float Tiempo_activacion)
{
	if(Bandera_DetectorCero == 0)
	{
		delay_us(Tiempo_activacion);
		HAL_GPIO_WritePin(SSR_GPIO_Port, SSR_Pin, 1);
		delay_us(3);
		//delay_us(20);
		HAL_GPIO_WritePin(SSR_GPIO_Port, SSR_Pin, 0);
		Bandera_DetectorCero = 1;
	}
}

void app_Dimmer_Prueba(void)
{
	 switch(opcion)
		  {
			  case Inicio:
			  {
					Total = 2;
					opcion = Ecuacion;
			  }
			  break;
			  case Ecuacion:
			  {

					  Tiempo_activacion = (4.62962962e-5*Total)*1000000;

					  opcion = Dimmer;
			  }
			  break;
			  case Dimmer:
			  {

					  app_CruceCero(Tiempo_activacion);
					  opcion = Inicio;
			  }break;
			  default:
			  {
				  opcion = Inicio;

			  }
		  }
}
void app_Dimmer(void)
{
	 switch(opcion)
		  {
			 case Debounce:
			 {
				 if((Aumento == 5) && (Bandera == 0))
				 {
					  opcion = Ecuacion;
				 }
				 else
				 {
					app_Debounce(Boton, 2);

					if (Bandera == 0)
					{
						opcion = Inicio;
					}
					else
					{
						opcion = Ecuacion;
					}
				 }
			 }break;
			  case Inicio:
			  {
					  app_SeleccionarAngulo();

					  app_NumeroAMAX7219(Total, 5);

					  if(Bandera == 0)
					  {
						 opcion = Debounce;
					  }
					  else if(Bandera == 1)
					  {
						 opcion = Ecuacion;
					  }
			  }
			  break;
			  case Ecuacion:
			  {
				  if(Aumento == 1)
				  {
					  opcion = Debounce;

					  Bandera = 0;

					  app_LimpiarDisplay(0x00);
				  }
				  else
				  {

					  //Tiempo_activacion = (4.62962962e-5*Total)*1000000;
					  //Tiempo_activacion = -4.85826E-023*(powf(Total,6))+4.33827E-018*(powf(Total,5))-0.000000000000157336*(powf(Total,4))+0.000000002909*(powf(Total,3))-0.0000284591*(powf(Total,2))+0.12621*Total+462.238;
					  //Tiempo_activacion = Total;
					  Tiempo_activacion = -0.00000000003548750199*pow(Total,3)+0.00000101425243671259*pow(Total,2)-0.017192868762661*Total+687.425829061752;

					  opcion = Dimmer;
				  }
			  }
			  break;
			  case Dimmer:
			  {
				  if(Aumento == 1)
				  {
					  opcion = Inicio;

					  Bandera = 0;

					  app_LimpiarDisplay(0x00);
				  }
				  else
				  {
					  app_CruceCero(Tiempo_activacion);

					  Bandera = 1;

					  opcion = Debounce;
				  }
			  }break;
			  default:
			  {
				  opcion = Debounce;
				  app_LimpiarDisplays();
			  }
		  }
}

void app_PIDDimmer(uint16_t Frecuencia)
{
	 switch(opcion)
		  {
	 	 	case Debounce:
			 {
				if ((Aumento == 5) && (Bandera == 0)) {
					opcion = Ecuacion;
				} else {
					app_Debounce(Boton, 2);

					if (Bandera == 0) {
						opcion = Inicio;
					} else {
						opcion = Ecuacion;
					}
				}
			 }break;
	 	 	case Inicio:
			  {
					  app_SeleccionarAngulo();

					  app_NumeroAMAX7219(Total, 5);

					  if(Bandera == 0)
					  {
						 opcion = Debounce;
					  }
					  else if(Bandera == 1)
					  {
						 opcion = Ecuacion;
					  }
			  }
			  break;
	 	 	case Ecuacion:
			  {
				  if(Aumento == 1)
				  {
					  opcion = Debounce;

					  Bandera = 0;

					  app_LimpiarDisplays();
				  }
				  else
				  {
					  RPM_cal = Frecuencia*60;

					  //Tiempo_activacion = (4.62962962e-5*Total)*1000000;
					  Tiempo_activacion = -0.00000000003548750199*pow(Total,3)+0.00000101425243671259*pow(Total,2)-0.017192868762661*Total+687.425829061752;

					  opcion = Dimmer;
				  }
			  }
			  break;
	 	 	case Dimmer:
	 	 	{
				  if(Aumento == 1)
				  {
					  opcion = Inicio;

					  Bandera = 0;

					  app_LimpiarDisplays();
				  }
				  /*if(PIDCompute() == false)
				  {
					  app_CruceCero(Tiempo_activacion);

					  Bandera = 1;

					  opcion = PID;
				  }*/
				  else
				  {
					  	  	 app_CruceCero(PIDOutputGet());
					  	  	 Bandera = 1;
					  	  	 opcion = PID;
				  }
			  }break;
			  case PID:
			 {
				 if(Aumento == 1)
				 {
					 opcion = Inicio;

					  Bandera = 0;

					  app_LimpiarDisplays();
				 }
				 else
				 {
					 PIDInputSet(Total);

					 PIDSetpointSet(RPM_cal);

					 PIDOutputLimitsSet(650, 200);

					 PIDCompute();

					 //Angulo = - (PIDOutputGet()) + 160;


					 opcion = Debounce;
				 }
			 }break;
			  default:
			  {
				  PIDInit(100, 400, 10, 650, 200, 20, DIRECT, AUTOMATIC);
				  opcion = Inicio;
			  }
		  }
}

