#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define AG_CONST        1/1.6467602578655
#define FIXED(X)        ((long int)((X) * 32768.0))
#define FLOAT(X)        ((X) / 32768.0)
#define PI2             FIXED(atan(1.0) * 2.0)

typedef long int        fixed; /* <18,15> fixed-point */

static const fixed Angles[]={
			     FIXED(0.7853981633974483L),
			     FIXED(0.4636476090008061L),
			     FIXED(0.2449786631268641L),
			     FIXED(0.1243549945467614L),
			     FIXED(0.0624188099959574L),
			     FIXED(0.0312398334302683L),
			     FIXED(0.0156237286204768L),
			     FIXED(0.0078123410601011L),
			     FIXED(0.0039062301319670L),
			     FIXED(0.0019531225164788L),
			     FIXED(0.0009765621895593L),
			     FIXED(0.0004882812111949L),
			     FIXED(0.0002441406201494L),
			     FIXED(0.0001220703118937L),
			     FIXED(0.0000610351561742L),
			     FIXED(0.0000305175781155L),
			     FIXED(0.0000152587890613L),
			     FIXED(0.0000076293945311L),
			     FIXED(0.0000038146972656L)
};

//-----------------------------------------------------
void showtable() {
  unsigned Step;

  printf("Angles Table\n");
  printf("PI2: 16'h%x\n", PI2);
  printf("AC_CONST: 16'h%x\n", FIXED(AG_CONST));
  for (Step = 0; Step < 16; Step++)
    printf("16'h%x\n", Angles[Step]);
}

//-----------------------------------------------------
fixed quadrant(fixed inangle) {
  // output: 0-3 for quadrant 0-3
  // we assume step-angle is smaller than pi
  // so that there are always at least two samples per period (alias-free)
  // hence the max input angle can be (2pi + pi)
  unsigned q = 0;

  // if inangle >2pi, subtract 2pi.
  // This brings inangle in the range 0 - pi and keeps the same quardrant
  if (inangle > 4*PI2) 
    inangle = inangle - 4*PI2;

  if (inangle > 3*PI2)
    return 3;
  else if (inangle > 2*PI2)
    return 2;
  else if (inangle > PI2)
    return 1;

  return 0;
}

//-----------------------------------------------------
fixed angleadj(fixed inangle) {

  // input angle is 0 .. 3pi
  // output angle in first quadrant such that
  // abs(sin(inangle)) = sin(outangle)

  // if inangle >2pi, subtract 2pi.
  // This brings inangle in the range 0 - pi and keeps the same quardrant
  if (inangle > 4*PI2) 
    inangle = inangle - 4*PI2;

  if (inangle > 3*PI2)
    return (4*PI2 - inangle);
  else if (inangle > 2*PI2)
    return (inangle - 2*PI2);
  else if (inangle > PI2)
    return (2*PI2 - inangle);

  return inangle;
}

//-----------------------------------------------------
fixed accumulator(fixed inangle, fixed inangleadd) {
  inangle = inangle + inangleadd;

  if (inangle > 4*PI2)
    inangle = inangle - 4*PI2;

  return inangle;
}

//-----------------------------------------------------
fixed cordicsine(fixed inangle) {
  fixed X, Y, TargetAngle, CurrAngle;
  unsigned Step;

  X=FIXED(AG_CONST);  /* AG_CONST * cos(0) */
  Y=0;                /* AG_CONST * sin(0) */
  
  TargetAngle = angleadj(inangle);
  CurrAngle=0;
  for(Step=0; Step < 16; Step++) {
    fixed NewX;
    printf("%x: y: %x, x:%x\n", Step, Y, X);
    if (TargetAngle > CurrAngle) {
      NewX       =  X - (Y >> Step);
      Y          = (X >> Step) + Y;
      X          = NewX;
      CurrAngle += Angles[Step];
    } else {
      NewX       = X + (Y >> Step);
      Y          = -(X >> Step) + Y;
      X          = NewX;
      CurrAngle -= Angles[Step];
    }
  }

  if (quadrant(inangle) < 2) 
    return  Y;
  else
    return -Y;
}

//-----------------------------------------------------
int main(int argc, char *argv[]) {

  fixed    angle;
  fixed    sine;
  unsigned i;
  double   fsine;

  showtable();
  if (argc != 4) {
    fprintf(stderr, "%s samples increment float\n", argv[0]);
    fprintf(stderr, "    samples:   number of samples to generate\n");
    fprintf(stderr, "    increment: angle step in fix<16,15> for DDS\n");
    fprintf(stderr, "    float: 1 (flp output) or 0 (fix <16,14> output)\n");
    exit(0);
  }

  unsigned samples  = atoi(argv[1]);
  fixed    angleadd = atoi(argv[2]);
  unsigned flpout   = atoi(argv[3]);
  if (flpout == 0) {
    // hex format will be used by the verilog testbench
    printf("%x\n", samples);
    printf("%x\n", angleadd);
  }
  
  angle = angleadd;
  for (i=0; i<samples; i++) {
    sine = cordicsine(angle);

    if (flpout)
      printf("a %5x s %10x ( sin(%8.5f) = %8.5f ) sin %8.5f err %18.15f\n",
	     angle,
	     sine,
	     FLOAT(angle),
	     FLOAT(sine),
	     sin(FLOAT(angle)),
	     FLOAT(sine) - sin(FLOAT(angle)));
    else {
      printf("%x\n", (sine >> 1) & 0xffff);
    }
    
    angle = accumulator(angle, angleadd);    
  }
}
