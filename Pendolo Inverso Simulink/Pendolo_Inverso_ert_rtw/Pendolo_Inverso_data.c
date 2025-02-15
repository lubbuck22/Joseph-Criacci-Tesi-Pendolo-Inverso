/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Pendolo_Inverso_data.c
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

/* Block parameters (default storage) */
P_Pendolo_Inverso_T Pendolo_Inverso_P = {
  /* Variable: Tc
   * Referenced by: '<S7>/Analog Input3'
   */
  0.005,

  /* Mask Parameter: DiscreteDerivative2_ICPrevScale
   * Referenced by: '<S14>/UD'
   */
  0.0,

  /* Mask Parameter: DiscreteDerivative_ICPrevScaled
   * Referenced by: '<S11>/UD'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<Root>/Serial Receive2'
   */
  0.0,

  /* Expression: 3
   * Referenced by: '<Root>/Serial Receive2'
   */
  3.0,

  /* Expression: 0
   * Referenced by: '<Root>/Serial Transmit4'
   */
  0.0,

  /* Expression: 511.5
   * Referenced by: '<S15>/Constant1'
   */
  511.5,

  /* Expression: 2658
   * Referenced by: '<S9>/Constant'
   */
  2658.0,

  /* Expression: 656
   * Referenced by: '<S9>/Constant1'
   */
  656.0,

  /* Expression: 360
   * Referenced by: '<S15>/Constant'
   */
  360.0,

  /* Expression: -0.75
   * Referenced by: '<S15>/RodOffset'
   */
  -0.75,

  /* Computed Parameter: DiscreteZeroPole1_A
   * Referenced by: '<S7>/Discrete Zero-Pole1'
   */
  0.92774348632855286,

  /* Computed Parameter: DiscreteZeroPole1_C
   * Referenced by: '<S7>/Discrete Zero-Pole1'
   */
  -0.069580761474641456,

  /* Computed Parameter: DiscreteZeroPole1_D
   * Referenced by: '<S7>/Discrete Zero-Pole1'
   */
  -0.0375,

  /* Expression: pi/180
   * Referenced by: '<S13>/Gain1'
   */
  0.017453292519943295,

  /* Computed Parameter: TSamp_WtEt
   * Referenced by: '<S14>/TSamp'
   */
  200.0,

  /* Computed Parameter: DiscreteZeroPole6_A
   * Referenced by: '<S7>/Discrete Zero-Pole6'
   */
  0.90483741803595952,

  /* Computed Parameter: DiscreteZeroPole6_C
   * Referenced by: '<S7>/Discrete Zero-Pole6'
   */
  0.09048374180359596,

  /* Computed Parameter: DiscreteZeroPole6_D
   * Referenced by: '<S7>/Discrete Zero-Pole6'
   */
  0.05,

  /* Expression: inf
   * Referenced by: '<S1>/Constant'
   */
  0.0,

  /* Expression: 1/1000
   * Referenced by: '<S4>/toMeters'
   */
  0.001,

  /* Computed Parameter: TSamp_WtEt_o
   * Referenced by: '<S11>/TSamp'
   */
  200.0,

  /* Computed Parameter: DiscreteZeroPole6_A_g
   * Referenced by: '<S4>/Discrete Zero-Pole6'
   */
  0.90483741803595952,

  /* Computed Parameter: DiscreteZeroPole6_C_j
   * Referenced by: '<S4>/Discrete Zero-Pole6'
   */
  0.09048374180359596,

  /* Computed Parameter: DiscreteZeroPole6_D_l
   * Referenced by: '<S4>/Discrete Zero-Pole6'
   */
  0.05,

  /* Expression: uint8(0)
   * Referenced by: '<S1>/S-Function Builder3'
   */
  0U,

  /* Expression: uint8(3)
   * Referenced by: '<S1>/S-Function Builder3'
   */
  3U,

  /* Expression: uint8(35)
   * Referenced by: '<S1>/S-Function Builder3'
   */
  35U
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
