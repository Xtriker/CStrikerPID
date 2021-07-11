//*********************************************************************************
// Arduino PID Library Version 1.0.1 Modified Version for C -
// Platform Independent
// 
// Revision: 1.1
// 
// Description: The PID Controller module originally meant for Arduino made
// platform independent. Some small bugs present in the original Arduino source
// have been rectified as well.
// 
// For a detailed explanation of the theory behind this library, go to:
// http://brettbeauregard.com/blog/2011/04/improving-the-beginners-pid-introduction/
// 
// Revisions can be found here:
// https://github.com/tcleg
// 
// Modified by: Trent Cleghorn , <trentoncleghorn@gmail.com> & Dario Diaz ,<dariodiaz@alumnos.udg.mx>
// 
// Copyright (C) Brett Beauregard , <br3ttb@gmail.com>
// 
//                                 GPLv3 License
// 
// This program is free software: you can redistribute it and/or modify it under 
// the terms of the GNU General Public License as published by the Free Software 
// Foundation, either version 3 of the License, or (at your option) any later 
// version.
// 
// This program is distributed in the hope that it will be useful, but WITHOUT ANY 
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
// PARTICULAR PURPOSE.  See the GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along with 
// this program.  If not, see <http://www.gnu.org/licenses/>.
//*********************************************************************************

//*********************************************************************************
// Headers
//*********************************************************************************
#include "pid_controller.h"

//*********************************************************************************
// Macros and Globals
//*********************************************************************************
#define CONSTRAIN(x,lower,upper)    ((x)<(lower)?(lower):((x)>(upper)?(upper):(x)))

//*********************************************************************************
// Functions
//*********************************************************************************

PIDControl pid;
void PIDInit(float kp, float ki, float kd,
             float sampleTimeSeconds, float minOutput, float maxOutput, 
             PIDMode mode, PIDDirection controllerDirection)
{
    pid.controllerDirection = DIRECT;
    pid.mode = AUTOMATIC;

    if(sampleTimeSeconds > 0.0f)
    {
        pid.sampleTime = sampleTimeSeconds;
    }
    else
    {
        // If the passed parameter was incorrect, set to 1 second
        pid.sampleTime = 1.0f;
    }
    
    PIDOutputLimitsSet(minOutput, maxOutput);
    PIDTuningsSet(kp, ki, kd);
}
        
bool PIDCompute(void)
{
    float error, dInput;

    if(pid.mode == MANUAL)
    {
        return false;
    }
    
    /* Error clasico de PID */
    error = (pid.setpoint) - (pid.input);
    
    /* Calculo de la parte integrativa */
    pid.iTerm += (pid.alteredKi) * error;
    
    // Constrain the integrator to make sure it does not exceed output bounds
    pid.iTerm = CONSTRAIN( (pid.iTerm), (pid.outMin), (pid.outMax) );
    
    /* Determinar la parte derivativa de la lectura y el error derivativo de la lectura */
    dInput = (pid.input) - (pid.lastInput);
    
    /* Realiza el ultimo calculo y lo guarda en la variable salida */
    pid.output = (pid.alteredKp) * error + (pid.iTerm) - (pid.alteredKd) * dInput;
    
    // Bound the output
    pid.output = CONSTRAIN( (pid.output), (pid.outMin), (pid.outMax) );
    
    /* Manda el valor actual de la lectura del sensor a una lectura previa */
    pid.lastInput = pid.input;
    
    return true;
}
     
void 
PIDModeSet(PIDMode mode)
{
    // If the mode changed from MANUAL to AUTOMATIC
    if(pid.mode != mode && mode == AUTOMATIC)
    {
        // Initialize a few PID parameters to new values
        pid.iTerm = pid.output;
        pid.lastInput = pid.input;
        
        // Constrain the integrator to make sure it does not exceed output bounds
        pid.iTerm = CONSTRAIN( (pid.iTerm), (pid.outMin), (pid.outMax) );
    }
    
    pid.mode = mode;
}

void 
PIDOutputLimitsSet(float min, float max)
{
    // Check if the parameters are valid
    if(min >= max)
    {
        return;
    }
    
    // Save the parameters
    pid.outMin = min;
    pid.outMax = max;
    
    // If in automatic, apply the new constraints
    if(pid.mode == AUTOMATIC)
    {
        pid.output = CONSTRAIN(pid.output, min, max);
        pid.iTerm  = CONSTRAIN(pid.iTerm,  min, max);
    }
}

