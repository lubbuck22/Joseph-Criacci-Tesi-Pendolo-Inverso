/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Pendolo_Inverso.h
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

#ifndef Pendolo_Inverso_h_
#define Pendolo_Inverso_h_
#ifndef Pendolo_Inverso_COMMON_INCLUDES_
#define Pendolo_Inverso_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "MW_arduino_digitalio.h"
#include "MW_PWM.h"
#include "MW_AnalogIn.h"
#include "MW_SerialRead.h"
#include "MW_SerialWrite.h"
#endif                                 /* Pendolo_Inverso_COMMON_INCLUDES_ */

#include "Pendolo_Inverso_types.h"
#include <math.h>
#include "rt_nonfinite.h"
#include "rtGetNaN.h"
#include <stddef.h>
#include "MW_target_hardware_resources.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmStepTask
#define rtmStepTask(rtm, idx)          ((rtm)->Timing.TaskCounters.TID[(idx)] == 0)
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

#ifndef rtmTaskCounter
#define rtmTaskCounter(rtm, idx)       ((rtm)->Timing.TaskCounters.TID[(idx)])
#endif

/* Block signals (default storage) */
typedef struct {
  real_T FromWorkspace[3];             /* '<S15>/From Workspace' */
  real_T rtb_SerialReceive2_o1_m[2];
  real_T Subtract1;                    /* '<S15>/Subtract1' */
  real_T Product;                      /* '<S9>/Product' */
  real_T torqueOut_n;                  /* '<S1>/Move to Center' */
  real_T Divide_j;                     /* '<S15>/Divide' */
  int16_T SFunctionBuilder3;           /* '<S1>/S-Function Builder3' */
} B_Pendolo_Inverso_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  codertarget_arduinobase_i_lzg_T obj; /* '<Root>/Serial Transmit4' */
  codertarget_arduinobase_in_lz_T obj_m;/* '<Root>/Serial Receive2' */
  codertarget_arduinobase_int_l_T obj_e;/* '<S7>/Analog Input3' */
  codertarget_arduinobase_block_T obj_e1;/* '<S1>/Digital Output20' */
  codertarget_arduinobase_block_T obj_e5;/* '<S1>/Digital Output19' */
  codertarget_arduinobase_inter_T obj_f;/* '<S1>/PWM3' */
  real_T SFunctionBuilder3_DSTATE;     /* '<S1>/S-Function Builder3' */
  real_T DiscreteZeroPole1_DSTATE;     /* '<S7>/Discrete Zero-Pole1' */
  real_T UD_DSTATE;                    /* '<S14>/UD' */
  real_T DiscreteZeroPole6_DSTATE;     /* '<S7>/Discrete Zero-Pole6' */
  real_T UD_DSTATE_n;                  /* '<S11>/UD' */
  real_T DiscreteZeroPole6_DSTATE_h;   /* '<S4>/Discrete Zero-Pole6' */
  real_T RateTransition1_Buffer[5];    /* '<Root>/Rate Transition1' */
  real_T torque_value;                 /* '<Root>/check_torque' */
  real_T mode_value;                   /* '<Root>/check_input' */
  real_T enable_value;                 /* '<Root>/check_input' */
  real_T home_value;                   /* '<Root>/check_input' */
  real_T move_center_value;            /* '<Root>/check_input' */
  real_T enable_control_value;         /* '<Root>/check_input' */
  real_T Dir;                          /* '<S1>/to Pins' */
  real_T PWMOut;                       /* '<S1>/to Pins' */
  real_T torqueval;                    /* '<S1>/Selection' */
  real_T kp;                           /* '<S1>/Move to Center' */
  real_T set_pos;                      /* '<S1>/Move to Center' */
  real_T torqueval_l;                  /* '<S1>/Homing Block' */
  real_T state;                        /* '<S1>/Homing Block' */
  real_T homeval;                      /* '<S1>/Homing Block' */
  real_T counter;                      /* '<S1>/Homing Block' */
  real_T i;                            /* '<S1>/Homing Block' */
  real_T precart;                      /* '<S1>/Homing Block' */
  real_T prepos;                       /* '<S1>/Homing Block' */
  real_T precartArray[10];             /* '<S1>/Homing Block' */
  struct {
    void *TimePtr;
    void *DataPtr;
    void *RSimInfoPtr;
  } FromWorkspace_PWORK;               /* '<S15>/From Workspace' */

  struct {
    int_T PrevIndex;
  } FromWorkspace_IWORK;               /* '<S15>/From Workspace' */
} DW_Pendolo_Inverso_T;

