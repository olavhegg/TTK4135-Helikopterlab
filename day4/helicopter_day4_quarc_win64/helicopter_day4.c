/*
 * helicopter_day4.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "helicopter_day4".
 *
 * Model version              : 11.10
 * Simulink Coder version : 9.4 (R2020b) 29-Jul-2020
 * C source code generated on : Wed Mar 16 12:38:50 2022
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "helicopter_day4.h"
#include "helicopter_day4_private.h"
#include "helicopter_day4_dt.h"

/* Block signals (default storage) */
B_helicopter_day4_T helicopter_day4_B;

/* Continuous states */
X_helicopter_day4_T helicopter_day4_X;

/* Block states (default storage) */
DW_helicopter_day4_T helicopter_day4_DW;

/* Real-time model */
static RT_MODEL_helicopter_day4_T helicopter_day4_M_;
RT_MODEL_helicopter_day4_T *const helicopter_day4_M = &helicopter_day4_M_;

/*
 * Writes out MAT-file header.  Returns success or failure.
 * Returns:
 *      0 - success
 *      1 - failure
 */
int_T rt_WriteMat4FileHeader(FILE *fp, int32_T m, int32_T n, const char *name)
{
  typedef enum { ELITTLE_ENDIAN, EBIG_ENDIAN } ByteOrder;

  int16_T one = 1;
  ByteOrder byteOrder = (*((int8_T *)&one)==1) ? ELITTLE_ENDIAN : EBIG_ENDIAN;
  int32_T type = (byteOrder == ELITTLE_ENDIAN) ? 0: 1000;
  int32_T imagf = 0;
  int32_T name_len = (int32_T)strlen(name) + 1;
  if ((fwrite(&type, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&m, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&n, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&imagf, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&name_len, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(name, sizeof(char), name_len, fp) == 0)) {
    return(1);
  } else {
    return(0);
  }
}                                      /* end rt_WriteMat4FileHeader */

/*
 * This function updates continuous states using the ODE1 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE1_IntgData *id = (ODE1_IntgData *)rtsiGetSolverData(si);
  real_T *f0 = id->f[0];
  int_T i;
  int_T nXc = 4;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  helicopter_day4_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void helicopter_day4_output(void)
{
  /* local block i/o variables */
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  real_T rtb_HILReadEncoderTimebase_o3;
  real_T rtb_TmpSignalConversionAtToFile[14];
  real_T rtb_Clock_0[6];
  real_T rtb_Clock_1[6];
  real_T rtb_Sum3_j[2];
  real_T tmp[2];
  real_T tmp_0[2];
  real_T lastTime;
  real_T rtb_Backgain;
  real_T rtb_Clock;
  real_T rtb_Derivative;
  real_T *lastU;
  int32_T i;
  int32_T i_0;
  int8_T rtAction;
  if (rtmIsMajorTimeStep(helicopter_day4_M)) {
    /* set solver stop time */
    if (!(helicopter_day4_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&helicopter_day4_M->solverInfo,
                            ((helicopter_day4_M->Timing.clockTickH0 + 1) *
        helicopter_day4_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&helicopter_day4_M->solverInfo,
                            ((helicopter_day4_M->Timing.clockTick0 + 1) *
        helicopter_day4_M->Timing.stepSize0 +
        helicopter_day4_M->Timing.clockTickH0 *
        helicopter_day4_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(helicopter_day4_M)) {
    helicopter_day4_M->Timing.t[0] = rtsiGetT(&helicopter_day4_M->solverInfo);
  }

  /* Reset subsysRan breadcrumbs */
  srClearBC(helicopter_day4_DW.IfActionSubsystem_SubsysRanBC);
  if (rtmIsMajorTimeStep(helicopter_day4_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

    /* S-Function Block: helicopter_day4/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder
        (helicopter_day4_DW.HILReadEncoderTimebase_Task, 1,
         &helicopter_day4_DW.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_day4_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 =
          helicopter_day4_DW.HILReadEncoderTimebase_Buffer[0];
        rtb_HILReadEncoderTimebase_o2 =
          helicopter_day4_DW.HILReadEncoderTimebase_Buffer[1];
        rtb_HILReadEncoderTimebase_o3 =
          helicopter_day4_DW.HILReadEncoderTimebase_Buffer[2];
      }
    }
  }

  /* FromWorkspace: '<Root>/From Workspace' */
  {
    real_T *pDataValues = (real_T *)
      helicopter_day4_DW.FromWorkspace_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *)
      helicopter_day4_DW.FromWorkspace_PWORK.TimePtr;
    int_T currTimeIndex = helicopter_day4_DW.FromWorkspace_IWORK.PrevIndex;
    real_T t = helicopter_day4_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[80]) {
      currTimeIndex = 79;
    } else {
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t >= pTimeValues[currTimeIndex + 1]) {
          currTimeIndex++;
        }
      }
    }

    helicopter_day4_DW.FromWorkspace_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          helicopter_day4_B.FromWorkspace = pDataValues[currTimeIndex];
        } else {
          helicopter_day4_B.FromWorkspace = pDataValues[currTimeIndex + 1];
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex= currTimeIndex;
        d1 = pDataValues[TimeIndex];
        d2 = pDataValues[TimeIndex + 1];
        helicopter_day4_B.FromWorkspace = (real_T) rtInterpolate(d1, d2, f1, f2);
        pDataValues += 81;
      }
    }
  }

  /* FromWorkspace: '<Root>/From Workspace2' */
  {
    real_T *pDataValues = (real_T *)
      helicopter_day4_DW.FromWorkspace2_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *)
      helicopter_day4_DW.FromWorkspace2_PWORK.TimePtr;
    int_T currTimeIndex = helicopter_day4_DW.FromWorkspace2_IWORK.PrevIndex;
    real_T t = helicopter_day4_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[80]) {
      currTimeIndex = 79;
    } else {
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t >= pTimeValues[currTimeIndex + 1]) {
          currTimeIndex++;
        }
      }
    }

    helicopter_day4_DW.FromWorkspace2_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          helicopter_day4_B.FromWorkspace2 = pDataValues[currTimeIndex];
        } else {
          helicopter_day4_B.FromWorkspace2 = pDataValues[currTimeIndex + 1];
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex= currTimeIndex;
        d1 = pDataValues[TimeIndex];
        d2 = pDataValues[TimeIndex + 1];
        helicopter_day4_B.FromWorkspace2 = (real_T) rtInterpolate(d1, d2, f1, f2);
        pDataValues += 81;
      }
    }
  }

  /* FromWorkspace: '<Root>/From Workspace1' */
  {
    real_T *pDataValues = (real_T *)
      helicopter_day4_DW.FromWorkspace1_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *)
      helicopter_day4_DW.FromWorkspace1_PWORK.TimePtr;
    int_T currTimeIndex = helicopter_day4_DW.FromWorkspace1_IWORK.PrevIndex;
    real_T t = helicopter_day4_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[80]) {
      currTimeIndex = 79;
    } else {
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t >= pTimeValues[currTimeIndex + 1]) {
          currTimeIndex++;
        }
      }
    }

    helicopter_day4_DW.FromWorkspace1_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 6; ++elIdx) {
              (&helicopter_day4_B.FromWorkspace1[0])[elIdx] =
                pDataValues[currTimeIndex];
              pDataValues += 81;
            }
          }
        } else {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 6; ++elIdx) {
              (&helicopter_day4_B.FromWorkspace1[0])[elIdx] =
                pDataValues[currTimeIndex + 1];
              pDataValues += 81;
            }
          }
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex= currTimeIndex;

        {
          int_T elIdx;
          for (elIdx = 0; elIdx < 6; ++elIdx) {
            d1 = pDataValues[TimeIndex];
            d2 = pDataValues[TimeIndex + 1];
            (&helicopter_day4_B.FromWorkspace1[0])[elIdx] = (real_T)
              rtInterpolate(d1, d2, f1, f2);
            pDataValues += 81;
          }
        }
      }
    }
  }

  if (rtmIsMajorTimeStep(helicopter_day4_M)) {
    /* Gain: '<S4>/Travel: Count to rad' incorporates:
     *  Gain: '<S4>/Travel_gain'
     */
    helicopter_day4_B.TravelCounttorad = helicopter_day4_P.travel_gain *
      rtb_HILReadEncoderTimebase_o1 * helicopter_day4_P.TravelCounttorad_Gain;

    /* Gain: '<S12>/Gain' */
    helicopter_day4_B.Gain = helicopter_day4_P.Gain_Gain *
      helicopter_day4_B.TravelCounttorad;

    /* Gain: '<S4>/Pitch: Count to rad' */
    helicopter_day4_B.PitchCounttorad = helicopter_day4_P.PitchCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o2;

    /* Gain: '<S9>/Gain' */
    helicopter_day4_B.Gain_i = helicopter_day4_P.Gain_Gain_a *
      helicopter_day4_B.PitchCounttorad;
  }

  /* Gain: '<S13>/Gain' incorporates:
   *  TransferFcn: '<S4>/Travel: Transfer Fcn'
   */
  helicopter_day4_B.Gain_d = (helicopter_day4_P.TravelTransferFcn_C *
    helicopter_day4_X.TravelTransferFcn_CSTATE +
    helicopter_day4_P.TravelTransferFcn_D * helicopter_day4_B.TravelCounttorad) *
    helicopter_day4_P.Gain_Gain_l;

  /* Gain: '<S10>/Gain' incorporates:
   *  TransferFcn: '<S4>/Pitch: Transfer Fcn'
   */
  helicopter_day4_B.Gain_b = (helicopter_day4_P.PitchTransferFcn_C *
    helicopter_day4_X.PitchTransferFcn_CSTATE +
    helicopter_day4_P.PitchTransferFcn_D * helicopter_day4_B.PitchCounttorad) *
    helicopter_day4_P.Gain_Gain_ae;
  if (rtmIsMajorTimeStep(helicopter_day4_M)) {
    /* Gain: '<S4>/Elevation: Count to rad' incorporates:
     *  Gain: '<S4>/Elevation_gain'
     */
    helicopter_day4_B.ElevationCounttorad = helicopter_day4_P.elevation_gain *
      rtb_HILReadEncoderTimebase_o3 * helicopter_day4_P.ElevationCounttorad_Gain;

    /* Gain: '<S7>/Gain' */
    helicopter_day4_B.Gain_e = helicopter_day4_P.Gain_Gain_lv *
      helicopter_day4_B.ElevationCounttorad;

    /* Sum: '<Root>/Sum' incorporates:
     *  Constant: '<Root>/elavation_offset [deg]'
     */
    helicopter_day4_B.Sum = helicopter_day4_B.Gain_e +
      helicopter_day4_P.elavation_offsetdeg_Value;
  }

  /* Gain: '<S8>/Gain' incorporates:
   *  TransferFcn: '<S4>/Elevation: Transfer Fcn'
   */
  helicopter_day4_B.Gain_dg = (helicopter_day4_P.ElevationTransferFcn_C *
    helicopter_day4_X.ElevationTransferFcn_CSTATE +
    helicopter_day4_P.ElevationTransferFcn_D *
    helicopter_day4_B.ElevationCounttorad) * helicopter_day4_P.Gain_Gain_n;

  /* Gain: '<S2>/Gain1' */
  helicopter_day4_B.Gain1[0] = helicopter_day4_P.Gain1_Gain *
    helicopter_day4_B.Gain;
  helicopter_day4_B.Gain1[1] = helicopter_day4_P.Gain1_Gain *
    helicopter_day4_B.Gain_d;
  helicopter_day4_B.Gain1[2] = helicopter_day4_P.Gain1_Gain *
    helicopter_day4_B.Gain_i;
  helicopter_day4_B.Gain1[3] = helicopter_day4_P.Gain1_Gain *
    helicopter_day4_B.Gain_b;
  helicopter_day4_B.Gain1[4] = helicopter_day4_P.Gain1_Gain *
    helicopter_day4_B.Sum;
  helicopter_day4_B.Gain1[5] = helicopter_day4_P.Gain1_Gain *
    helicopter_day4_B.Gain_dg;
  if (rtmIsMajorTimeStep(helicopter_day4_M)) {
    /* SignalConversion generated from: '<Root>/To File' */
    rtb_TmpSignalConversionAtToFile[0] = helicopter_day4_B.FromWorkspace;
    rtb_TmpSignalConversionAtToFile[1] = helicopter_day4_B.FromWorkspace2;
    for (i = 0; i < 6; i++) {
      rtb_TmpSignalConversionAtToFile[i + 2] =
        helicopter_day4_B.FromWorkspace1[i];
      rtb_TmpSignalConversionAtToFile[i + 8] = helicopter_day4_B.Gain1[i];
    }

    /* End of SignalConversion generated from: '<Root>/To File' */

    /* ToFile: '<Root>/To File' */
    {
      if (!(++helicopter_day4_DW.ToFile_IWORK.Decimation % 1) &&
          (helicopter_day4_DW.ToFile_IWORK.Count * (14 + 1)) + 1 < 100000000 ) {
        FILE *fp = (FILE *) helicopter_day4_DW.ToFile_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[14 + 1];
          helicopter_day4_DW.ToFile_IWORK.Decimation = 0;
          u[0] = helicopter_day4_M->Timing.t[1];
          u[1] = rtb_TmpSignalConversionAtToFile[0];
          u[2] = rtb_TmpSignalConversionAtToFile[1];
          u[3] = rtb_TmpSignalConversionAtToFile[2];
          u[4] = rtb_TmpSignalConversionAtToFile[3];
          u[5] = rtb_TmpSignalConversionAtToFile[4];
          u[6] = rtb_TmpSignalConversionAtToFile[5];
          u[7] = rtb_TmpSignalConversionAtToFile[6];
          u[8] = rtb_TmpSignalConversionAtToFile[7];
          u[9] = rtb_TmpSignalConversionAtToFile[8];
          u[10] = rtb_TmpSignalConversionAtToFile[9];
          u[11] = rtb_TmpSignalConversionAtToFile[10];
          u[12] = rtb_TmpSignalConversionAtToFile[11];
          u[13] = rtb_TmpSignalConversionAtToFile[12];
          u[14] = rtb_TmpSignalConversionAtToFile[13];
          if (fwrite(u, sizeof(real_T), 14 + 1, fp) != 14 + 1) {
            rtmSetErrorStatus(helicopter_day4_M,
                              "Error writing to MAT-file lab_day4_4.mat");
            return;
          }

          if (((++helicopter_day4_DW.ToFile_IWORK.Count) * (14 + 1))+1 >=
              100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file lab_day4_4.mat.\n");
          }
        }
      }
    }
  }

  /* Sum: '<Root>/Sum4' incorporates:
   *  Constant: '<Root>/Bias'
   *  FromWorkspace: '<Root>/From Workspace1'
   *  Sum: '<Root>/Sum5'
   */
  rtb_Clock_0[0] = helicopter_day4_P.Bias_Value + helicopter_day4_B.Gain1[0];
  for (i = 0; i < 5; i++) {
    rtb_Clock_0[i + 1] = helicopter_day4_B.Gain1[i + 1];
  }

  for (i = 0; i < 6; i++) {
    rtb_Clock_1[i] = rtb_Clock_0[i] - helicopter_day4_B.FromWorkspace1[i];
  }

  /* End of Sum: '<Root>/Sum4' */

  /* Sum: '<Root>/Sum3' */
  tmp[0] = helicopter_day4_B.FromWorkspace;
  tmp[1] = helicopter_day4_B.FromWorkspace2;
  for (i = 0; i < 2; i++) {
    /* Gain: '<Root>/Gain' */
    tmp_0[i] = 0.0;
    for (i_0 = 0; i_0 < 6; i_0++) {
      tmp_0[i] += helicopter_day4_P.K_lqr[(i_0 << 1) + i] * rtb_Clock_1[i_0];
    }

    /* End of Gain: '<Root>/Gain' */

    /* Sum: '<Root>/Sum3' */
    rtb_Sum3_j[i] = tmp[i] - tmp_0[i];
  }

  /* Sum: '<Root>/Sum1' incorporates:
   *  Constant: '<Root>/Vd_bias'
   *  Gain: '<S5>/K_pd'
   *  Gain: '<S5>/K_pp'
   *  Sum: '<S5>/Sum2'
   *  Sum: '<S5>/Sum3'
   */
  rtb_Clock = ((rtb_Sum3_j[0] - helicopter_day4_B.Gain1[2]) *
               helicopter_day4_P.K_pp - helicopter_day4_P.K_pd *
               helicopter_day4_B.Gain1[3]) + helicopter_day4_P.Vd_ff;

  /* Integrator: '<S3>/Integrator' */
  /* Limited  Integrator  */
  if (helicopter_day4_X.Integrator_CSTATE >=
      helicopter_day4_P.Integrator_UpperSat) {
    helicopter_day4_X.Integrator_CSTATE = helicopter_day4_P.Integrator_UpperSat;
  } else {
    if (helicopter_day4_X.Integrator_CSTATE <=
        helicopter_day4_P.Integrator_LowerSat) {
      helicopter_day4_X.Integrator_CSTATE =
        helicopter_day4_P.Integrator_LowerSat;
    }
  }

  /* Sum: '<S3>/Sum' */
  rtb_Derivative = rtb_Sum3_j[1] - helicopter_day4_B.Gain1[4];

  /* Sum: '<Root>/Sum2' incorporates:
   *  Constant: '<Root>/Vs_bias'
   *  Gain: '<S3>/K_ed'
   *  Gain: '<S3>/K_ep'
   *  Integrator: '<S3>/Integrator'
   *  Sum: '<S3>/Sum1'
   */
  rtb_Backgain = ((helicopter_day4_P.K_ep * rtb_Derivative +
                   helicopter_day4_X.Integrator_CSTATE) - helicopter_day4_P.K_ed
                  * helicopter_day4_B.Gain1[5]) + helicopter_day4_P.Vs_ff;

  /* If: '<S3>/If' incorporates:
   *  Clock: '<S3>/Clock'
   *  Gain: '<S3>/K_ei'
   *  Inport: '<S6>/In1'
   */
  if (rtmIsMajorTimeStep(helicopter_day4_M)) {
    rtAction = (int8_T)!(helicopter_day4_M->Timing.t[0] >= 2.0);
    helicopter_day4_DW.If_ActiveSubsystem = rtAction;
  } else {
    rtAction = helicopter_day4_DW.If_ActiveSubsystem;
  }

  if (rtAction == 0) {
    /* Outputs for IfAction SubSystem: '<S3>/If Action Subsystem' incorporates:
     *  ActionPort: '<S6>/Action Port'
     */
    helicopter_day4_B.In1 = helicopter_day4_P.K_ei * rtb_Derivative;
    if (rtmIsMajorTimeStep(helicopter_day4_M)) {
      srUpdateBC(helicopter_day4_DW.IfActionSubsystem_SubsysRanBC);
    }

    /* End of Outputs for SubSystem: '<S3>/If Action Subsystem' */
  }

  /* End of If: '<S3>/If' */
  if (rtmIsMajorTimeStep(helicopter_day4_M)) {
  }

  /* Derivative: '<S4>/Derivative' */
  rtb_Derivative = helicopter_day4_M->Timing.t[0];
  if ((helicopter_day4_DW.TimeStampA >= rtb_Derivative) &&
      (helicopter_day4_DW.TimeStampB >= rtb_Derivative)) {
    rtb_Derivative = 0.0;
  } else {
    lastTime = helicopter_day4_DW.TimeStampA;
    lastU = &helicopter_day4_DW.LastUAtTimeA;
    if (helicopter_day4_DW.TimeStampA < helicopter_day4_DW.TimeStampB) {
      if (helicopter_day4_DW.TimeStampB < rtb_Derivative) {
        lastTime = helicopter_day4_DW.TimeStampB;
        lastU = &helicopter_day4_DW.LastUAtTimeB;
      }
    } else {
      if (helicopter_day4_DW.TimeStampA >= rtb_Derivative) {
        lastTime = helicopter_day4_DW.TimeStampB;
        lastU = &helicopter_day4_DW.LastUAtTimeB;
      }
    }

    rtb_Derivative = (helicopter_day4_B.PitchCounttorad - *lastU) /
      (rtb_Derivative - lastTime);
  }

  /* End of Derivative: '<S4>/Derivative' */

  /* Gain: '<S11>/Gain' */
  helicopter_day4_B.Gain_l = helicopter_day4_P.Gain_Gain_a1 * rtb_Derivative;
  if (rtmIsMajorTimeStep(helicopter_day4_M)) {
  }

  /* Gain: '<S1>/Back gain' incorporates:
   *  Sum: '<S1>/Subtract'
   */
  rtb_Derivative = (rtb_Backgain - rtb_Clock) * helicopter_day4_P.Backgain_Gain;

  /* Saturate: '<S4>/Back motor: Saturation' */
  if (rtb_Derivative > helicopter_day4_P.BackmotorSaturation_UpperSat) {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopter_day4_B.BackmotorSaturation =
      helicopter_day4_P.BackmotorSaturation_UpperSat;
  } else if (rtb_Derivative < helicopter_day4_P.BackmotorSaturation_LowerSat) {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopter_day4_B.BackmotorSaturation =
      helicopter_day4_P.BackmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopter_day4_B.BackmotorSaturation = rtb_Derivative;
  }

  /* End of Saturate: '<S4>/Back motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopter_day4_M)) {
  }

  /* Gain: '<S1>/Front gain' incorporates:
   *  Sum: '<S1>/Add'
   */
  rtb_Derivative = (rtb_Clock + rtb_Backgain) * helicopter_day4_P.Frontgain_Gain;

  /* Saturate: '<S4>/Front motor: Saturation' */
  if (rtb_Derivative > helicopter_day4_P.FrontmotorSaturation_UpperSat) {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopter_day4_B.FrontmotorSaturation =
      helicopter_day4_P.FrontmotorSaturation_UpperSat;
  } else if (rtb_Derivative < helicopter_day4_P.FrontmotorSaturation_LowerSat) {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopter_day4_B.FrontmotorSaturation =
      helicopter_day4_P.FrontmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopter_day4_B.FrontmotorSaturation = rtb_Derivative;
  }

  /* End of Saturate: '<S4>/Front motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopter_day4_M)) {
    /* S-Function (hil_write_analog_block): '<S4>/HIL Write Analog' */

    /* S-Function Block: helicopter_day4/Helicopter_interface/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      helicopter_day4_DW.HILWriteAnalog_Buffer[0] =
        helicopter_day4_B.FrontmotorSaturation;
      helicopter_day4_DW.HILWriteAnalog_Buffer[1] =
        helicopter_day4_B.BackmotorSaturation;
      result = hil_write_analog(helicopter_day4_DW.HILInitialize_Card,
        helicopter_day4_P.HILWriteAnalog_channels, 2,
        &helicopter_day4_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_day4_M, _rt_error_message);
      }
    }
  }
}

/* Model update function */
void helicopter_day4_update(void)
{
  real_T *lastU;

  /* Update for Derivative: '<S4>/Derivative' */
  if (helicopter_day4_DW.TimeStampA == (rtInf)) {
    helicopter_day4_DW.TimeStampA = helicopter_day4_M->Timing.t[0];
    lastU = &helicopter_day4_DW.LastUAtTimeA;
  } else if (helicopter_day4_DW.TimeStampB == (rtInf)) {
    helicopter_day4_DW.TimeStampB = helicopter_day4_M->Timing.t[0];
    lastU = &helicopter_day4_DW.LastUAtTimeB;
  } else if (helicopter_day4_DW.TimeStampA < helicopter_day4_DW.TimeStampB) {
    helicopter_day4_DW.TimeStampA = helicopter_day4_M->Timing.t[0];
    lastU = &helicopter_day4_DW.LastUAtTimeA;
  } else {
    helicopter_day4_DW.TimeStampB = helicopter_day4_M->Timing.t[0];
    lastU = &helicopter_day4_DW.LastUAtTimeB;
  }

  *lastU = helicopter_day4_B.PitchCounttorad;

  /* End of Update for Derivative: '<S4>/Derivative' */
  if (rtmIsMajorTimeStep(helicopter_day4_M)) {
    rt_ertODEUpdateContinuousStates(&helicopter_day4_M->solverInfo);
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++helicopter_day4_M->Timing.clockTick0)) {
    ++helicopter_day4_M->Timing.clockTickH0;
  }

  helicopter_day4_M->Timing.t[0] = rtsiGetSolverStopTime
    (&helicopter_day4_M->solverInfo);

  {
    /* Update absolute timer for sample time: [0.002s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++helicopter_day4_M->Timing.clockTick1)) {
      ++helicopter_day4_M->Timing.clockTickH1;
    }

    helicopter_day4_M->Timing.t[1] = helicopter_day4_M->Timing.clockTick1 *
      helicopter_day4_M->Timing.stepSize1 +
      helicopter_day4_M->Timing.clockTickH1 *
      helicopter_day4_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void helicopter_day4_derivatives(void)
{
  XDot_helicopter_day4_T *_rtXdot;
  boolean_T lsat;
  boolean_T usat;
  _rtXdot = ((XDot_helicopter_day4_T *) helicopter_day4_M->derivs);

  /* Derivatives for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  _rtXdot->TravelTransferFcn_CSTATE = 0.0;
  _rtXdot->TravelTransferFcn_CSTATE += helicopter_day4_P.TravelTransferFcn_A *
    helicopter_day4_X.TravelTransferFcn_CSTATE;
  _rtXdot->TravelTransferFcn_CSTATE += helicopter_day4_B.TravelCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  _rtXdot->PitchTransferFcn_CSTATE = 0.0;
  _rtXdot->PitchTransferFcn_CSTATE += helicopter_day4_P.PitchTransferFcn_A *
    helicopter_day4_X.PitchTransferFcn_CSTATE;
  _rtXdot->PitchTransferFcn_CSTATE += helicopter_day4_B.PitchCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  _rtXdot->ElevationTransferFcn_CSTATE = 0.0;
  _rtXdot->ElevationTransferFcn_CSTATE +=
    helicopter_day4_P.ElevationTransferFcn_A *
    helicopter_day4_X.ElevationTransferFcn_CSTATE;
  _rtXdot->ElevationTransferFcn_CSTATE += helicopter_day4_B.ElevationCounttorad;

  /* Derivatives for Integrator: '<S3>/Integrator' */
  lsat = (helicopter_day4_X.Integrator_CSTATE <=
          helicopter_day4_P.Integrator_LowerSat);
  usat = (helicopter_day4_X.Integrator_CSTATE >=
          helicopter_day4_P.Integrator_UpperSat);
  if (((!lsat) && (!usat)) || (lsat && (helicopter_day4_B.In1 > 0.0)) || (usat &&
       (helicopter_day4_B.In1 < 0.0))) {
    _rtXdot->Integrator_CSTATE = helicopter_day4_B.In1;
  } else {
    /* in saturation */
    _rtXdot->Integrator_CSTATE = 0.0;
  }

  /* End of Derivatives for Integrator: '<S3>/Integrator' */
}

