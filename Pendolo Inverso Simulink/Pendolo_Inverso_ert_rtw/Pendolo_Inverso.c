/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Pendolo_Inverso.c
 *
 * Code generated for Simulink model 'Pendolo_Inverso'.
 *
 * Model version                  : 1.41
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Wed Jan 22 09:53:20 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Pendolo_Inverso.h"
#include "rtwtypes.h"
#include "Pendolo_Inverso_private.h"
#include <math.h>
#include <string.h>
#include <stddef.h>
#include "rt_nonfinite.h"

/* Block signals (default storage) */
B_Pendolo_Inverso_T Pendolo_Inverso_B;

/* Block states (default storage) */
DW_Pendolo_Inverso_T Pendolo_Inverso_DW;

/* Real-time model */
static RT_MODEL_Pendolo_Inverso_T Pendolo_Inverso_M_;
RT_MODEL_Pendolo_Inverso_T *const Pendolo_Inverso_M = &Pendolo_Inverso_M_;

/* Forward declaration for local functions */
static real_T Pendolo_Inverso_mod(real_T x);
static void rate_monotonic_scheduler(void);

/*
 * Set which subrates need to run this base step (base rate always runs).
 * This function must be called prior to calling the model step function
 * in order to remember which rates need to run this base step.  The
 * buffering of events allows for overlapping preemption.
 */
void Pendolo_Inverso_SetEventsForThisBaseStep(boolean_T *eventFlags)
{
  /* Task runs when its counter is zero, computed via rtmStepTask macro */
  eventFlags[2] = ((boolean_T)rtmStepTask(Pendolo_Inverso_M, 2));
}

/*
 *         This function updates active task flag for each subrate
 *         and rate transition flags for tasks that exchange data.
 *         The function assumes rate-monotonic multitasking scheduler.
 *         The function must be called at model base rate so that
 *         the generated code self-manages all its subrates and rate
 *         transition flags.
 */
static void rate_monotonic_scheduler(void)
{
  /* To ensure a deterministic data transfer between two rates,
   * data is transferred at the priority of a fast task and the frequency
   * of the slow task.  The following flags indicate when the data transfer
   * happens.  That is, a rate interaction flag is set true when both rates
   * will run, and false otherwise.
   */

  /* tid 1 shares data with slower tid rate: 2 */
  if (Pendolo_Inverso_M->Timing.TaskCounters.TID[1] == 0) {
    Pendolo_Inverso_M->Timing.RateInteraction.TID1_2 =
      (Pendolo_Inverso_M->Timing.TaskCounters.TID[2] == 0);
  }

  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (Pendolo_Inverso_M->Timing.TaskCounters.TID[2])++;
  if ((Pendolo_Inverso_M->Timing.TaskCounters.TID[2]) > 9) {/* Sample time: [0.05s, 0.0s] */
    Pendolo_Inverso_M->Timing.TaskCounters.TID[2] = 0;
  }
}

real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/* Function for MATLAB Function: '<Root>/check_input' */
static real_T Pendolo_Inverso_mod(real_T x)
{
  real_T r;
  if (rtIsNaN(x)) {
    r = (rtNaN);
  } else if (rtIsInf(x)) {
    r = (rtNaN);
  } else if (x == 0.0) {
    r = 0.0;
  } else {
    r = fmod(x, 2.0);
    if (r == 0.0) {
      r = 0.0;
    } else if (x < 0.0) {
      r += 2.0;
    }
  }

  return r;
}