/* Parameters (default storage) */
struct P_Pendolo_Inverso_T_ {
  real_T Tc;                           /* Variable: Tc
                                        * Referenced by: '<S7>/Analog Input3'
                                        */
  real_T DiscreteDerivative2_ICPrevScale;
                              /* Mask Parameter: DiscreteDerivative2_ICPrevScale
                               * Referenced by: '<S14>/UD'
                               */
  real_T DiscreteDerivative_ICPrevScaled;
                              /* Mask Parameter: DiscreteDerivative_ICPrevScaled
                               * Referenced by: '<S11>/UD'
                               */
  real_T SerialReceive2_Protocol;      /* Expression: 0
                                        * Referenced by: '<Root>/Serial Receive2'
                                        */
  real_T SerialReceive2_QueueSizeFactor;/* Expression: 3
                                         * Referenced by: '<Root>/Serial Receive2'
                                         */
  real_T SerialTransmit4_Protocol;     /* Expression: 0
                                        * Referenced by: '<Root>/Serial Transmit4'
                                        */
  real_T Constant1_Value;              /* Expression: 511.5
                                        * Referenced by: '<S15>/Constant1'
                                        */
  real_T Constant_Value;               /* Expression: 2658
                                        * Referenced by: '<S9>/Constant'
                                        */
  real_T Constant1_Value_c;            /* Expression: 656
                                        * Referenced by: '<S9>/Constant1'
                                        */
  real_T Constant_Value_c;             /* Expression: 360
                                        * Referenced by: '<S15>/Constant'
                                        */
  real_T RodOffset_Value;              /* Expression: -0.75
                                        * Referenced by: '<S15>/RodOffset'
                                        */
  real_T DiscreteZeroPole1_A;         /* Computed Parameter: DiscreteZeroPole1_A
                                       * Referenced by: '<S7>/Discrete Zero-Pole1'
                                       */
  real_T DiscreteZeroPole1_C;         /* Computed Parameter: DiscreteZeroPole1_C
                                       * Referenced by: '<S7>/Discrete Zero-Pole1'
                                       */
  real_T DiscreteZeroPole1_D;         /* Computed Parameter: DiscreteZeroPole1_D
                                       * Referenced by: '<S7>/Discrete Zero-Pole1'
                                       */
  real_T Gain1_Gain;                   /* Expression: pi/180
                                        * Referenced by: '<S13>/Gain1'
                                        */
  real_T TSamp_WtEt;                   /* Computed Parameter: TSamp_WtEt
                                        * Referenced by: '<S14>/TSamp'
                                        */
  real_T DiscreteZeroPole6_A;         /* Computed Parameter: DiscreteZeroPole6_A
                                       * Referenced by: '<S7>/Discrete Zero-Pole6'
                                       */
  real_T DiscreteZeroPole6_C;         /* Computed Parameter: DiscreteZeroPole6_C
                                       * Referenced by: '<S7>/Discrete Zero-Pole6'
                                       */
  real_T DiscreteZeroPole6_D;         /* Computed Parameter: DiscreteZeroPole6_D
                                       * Referenced by: '<S7>/Discrete Zero-Pole6'
                                       */
  real_T Constant_Value_o;             /* Expression: inf
                                        * Referenced by: '<S1>/Constant'
                                        */
  real_T toMeters_Gain;                /* Expression: 1/1000
                                        * Referenced by: '<S4>/toMeters'
                                        */
  real_T TSamp_WtEt_o;                 /* Computed Parameter: TSamp_WtEt_o
                                        * Referenced by: '<S11>/TSamp'
                                        */
  real_T DiscreteZeroPole6_A_g;     /* Computed Parameter: DiscreteZeroPole6_A_g
                                     * Referenced by: '<S4>/Discrete Zero-Pole6'
                                     */
  real_T DiscreteZeroPole6_C_j;     /* Computed Parameter: DiscreteZeroPole6_C_j
                                     * Referenced by: '<S4>/Discrete Zero-Pole6'
                                     */
  real_T DiscreteZeroPole6_D_l;     /* Computed Parameter: DiscreteZeroPole6_D_l
                                     * Referenced by: '<S4>/Discrete Zero-Pole6'
                                     */
  uint8_T SFunctionBuilder3_P1;        /* Expression: uint8(0)
                                        * Referenced by: '<S1>/S-Function Builder3'
                                        */
  uint8_T SFunctionBuilder3_P2;        /* Expression: uint8(3)
                                        * Referenced by: '<S1>/S-Function Builder3'
                                        */
  uint8_T SFunctionBuilder3_P3;        /* Expression: uint8(35)
                                        * Referenced by: '<S1>/S-Function Builder3'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_Pendolo_Inverso_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    struct {
      uint8_T TID[3];
    } TaskCounters;

    struct {
      boolean_T TID1_2;
    } RateInteraction;

    SimTimeStep simTimeStep;
    time_T *t;
    time_T tArray[3];
  } Timing;
};

/* Block parameters (default storage) */
extern P_Pendolo_Inverso_T Pendolo_Inverso_P;

/* Block signals (default storage) */
extern B_Pendolo_Inverso_T Pendolo_Inverso_B;

/* Block states (default storage) */
extern DW_Pendolo_Inverso_T Pendolo_Inverso_DW;

/* External function called from main */
extern void Pendolo_Inverso_SetEventsForThisBaseStep(boolean_T *eventFlags);

/* Model entry point functions */
extern void Pendolo_Inverso_initialize(void);
extern void Pendolo_Inverso_step0(void);
extern void Pendolo_Inverso_step2(void);
extern void Pendolo_Inverso_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Pendolo_Inverso_T *const Pendolo_Inverso_M;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S11>/Data Type Duplicate' : Unused code path elimination
 * Block '<S15>/Display' : Unused code path elimination
 * Block '<S15>/Display1' : Unused code path elimination
 * Block '<S15>/Display2' : Unused code path elimination
 * Block '<S15>/Display3' : Unused code path elimination
 * Block '<S15>/Display4' : Unused code path elimination
 * Block '<S12>/Display' : Unused code path elimination
 * Block '<S14>/Data Type Duplicate' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Pendolo_Inverso'
 * '<S1>'   : 'Pendolo_Inverso/Pendulum Control'
 * '<S2>'   : 'Pendolo_Inverso/check_input'
 * '<S3>'   : 'Pendolo_Inverso/check_torque'
 * '<S4>'   : 'Pendolo_Inverso/Pendulum Control/Check Position1'
 * '<S5>'   : 'Pendolo_Inverso/Pendulum Control/Homing Block'
 * '<S6>'   : 'Pendolo_Inverso/Pendulum Control/Move to Center'
 * '<S7>'   : 'Pendolo_Inverso/Pendulum Control/Read Angle'
 * '<S8>'   : 'Pendolo_Inverso/Pendulum Control/Selection'
 * '<S9>'   : 'Pendolo_Inverso/Pendulum Control/encoder to mm'
 * '<S10>'  : 'Pendolo_Inverso/Pendulum Control/to Pins'
 * '<S11>'  : 'Pendolo_Inverso/Pendulum Control/Check Position1/Discrete Derivative'
 * '<S12>'  : 'Pendolo_Inverso/Pendulum Control/Read Angle/Convert3'
 * '<S13>'  : 'Pendolo_Inverso/Pendulum Control/Read Angle/Degrees to Radians2'
 * '<S14>'  : 'Pendolo_Inverso/Pendulum Control/Read Angle/Discrete Derivative2'
 * '<S15>'  : 'Pendolo_Inverso/Pendulum Control/Read Angle/Convert3/Analog to Angle'
 * '<S16>'  : 'Pendolo_Inverso/Pendulum Control/Read Angle/Convert3/Analog to Angle/If Action Subsystem'
 * '<S17>'  : 'Pendolo_Inverso/Pendulum Control/Read Angle/Convert3/Analog to Angle/If Action Subsystem1'
 */
#endif                                 /* Pendolo_Inverso_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