/* Model initialize function */
void helicopter_day4_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopter_day4/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &helicopter_day4_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_day4_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(helicopter_day4_DW.HILInitialize_Card,
      "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_day4_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(helicopter_day4_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_day4_M, _rt_error_message);
      return;
    }

    if ((helicopter_day4_P.HILInitialize_AIPStart && !is_switching) ||
        (helicopter_day4_P.HILInitialize_AIPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &helicopter_day4_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = (helicopter_day4_P.HILInitialize_AILow);
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &helicopter_day4_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = helicopter_day4_P.HILInitialize_AIHigh;
        }
      }

      result = hil_set_analog_input_ranges(helicopter_day4_DW.HILInitialize_Card,
        helicopter_day4_P.HILInitialize_AIChannels, 8U,
        &helicopter_day4_DW.HILInitialize_AIMinimums[0],
        &helicopter_day4_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_day4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_day4_P.HILInitialize_AOPStart && !is_switching) ||
        (helicopter_day4_P.HILInitialize_AOPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &helicopter_day4_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = (helicopter_day4_P.HILInitialize_AOLow);
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &helicopter_day4_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = helicopter_day4_P.HILInitialize_AOHigh;
        }
      }

      result = hil_set_analog_output_ranges
        (helicopter_day4_DW.HILInitialize_Card,
         helicopter_day4_P.HILInitialize_AOChannels, 8U,
         &helicopter_day4_DW.HILInitialize_AOMinimums[0],
         &helicopter_day4_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_day4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_day4_P.HILInitialize_AOStart && !is_switching) ||
        (helicopter_day4_P.HILInitialize_AOEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter_day4_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter_day4_P.HILInitialize_AOInitial;
        }
      }

      result = hil_write_analog(helicopter_day4_DW.HILInitialize_Card,
        helicopter_day4_P.HILInitialize_AOChannels, 8U,
        &helicopter_day4_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_day4_M, _rt_error_message);
        return;
      }
    }

    if (helicopter_day4_P.HILInitialize_AOReset) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter_day4_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter_day4_P.HILInitialize_AOWatchdog;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (helicopter_day4_DW.HILInitialize_Card,
         helicopter_day4_P.HILInitialize_AOChannels, 8U,
         &helicopter_day4_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_day4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_day4_P.HILInitialize_EIPStart && !is_switching) ||
        (helicopter_day4_P.HILInitialize_EIPEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &helicopter_day4_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = helicopter_day4_P.HILInitialize_EIQuadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode
        (helicopter_day4_DW.HILInitialize_Card,
         helicopter_day4_P.HILInitialize_EIChannels, 8U,
         (t_encoder_quadrature_mode *)
         &helicopter_day4_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_day4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_day4_P.HILInitialize_EIStart && !is_switching) ||
        (helicopter_day4_P.HILInitialize_EIEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &helicopter_day4_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = helicopter_day4_P.HILInitialize_EIInitial;
        }
      }

      result = hil_set_encoder_counts(helicopter_day4_DW.HILInitialize_Card,
        helicopter_day4_P.HILInitialize_EIChannels, 8U,
        &helicopter_day4_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_day4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_day4_P.HILInitialize_POPStart && !is_switching) ||
        (helicopter_day4_P.HILInitialize_POPEnter && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &helicopter_day4_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = helicopter_day4_P.HILInitialize_POModes;
        }
      }

      result = hil_set_pwm_mode(helicopter_day4_DW.HILInitialize_Card,
        helicopter_day4_P.HILInitialize_POChannels, 8U, (t_pwm_mode *)
        &helicopter_day4_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_day4_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_POChannels =
          helicopter_day4_P.HILInitialize_POChannels;
        int32_T *dw_POModeValues =
          &helicopter_day4_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE ||
              dw_POModeValues[i1] == PWM_RAW_MODE) {
            helicopter_day4_DW.HILInitialize_POSortedChans[num_duty_cycle_modes]
              = (p_HILInitialize_POChannels[i1]);
            helicopter_day4_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]
              = helicopter_day4_P.HILInitialize_POFrequency;
            num_duty_cycle_modes++;
          } else {
            helicopter_day4_DW.HILInitialize_POSortedChans[7U -
              num_frequency_modes] = (p_HILInitialize_POChannels[i1]);
            helicopter_day4_DW.HILInitialize_POSortedFreqs[7U -
              num_frequency_modes] = helicopter_day4_P.HILInitialize_POFrequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(helicopter_day4_DW.HILInitialize_Card,
          &helicopter_day4_DW.HILInitialize_POSortedChans[0],
          num_duty_cycle_modes, &helicopter_day4_DW.HILInitialize_POSortedFreqs
          [0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter_day4_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(helicopter_day4_DW.HILInitialize_Card,
          &helicopter_day4_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &helicopter_day4_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter_day4_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &helicopter_day4_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = helicopter_day4_P.HILInitialize_POConfiguration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues =
          &helicopter_day4_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = helicopter_day4_P.HILInitialize_POAlignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &helicopter_day4_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = helicopter_day4_P.HILInitialize_POPolarity;
        }
      }

      result = hil_set_pwm_configuration(helicopter_day4_DW.HILInitialize_Card,
        helicopter_day4_P.HILInitialize_POChannels, 8U,
        (t_pwm_configuration *) &helicopter_day4_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &helicopter_day4_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &helicopter_day4_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_day4_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs =
          &helicopter_day4_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = helicopter_day4_P.HILInitialize_POLeading;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &helicopter_day4_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_day4_P.HILInitialize_POTrailing;
        }
      }

      result = hil_set_pwm_deadband(helicopter_day4_DW.HILInitialize_Card,
        helicopter_day4_P.HILInitialize_POChannels, 8U,
        &helicopter_day4_DW.HILInitialize_POSortedFreqs[0],
        &helicopter_day4_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_day4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_day4_P.HILInitialize_POStart && !is_switching) ||
        (helicopter_day4_P.HILInitialize_POEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter_day4_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_day4_P.HILInitialize_POInitial;
        }
      }

      result = hil_write_pwm(helicopter_day4_DW.HILInitialize_Card,
        helicopter_day4_P.HILInitialize_POChannels, 8U,
        &helicopter_day4_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_day4_M, _rt_error_message);
        return;
      }
    }

    if (helicopter_day4_P.HILInitialize_POReset) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter_day4_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_day4_P.HILInitialize_POWatchdog;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (helicopter_day4_DW.HILInitialize_Card,
         helicopter_day4_P.HILInitialize_POChannels, 8U,
         &helicopter_day4_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_day4_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

  /* S-Function Block: helicopter_day4/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader
      (helicopter_day4_DW.HILInitialize_Card,
       helicopter_day4_P.HILReadEncoderTimebase_SamplesI,
       helicopter_day4_P.HILReadEncoderTimebase_Channels, 3,
       &helicopter_day4_DW.HILReadEncoderTimebase_Task);
    if (result >= 0) {
      result = hil_task_set_buffer_overflow_mode
        (helicopter_day4_DW.HILReadEncoderTimebase_Task, (t_buffer_overflow_mode)
         (helicopter_day4_P.HILReadEncoderTimebase_Overflow - 1));
    }

    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_day4_M, _rt_error_message);
    }
  }

  /* Start for FromWorkspace: '<Root>/From Workspace' */
  {
    static real_T pTimeValues0[] = { 0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75,
      2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.25, 4.5, 4.75, 5.0,
      5.25, 5.5, 5.75, 6.0, 6.25, 6.5, 6.75, 7.0, 7.25, 7.5, 7.75, 8.0, 8.25,
      8.5, 8.75, 9.0, 9.25, 9.5, 9.75, 10.0, 10.25, 10.5, 10.75, 11.0, 11.25,
      11.5, 11.75, 12.0, 12.25, 12.5, 12.75, 13.0, 13.25, 13.5, 13.75, 14.0,
      14.25, 14.5, 14.75, 15.0, 15.25, 15.5, 15.75, 16.0, 16.25, 16.5, 16.75,
      17.0, 17.25, 17.5, 17.75, 18.0, 18.25, 18.5, 18.75, 19.0, 19.25, 19.5,
      19.75, 20.0 } ;

    static real_T pDataValues0[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.5235987755982987,
      0.52359877559829859, 0.52359877559829882, 0.51503833387636055,
      0.4454932443953078, 0.39707349853021634, 0.23889196941789659,
      0.021964528241068815, -0.068376683212377665, -0.16283213782372136,
      -0.21969234786067246, -0.2545990423792619, -0.28794488871669249,
      -0.31299058779461719, -0.32901402003369029, -0.33726294648380817,
      -0.33747266152885191, -0.32346851375213481, -0.30838163006576247,
      -0.3415771589590314, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
    } ;

    helicopter_day4_DW.FromWorkspace_PWORK.TimePtr = (void *) pTimeValues0;
    helicopter_day4_DW.FromWorkspace_PWORK.DataPtr = (void *) pDataValues0;
    helicopter_day4_DW.FromWorkspace_IWORK.PrevIndex = 0;
  }

  /* Start for FromWorkspace: '<Root>/From Workspace2' */
  {
    static real_T pTimeValues0[] = { 0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75,
      2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.25, 4.5, 4.75, 5.0,
      5.25, 5.5, 5.75, 6.0, 6.25, 6.5, 6.75, 7.0, 7.25, 7.5, 7.75, 8.0, 8.25,
      8.5, 8.75, 9.0, 9.25, 9.5, 9.75, 10.0, 10.25, 10.5, 10.75, 11.0, 11.25,
      11.5, 11.75, 12.0, 12.25, 12.5, 12.75, 13.0, 13.25, 13.5, 13.75, 14.0,
      14.25, 14.5, 14.75, 15.0, 15.25, 15.5, 15.75, 16.0, 16.25, 16.5, 16.75,
      17.0, 17.25, 17.5, 17.75, 18.0, 18.25, 18.5, 18.75, 19.0, 19.25, 19.5,
      19.75, 20.0 } ;

    static real_T pDataValues0[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.36243201513662454,
      0.36561873994636229, 0.36537648286454055, 0.36083639313789023,
      0.35954366033789786, 0.36225695466357233, 0.3644717944080238,
      0.36624080144303667, 0.36752520151021356, 0.36818097273514516,
      -0.13354283717725793, -0.097896255279064384, -0.075578692455125482,
      -0.059387112838318656, -0.047476799137725678, -0.03878540005868799,
      -0.032615867867974324, -0.028487908796085266, -0.0260910326461467,
      -0.025261057672270874, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0 } ;

    helicopter_day4_DW.FromWorkspace2_PWORK.TimePtr = (void *) pTimeValues0;
    helicopter_day4_DW.FromWorkspace2_PWORK.DataPtr = (void *) pDataValues0;
    helicopter_day4_DW.FromWorkspace2_IWORK.PrevIndex = 0;
  }

  /* Start for FromWorkspace: '<Root>/From Workspace1' */
  {
    static real_T pTimeValues0[] = { 0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75,
      2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.25, 4.5, 4.75, 5.0,
      5.25, 5.5, 5.75, 6.0, 6.25, 6.5, 6.75, 7.0, 7.25, 7.5, 7.75, 8.0, 8.25,
      8.5, 8.75, 9.0, 9.25, 9.5, 9.75, 10.0, 10.25, 10.5, 10.75, 11.0, 11.25,
      11.5, 11.75, 12.0, 12.25, 12.5, 12.75, 13.0, 13.25, 13.5, 13.75, 14.0,
      14.25, 14.5, 14.75, 15.0, 15.25, 15.5, 15.75, 16.0, 16.25, 16.5, 16.75,
      17.0, 17.25, 17.5, 17.75, 18.0, 18.25, 18.5, 18.75, 19.0, 19.25, 19.5,
      19.75, 20.0 } ;

    static real_T pDataValues0[] = { 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.0785552278535877,
      3.0155178021173827, 2.9487298641534836, 2.8740658505118555,
      2.7881221713463007, 2.68846417879188, 2.5739414941744831,
      2.4443720101852966, 2.3010364448315723, 2.146952515953418,
      1.9856994056234898, 1.8209779342418018, 1.6561835885538803,
      1.4941819407414754, 1.3373368401180588, 1.1875610864517445,
      1.046358470125643, 0.91486362528498844, 0.79387125507717649,
      0.68381199511499791, 0.58481108026604911, 0.49711377954944519,
      0.41850530498168342, 0.34647519590261849, 0.27893191895109848,
      0.21433420177954687, 0.15161933364737681, 0.090084567625087347,
      0.029278352089254112, -0.031083438799717186, -0.091176749099292353,
      -0.15110916920620757, -0.21094582547948987, -0.27072581081905484,
      -0.330472426691205, -0.39019947910664809, -0.44991510598360646,
      -0.50962408271388582, -0.56932920050820934, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, -0.25214970294482131, -0.25214970294482147,
      -0.26715175185559487, -0.29865605456651406, -0.34377471666221693,
      -0.39863197021768254, -0.45809073846958731, -0.51827793595674621,
      -0.5733422614148993, -0.61633571551261856, -0.64501244131971336,
      -0.65888588552675187, -0.659177382751686, -0.64800659124962157,
      -0.62738040249366522, -0.59910301466525639, -0.56481046530440338,
      -0.52597937936261985, -0.48396948083124464, -0.44023703984871621,
      -0.39600365939579524, -0.35078920286641579, -0.314433898271048,
      -0.28812043631625978, -0.27017310780608156, -0.2583908686862092,
      -0.25085947252867874, -0.2461390640891564, -0.2432248621433343,
      -0.2414471635558845, -0.24037324119830072, -0.23972968042766224,
      -0.23934662509312893, -0.23911994135825995, -0.2389864634886005,
      -0.23890820966177265, -0.23886250750783419, -0.23883590692111722,
      -0.23882047117729474, -0.238811538536572, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, -8.0895307685418834E-17, 0.10602875207070717,
      0.222660379336433, 0.318881471828275, 0.38771011687179469,
      0.42023186532097051, 0.42538012495171862, 0.38917362199442096,
      0.30386131336478428, 0.20267614569744385, 0.098052205065037867,
      0.0020601910562787762, -0.078950887952067866, -0.14577802450692917,
      -0.19985377738053187, -0.24236664176206102, -0.27444328494362752,
      -0.29690991826455926, -0.30908419043037527, -0.31262463928670042,
      -0.31955851029938565, -0.25694540794551618, -0.18597349937464974,
      -0.12684486340866472, -0.083272366188699862, -0.053229031626448722,
      -0.033362044017012121, -0.02059646635171259, -0.012564094671748207,
      -0.00759007306752997, -0.0045484417360790886, -0.0027072888067592787,
      -0.0016021140622710774, -0.00094337060445736645, -0.0005530681610660922,
      -0.00032300536932436191, -0.00018800278753427615, -0.00010909394206697861,
      -6.31324930445177E-5, -3.6444824873474456E-5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.4241150082828285, 0.46652650906290516,
      0.3848843699673673, 0.27531458017407823, 0.13008699379670441,
      0.020593038522991797, -0.144826011829191, -0.34124923451854583,
      -0.40474067066936237, -0.4184957625296255, -0.38396805603503653,
      -0.32404431603338646, -0.26730854621944539, -0.21630301149440936,
      -0.17005145752611669, -0.12830657272626572, -0.089866533283726707,
      -0.048697088663263277, -0.014161795425300654, -0.027735484050741208,
      0.25045240941547775, 0.28388763428346575, 0.23651454386394066,
      0.17428998887986005, 0.12017333824900411, 0.0794679504377472,
      0.051062310661198068, 0.032129486719857374, 0.019896086416872589,
      0.012166525325803444, 0.0073646117172796663, 0.00442069897795206,
      0.0026349738312545258, 0.001561209773565094, 0.00092025116696701657,
      0.00054001032716043064, 0.00031563538186864281, 0.00018384579608965812,
      0.0001067506726834734, 6.1812386634298169E-5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0046308854963209179, 0.019128166101785797,
      0.042266048643066531, 0.069998710838345163, 0.09938112193530535,
      0.12859236657346362, 0.15663414666548919, 0.18289439183408704,
      0.20703480512634737, 0.22890428548874886, 0.24847182041054161,
      0.245714456456977, 0.23020531505725395, 0.20804810426093615,
      0.18317008066732238, 0.15802227037520791, 0.13405536497089859,
      0.11204969619858589, 0.092344563984518707, 0.074995855502289183,
      0.059882405546679757, 0.047814501353222946, 0.038178462615281676,
      0.030484259318388138, 0.024340598835640576, 0.019435032173256768,
      0.015518068222400748, 0.012390488564956748, 0.009893218041594494,
      0.0078992361849788816, 0.0063071183493457255, 0.0050358782005667669,
      0.004020849377325551, 0.0032103969553580638, 0.0025632915270847414,
      0.0020466123919062108, 0.0016340732497157507, 0.0013046852687249749,
      0.0010416895501421063, 0.0008317047082434725, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.057989122421859891, 0.092551530165122492,
      0.11093064878111442, 0.11752964438784053, 0.11684497855263294,
      0.11216712036810253, 0.10504098067439105, 0.096561653169042277,
      0.087477921449605658, 0.078270139687170975, -0.011029455814258418,
      -0.062036565598891952, -0.0886288431852717, -0.099512094374454518,
      -0.10059124116845873, -0.095867621617236928, -0.088022675089251282,
      -0.078820528856267974, -0.069394833928917918, -0.060453799822437107,
      -0.048271616773828414, -0.038544154951765004, -0.030776813187574283,
      -0.024574641930989644, -0.019622266649536195, -0.015667855803424207,
      -0.012510318629775672, -0.0099890820934495049, -0.0079759274264628241,
      -0.0063684713425329045, -0.00508496059511647, -0.0040601152929650008,
      -0.0032418096878695278, -0.0025884217130938887, -0.00206671654071369,
      -0.0016501565687618374, -0.0013175519239621626, -0.0010519828743319596,
      -0.00083993936759532955, -0.00067063394857985292, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
    } ;

    helicopter_day4_DW.FromWorkspace1_PWORK.TimePtr = (void *) pTimeValues0;
    helicopter_day4_DW.FromWorkspace1_PWORK.DataPtr = (void *) pDataValues0;
    helicopter_day4_DW.FromWorkspace1_IWORK.PrevIndex = 0;
  }

  /* Start for ToFile: '<Root>/To File' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "lab_day4_4.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helicopter_day4_M,
                        "Error creating .mat file lab_day4_4.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp, 14 + 1, 0, "data")) {
      rtmSetErrorStatus(helicopter_day4_M,
                        "Error writing mat file header to file lab_day4_4.mat");
      return;
    }

    helicopter_day4_DW.ToFile_IWORK.Count = 0;
    helicopter_day4_DW.ToFile_IWORK.Decimation = -1;
    helicopter_day4_DW.ToFile_PWORK.FilePtr = fp;
  }

  /* Start for If: '<S3>/If' */
  helicopter_day4_DW.If_ActiveSubsystem = -1;

  /* InitializeConditions for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  helicopter_day4_X.TravelTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  helicopter_day4_X.PitchTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  helicopter_day4_X.ElevationTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S3>/Integrator' */
  helicopter_day4_X.Integrator_CSTATE = helicopter_day4_P.Integrator_IC;

  /* InitializeConditions for Derivative: '<S4>/Derivative' */
  helicopter_day4_DW.TimeStampA = (rtInf);
  helicopter_day4_DW.TimeStampB = (rtInf);
}