/* Model step function for TID0 */
void Pendolo_Inverso_step0(void)       /* Sample time: [0.0s, 0.0s] */
{
  /* local block i/o variables */
  real_T rtb_rodangle;
  real_T rtb_TSamp;
  real_T rtb_Diff;
  real_T rtb_TSamp_h;
  real_T rtb_Diff_k;
  real_T rtb_DiscreteZeroPole6;
  real_T rtb_DiscreteZeroPole6_j;
  int16_T i;
  uint16_T b_varargout_1;
  int8_T tmp;
  uint8_T b_status;
  boolean_T exitg1;
  boolean_T y;

  {                                    /* Sample time: [0.0s, 0.0s] */
    rate_monotonic_scheduler();
  }

  /* FromWorkspace: '<S15>/From Workspace' */
  {
    real_T *pDataValues = (real_T *)
      Pendolo_Inverso_DW.FromWorkspace_PWORK.DataPtr;

    {
      int_T elIdx;
      for (elIdx = 0; elIdx < 3; ++elIdx) {
        (&Pendolo_Inverso_B.FromWorkspace[0])[elIdx] = pDataValues[0];
        pDataValues += 1;
      }
    }
  }

  /* MATLABSystem: '<Root>/Serial Receive2' */
  if (Pendolo_Inverso_DW.obj_m.Protocol !=
      Pendolo_Inverso_P.SerialReceive2_Protocol) {
    Pendolo_Inverso_DW.obj_m.Protocol =
      Pendolo_Inverso_P.SerialReceive2_Protocol;
  }

  if (Pendolo_Inverso_DW.obj_m.QueueSizeFactor !=
      Pendolo_Inverso_P.SerialReceive2_QueueSizeFactor) {
    Pendolo_Inverso_DW.obj_m.QueueSizeFactor =
      Pendolo_Inverso_P.SerialReceive2_QueueSizeFactor;
  }

  MW_Serial_read(0, Pendolo_Inverso_DW.obj_m.DataSizeInBytes,
                 &Pendolo_Inverso_B.rtb_SerialReceive2_o1_m[0], &b_status, NULL,
                 0.0, NULL, 0.0);

  /* MATLAB Function: '<Root>/check_input' incorporates:
   *  MATLABSystem: '<Root>/Serial Receive2'
   * */
  if (b_status == 1) {
    Pendolo_Inverso_B.torqueOut_n = rt_roundd_snf
      (Pendolo_Inverso_B.rtb_SerialReceive2_o1_m[0]);
    if (Pendolo_Inverso_B.torqueOut_n < 128.0) {
      if (Pendolo_Inverso_B.torqueOut_n >= -128.0) {
        tmp = (int8_T)Pendolo_Inverso_B.torqueOut_n;
      } else {
        tmp = MIN_int8_T;
      }
    } else {
      tmp = MAX_int8_T;
    }

    switch (tmp) {
     case 1:
      Pendolo_Inverso_DW.enable_value = Pendolo_Inverso_mod
        (Pendolo_Inverso_DW.enable_value + 1.0);
      break;

     case 2:
      Pendolo_Inverso_DW.home_value = Pendolo_Inverso_mod
        (Pendolo_Inverso_DW.home_value + 1.0);
      break;

     case 3:
      Pendolo_Inverso_DW.move_center_value = Pendolo_Inverso_mod
        (Pendolo_Inverso_DW.move_center_value + 1.0);
      break;

     case 4:
      Pendolo_Inverso_DW.mode_value = Pendolo_Inverso_mod
        (Pendolo_Inverso_DW.mode_value + 1.0);
      break;

     case 5:
      Pendolo_Inverso_DW.enable_control_value = Pendolo_Inverso_mod
        (Pendolo_Inverso_DW.enable_control_value + 1.0);
      break;
    }
  }

  /* S-Function (sfcn_encoder): '<S1>/S-Function Builder3' */
  sfcn_encoder_Outputs_wrapper(&Pendolo_Inverso_B.SFunctionBuilder3,
    &Pendolo_Inverso_DW.SFunctionBuilder3_DSTATE,
    &Pendolo_Inverso_P.SFunctionBuilder3_P1, 1,
    &Pendolo_Inverso_P.SFunctionBuilder3_P2, 1,
    &Pendolo_Inverso_P.SFunctionBuilder3_P3, 1);

  /* Product: '<S9>/Product' incorporates:
   *  Constant: '<S9>/Constant'
   *  Constant: '<S9>/Constant1'
   *  DataTypeConversion: '<S1>/Data Type Conversion2'
   *  Product: '<S9>/Divide'
   */
  Pendolo_Inverso_B.Product = (real_T)Pendolo_Inverso_B.SFunctionBuilder3 /
    Pendolo_Inverso_P.Constant_Value * Pendolo_Inverso_P.Constant1_Value_c;

  /* MATLAB Function: '<S1>/Homing Block' incorporates:
   *  MATLAB Function: '<Root>/check_input'
   */
  if (Pendolo_Inverso_DW.mode_value == 0.0) {
    if (Pendolo_Inverso_DW.homeval == 0.0) {
      if (Pendolo_Inverso_DW.home_value == 0.0) {
        Pendolo_Inverso_DW.state = 0.0;
        Pendolo_Inverso_DW.homeval = 0.0;
        Pendolo_Inverso_DW.counter = 0.0;
        Pendolo_Inverso_DW.precart = 0.0;
        Pendolo_Inverso_DW.prepos = 0.0;
        memset(&Pendolo_Inverso_DW.precartArray[0], 0, 10U * sizeof(real_T));
      }

      if (Pendolo_Inverso_DW.state == 0.0) {
        Pendolo_Inverso_DW.torqueval_l = 0.0;
        if (Pendolo_Inverso_DW.home_value == 1.0) {
          Pendolo_Inverso_DW.state = 1.0;
        }
      } else if (Pendolo_Inverso_DW.state == 1.0) {
        Pendolo_Inverso_DW.torqueval_l = -250.0;
        Pendolo_Inverso_DW.state = 2.0;
      } else if (Pendolo_Inverso_DW.counter == 100.0) {
        y = true;
        i = 0;
        exitg1 = false;
        while ((!exitg1) && (i < 10)) {
          if (!(Pendolo_Inverso_DW.precartArray[i] == Pendolo_Inverso_B.Product))
          {
            y = false;
            exitg1 = true;
          } else {
            i++;
          }
        }

        if (y) {
          Pendolo_Inverso_DW.torqueval_l = 0.0;
          Pendolo_Inverso_DW.homeval = 1.0;
          Pendolo_Inverso_DW.prepos = Pendolo_Inverso_B.Product;
        } else {
          Pendolo_Inverso_DW.i++;
          Pendolo_Inverso_DW.precartArray[(int16_T)Pendolo_Inverso_DW.i - 1] =
            Pendolo_Inverso_DW.precart;
          if (Pendolo_Inverso_DW.i == 10.0) {
            Pendolo_Inverso_DW.i = 0.0;
          }

          Pendolo_Inverso_DW.precart = Pendolo_Inverso_B.Product;
        }
      } else {
        Pendolo_Inverso_DW.counter++;
      }
    } else if (Pendolo_Inverso_DW.home_value == 0.0) {
      Pendolo_Inverso_DW.state = 0.0;
      Pendolo_Inverso_DW.homeval = 0.0;
      Pendolo_Inverso_DW.counter = 0.0;
      Pendolo_Inverso_DW.prepos = 0.0;
    }
  }

  if (Pendolo_Inverso_DW.homeval == 1.0) {
    Pendolo_Inverso_B.Product += -328.0 - Pendolo_Inverso_DW.prepos;
  }

  /* MATLAB Function: '<S1>/Move to Center' incorporates:
   *  MATLAB Function: '<Root>/check_input'
   *  MATLAB Function: '<S1>/Homing Block'
   */
  if ((Pendolo_Inverso_DW.homeval == 1.0) &&
      (Pendolo_Inverso_DW.move_center_value == 1.0)) {
    Pendolo_Inverso_B.Divide_j = Pendolo_Inverso_DW.set_pos -
      Pendolo_Inverso_B.Product;
    Pendolo_Inverso_B.torqueOut_n = Pendolo_Inverso_B.Divide_j *
      Pendolo_Inverso_DW.kp;
    if (fabs(Pendolo_Inverso_B.Divide_j) < 10.0) {
      Pendolo_Inverso_B.torqueOut_n = 0.0;
    }
  } else {
    Pendolo_Inverso_B.torqueOut_n = Pendolo_Inverso_DW.torqueval_l;
  }

  /* End of MATLAB Function: '<S1>/Move to Center' */

  /* MATLAB Function: '<Root>/check_torque' incorporates:
   *  MATLABSystem: '<Root>/Serial Receive2'
   * */
  if (b_status == 1) {
    Pendolo_Inverso_DW.torque_value = Pendolo_Inverso_B.rtb_SerialReceive2_o1_m
      [1];
  }

  /* MATLAB Function: '<S1>/Selection' incorporates:
   *  MATLAB Function: '<Root>/check_input'
   *  MATLAB Function: '<Root>/check_torque'
   *  MATLAB Function: '<S1>/Homing Block'
   */
  if (Pendolo_Inverso_DW.mode_value == 0.0) {
    Pendolo_Inverso_DW.torqueval = Pendolo_Inverso_B.torqueOut_n;
  }

  if ((Pendolo_Inverso_DW.mode_value == 1.0) && (Pendolo_Inverso_DW.homeval ==
       1.0)) {
    if (Pendolo_Inverso_DW.enable_control_value == 1.0) {
      Pendolo_Inverso_DW.torqueval = Pendolo_Inverso_DW.torque_value;
    } else {
      Pendolo_Inverso_DW.torqueval = 0.0;
    }
  }

  /* MATLABSystem: '<S7>/Analog Input3' */
  if (Pendolo_Inverso_DW.obj_e.SampleTime != Pendolo_Inverso_P.Tc) {
    Pendolo_Inverso_DW.obj_e.SampleTime = Pendolo_Inverso_P.Tc;
  }

  Pendolo_Inverso_DW.obj_e.AnalogInDriverObj.MW_ANALOGIN_HANDLE =
    MW_AnalogIn_GetHandle(59UL);
  MW_AnalogInSingle_ReadResult
    (Pendolo_Inverso_DW.obj_e.AnalogInDriverObj.MW_ANALOGIN_HANDLE,
     &b_varargout_1, MW_ANALOGIN_UINT16);

  /* Product: '<S15>/Divide' incorporates:
   *  Constant: '<S15>/Constant'
   *  Sum: '<S15>/Subtract'
   */
  Pendolo_Inverso_B.Divide_j = (Pendolo_Inverso_B.FromWorkspace[0] -
    Pendolo_Inverso_B.FromWorkspace[1]) / Pendolo_Inverso_P.Constant_Value_c;

  /* If: '<S15>/If' incorporates:
   *  Constant: '<S15>/Constant1'
   *  Constant: '<S15>/RodOffset'
   *  DataTypeConversion: '<S7>/Data Type Conversion3'
   *  MATLABSystem: '<S7>/Analog Input3'
   *  Product: '<S15>/Divide1'
   *  Product: '<S15>/Divide3'
   *  Sum: '<S15>/Subtract1'
   *  Sum: '<S15>/Sum'
   *  Sum: '<S16>/Sum'
   *  Sum: '<S17>/Sum'
   * */
  if (Pendolo_Inverso_B.FromWorkspace[2] < 511.5) {
    /* Outputs for IfAction SubSystem: '<S15>/If Action Subsystem' incorporates:
     *  ActionPort: '<S16>/Action Port'
     */
    Pendolo_Inverso_B.torqueOut_n = Pendolo_Inverso_B.FromWorkspace[2] +
      Pendolo_Inverso_P.Constant1_Value;

    /* End of Outputs for SubSystem: '<S15>/If Action Subsystem' */
  } else {
    /* Outputs for IfAction SubSystem: '<S15>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S17>/Action Port'
     */
    Pendolo_Inverso_B.torqueOut_n = Pendolo_Inverso_B.FromWorkspace[2] -
      Pendolo_Inverso_P.Constant1_Value;

    /* End of Outputs for SubSystem: '<S15>/If Action Subsystem1' */
  }

  Pendolo_Inverso_B.Subtract1 = (real_T)b_varargout_1 /
    Pendolo_Inverso_B.Divide_j - (Pendolo_Inverso_P.RodOffset_Value +
    Pendolo_Inverso_B.torqueOut_n) / Pendolo_Inverso_B.Divide_j;

  /* End of If: '<S15>/If' */

  /* DiscreteZeroPole: '<S7>/Discrete Zero-Pole1' */
  {
    rtb_rodangle = (Pendolo_Inverso_P.DiscreteZeroPole1_D)*
      Pendolo_Inverso_B.Subtract1;
    rtb_rodangle += Pendolo_Inverso_P.DiscreteZeroPole1_C*
      Pendolo_Inverso_DW.DiscreteZeroPole1_DSTATE;
  }

  /* MATLAB Function: '<S1>/to Pins' incorporates:
   *  MATLAB Function: '<Root>/check_input'
   *  MATLAB Function: '<S1>/Selection'
   */
  i = (Pendolo_Inverso_DW.enable_value == 1.0);
  if (i == 1) {
    if (Pendolo_Inverso_DW.mode_value == 0.0) {
      if (Pendolo_Inverso_DW.torqueval > 0.0) {
        Pendolo_Inverso_DW.PWMOut = Pendolo_Inverso_DW.torqueval / 5.8824;
        Pendolo_Inverso_DW.Dir = 0.0;
      } else if (Pendolo_Inverso_DW.torqueval <= 0.0) {
        Pendolo_Inverso_DW.PWMOut = -Pendolo_Inverso_DW.torqueval / 5.8824;
        Pendolo_Inverso_DW.Dir = 1.0;
      }
    } else if ((rtb_rodangle >= -20.0) && (rtb_rodangle <= 20.0)) {
      if (Pendolo_Inverso_DW.torqueval > 0.0) {
        Pendolo_Inverso_DW.PWMOut = Pendolo_Inverso_DW.torqueval / 5.8824;
        Pendolo_Inverso_DW.Dir = 0.0;
      } else if (Pendolo_Inverso_DW.torqueval <= 0.0) {
        Pendolo_Inverso_DW.PWMOut = -Pendolo_Inverso_DW.torqueval / 5.8824;
        Pendolo_Inverso_DW.Dir = 1.0;
      }
    } else {
      i = 0;
      Pendolo_Inverso_DW.Dir = 0.0;
      Pendolo_Inverso_DW.PWMOut = 0.0;
    }
  }

  /* MATLABSystem: '<S1>/Digital Output19' incorporates:
   *  MATLAB Function: '<S1>/to Pins'
   */
  writeDigitalPin(12, (uint8_T)i);

  /* MATLABSystem: '<S1>/Digital Output20' incorporates:
   *  MATLAB Function: '<S1>/to Pins'
   */
  Pendolo_Inverso_B.torqueOut_n = rt_roundd_snf(Pendolo_Inverso_DW.Dir);
  if (Pendolo_Inverso_B.torqueOut_n < 256.0) {
    if (Pendolo_Inverso_B.torqueOut_n >= 0.0) {
      b_status = (uint8_T)Pendolo_Inverso_B.torqueOut_n;
    } else {
      b_status = 0U;
    }
  } else {
    b_status = MAX_uint8_T;
  }

  writeDigitalPin(34, b_status);

  /* End of MATLABSystem: '<S1>/Digital Output20' */

  /* MATLABSystem: '<S1>/PWM3' */
  Pendolo_Inverso_DW.obj_f.PWMDriverObj.MW_PWM_HANDLE = MW_PWM_GetHandle(11UL);

  /* Start for MATLABSystem: '<S1>/PWM3' incorporates:
   *  MATLAB Function: '<S1>/to Pins'
   */
  if (Pendolo_Inverso_DW.PWMOut <= 255.0) {
    Pendolo_Inverso_B.torqueOut_n = Pendolo_Inverso_DW.PWMOut;
  } else {
    Pendolo_Inverso_B.torqueOut_n = 255.0;
  }

  if (!(Pendolo_Inverso_B.torqueOut_n >= 0.0)) {
    Pendolo_Inverso_B.torqueOut_n = 0.0;
  }

  /* MATLABSystem: '<S1>/PWM3' */
  MW_PWM_SetDutyCycle(Pendolo_Inverso_DW.obj_f.PWMDriverObj.MW_PWM_HANDLE,
                      Pendolo_Inverso_B.torqueOut_n);

  /* Gain: '<S13>/Gain1' */
  Pendolo_Inverso_B.torqueOut_n = Pendolo_Inverso_P.Gain1_Gain * rtb_rodangle;

  /* SampleTimeMath: '<S14>/TSamp'
   *
   * About '<S14>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   *   */
  rtb_TSamp = Pendolo_Inverso_B.torqueOut_n * Pendolo_Inverso_P.TSamp_WtEt;

  /* Sum: '<S14>/Diff' incorporates:
   *  UnitDelay: '<S14>/UD'
   *
   * Block description for '<S14>/Diff':
   *
   *  Add in CPU
   *
   * Block description for '<S14>/UD':
   *
   *  Store in Global RAM
   */
  rtb_Diff = rtb_TSamp - Pendolo_Inverso_DW.UD_DSTATE;

  /* DiscreteZeroPole: '<S7>/Discrete Zero-Pole6' */
  {
    rtb_DiscreteZeroPole6 = Pendolo_Inverso_P.DiscreteZeroPole6_D*rtb_Diff;
    rtb_DiscreteZeroPole6 += Pendolo_Inverso_P.DiscreteZeroPole6_C*
      Pendolo_Inverso_DW.DiscreteZeroPole6_DSTATE;
  }

  /* Gain: '<S4>/toMeters' */
  Pendolo_Inverso_B.Product *= Pendolo_Inverso_P.toMeters_Gain;

  /* SampleTimeMath: '<S11>/TSamp'
   *
   * About '<S11>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   *   */
  rtb_TSamp_h = Pendolo_Inverso_B.Product * Pendolo_Inverso_P.TSamp_WtEt_o;

  /* Sum: '<S11>/Diff' incorporates:
   *  UnitDelay: '<S11>/UD'
   *
   * Block description for '<S11>/Diff':
   *
   *  Add in CPU
   *
   * Block description for '<S11>/UD':
   *
   *  Store in Global RAM
   */
  rtb_Diff_k = rtb_TSamp_h - Pendolo_Inverso_DW.UD_DSTATE_n;

  /* DiscreteZeroPole: '<S4>/Discrete Zero-Pole6' */
  {
    rtb_DiscreteZeroPole6_j = Pendolo_Inverso_P.DiscreteZeroPole6_D_l*rtb_Diff_k;
    rtb_DiscreteZeroPole6_j += Pendolo_Inverso_P.DiscreteZeroPole6_C_j*
      Pendolo_Inverso_DW.DiscreteZeroPole6_DSTATE_h;
  }

  /* RateTransition: '<Root>/Rate Transition1' incorporates:
   *  Constant: '<S1>/Constant'
   */
  if (Pendolo_Inverso_M->Timing.RateInteraction.TID1_2) {
    Pendolo_Inverso_DW.RateTransition1_Buffer[0] =
      Pendolo_Inverso_P.Constant_Value_o;
    Pendolo_Inverso_DW.RateTransition1_Buffer[1] = Pendolo_Inverso_B.Product;
    Pendolo_Inverso_DW.RateTransition1_Buffer[2] = rtb_DiscreteZeroPole6_j;
    Pendolo_Inverso_DW.RateTransition1_Buffer[3] = Pendolo_Inverso_B.torqueOut_n;
    Pendolo_Inverso_DW.RateTransition1_Buffer[4] = rtb_DiscreteZeroPole6;
  }

  /* End of RateTransition: '<Root>/Rate Transition1' */

  /* Update for S-Function (sfcn_encoder): '<S1>/S-Function Builder3' */

  /* S-Function "sfcn_encoder_wrapper" Block: <S1>/S-Function Builder3 */
  sfcn_encoder_Update_wrapper(&Pendolo_Inverso_B.SFunctionBuilder3,
    &Pendolo_Inverso_DW.SFunctionBuilder3_DSTATE,
    &Pendolo_Inverso_P.SFunctionBuilder3_P1, 1,
    &Pendolo_Inverso_P.SFunctionBuilder3_P2, 1,
    &Pendolo_Inverso_P.SFunctionBuilder3_P3, 1);

  /* Update for DiscreteZeroPole: '<S7>/Discrete Zero-Pole1' */
  {
    Pendolo_Inverso_DW.DiscreteZeroPole1_DSTATE = Pendolo_Inverso_B.Subtract1 +
      Pendolo_Inverso_P.DiscreteZeroPole1_A*
      Pendolo_Inverso_DW.DiscreteZeroPole1_DSTATE;
  }

  /* Update for UnitDelay: '<S14>/UD'
   *
   * Block description for '<S14>/UD':
   *
   *  Store in Global RAM
   */
  Pendolo_Inverso_DW.UD_DSTATE = rtb_TSamp;

  /* Update for DiscreteZeroPole: '<S7>/Discrete Zero-Pole6' */
  {
    Pendolo_Inverso_DW.DiscreteZeroPole6_DSTATE = rtb_Diff +
      Pendolo_Inverso_P.DiscreteZeroPole6_A*
      Pendolo_Inverso_DW.DiscreteZeroPole6_DSTATE;
  }

  /* Update for UnitDelay: '<S11>/UD'
   *
   * Block description for '<S11>/UD':
   *
   *  Store in Global RAM
   */
  Pendolo_Inverso_DW.UD_DSTATE_n = rtb_TSamp_h;

  /* Update for DiscreteZeroPole: '<S4>/Discrete Zero-Pole6' */
  {
    Pendolo_Inverso_DW.DiscreteZeroPole6_DSTATE_h = rtb_Diff_k +
      Pendolo_Inverso_P.DiscreteZeroPole6_A_g*
      Pendolo_Inverso_DW.DiscreteZeroPole6_DSTATE_h;
  }

  /* Update absolute time */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  Pendolo_Inverso_M->Timing.t[0] =
    ((time_T)(++Pendolo_Inverso_M->Timing.clockTick0)) *
    Pendolo_Inverso_M->Timing.stepSize0;

  /* Update absolute time */
  /* The "clockTick1" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 0.005, which is the step size
   * of the task. Size of "clockTick1" ensures timer will not overflow during the
   * application lifespan selected.
   */
  Pendolo_Inverso_M->Timing.clockTick1++;
}

