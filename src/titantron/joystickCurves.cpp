#include "main.h"

double leftCurveScale = 0.4;
double rightCurveScale = 2.0;

double opcontrolLeftCurve(double stickInput) {
  if (leftCurveScale != 0) {
    return tan((M_PI/4)*pow(fabs(stickInput)/127,leftCurveScale))*stickInput;
  }
  return stickInput;
}

double opcontrolRightCurve(double stickInput) {
  if (rightCurveScale != 0) {
    return tan((M_PI/4)*pow(fabs(stickInput)/127,rightCurveScale))*stickInput;
  }
  return stickInput;
}