void 
PIDTuningsSet(float kp, float ki, float kd)
{
    // Check if the parameters are valid
    if(kp < 0.0f || ki < 0.0f || kd < 0.0f)
    {
        return;
    }
    
    // Save the parameters for displaying purposes
    pid.dispKp = kp;
    pid.dispKi = ki;
    pid.dispKd = kd;
    
    // Alter the parameters for PID
    pid.alteredKp = kp;
    pid.alteredKi = ki * pid.sampleTime;
    pid.alteredKd = kd / pid.sampleTime;
    
    // Apply reverse direction to the altered values if necessary
    if(pid.controllerDirection == REVERSE)
    {
        pid.alteredKp = -(pid.alteredKp);
        pid.alteredKi = -(pid.alteredKi);
        pid.alteredKd = -(pid.alteredKd);
    }
}

void 
PIDTuningKpSet(float kp)
{
    PIDTuningsSet(kp, pid.dispKi, pid.dispKd);
}

void 
PIDTuningKiSet(float ki)
{
    PIDTuningsSet(pid.dispKp, ki, pid.dispKd);
}

void 
PIDTuningKdSet(float kd)
{
    PIDTuningsSet(pid.dispKp, pid.dispKi, kd);
}

void 
PIDControllerDirectionSet(PIDDirection controllerDirection)
{
    // If in automatic mode and the controller's sense of direction is reversed
    if(pid.mode == AUTOMATIC && controllerDirection == REVERSE)
    {
        // Reverse sense of direction of PID gain constants
        pid.alteredKp = -(pid.alteredKp);
        pid.alteredKi = -(pid.alteredKi);
        pid.alteredKd = -(pid.alteredKd);
    }
    
    pid.controllerDirection = controllerDirection;
}

void 
PIDSampleTimeSet(float sampleTimeSeconds)
{
    float ratio;

    if(sampleTimeSeconds > 0.0f)
    {
        // Find the ratio of change and apply to the altered values
        ratio = sampleTimeSeconds / pid.sampleTime;
        pid.alteredKi *= ratio;
        pid.alteredKd /= ratio;
        
        // Save the new sampling time
        pid.sampleTime = sampleTimeSeconds;
    }
}

void PIDSetpointSet(float setpoint) { pid.setpoint = setpoint; }

//
// PID Input Set
// Description:
//      Should be called before calling PIDCompute so the PID controller will
//      have an updated input value to work with.
// Parameters:
//      pid - The address of a PIDControl instantiation.
//      input - The value the controller will work with.
// Returns:
//      Nothing.
//
void PIDInputSet(float input) { pid.input = input; }

//
// PID Output Get
// Description:
//      Typically, this function is called after PIDCompute in order to
//      retrieve the output of the controller.
// Parameters:
//      pid - The address of a PIDControl instantiation.
// Returns:
//      The output of the specific PID controller.
//
float PIDOutputGet(void);

//
// PID Proportional Gain Constant Get
// Description:
//      Returns the proportional gain constant value the particular
//      controller is set to.
// Parameters:
//      pid - The address of a PIDControl instantiation.
// Returns:
//      The proportional gain constant.
//
float PIDKpGet(void) { return pid.dispKp; }

//
// PID Integral Gain Constant Get
// Description:
//      Returns the integral gain constant value the particular
//      controller is set to.
// Parameters:
//      pid - The address of a PIDControl instantiation.
// Returns:
//      The integral gain constant.
//
float PIDKiGet(void) { return pid.dispKi; }

//
// PID Derivative Gain Constant Get
// Description:
//      Returns the derivative gain constant value the particular
//      controller is set to.
// Parameters:
//      pid - The address of a PIDControl instantiation.
// Returns:
//      The derivative gain constant.
//
float PIDKdGet(void) { return pid.dispKd; }

//
// PID Mode Get
// Description:
//      Returns the mode the particular controller is set to.
// Parameters:
//      pid - The address of a PIDControl instantiation.
// Returns:
//      MANUAL or AUTOMATIC depending on what the user set the
//      controller to.
//
PIDMode PIDModeGet(void) { return pid.mode; }

//
// PID Direction Get
// Description:
//      Returns the direction the particular controller is set to.
// Parameters:
//      pid - The address of a PIDControl instantiation.
// Returns:
//      DIRECT or REVERSE depending on what the user set the
//      controller to.
//
 PIDDirection PIDDirectionGet(void)
 {
	 return pid.controllerDirection;
 }

float PIDOutputGet(void)
{
	return pid.output;
}