/* Model step function for TID2 */
void Pendolo_Inverso_step2(void)       /* Sample time: [0.05s, 0.0s] */
{
  real_T dataIn[5];
  int16_T i;

  /* MATLABSystem: '<Root>/Serial Transmit4' incorporates:
   *  RateTransition: '<Root>/Rate Transition1'
   */
  if (Pendolo_Inverso_DW.obj.Protocol !=
      Pendolo_Inverso_P.SerialTransmit4_Protocol) {
    Pendolo_Inverso_DW.obj.Protocol = Pendolo_Inverso_P.SerialTransmit4_Protocol;
  }

  for (i = 0; i < 5; i++) {
    dataIn[i] = Pendolo_Inverso_DW.RateTransition1_Buffer[i];
  }

  MW_Serial_write(Pendolo_Inverso_DW.obj.port, &dataIn[0], 5.0,
                  Pendolo_Inverso_DW.obj.dataSizeInBytes,
                  Pendolo_Inverso_DW.obj.sendModeEnum,
                  Pendolo_Inverso_DW.obj.dataType,
                  Pendolo_Inverso_DW.obj.sendFormatEnum, 2.0, '\x00', NULL, 0.0,
                  NULL, 0.0);

  /* End of MATLABSystem: '<Root>/Serial Transmit4' */
}