/* Model terminate function */
void helicopter_day4_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopter_day4/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(helicopter_day4_DW.HILInitialize_Card);
    hil_monitor_stop_all(helicopter_day4_DW.HILInitialize_Card);
    is_switching = false;
    if ((helicopter_day4_P.HILInitialize_AOTerminate && !is_switching) ||
        (helicopter_day4_P.HILInitialize_AOExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter_day4_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter_day4_P.HILInitialize_AOFinal;
        }
      }

      num_final_analog_outputs = 8U;
    } else {
      num_final_analog_outputs = 0;
    }

    if ((helicopter_day4_P.HILInitialize_POTerminate && !is_switching) ||
        (helicopter_day4_P.HILInitialize_POExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter_day4_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_day4_P.HILInitialize_POFinal;
        }
      }

      num_final_pwm_outputs = 8U;
    } else {
      num_final_pwm_outputs = 0;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_pwm_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(helicopter_day4_DW.HILInitialize_Card
                         , helicopter_day4_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , helicopter_day4_P.HILInitialize_POChannels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &helicopter_day4_DW.HILInitialize_AOVoltages[0]
                         , &helicopter_day4_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(helicopter_day4_DW.HILInitialize_Card,
            helicopter_day4_P.HILInitialize_AOChannels, num_final_analog_outputs,
            &helicopter_day4_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(helicopter_day4_DW.HILInitialize_Card,
            helicopter_day4_P.HILInitialize_POChannels, num_final_pwm_outputs,
            &helicopter_day4_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter_day4_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(helicopter_day4_DW.HILInitialize_Card);
    hil_monitor_delete_all(helicopter_day4_DW.HILInitialize_Card);
    hil_close(helicopter_day4_DW.HILInitialize_Card);
    helicopter_day4_DW.HILInitialize_Card = NULL;
  }

  /* Terminate for ToFile: '<Root>/To File' */
  {
    FILE *fp = (FILE *) helicopter_day4_DW.ToFile_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "lab_day4_4.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_day4_M,
                          "Error closing MAT-file lab_day4_4.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helicopter_day4_M,
                          "Error reopening MAT-file lab_day4_4.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 14 + 1,
           helicopter_day4_DW.ToFile_IWORK.Count, "data")) {
        rtmSetErrorStatus(helicopter_day4_M,
                          "Error writing header for data to MAT-file lab_day4_4.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_day4_M,
                          "Error closing MAT-file lab_day4_4.mat");
        return;
      }

      helicopter_day4_DW.ToFile_PWORK.FilePtr = (NULL);
    }
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  helicopter_day4_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  helicopter_day4_update();
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  helicopter_day4_initialize();
}

