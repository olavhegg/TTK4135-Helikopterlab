/*
 * helicopter_day3.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "helicopter_day3".
 *
 * Model version              : 11.10
 * Simulink Coder version : 9.4 (R2020b) 29-Jul-2020
 * C source code generated on : Wed Feb 16 11:55:33 2022
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "helicopter_day3.h"
#include "helicopter_day3_private.h"
#include "helicopter_day3_dt.h"

/* Block signals (default storage) */
B_helicopter_day3_T helicopter_day3_B;

/* Continuous states */
X_helicopter_day3_T helicopter_day3_X;

/* Block states (default storage) */
DW_helicopter_day3_T helicopter_day3_DW;

/* Real-time model */
static RT_MODEL_helicopter_day3_T helicopter_day3_M_;
RT_MODEL_helicopter_day3_T *const helicopter_day3_M = &helicopter_day3_M_;

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
  helicopter_day3_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void helicopter_day3_output(void)
{
  /* local block i/o variables */
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  real_T rtb_HILReadEncoderTimebase_o3;
  real_T rtb_TmpSignalConversionAtToFile[11];
  real_T lastTime;
  real_T rtb_Backgain;
  real_T rtb_Clock;
  real_T rtb_Derivative;
  real_T *lastU;
  int32_T i;
  int8_T rtAction;
  if (rtmIsMajorTimeStep(helicopter_day3_M)) {
    /* set solver stop time */
    if (!(helicopter_day3_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&helicopter_day3_M->solverInfo,
                            ((helicopter_day3_M->Timing.clockTickH0 + 1) *
        helicopter_day3_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&helicopter_day3_M->solverInfo,
                            ((helicopter_day3_M->Timing.clockTick0 + 1) *
        helicopter_day3_M->Timing.stepSize0 +
        helicopter_day3_M->Timing.clockTickH0 *
        helicopter_day3_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(helicopter_day3_M)) {
    helicopter_day3_M->Timing.t[0] = rtsiGetT(&helicopter_day3_M->solverInfo);
  }

  /* Reset subsysRan breadcrumbs */
  srClearBC(helicopter_day3_DW.IfActionSubsystem_SubsysRanBC);
  if (rtmIsMajorTimeStep(helicopter_day3_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

    /* S-Function Block: helicopter_day3/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder
        (helicopter_day3_DW.HILReadEncoderTimebase_Task, 1,
         &helicopter_day3_DW.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_day3_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 =
          helicopter_day3_DW.HILReadEncoderTimebase_Buffer[0];
        rtb_HILReadEncoderTimebase_o2 =
          helicopter_day3_DW.HILReadEncoderTimebase_Buffer[1];
        rtb_HILReadEncoderTimebase_o3 =
          helicopter_day3_DW.HILReadEncoderTimebase_Buffer[2];
      }
    }
  }

  /* FromWorkspace: '<Root>/From Workspace' */
  {
    real_T *pDataValues = (real_T *)
      helicopter_day3_DW.FromWorkspace_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *)
      helicopter_day3_DW.FromWorkspace_PWORK.TimePtr;
    int_T currTimeIndex = helicopter_day3_DW.FromWorkspace_IWORK.PrevIndex;
    real_T t = helicopter_day3_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[140]) {
      currTimeIndex = 139;
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

    helicopter_day3_DW.FromWorkspace_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          helicopter_day3_B.FromWorkspace = pDataValues[currTimeIndex];
        } else {
          helicopter_day3_B.FromWorkspace = pDataValues[currTimeIndex + 1];
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex= currTimeIndex;
        d1 = pDataValues[TimeIndex];
        d2 = pDataValues[TimeIndex + 1];
        helicopter_day3_B.FromWorkspace = (real_T) rtInterpolate(d1, d2, f1, f2);
        pDataValues += 141;
      }
    }
  }

  /* FromWorkspace: '<Root>/From Workspace1' */
  {
    real_T *pDataValues = (real_T *)
      helicopter_day3_DW.FromWorkspace1_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *)
      helicopter_day3_DW.FromWorkspace1_PWORK.TimePtr;
    int_T currTimeIndex = helicopter_day3_DW.FromWorkspace1_IWORK.PrevIndex;
    real_T t = helicopter_day3_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[140]) {
      currTimeIndex = 139;
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

    helicopter_day3_DW.FromWorkspace1_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 4; ++elIdx) {
              (&helicopter_day3_B.FromWorkspace1[0])[elIdx] =
                pDataValues[currTimeIndex];
              pDataValues += 141;
            }
          }
        } else {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 4; ++elIdx) {
              (&helicopter_day3_B.FromWorkspace1[0])[elIdx] =
                pDataValues[currTimeIndex + 1];
              pDataValues += 141;
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
          for (elIdx = 0; elIdx < 4; ++elIdx) {
            d1 = pDataValues[TimeIndex];
            d2 = pDataValues[TimeIndex + 1];
            (&helicopter_day3_B.FromWorkspace1[0])[elIdx] = (real_T)
              rtInterpolate(d1, d2, f1, f2);
            pDataValues += 141;
          }
        }
      }
    }
  }

  if (rtmIsMajorTimeStep(helicopter_day3_M)) {
    /* Gain: '<S4>/Travel: Count to rad' incorporates:
     *  Gain: '<S4>/Travel_gain'
     */
    helicopter_day3_B.TravelCounttorad = helicopter_day3_P.travel_gain *
      rtb_HILReadEncoderTimebase_o1 * helicopter_day3_P.TravelCounttorad_Gain;

    /* Gain: '<S12>/Gain' */
    helicopter_day3_B.Gain = helicopter_day3_P.Gain_Gain *
      helicopter_day3_B.TravelCounttorad;

    /* Gain: '<S4>/Pitch: Count to rad' */
    helicopter_day3_B.PitchCounttorad = helicopter_day3_P.PitchCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o2;

    /* Gain: '<S9>/Gain' */
    helicopter_day3_B.Gain_i = helicopter_day3_P.Gain_Gain_a *
      helicopter_day3_B.PitchCounttorad;
  }

  /* Gain: '<S13>/Gain' incorporates:
   *  TransferFcn: '<S4>/Travel: Transfer Fcn'
   */
  helicopter_day3_B.Gain_d = (helicopter_day3_P.TravelTransferFcn_C *
    helicopter_day3_X.TravelTransferFcn_CSTATE +
    helicopter_day3_P.TravelTransferFcn_D * helicopter_day3_B.TravelCounttorad) *
    helicopter_day3_P.Gain_Gain_l;

  /* Gain: '<S10>/Gain' incorporates:
   *  TransferFcn: '<S4>/Pitch: Transfer Fcn'
   */
  helicopter_day3_B.Gain_b = (helicopter_day3_P.PitchTransferFcn_C *
    helicopter_day3_X.PitchTransferFcn_CSTATE +
    helicopter_day3_P.PitchTransferFcn_D * helicopter_day3_B.PitchCounttorad) *
    helicopter_day3_P.Gain_Gain_ae;
  if (rtmIsMajorTimeStep(helicopter_day3_M)) {
    /* Gain: '<S4>/Elevation: Count to rad' incorporates:
     *  Gain: '<S4>/Elevation_gain'
     */
    helicopter_day3_B.ElevationCounttorad = helicopter_day3_P.elevation_gain *
      rtb_HILReadEncoderTimebase_o3 * helicopter_day3_P.ElevationCounttorad_Gain;

    /* Gain: '<S7>/Gain' */
    helicopter_day3_B.Gain_e = helicopter_day3_P.Gain_Gain_lv *
      helicopter_day3_B.ElevationCounttorad;

    /* Sum: '<Root>/Sum' incorporates:
     *  Constant: '<Root>/elavation_offset [deg]'
     */
    helicopter_day3_B.Sum = helicopter_day3_B.Gain_e +
      helicopter_day3_P.elavation_offsetdeg_Value;
  }

  /* Gain: '<S8>/Gain' incorporates:
   *  TransferFcn: '<S4>/Elevation: Transfer Fcn'
   */
  helicopter_day3_B.Gain_dg = (helicopter_day3_P.ElevationTransferFcn_C *
    helicopter_day3_X.ElevationTransferFcn_CSTATE +
    helicopter_day3_P.ElevationTransferFcn_D *
    helicopter_day3_B.ElevationCounttorad) * helicopter_day3_P.Gain_Gain_n;

  /* Gain: '<S2>/Gain1' */
  helicopter_day3_B.Gain1[0] = helicopter_day3_P.Gain1_Gain *
    helicopter_day3_B.Gain;
  helicopter_day3_B.Gain1[1] = helicopter_day3_P.Gain1_Gain *
    helicopter_day3_B.Gain_d;
  helicopter_day3_B.Gain1[2] = helicopter_day3_P.Gain1_Gain *
    helicopter_day3_B.Gain_i;
  helicopter_day3_B.Gain1[3] = helicopter_day3_P.Gain1_Gain *
    helicopter_day3_B.Gain_b;
  helicopter_day3_B.Gain1[4] = helicopter_day3_P.Gain1_Gain *
    helicopter_day3_B.Sum;
  helicopter_day3_B.Gain1[5] = helicopter_day3_P.Gain1_Gain *
    helicopter_day3_B.Gain_dg;
  if (rtmIsMajorTimeStep(helicopter_day3_M)) {
    /* SignalConversion generated from: '<Root>/To File' */
    rtb_TmpSignalConversionAtToFile[0] = helicopter_day3_B.FromWorkspace;
    rtb_TmpSignalConversionAtToFile[1] = helicopter_day3_B.FromWorkspace1[0];
    rtb_TmpSignalConversionAtToFile[2] = helicopter_day3_B.FromWorkspace1[1];
    rtb_TmpSignalConversionAtToFile[3] = helicopter_day3_B.FromWorkspace1[2];
    rtb_TmpSignalConversionAtToFile[4] = helicopter_day3_B.FromWorkspace1[3];
    for (i = 0; i < 6; i++) {
      rtb_TmpSignalConversionAtToFile[i + 5] = helicopter_day3_B.Gain1[i];
    }

    /* End of SignalConversion generated from: '<Root>/To File' */

    /* ToFile: '<Root>/To File' */
    {
      if (!(++helicopter_day3_DW.ToFile_IWORK.Decimation % 1) &&
          (helicopter_day3_DW.ToFile_IWORK.Count * (11 + 1)) + 1 < 100000000 ) {
        FILE *fp = (FILE *) helicopter_day3_DW.ToFile_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[11 + 1];
          helicopter_day3_DW.ToFile_IWORK.Decimation = 0;
          u[0] = helicopter_day3_M->Timing.t[1];
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
          if (fwrite(u, sizeof(real_T), 11 + 1, fp) != 11 + 1) {
            rtmSetErrorStatus(helicopter_day3_M,
                              "Error writing to MAT-file lab_day3_test.mat");
            return;
          }

          if (((++helicopter_day3_DW.ToFile_IWORK.Count) * (11 + 1))+1 >=
              100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file lab_day3_test.mat.\n");
          }
        }
      }
    }
  }

  /* Sum: '<Root>/Sum1' incorporates:
   *  Constant: '<Root>/Bias'
   *  Constant: '<Root>/Vd_bias'
   *  FromWorkspace: '<Root>/From Workspace1'
   *  Gain: '<Root>/Gain'
   *  Gain: '<S5>/K_pd'
   *  Gain: '<S5>/K_pp'
   *  Sum: '<Root>/Sum3'
   *  Sum: '<Root>/Sum4'
   *  Sum: '<Root>/Sum5'
   *  Sum: '<S5>/Sum2'
   *  Sum: '<S5>/Sum3'
   */
  rtb_Clock = (((helicopter_day3_B.FromWorkspace -
                 (((((helicopter_day3_P.Bias_Value + helicopter_day3_B.Gain1[0])
                     - helicopter_day3_B.FromWorkspace1[0]) *
                    helicopter_day3_P.K_lqr[0] + (helicopter_day3_B.Gain1[1] -
    helicopter_day3_B.FromWorkspace1[1]) * helicopter_day3_P.K_lqr[1]) +
                   (helicopter_day3_B.Gain1[2] -
                    helicopter_day3_B.FromWorkspace1[2]) *
                   helicopter_day3_P.K_lqr[2]) + (helicopter_day3_B.Gain1[3] -
    helicopter_day3_B.FromWorkspace1[3]) * helicopter_day3_P.K_lqr[3])) -
                helicopter_day3_B.Gain1[2]) * helicopter_day3_P.K_pp -
               helicopter_day3_P.K_pd * helicopter_day3_B.Gain1[3]) +
    helicopter_day3_P.Vd_ff;

  /* Integrator: '<S3>/Integrator' */
  /* Limited  Integrator  */
  if (helicopter_day3_X.Integrator_CSTATE >=
      helicopter_day3_P.Integrator_UpperSat) {
    helicopter_day3_X.Integrator_CSTATE = helicopter_day3_P.Integrator_UpperSat;
  } else {
    if (helicopter_day3_X.Integrator_CSTATE <=
        helicopter_day3_P.Integrator_LowerSat) {
      helicopter_day3_X.Integrator_CSTATE =
        helicopter_day3_P.Integrator_LowerSat;
    }
  }

  /* Sum: '<S3>/Sum' incorporates:
   *  Constant: '<Root>/elevation_ref'
   */
  rtb_Derivative = helicopter_day3_P.elevation_ref_Value -
    helicopter_day3_B.Gain1[4];

  /* Sum: '<Root>/Sum2' incorporates:
   *  Constant: '<Root>/Vs_bias'
   *  Gain: '<S3>/K_ed'
   *  Gain: '<S3>/K_ep'
   *  Integrator: '<S3>/Integrator'
   *  Sum: '<S3>/Sum1'
   */
  rtb_Backgain = ((helicopter_day3_P.K_ep * rtb_Derivative +
                   helicopter_day3_X.Integrator_CSTATE) - helicopter_day3_P.K_ed
                  * helicopter_day3_B.Gain1[5]) + helicopter_day3_P.Vs_ff;

  /* If: '<S3>/If' incorporates:
   *  Clock: '<S3>/Clock'
   *  Gain: '<S3>/K_ei'
   *  Inport: '<S6>/In1'
   */
  if (rtmIsMajorTimeStep(helicopter_day3_M)) {
    rtAction = (int8_T)!(helicopter_day3_M->Timing.t[0] >= 2.0);
    helicopter_day3_DW.If_ActiveSubsystem = rtAction;
  } else {
    rtAction = helicopter_day3_DW.If_ActiveSubsystem;
  }

  if (rtAction == 0) {
    /* Outputs for IfAction SubSystem: '<S3>/If Action Subsystem' incorporates:
     *  ActionPort: '<S6>/Action Port'
     */
    helicopter_day3_B.In1 = helicopter_day3_P.K_ei * rtb_Derivative;
    if (rtmIsMajorTimeStep(helicopter_day3_M)) {
      srUpdateBC(helicopter_day3_DW.IfActionSubsystem_SubsysRanBC);
    }

    /* End of Outputs for SubSystem: '<S3>/If Action Subsystem' */
  }

  /* End of If: '<S3>/If' */
  if (rtmIsMajorTimeStep(helicopter_day3_M)) {
  }

  /* Derivative: '<S4>/Derivative' */
  rtb_Derivative = helicopter_day3_M->Timing.t[0];
  if ((helicopter_day3_DW.TimeStampA >= rtb_Derivative) &&
      (helicopter_day3_DW.TimeStampB >= rtb_Derivative)) {
    rtb_Derivative = 0.0;
  } else {
    lastTime = helicopter_day3_DW.TimeStampA;
    lastU = &helicopter_day3_DW.LastUAtTimeA;
    if (helicopter_day3_DW.TimeStampA < helicopter_day3_DW.TimeStampB) {
      if (helicopter_day3_DW.TimeStampB < rtb_Derivative) {
        lastTime = helicopter_day3_DW.TimeStampB;
        lastU = &helicopter_day3_DW.LastUAtTimeB;
      }
    } else {
      if (helicopter_day3_DW.TimeStampA >= rtb_Derivative) {
        lastTime = helicopter_day3_DW.TimeStampB;
        lastU = &helicopter_day3_DW.LastUAtTimeB;
      }
    }

    rtb_Derivative = (helicopter_day3_B.PitchCounttorad - *lastU) /
      (rtb_Derivative - lastTime);
  }

  /* End of Derivative: '<S4>/Derivative' */

  /* Gain: '<S11>/Gain' */
  helicopter_day3_B.Gain_l = helicopter_day3_P.Gain_Gain_a1 * rtb_Derivative;
  if (rtmIsMajorTimeStep(helicopter_day3_M)) {
  }

  /* Gain: '<S1>/Back gain' incorporates:
   *  Sum: '<S1>/Subtract'
   */
  rtb_Derivative = (rtb_Backgain - rtb_Clock) * helicopter_day3_P.Backgain_Gain;

  /* Saturate: '<S4>/Back motor: Saturation' */
  if (rtb_Derivative > helicopter_day3_P.BackmotorSaturation_UpperSat) {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopter_day3_B.BackmotorSaturation =
      helicopter_day3_P.BackmotorSaturation_UpperSat;
  } else if (rtb_Derivative < helicopter_day3_P.BackmotorSaturation_LowerSat) {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopter_day3_B.BackmotorSaturation =
      helicopter_day3_P.BackmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopter_day3_B.BackmotorSaturation = rtb_Derivative;
  }

  /* End of Saturate: '<S4>/Back motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopter_day3_M)) {
  }

  /* Gain: '<S1>/Front gain' incorporates:
   *  Sum: '<S1>/Add'
   */
  rtb_Derivative = (rtb_Clock + rtb_Backgain) * helicopter_day3_P.Frontgain_Gain;

  /* Saturate: '<S4>/Front motor: Saturation' */
  if (rtb_Derivative > helicopter_day3_P.FrontmotorSaturation_UpperSat) {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopter_day3_B.FrontmotorSaturation =
      helicopter_day3_P.FrontmotorSaturation_UpperSat;
  } else if (rtb_Derivative < helicopter_day3_P.FrontmotorSaturation_LowerSat) {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopter_day3_B.FrontmotorSaturation =
      helicopter_day3_P.FrontmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopter_day3_B.FrontmotorSaturation = rtb_Derivative;
  }

  /* End of Saturate: '<S4>/Front motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopter_day3_M)) {
    /* S-Function (hil_write_analog_block): '<S4>/HIL Write Analog' */

    /* S-Function Block: helicopter_day3/Helicopter_interface/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      helicopter_day3_DW.HILWriteAnalog_Buffer[0] =
        helicopter_day3_B.FrontmotorSaturation;
      helicopter_day3_DW.HILWriteAnalog_Buffer[1] =
        helicopter_day3_B.BackmotorSaturation;
      result = hil_write_analog(helicopter_day3_DW.HILInitialize_Card,
        helicopter_day3_P.HILWriteAnalog_channels, 2,
        &helicopter_day3_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_day3_M, _rt_error_message);
      }
    }
  }
}

/* Model update function */
void helicopter_day3_update(void)
{
  real_T *lastU;

  /* Update for Derivative: '<S4>/Derivative' */
  if (helicopter_day3_DW.TimeStampA == (rtInf)) {
    helicopter_day3_DW.TimeStampA = helicopter_day3_M->Timing.t[0];
    lastU = &helicopter_day3_DW.LastUAtTimeA;
  } else if (helicopter_day3_DW.TimeStampB == (rtInf)) {
    helicopter_day3_DW.TimeStampB = helicopter_day3_M->Timing.t[0];
    lastU = &helicopter_day3_DW.LastUAtTimeB;
  } else if (helicopter_day3_DW.TimeStampA < helicopter_day3_DW.TimeStampB) {
    helicopter_day3_DW.TimeStampA = helicopter_day3_M->Timing.t[0];
    lastU = &helicopter_day3_DW.LastUAtTimeA;
  } else {
    helicopter_day3_DW.TimeStampB = helicopter_day3_M->Timing.t[0];
    lastU = &helicopter_day3_DW.LastUAtTimeB;
  }

  *lastU = helicopter_day3_B.PitchCounttorad;

  /* End of Update for Derivative: '<S4>/Derivative' */
  if (rtmIsMajorTimeStep(helicopter_day3_M)) {
    rt_ertODEUpdateContinuousStates(&helicopter_day3_M->solverInfo);
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
  if (!(++helicopter_day3_M->Timing.clockTick0)) {
    ++helicopter_day3_M->Timing.clockTickH0;
  }

  helicopter_day3_M->Timing.t[0] = rtsiGetSolverStopTime
    (&helicopter_day3_M->solverInfo);

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
    if (!(++helicopter_day3_M->Timing.clockTick1)) {
      ++helicopter_day3_M->Timing.clockTickH1;
    }

    helicopter_day3_M->Timing.t[1] = helicopter_day3_M->Timing.clockTick1 *
      helicopter_day3_M->Timing.stepSize1 +
      helicopter_day3_M->Timing.clockTickH1 *
      helicopter_day3_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void helicopter_day3_derivatives(void)
{
  XDot_helicopter_day3_T *_rtXdot;
  boolean_T lsat;
  boolean_T usat;
  _rtXdot = ((XDot_helicopter_day3_T *) helicopter_day3_M->derivs);

  /* Derivatives for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  _rtXdot->TravelTransferFcn_CSTATE = 0.0;
  _rtXdot->TravelTransferFcn_CSTATE += helicopter_day3_P.TravelTransferFcn_A *
    helicopter_day3_X.TravelTransferFcn_CSTATE;
  _rtXdot->TravelTransferFcn_CSTATE += helicopter_day3_B.TravelCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  _rtXdot->PitchTransferFcn_CSTATE = 0.0;
  _rtXdot->PitchTransferFcn_CSTATE += helicopter_day3_P.PitchTransferFcn_A *
    helicopter_day3_X.PitchTransferFcn_CSTATE;
  _rtXdot->PitchTransferFcn_CSTATE += helicopter_day3_B.PitchCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  _rtXdot->ElevationTransferFcn_CSTATE = 0.0;
  _rtXdot->ElevationTransferFcn_CSTATE +=
    helicopter_day3_P.ElevationTransferFcn_A *
    helicopter_day3_X.ElevationTransferFcn_CSTATE;
  _rtXdot->ElevationTransferFcn_CSTATE += helicopter_day3_B.ElevationCounttorad;

  /* Derivatives for Integrator: '<S3>/Integrator' */
  lsat = (helicopter_day3_X.Integrator_CSTATE <=
          helicopter_day3_P.Integrator_LowerSat);
  usat = (helicopter_day3_X.Integrator_CSTATE >=
          helicopter_day3_P.Integrator_UpperSat);
  if (((!lsat) && (!usat)) || (lsat && (helicopter_day3_B.In1 > 0.0)) || (usat &&
       (helicopter_day3_B.In1 < 0.0))) {
    _rtXdot->Integrator_CSTATE = helicopter_day3_B.In1;
  } else {
    /* in saturation */
    _rtXdot->Integrator_CSTATE = 0.0;
  }

  /* End of Derivatives for Integrator: '<S3>/Integrator' */
}

/* Model initialize function */
void helicopter_day3_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopter_day3/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &helicopter_day3_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_day3_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(helicopter_day3_DW.HILInitialize_Card,
      "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_day3_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(helicopter_day3_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_day3_M, _rt_error_message);
      return;
    }

    if ((helicopter_day3_P.HILInitialize_AIPStart && !is_switching) ||
        (helicopter_day3_P.HILInitialize_AIPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &helicopter_day3_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = (helicopter_day3_P.HILInitialize_AILow);
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &helicopter_day3_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = helicopter_day3_P.HILInitialize_AIHigh;
        }
      }

      result = hil_set_analog_input_ranges(helicopter_day3_DW.HILInitialize_Card,
        helicopter_day3_P.HILInitialize_AIChannels, 8U,
        &helicopter_day3_DW.HILInitialize_AIMinimums[0],
        &helicopter_day3_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_day3_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_day3_P.HILInitialize_AOPStart && !is_switching) ||
        (helicopter_day3_P.HILInitialize_AOPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &helicopter_day3_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = (helicopter_day3_P.HILInitialize_AOLow);
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &helicopter_day3_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = helicopter_day3_P.HILInitialize_AOHigh;
        }
      }

      result = hil_set_analog_output_ranges
        (helicopter_day3_DW.HILInitialize_Card,
         helicopter_day3_P.HILInitialize_AOChannels, 8U,
         &helicopter_day3_DW.HILInitialize_AOMinimums[0],
         &helicopter_day3_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_day3_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_day3_P.HILInitialize_AOStart && !is_switching) ||
        (helicopter_day3_P.HILInitialize_AOEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter_day3_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter_day3_P.HILInitialize_AOInitial;
        }
      }

      result = hil_write_analog(helicopter_day3_DW.HILInitialize_Card,
        helicopter_day3_P.HILInitialize_AOChannels, 8U,
        &helicopter_day3_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_day3_M, _rt_error_message);
        return;
      }
    }

    if (helicopter_day3_P.HILInitialize_AOReset) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter_day3_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter_day3_P.HILInitialize_AOWatchdog;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (helicopter_day3_DW.HILInitialize_Card,
         helicopter_day3_P.HILInitialize_AOChannels, 8U,
         &helicopter_day3_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_day3_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_day3_P.HILInitialize_EIPStart && !is_switching) ||
        (helicopter_day3_P.HILInitialize_EIPEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &helicopter_day3_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = helicopter_day3_P.HILInitialize_EIQuadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode
        (helicopter_day3_DW.HILInitialize_Card,
         helicopter_day3_P.HILInitialize_EIChannels, 8U,
         (t_encoder_quadrature_mode *)
         &helicopter_day3_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_day3_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_day3_P.HILInitialize_EIStart && !is_switching) ||
        (helicopter_day3_P.HILInitialize_EIEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &helicopter_day3_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = helicopter_day3_P.HILInitialize_EIInitial;
        }
      }

      result = hil_set_encoder_counts(helicopter_day3_DW.HILInitialize_Card,
        helicopter_day3_P.HILInitialize_EIChannels, 8U,
        &helicopter_day3_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_day3_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_day3_P.HILInitialize_POPStart && !is_switching) ||
        (helicopter_day3_P.HILInitialize_POPEnter && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &helicopter_day3_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = helicopter_day3_P.HILInitialize_POModes;
        }
      }

      result = hil_set_pwm_mode(helicopter_day3_DW.HILInitialize_Card,
        helicopter_day3_P.HILInitialize_POChannels, 8U, (t_pwm_mode *)
        &helicopter_day3_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_day3_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_POChannels =
          helicopter_day3_P.HILInitialize_POChannels;
        int32_T *dw_POModeValues =
          &helicopter_day3_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE ||
              dw_POModeValues[i1] == PWM_RAW_MODE) {
            helicopter_day3_DW.HILInitialize_POSortedChans[num_duty_cycle_modes]
              = (p_HILInitialize_POChannels[i1]);
            helicopter_day3_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]
              = helicopter_day3_P.HILInitialize_POFrequency;
            num_duty_cycle_modes++;
          } else {
            helicopter_day3_DW.HILInitialize_POSortedChans[7U -
              num_frequency_modes] = (p_HILInitialize_POChannels[i1]);
            helicopter_day3_DW.HILInitialize_POSortedFreqs[7U -
              num_frequency_modes] = helicopter_day3_P.HILInitialize_POFrequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(helicopter_day3_DW.HILInitialize_Card,
          &helicopter_day3_DW.HILInitialize_POSortedChans[0],
          num_duty_cycle_modes, &helicopter_day3_DW.HILInitialize_POSortedFreqs
          [0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter_day3_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(helicopter_day3_DW.HILInitialize_Card,
          &helicopter_day3_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &helicopter_day3_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter_day3_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &helicopter_day3_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = helicopter_day3_P.HILInitialize_POConfiguration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues =
          &helicopter_day3_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = helicopter_day3_P.HILInitialize_POAlignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &helicopter_day3_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = helicopter_day3_P.HILInitialize_POPolarity;
        }
      }

      result = hil_set_pwm_configuration(helicopter_day3_DW.HILInitialize_Card,
        helicopter_day3_P.HILInitialize_POChannels, 8U,
        (t_pwm_configuration *) &helicopter_day3_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &helicopter_day3_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &helicopter_day3_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_day3_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs =
          &helicopter_day3_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = helicopter_day3_P.HILInitialize_POLeading;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &helicopter_day3_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_day3_P.HILInitialize_POTrailing;
        }
      }

      result = hil_set_pwm_deadband(helicopter_day3_DW.HILInitialize_Card,
        helicopter_day3_P.HILInitialize_POChannels, 8U,
        &helicopter_day3_DW.HILInitialize_POSortedFreqs[0],
        &helicopter_day3_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_day3_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_day3_P.HILInitialize_POStart && !is_switching) ||
        (helicopter_day3_P.HILInitialize_POEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter_day3_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_day3_P.HILInitialize_POInitial;
        }
      }

      result = hil_write_pwm(helicopter_day3_DW.HILInitialize_Card,
        helicopter_day3_P.HILInitialize_POChannels, 8U,
        &helicopter_day3_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_day3_M, _rt_error_message);
        return;
      }
    }

    if (helicopter_day3_P.HILInitialize_POReset) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter_day3_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_day3_P.HILInitialize_POWatchdog;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (helicopter_day3_DW.HILInitialize_Card,
         helicopter_day3_P.HILInitialize_POChannels, 8U,
         &helicopter_day3_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_day3_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

  /* S-Function Block: helicopter_day3/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader
      (helicopter_day3_DW.HILInitialize_Card,
       helicopter_day3_P.HILReadEncoderTimebase_SamplesI,
       helicopter_day3_P.HILReadEncoderTimebase_Channels, 3,
       &helicopter_day3_DW.HILReadEncoderTimebase_Task);
    if (result >= 0) {
      result = hil_task_set_buffer_overflow_mode
        (helicopter_day3_DW.HILReadEncoderTimebase_Task, (t_buffer_overflow_mode)
         (helicopter_day3_P.HILReadEncoderTimebase_Overflow - 1));
    }

    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_day3_M, _rt_error_message);
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
      19.75, 20.0, 20.25, 20.5, 20.75, 21.0, 21.25, 21.5, 21.75, 22.0, 22.25,
      22.5, 22.75, 23.0, 23.25, 23.5, 23.75, 24.0, 24.25, 24.5, 24.75, 25.0,
      25.25, 25.5, 25.75, 26.0, 26.25, 26.5, 26.75, 27.0, 27.25, 27.5, 27.75,
      28.0, 28.25, 28.5, 28.75, 29.0, 29.25, 29.5, 29.75, 30.0, 30.25, 30.5,
      30.75, 31.0, 31.25, 31.5, 31.75, 32.0, 32.25, 32.5, 32.75, 33.0, 33.25,
      33.5, 33.75, 34.0, 34.25, 34.5, 34.75, 35.0 } ;

    static real_T pDataValues0[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.52359877559829882,
      0.52359877559829882, 0.52359877559829882, 0.52359877559829882,
      0.52359877559829882, 0.52359877559829882, 0.52359877559829882,
      0.52359877559829882, 0.52359877559829882, 0.52359877559829882,
      0.52359877559829859, 0.38860612255405957, 0.1095176648528754,
      -0.11003765122302378, -0.27691054144987043, -0.39790612927964514,
      -0.47963605880920746, -0.52359877533083565, -0.52359877559826973,
      -0.52359877559827184, -0.52359877559525614, -0.50343436003610353,
      -0.46496995789077566, -0.42077302987495752, -0.37347825123326978,
      -0.32522954464205189, -0.27772317715754113, -0.23225508106825171,
      -0.18977001050145492, -0.15091060285232188, -0.1160648435785408,
      -0.085410818067272742, -0.058957969232035223, -0.036584363680946308,
      -0.018069704886488513, -0.0031240223576550763, 0.0085878843482954936,
      0.017426054241604594, 0.023758751395600686, 0.027949299278970718,
      0.030346000156382225, 0.031274762577705673, 0.031034060568535859,
      0.029891860200525255, 0.028084169823040517, 0.02581489683630922,
      0.023256724323099109, 0.020552753337129137, 0.017818689715723535,
      0.015145386792202453, 0.012601586454356384, 0.010236729992818772,
      0.0080837366766109975, 0.0061616717250452258, 0.0044782462004481216,
      0.0030321093238400154, 0.001814908903673973, 0.00081310812015167322,
      9.5570254320387349E-6, -0.00061517496563823215, -0.0010816933613917445,
      -0.0014108831681862721, -0.0016232044667041645, -0.0017381581190205608,
      -0.0017739001468705107, -0.0017469835234231734, -0.00167220693100123,
      -0.0015625512950236953, -0.0014291864714510716, -0.0012815322239977389,
      -0.0011273594814287247, -0.00097291973612834148, -0.00082309227159338416,
      -0.00068154064236525258, -0.00055087144220966611, -0.0004327898633181837,
      -0.00032824785870921858, -0.00023758186733013886, -0.00016063804837007645,
      -9.688380460637358E-5, -4.55050645912225E-5, -5.4893533024680252E-6,
      2.4304874204128524E-5, 4.5091814591446955E-5, 5.8113724208608275E-5,
      6.4606854863757945E-5, 6.5776445203225009E-5, 6.27791295313429E-5,
      5.6710935087966874E-5, 4.8598784488373958E-5, 3.9393060344727893E-5,
      2.9958290771125995E-5, 2.1058387462469241E-5, 1.3332252023490199E-5,
      7.25543154012076E-6, 3.0850963383954877E-6, 7.9190416224506066E-7, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } ;

    helicopter_day3_DW.FromWorkspace_PWORK.TimePtr = (void *) pTimeValues0;
    helicopter_day3_DW.FromWorkspace_PWORK.DataPtr = (void *) pDataValues0;
    helicopter_day3_DW.FromWorkspace_IWORK.PrevIndex = 0;
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
      19.75, 20.0, 20.25, 20.5, 20.75, 21.0, 21.25, 21.5, 21.75, 22.0, 22.25,
      22.5, 22.75, 23.0, 23.25, 23.5, 23.75, 24.0, 24.25, 24.5, 24.75, 25.0,
      25.25, 25.5, 25.75, 26.0, 26.25, 26.5, 26.75, 27.0, 27.25, 27.5, 27.75,
      28.0, 28.25, 28.5, 28.75, 29.0, 29.25, 29.5, 29.75, 30.0, 30.25, 30.5,
      30.75, 31.0, 31.25, 31.5, 31.75, 32.0, 32.25, 32.5, 32.75, 33.0, 33.25,
      33.5, 33.75, 34.0, 34.25, 34.5, 34.75, 35.0 } ;

    static real_T pDataValues0[] = { 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1378421413624498, 3.1262155534584366,
      3.1033093000411074, 3.0666274152234911, 3.0144539224474727,
      2.9456562771799621, 2.8595077633652255, 2.7555515880456922,
      2.633505110579951, 2.4931956061304872, 2.3345185761717842, 2.1583782673227,
      1.9678000584956126, 1.7674109958636912, 1.5625809553194681,
      1.3586838043835454, 1.1605918372514115, 0.97235388546160062,
      0.79694979464566162, 0.63643262348644025, 0.49215933323197075,
      0.36485709430437568, 0.2546397947734575, 0.16109616201120017,
      0.083400574810361991, 0.020423656761308296, -0.029167441566965661,
      -0.0668229039358445, -0.094039063970890319, -0.11230155611132692,
      -0.12304153576614682, -0.12760344274134175, -0.12722271677438504,
      -0.12301190955779223, -0.11595372702569194, -0.10689965400717988,
      -0.096572947079424973, -0.085574921690896338, -0.074393600518875211,
      -0.063413927273471823, -0.052928880623821992, -0.043150944317362334,
      -0.034223500287188513, -0.026231810805988062, -0.019213342939206918,
      -0.013167263931041931, -0.00806299989912879, -0.0038478030699207444,
      -0.00045331552993235644, 0.00219884896084414, 0.004192458115494394,
      0.0056128839298334827, 0.0065441176520000359, 0.0070664922819843523,
      0.0072550250615871737, 0.0071782928315725142, 0.006897756147618464,
      0.0064674529763385537, 0.005933989059843844, 0.0053367591539994728,
      0.0047083409015082492, 0.0040750107661335667, 0.0034573389680228987,
      0.0028708275264058818, 0.0023265621892417996, 0.0018318551160659224,
      0.0013908606225143531, 0.0010051510696696591, 0.00067424408850216193,
      0.00039607579378730636, 0.00016741749658591277, -1.5764279839354214E-5,
      -0.00015800288825508648, -0.000264078817378658, -0.00033881524261691762,
      -0.00038691737158125185, -0.00041285075135006493, -0.00042075359439943652,
      -0.00041437825128763553, -0.00039705716682552028, -0.00037168896766201243,
      -0.00034074070911425589, -0.00030626273205991959, -0.00026991302305748852,
      -0.00023298841450232043, -0.00019646039107026653, -0.00016101367182365595,
      -0.00012708610399440767, -9.4908725840992217E-5, -6.45451237252004E-5,
      -3.5929413425652248E-5, -8.90230663231178E-6, 1.6755233388001709E-5,
      4.1291304253719639E-5, 6.4956082699385242E-5, 8.79795855093027E-5,
      0.00011055557870659457, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, -0.015002048930552628, -0.046506351607376289,
      -0.091625013679415321, -0.14672753927165028, -0.20869397111594962,
      -0.27519058106839356, -0.34459405523449849, -0.4158247013056201,
      -0.48818590987465332, -0.56123801779324178, -0.63470811986548,
      -0.70456123537542159, -0.76231283530141514, -0.80155625050084423,
      -0.81932016219071, -0.81558860372057784, -0.79236786860010644,
      -0.75295180710744813, -0.7016163632213207, -0.64206868469185518,
      -0.57709316102636055, -0.5092089556806515, -0.44086919811168934,
      -0.37417453105745618, -0.31078234878946415, -0.25190767218756893,
      -0.19836439332716888, -0.15062184950397528, -0.10886464017288866,
      -0.073049968572901108, -0.042959918616354523, -0.0182476278994118,
      0.0015229038705734711, 0.01684322886564386, 0.028232730129854864,
      0.03621629207379682, 0.041306827710084155, 0.043992101553807839,
      0.044725284688929806, 0.043918692981859069, 0.041940186595972942,
      0.039111745226336973, 0.035709776120369754, 0.031966757925949975,
      0.028073871466714483, 0.024184316033594631, 0.020417056128089379,
      0.016860787316660072, 0.013577950159558644, 0.010608657964084367,
      0.007974436618732, 0.0056817032579705188, 0.0037249348892740021,
      0.0020894985190175225, 0.00075413111855430614, -0.00030692891999211508,
      -0.0011221467358579083, -0.0017212126850504321, -0.0021338556659622927,
      -0.0023889196233890116, -0.0025136730098062041, -0.0025333205414557222,
      -0.0024706871924123426, -0.0023460457663429433, -0.0021770613487725105,
      -0.0019788282927614836, -0.0017639779740822985, -0.0015428382111596316,
      -0.0013236279246274015, -0.0011126731789519674, -0.00091463318895553989,
      -0.000732727105624324, -0.00056895443363380778, -0.00042430371646267375,
      -0.00029894570088696631, -0.00019240851587405309, -0.0001037335190740843,
      -3.161137219085859E-5, 2.5501372446283269E-5, 6.928433783933429E-5,
      0.00010147279665845606, 0.00012379303418930839, 0.00013791190821852646,
      0.00014539883600544196, 0.00014769843421508469, 0.00014611209373272937,
      0.00014178687698842771, 0.00013571027131680291, 0.00012870951261098517,
      0.00012145440846098015, 0.00011446284120221104, 0.00010810842717150988,
      0.00010263016007926775, 9.8144283461505747E-5, 9.4659113781761685E-5,
      9.209401123924596E-5, 9.0303972789222364E-5, 8.9110874012770638E-5, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1060287520658465,
      0.22266037931826521, 0.31888147179790782, 0.3894436062956641,
      0.43795507376078935, 0.46997264229059144, 0.490517248763667,
      0.50343100140566677, 0.51142138585366281, 0.516304398574161,
      0.519258621268189, 0.49369514264343961, 0.40816625110514637,
      0.27735747119022547, 0.12554854275641425, -0.026373229222867278,
      -0.16411528826322508, -0.27857766724412869, -0.36281931133923317,
      -0.42086025018555806, -0.459222185584521, -0.47977963637097037,
      -0.48299930533941843, -0.47137243442091581, -0.44803173387140732,
      -0.41610372863754352, -0.37842344537789063, -0.33742606591727209,
      -0.29512400741287392, -0.25312442028716897, -0.21266498089782354,
      -0.1746570325091501, -0.13973056781027837, -0.10827820590262444,
      -0.080496644968802988, -0.056424766708759011, -0.035977961696041172,
      -0.018978489954152966, -0.0051818583787351935, 0.0057006821003234842,
      0.013983327497774312, 0.01999034333603511, 0.024043818368713388,
      0.026454223036059044, 0.027513434671657455, 0.027489892282188677,
      0.026625554197897916, 0.025134349752043761, 0.0232018392502783,
      0.020985823200927456, 0.018617670405948306, 0.016204163751076583,
      0.013829691505578445, 0.011558639645953162, 0.0094378667860827159,
      0.007499167109644489, 0.0057616481709038547, 0.0042339693316548743,
      0.0029164029907067235, 0.0018026946365040653, 0.00088170928960662476,
      0.00013886124950246437, -0.00044266859008179615, -0.00088091799616996092,
      -0.0011943173271339314, -0.0014010355295558385, -0.0015184799946741379,
      -0.0015629313838014802, -0.0015492945841818484, -0.001490947574366408,
      -0.0013996710150631086, -0.0012856427218147504, -0.0011574826970159879,
      -0.0010223360234311585, -0.00088598257698102589, -0.00075296413493863845,
      -0.000626721010293263, -0.00050973178864655022, -0.00040365106669859596,
      -0.00030944127773180341, -0.00022749573340985485, -0.00015775091428127386,
      -9.9786809323210157E-5, -5.2914746229038023E-5, -1.6252681879658226E-5,
      1.1211648783038264E-5, 3.0568980086465025E-5, 4.2947128068515639E-5,
      4.9478688754378553E-5, 5.1276305251701793E-5, 4.9413727148062137E-5,
      4.4910571407541511E-5, 3.8718299543050172E-5, 3.1704462683745938E-5,
      2.4631848226985831E-5, 1.8129165096691935E-5, 1.265130811056725E-5,
      8.43236647984913E-6, 5.4485824244610015E-6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.42411500823623033, 0.46652650905878412,
      0.38488436996993586, 0.28224853799308736, 0.19404586987543027,
      0.12807027412330121, 0.082178425895457416, 0.051655010566202184,
      0.031961537790384638, 0.019532050878763845, 0.011816890777643089,
      -0.1022539145000062, -0.34211556616310351, -0.5232351196596956,
      -0.60723571393755349, -0.60768708778315184, -0.55096823602837552,
      -0.45784951594759, -0.33696657633617583, -0.23216375539794981,
      -0.15344774160747632, -0.082229803145518282, -0.012878675879460446,
      0.046507483675011771, 0.093362802193293709, 0.12771202093978062,
      0.15072113303101409, 0.16398951783674381, 0.16920823403007854,
      0.16799834848605211, 0.16183775754989915, 0.15203179355607258,
      0.13970585880539962, 0.12580944763063756, 0.11112624373092754,
      0.096287513044701484, 0.081787220052012055, 0.0679978869747164,
      0.0551865263021644, 0.043530161908758767, 0.03313058160374964,
      0.024028063347597613, 0.016213900121304213, 0.0096416186715499019,
      0.004236846546266923, -9.4169567648727041E-5, -0.0034573523396599069,
      -0.0059648177792124774, -0.0077300420072775843, -0.0088640641982496177,
      -0.0094726111843803709, -0.009654026616868221, -0.0094978889820745271,
      -0.0090842074392858789, -0.0084830914411616644, -0.0077547987050939245,
      -0.0069500757552161362, -0.0061107153570493181, -0.0052702653635452084,
      -0.004454833417178076, -0.0036839413869773139, -0.0029713921604611394,
      -0.0023261193587415913, -0.0017529976244021017, -0.0012535973234204733,
      -0.00082687280935904092, -0.00046977786006238237, -0.00017780555601930691,
      5.4547198286580811E-5, 0.00023338803928298584, 0.00036510623722626421,
      0.00045611317269403205, 0.00051264009944276628, 0.00054058669432651275,
      0.000545413785811331, 0.0005320737682775466, 0.00050497249863114355,
      0.00046795688661744862, 0.00042432288781753719, 0.00037683915585346849,
      0.00032778217729481423, 0.00027897927651755121, 0.00023185641981862096,
      0.0001874882523664358, 0.0001466482573987278, 0.00010985732262549377,
      7.7429325200849925E-5, 4.9512591928292605E-5, 2.6126242743100791E-5,
      7.1904659737928315E-6, -7.450312413519075E-6, -1.8012622969529041E-5,
      -2.476908744258406E-5, -2.8055347443175038E-5, -2.8290457827687655E-5,
      -2.6010732522315287E-5, -2.1911427944682834E-5, -1.6875766522722086E-5,
      -1.193513622182281E-5, -8.023730470860077E-6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } ;

    helicopter_day3_DW.FromWorkspace1_PWORK.TimePtr = (void *) pTimeValues0;
    helicopter_day3_DW.FromWorkspace1_PWORK.DataPtr = (void *) pDataValues0;
    helicopter_day3_DW.FromWorkspace1_IWORK.PrevIndex = 0;
  }

  /* Start for ToFile: '<Root>/To File' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "lab_day3_test.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helicopter_day3_M,
                        "Error creating .mat file lab_day3_test.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp, 11 + 1, 0, "data")) {
      rtmSetErrorStatus(helicopter_day3_M,
                        "Error writing mat file header to file lab_day3_test.mat");
      return;
    }

    helicopter_day3_DW.ToFile_IWORK.Count = 0;
    helicopter_day3_DW.ToFile_IWORK.Decimation = -1;
    helicopter_day3_DW.ToFile_PWORK.FilePtr = fp;
  }

  /* Start for If: '<S3>/If' */
  helicopter_day3_DW.If_ActiveSubsystem = -1;

  /* InitializeConditions for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  helicopter_day3_X.TravelTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  helicopter_day3_X.PitchTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  helicopter_day3_X.ElevationTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S3>/Integrator' */
  helicopter_day3_X.Integrator_CSTATE = helicopter_day3_P.Integrator_IC;

  /* InitializeConditions for Derivative: '<S4>/Derivative' */
  helicopter_day3_DW.TimeStampA = (rtInf);
  helicopter_day3_DW.TimeStampB = (rtInf);
}