/* Model initialize function */
void Pendolo_Inverso_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  Pendolo_Inverso_P.Constant_Value_o = rtInf;

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&Pendolo_Inverso_M->solverInfo,
                          &Pendolo_Inverso_M->Timing.simTimeStep);
    rtsiSetTPtr(&Pendolo_Inverso_M->solverInfo, &rtmGetTPtr(Pendolo_Inverso_M));
    rtsiSetStepSizePtr(&Pendolo_Inverso_M->solverInfo,
                       &Pendolo_Inverso_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&Pendolo_Inverso_M->solverInfo, (&rtmGetErrorStatus
      (Pendolo_Inverso_M)));
    rtsiSetRTModelPtr(&Pendolo_Inverso_M->solverInfo, Pendolo_Inverso_M);
  }

  rtsiSetSimTimeStep(&Pendolo_Inverso_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange(&Pendolo_Inverso_M->solverInfo, false);
  rtsiSetIsContModeFrozen(&Pendolo_Inverso_M->solverInfo, false);
  rtsiSetSolverName(&Pendolo_Inverso_M->solverInfo,"FixedStepDiscrete");
  rtmSetTPtr(Pendolo_Inverso_M, &Pendolo_Inverso_M->Timing.tArray[0]);
  Pendolo_Inverso_M->Timing.stepSize0 = 0.005;

  /* Start for FromWorkspace: '<S15>/From Workspace' */
  {
    static real_T pTimeValues0[] = { 0.0 } ;

    static real_T pDataValues0[] = { 1023.0, 3.0, 91.0 } ;

    Pendolo_Inverso_DW.FromWorkspace_PWORK.TimePtr = (void *) pTimeValues0;
    Pendolo_Inverso_DW.FromWorkspace_PWORK.DataPtr = (void *) pDataValues0;
    Pendolo_Inverso_DW.FromWorkspace_IWORK.PrevIndex = 0;
  }

  /* InitializeConditions for S-Function (sfcn_encoder): '<S1>/S-Function Builder3' */

  /* S-Function Block: <S1>/S-Function Builder3 */
  {
    real_T initVector[1] = { 0 };

    {
      int_T i1;
      for (i1=0; i1 < 1; i1++) {
        Pendolo_Inverso_DW.SFunctionBuilder3_DSTATE = initVector[0];
      }
    }
  }

  /* InitializeConditions for UnitDelay: '<S14>/UD'
   *
   * Block description for '<S14>/UD':
   *
   *  Store in Global RAM
   */
  Pendolo_Inverso_DW.UD_DSTATE =
    Pendolo_Inverso_P.DiscreteDerivative2_ICPrevScale;

  /* InitializeConditions for UnitDelay: '<S11>/UD'
   *
   * Block description for '<S11>/UD':
   *
   *  Store in Global RAM
   */
  Pendolo_Inverso_DW.UD_DSTATE_n =
    Pendolo_Inverso_P.DiscreteDerivative_ICPrevScaled;

  /* SystemInitialize for MATLAB Function: '<S1>/Move to Center' */
  Pendolo_Inverso_DW.kp = 10.0;

  /* Start for MATLABSystem: '<Root>/Serial Receive2' */
  Pendolo_Inverso_DW.obj_m.matlabCodegenIsDeleted = false;
  Pendolo_Inverso_DW.obj_m.Protocol = Pendolo_Inverso_P.SerialReceive2_Protocol;
  Pendolo_Inverso_DW.obj_m.QueueSizeFactor =
    Pendolo_Inverso_P.SerialReceive2_QueueSizeFactor;
  Pendolo_Inverso_DW.obj_m.isInitialized = 1L;
  Pendolo_Inverso_DW.obj_m.DataTypeWidth = 4U;
  Pendolo_Inverso_DW.obj_m.DataSizeInBytes = 8U;
  MW_SCI_Open(0);
  Pendolo_Inverso_DW.obj_m.isSetupComplete = true;

  /* Start for MATLABSystem: '<S7>/Analog Input3' */
  Pendolo_Inverso_DW.obj_e.matlabCodegenIsDeleted = false;
  Pendolo_Inverso_DW.obj_e.SampleTime = Pendolo_Inverso_P.Tc;
  Pendolo_Inverso_DW.obj_e.isInitialized = 1L;
  Pendolo_Inverso_DW.obj_e.AnalogInDriverObj.MW_ANALOGIN_HANDLE =
    MW_AnalogInSingle_Open(59UL);
  Pendolo_Inverso_DW.obj_e.isSetupComplete = true;

  /* Start for MATLABSystem: '<S1>/Digital Output19' */
  Pendolo_Inverso_DW.obj_e5.matlabCodegenIsDeleted = false;
  Pendolo_Inverso_DW.obj_e5.isInitialized = 1L;
  digitalIOSetup(12, 1);
  Pendolo_Inverso_DW.obj_e5.isSetupComplete = true;

  /* Start for MATLABSystem: '<S1>/Digital Output20' */
  Pendolo_Inverso_DW.obj_e1.matlabCodegenIsDeleted = false;
  Pendolo_Inverso_DW.obj_e1.isInitialized = 1L;
  digitalIOSetup(34, 1);
  Pendolo_Inverso_DW.obj_e1.isSetupComplete = true;

  /* Start for MATLABSystem: '<S1>/PWM3' */
  Pendolo_Inverso_DW.obj_f.matlabCodegenIsDeleted = false;
  Pendolo_Inverso_DW.obj_f.isInitialized = 1L;
  Pendolo_Inverso_DW.obj_f.PWMDriverObj.MW_PWM_HANDLE = MW_PWM_Open(11UL, 0.0,
    0.0);
  Pendolo_Inverso_DW.obj_f.isSetupComplete = true;

  /* Start for MATLABSystem: '<Root>/Serial Transmit4' */
  Pendolo_Inverso_DW.obj.matlabCodegenIsDeleted = false;
  Pendolo_Inverso_DW.obj.Protocol = Pendolo_Inverso_P.SerialTransmit4_Protocol;
  Pendolo_Inverso_DW.obj.isInitialized = 1L;
  Pendolo_Inverso_DW.obj.port = 0.0;
  Pendolo_Inverso_DW.obj.dataSizeInBytes = 8.0;
  Pendolo_Inverso_DW.obj.dataType = 6.0;
  Pendolo_Inverso_DW.obj.sendModeEnum = 0.0;
  Pendolo_Inverso_DW.obj.sendFormatEnum = 0.0;
  MW_SCI_Open(0);
  Pendolo_Inverso_DW.obj.isSetupComplete = true;
}