void MdlTerminate(void)
{
  helicopter_day4_terminate();
}

/* Registration function */
RT_MODEL_helicopter_day4_T *helicopter_day4(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  helicopter_day4_P.Integrator_UpperSat = rtInf;
  helicopter_day4_P.Integrator_LowerSat = rtMinusInf;

  /* initialize real-time model */
  (void) memset((void *)helicopter_day4_M, 0,
                sizeof(RT_MODEL_helicopter_day4_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&helicopter_day4_M->solverInfo,
                          &helicopter_day4_M->Timing.simTimeStep);
    rtsiSetTPtr(&helicopter_day4_M->solverInfo, &rtmGetTPtr(helicopter_day4_M));
    rtsiSetStepSizePtr(&helicopter_day4_M->solverInfo,
                       &helicopter_day4_M->Timing.stepSize0);
    rtsiSetdXPtr(&helicopter_day4_M->solverInfo, &helicopter_day4_M->derivs);
    rtsiSetContStatesPtr(&helicopter_day4_M->solverInfo, (real_T **)
                         &helicopter_day4_M->contStates);
    rtsiSetNumContStatesPtr(&helicopter_day4_M->solverInfo,
      &helicopter_day4_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&helicopter_day4_M->solverInfo,
      &helicopter_day4_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&helicopter_day4_M->solverInfo,
      &helicopter_day4_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&helicopter_day4_M->solverInfo,
      &helicopter_day4_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&helicopter_day4_M->solverInfo, (&rtmGetErrorStatus
      (helicopter_day4_M)));
    rtsiSetRTModelPtr(&helicopter_day4_M->solverInfo, helicopter_day4_M);
  }

  rtsiSetSimTimeStep(&helicopter_day4_M->solverInfo, MAJOR_TIME_STEP);
  helicopter_day4_M->intgData.f[0] = helicopter_day4_M->odeF[0];
  helicopter_day4_M->contStates = ((real_T *) &helicopter_day4_X);
  rtsiSetSolverData(&helicopter_day4_M->solverInfo, (void *)
                    &helicopter_day4_M->intgData);
  rtsiSetSolverName(&helicopter_day4_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = helicopter_day4_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    helicopter_day4_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    helicopter_day4_M->Timing.sampleTimes =
      (&helicopter_day4_M->Timing.sampleTimesArray[0]);
    helicopter_day4_M->Timing.offsetTimes =
      (&helicopter_day4_M->Timing.offsetTimesArray[0]);

    /* task periods */
    helicopter_day4_M->Timing.sampleTimes[0] = (0.0);
    helicopter_day4_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    helicopter_day4_M->Timing.offsetTimes[0] = (0.0);
    helicopter_day4_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(helicopter_day4_M, &helicopter_day4_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = helicopter_day4_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    helicopter_day4_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(helicopter_day4_M, -1);
  helicopter_day4_M->Timing.stepSize0 = 0.002;
  helicopter_day4_M->Timing.stepSize1 = 0.002;

  /* External mode info */
  helicopter_day4_M->Sizes.checksums[0] = (3577564809U);
  helicopter_day4_M->Sizes.checksums[1] = (3672591576U);
  helicopter_day4_M->Sizes.checksums[2] = (337917645U);
  helicopter_day4_M->Sizes.checksums[3] = (801358268U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[2];
    helicopter_day4_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = (sysRanDType *)
      &helicopter_day4_DW.IfActionSubsystem_SubsysRanBC;
    rteiSetModelMappingInfoPtr(helicopter_day4_M->extModeInfo,
      &helicopter_day4_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(helicopter_day4_M->extModeInfo,
                        helicopter_day4_M->Sizes.checksums);
    rteiSetTPtr(helicopter_day4_M->extModeInfo, rtmGetTPtr(helicopter_day4_M));
  }

  helicopter_day4_M->solverInfoPtr = (&helicopter_day4_M->solverInfo);
  helicopter_day4_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&helicopter_day4_M->solverInfo, 0.002);
  rtsiSetSolverMode(&helicopter_day4_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  helicopter_day4_M->blockIO = ((void *) &helicopter_day4_B);

  {
    int32_T i;
    for (i = 0; i < 6; i++) {
      helicopter_day4_B.FromWorkspace1[i] = 0.0;
    }

    for (i = 0; i < 6; i++) {
      helicopter_day4_B.Gain1[i] = 0.0;
    }

    helicopter_day4_B.FromWorkspace = 0.0;
    helicopter_day4_B.FromWorkspace2 = 0.0;
    helicopter_day4_B.TravelCounttorad = 0.0;
    helicopter_day4_B.Gain = 0.0;
    helicopter_day4_B.Gain_d = 0.0;
    helicopter_day4_B.PitchCounttorad = 0.0;
    helicopter_day4_B.Gain_i = 0.0;
    helicopter_day4_B.Gain_b = 0.0;
    helicopter_day4_B.ElevationCounttorad = 0.0;
    helicopter_day4_B.Gain_e = 0.0;
    helicopter_day4_B.Sum = 0.0;
    helicopter_day4_B.Gain_dg = 0.0;
    helicopter_day4_B.Gain_l = 0.0;
    helicopter_day4_B.BackmotorSaturation = 0.0;
    helicopter_day4_B.FrontmotorSaturation = 0.0;
    helicopter_day4_B.In1 = 0.0;
  }

  /* parameters */
  helicopter_day4_M->defaultParam = ((real_T *)&helicopter_day4_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &helicopter_day4_X;
    helicopter_day4_M->contStates = (x);
    (void) memset((void *)&helicopter_day4_X, 0,
                  sizeof(X_helicopter_day4_T));
  }

  /* states (dwork) */
  helicopter_day4_M->dwork = ((void *) &helicopter_day4_DW);
  (void) memset((void *)&helicopter_day4_DW, 0,
                sizeof(DW_helicopter_day4_T));

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_day4_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_day4_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_day4_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_day4_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_day4_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_day4_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_day4_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_day4_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  helicopter_day4_DW.TimeStampA = 0.0;
  helicopter_day4_DW.LastUAtTimeA = 0.0;
  helicopter_day4_DW.TimeStampB = 0.0;
  helicopter_day4_DW.LastUAtTimeB = 0.0;
  helicopter_day4_DW.HILWriteAnalog_Buffer[0] = 0.0;
  helicopter_day4_DW.HILWriteAnalog_Buffer[1] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    helicopter_day4_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 16;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  helicopter_day4_M->Sizes.numContStates = (4);/* Number of continuous states */
  helicopter_day4_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  helicopter_day4_M->Sizes.numY = (0); /* Number of model outputs */
  helicopter_day4_M->Sizes.numU = (0); /* Number of model inputs */
  helicopter_day4_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  helicopter_day4_M->Sizes.numSampTimes = (2);/* Number of sample times */
  helicopter_day4_M->Sizes.numBlocks = (65);/* Number of blocks */
  helicopter_day4_M->Sizes.numBlockIO = (18);/* Number of block outputs */
  helicopter_day4_M->Sizes.numBlockPrms = (156);/* Sum of parameter "widths" */
  return helicopter_day4_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