/* Model terminate function */
void helicopter_day3_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopter_day3/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(helicopter_day3_DW.HILInitialize_Card);
    hil_monitor_stop_all(helicopter_day3_DW.HILInitialize_Card);
    is_switching = false;
    if ((helicopter_day3_P.HILInitialize_AOTerminate && !is_switching) ||
        (helicopter_day3_P.HILInitialize_AOExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter_day3_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter_day3_P.HILInitialize_AOFinal;
        }
      }

      num_final_analog_outputs = 8U;
    } else {
      num_final_analog_outputs = 0;
    }

    if ((helicopter_day3_P.HILInitialize_POTerminate && !is_switching) ||
        (helicopter_day3_P.HILInitialize_POExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter_day3_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_day3_P.HILInitialize_POFinal;
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
      result = hil_write(helicopter_day3_DW.HILInitialize_Card
                         , helicopter_day3_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , helicopter_day3_P.HILInitialize_POChannels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &helicopter_day3_DW.HILInitialize_AOVoltages[0]
                         , &helicopter_day3_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(helicopter_day3_DW.HILInitialize_Card,
            helicopter_day3_P.HILInitialize_AOChannels, num_final_analog_outputs,
            &helicopter_day3_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(helicopter_day3_DW.HILInitialize_Card,
            helicopter_day3_P.HILInitialize_POChannels, num_final_pwm_outputs,
            &helicopter_day3_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter_day3_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(helicopter_day3_DW.HILInitialize_Card);
    hil_monitor_delete_all(helicopter_day3_DW.HILInitialize_Card);
    hil_close(helicopter_day3_DW.HILInitialize_Card);
    helicopter_day3_DW.HILInitialize_Card = NULL;
  }

  /* Terminate for ToFile: '<Root>/To File' */
  {
    FILE *fp = (FILE *) helicopter_day3_DW.ToFile_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "lab_day3_test.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_day3_M,
                          "Error closing MAT-file lab_day3_test.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helicopter_day3_M,
                          "Error reopening MAT-file lab_day3_test.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 11 + 1,
           helicopter_day3_DW.ToFile_IWORK.Count, "data")) {
        rtmSetErrorStatus(helicopter_day3_M,
                          "Error writing header for data to MAT-file lab_day3_test.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_day3_M,
                          "Error closing MAT-file lab_day3_test.mat");
        return;
      }

      helicopter_day3_DW.ToFile_PWORK.FilePtr = (NULL);
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
  helicopter_day3_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  helicopter_day3_update();
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
  helicopter_day3_initialize();
}

void MdlTerminate(void)
{
  helicopter_day3_terminate();
}

/* Registration function */
RT_MODEL_helicopter_day3_T *helicopter_day3(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  helicopter_day3_P.Integrator_UpperSat = rtInf;
  helicopter_day3_P.Integrator_LowerSat = rtMinusInf;

  /* initialize real-time model */
  (void) memset((void *)helicopter_day3_M, 0,
                sizeof(RT_MODEL_helicopter_day3_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&helicopter_day3_M->solverInfo,
                          &helicopter_day3_M->Timing.simTimeStep);
    rtsiSetTPtr(&helicopter_day3_M->solverInfo, &rtmGetTPtr(helicopter_day3_M));
    rtsiSetStepSizePtr(&helicopter_day3_M->solverInfo,
                       &helicopter_day3_M->Timing.stepSize0);
    rtsiSetdXPtr(&helicopter_day3_M->solverInfo, &helicopter_day3_M->derivs);
    rtsiSetContStatesPtr(&helicopter_day3_M->solverInfo, (real_T **)
                         &helicopter_day3_M->contStates);
    rtsiSetNumContStatesPtr(&helicopter_day3_M->solverInfo,
      &helicopter_day3_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&helicopter_day3_M->solverInfo,
      &helicopter_day3_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&helicopter_day3_M->solverInfo,
      &helicopter_day3_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&helicopter_day3_M->solverInfo,
      &helicopter_day3_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&helicopter_day3_M->solverInfo, (&rtmGetErrorStatus
      (helicopter_day3_M)));
    rtsiSetRTModelPtr(&helicopter_day3_M->solverInfo, helicopter_day3_M);
  }

  rtsiSetSimTimeStep(&helicopter_day3_M->solverInfo, MAJOR_TIME_STEP);
  helicopter_day3_M->intgData.f[0] = helicopter_day3_M->odeF[0];
  helicopter_day3_M->contStates = ((real_T *) &helicopter_day3_X);
  rtsiSetSolverData(&helicopter_day3_M->solverInfo, (void *)
                    &helicopter_day3_M->intgData);
  rtsiSetSolverName(&helicopter_day3_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = helicopter_day3_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    helicopter_day3_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    helicopter_day3_M->Timing.sampleTimes =
      (&helicopter_day3_M->Timing.sampleTimesArray[0]);
    helicopter_day3_M->Timing.offsetTimes =
      (&helicopter_day3_M->Timing.offsetTimesArray[0]);

    /* task periods */
    helicopter_day3_M->Timing.sampleTimes[0] = (0.0);
    helicopter_day3_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    helicopter_day3_M->Timing.offsetTimes[0] = (0.0);
    helicopter_day3_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(helicopter_day3_M, &helicopter_day3_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = helicopter_day3_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    helicopter_day3_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(helicopter_day3_M, -1);
  helicopter_day3_M->Timing.stepSize0 = 0.002;
  helicopter_day3_M->Timing.stepSize1 = 0.002;

  /* External mode info */
  helicopter_day3_M->Sizes.checksums[0] = (3596188742U);
  helicopter_day3_M->Sizes.checksums[1] = (292467336U);
  helicopter_day3_M->Sizes.checksums[2] = (2701147771U);
  helicopter_day3_M->Sizes.checksums[3] = (909374236U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[2];
    helicopter_day3_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = (sysRanDType *)
      &helicopter_day3_DW.IfActionSubsystem_SubsysRanBC;
    rteiSetModelMappingInfoPtr(helicopter_day3_M->extModeInfo,
      &helicopter_day3_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(helicopter_day3_M->extModeInfo,
                        helicopter_day3_M->Sizes.checksums);
    rteiSetTPtr(helicopter_day3_M->extModeInfo, rtmGetTPtr(helicopter_day3_M));
  }

  helicopter_day3_M->solverInfoPtr = (&helicopter_day3_M->solverInfo);
  helicopter_day3_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&helicopter_day3_M->solverInfo, 0.002);
  rtsiSetSolverMode(&helicopter_day3_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  helicopter_day3_M->blockIO = ((void *) &helicopter_day3_B);

  {
    int32_T i;
    for (i = 0; i < 6; i++) {
      helicopter_day3_B.Gain1[i] = 0.0;
    }

    helicopter_day3_B.FromWorkspace = 0.0;
    helicopter_day3_B.FromWorkspace1[0] = 0.0;
    helicopter_day3_B.FromWorkspace1[1] = 0.0;
    helicopter_day3_B.FromWorkspace1[2] = 0.0;
    helicopter_day3_B.FromWorkspace1[3] = 0.0;
    helicopter_day3_B.TravelCounttorad = 0.0;
    helicopter_day3_B.Gain = 0.0;
    helicopter_day3_B.Gain_d = 0.0;
    helicopter_day3_B.PitchCounttorad = 0.0;
    helicopter_day3_B.Gain_i = 0.0;
    helicopter_day3_B.Gain_b = 0.0;
    helicopter_day3_B.ElevationCounttorad = 0.0;
    helicopter_day3_B.Gain_e = 0.0;
    helicopter_day3_B.Sum = 0.0;
    helicopter_day3_B.Gain_dg = 0.0;
    helicopter_day3_B.Gain_l = 0.0;
    helicopter_day3_B.BackmotorSaturation = 0.0;
    helicopter_day3_B.FrontmotorSaturation = 0.0;
    helicopter_day3_B.In1 = 0.0;
  }

  /* parameters */
  helicopter_day3_M->defaultParam = ((real_T *)&helicopter_day3_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &helicopter_day3_X;
    helicopter_day3_M->contStates = (x);
    (void) memset((void *)&helicopter_day3_X, 0,
                  sizeof(X_helicopter_day3_T));
  }

  /* states (dwork) */
  helicopter_day3_M->dwork = ((void *) &helicopter_day3_DW);
  (void) memset((void *)&helicopter_day3_DW, 0,
                sizeof(DW_helicopter_day3_T));

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_day3_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_day3_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_day3_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_day3_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_day3_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_day3_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_day3_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_day3_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  helicopter_day3_DW.TimeStampA = 0.0;
  helicopter_day3_DW.LastUAtTimeA = 0.0;
  helicopter_day3_DW.TimeStampB = 0.0;
  helicopter_day3_DW.LastUAtTimeB = 0.0;
  helicopter_day3_DW.HILWriteAnalog_Buffer[0] = 0.0;
  helicopter_day3_DW.HILWriteAnalog_Buffer[1] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    helicopter_day3_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 16;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  helicopter_day3_M->Sizes.numContStates = (4);/* Number of continuous states */
  helicopter_day3_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  helicopter_day3_M->Sizes.numY = (0); /* Number of model outputs */
  helicopter_day3_M->Sizes.numU = (0); /* Number of model inputs */
  helicopter_day3_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  helicopter_day3_M->Sizes.numSampTimes = (2);/* Number of sample times */
  helicopter_day3_M->Sizes.numBlocks = (65);/* Number of blocks */
  helicopter_day3_M->Sizes.numBlockIO = (17);/* Number of block outputs */
  helicopter_day3_M->Sizes.numBlockPrms = (149);/* Sum of parameter "widths" */
  return helicopter_day3_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