/* Model terminate function */
void Pendolo_Inverso_terminate(void)
{
  /* Terminate for MATLABSystem: '<Root>/Serial Receive2' */
  if (!Pendolo_Inverso_DW.obj_m.matlabCodegenIsDeleted) {
    Pendolo_Inverso_DW.obj_m.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/Serial Receive2' */

  /* Terminate for MATLABSystem: '<S7>/Analog Input3' */
  if (!Pendolo_Inverso_DW.obj_e.matlabCodegenIsDeleted) {
    Pendolo_Inverso_DW.obj_e.matlabCodegenIsDeleted = true;
    if ((Pendolo_Inverso_DW.obj_e.isInitialized == 1L) &&
        Pendolo_Inverso_DW.obj_e.isSetupComplete) {
      Pendolo_Inverso_DW.obj_e.AnalogInDriverObj.MW_ANALOGIN_HANDLE =
        MW_AnalogIn_GetHandle(59UL);
      MW_AnalogIn_Close
        (Pendolo_Inverso_DW.obj_e.AnalogInDriverObj.MW_ANALOGIN_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<S7>/Analog Input3' */

  /* Terminate for MATLABSystem: '<S1>/Digital Output19' */
  if (!Pendolo_Inverso_DW.obj_e5.matlabCodegenIsDeleted) {
    Pendolo_Inverso_DW.obj_e5.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S1>/Digital Output19' */

  /* Terminate for MATLABSystem: '<S1>/Digital Output20' */
  if (!Pendolo_Inverso_DW.obj_e1.matlabCodegenIsDeleted) {
    Pendolo_Inverso_DW.obj_e1.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S1>/Digital Output20' */

  /* Terminate for MATLABSystem: '<S1>/PWM3' */
  if (!Pendolo_Inverso_DW.obj_f.matlabCodegenIsDeleted) {
    Pendolo_Inverso_DW.obj_f.matlabCodegenIsDeleted = true;
    if ((Pendolo_Inverso_DW.obj_f.isInitialized == 1L) &&
        Pendolo_Inverso_DW.obj_f.isSetupComplete) {
      Pendolo_Inverso_DW.obj_f.PWMDriverObj.MW_PWM_HANDLE = MW_PWM_GetHandle
        (11UL);
      MW_PWM_SetDutyCycle(Pendolo_Inverso_DW.obj_f.PWMDriverObj.MW_PWM_HANDLE,
                          0.0);
      Pendolo_Inverso_DW.obj_f.PWMDriverObj.MW_PWM_HANDLE = MW_PWM_GetHandle
        (11UL);
      MW_PWM_Close(Pendolo_Inverso_DW.obj_f.PWMDriverObj.MW_PWM_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<S1>/PWM3' */

  /* Terminate for MATLABSystem: '<Root>/Serial Transmit4' */
  if (!Pendolo_Inverso_DW.obj.matlabCodegenIsDeleted) {
    Pendolo_Inverso_DW.obj.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/Serial Transmit4' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
