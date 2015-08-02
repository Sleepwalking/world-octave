#include <octave/oct.h>
#include <octave/ov-struct.h>
#include "../stonemask.h"

// [refined_f0] = stonemask(x, fs, time_axis, f0)
DEFUN_DLD (stonemask, args, nargout, "") {
  int nargin = args.length();
  
  if(nargin != 4) {
    printf("4 arguments are required.\n");
    return octave_value(0);
  }

  NDArray x         = args(0).array_value();
  int     fs        = args(1).int_value();
  NDArray time_axis = args(2).array_value();
  NDArray f0        = args(3).array_value();
  int x_length = x.length();
  int f0_length = f0.length();

  double* stone_x = new double[x_length];
  double* stone_f0 = new double[f0_length];
  double* stone_time_axis = new double[f0_length];
  double* stone_refined_f0 = new double[f0_length];
  for(int i = 0; i < x_length; ++i)
    stone_x[i] = x(i);
  for(int i = 0; i < f0_length; ++i) {
    stone_f0[i] = f0(i);
    stone_time_axis[i] = time_axis(i);
  }
  StoneMask(stone_x, x_length, fs, stone_time_axis, stone_f0, f0_length, stone_refined_f0);
    
  NDArray refined_f0;
  refined_f0.resize1(f0_length);
  for(int i = 0; i < f0_length; ++i)
    refined_f0(i) = stone_refined_f0[i];
  delete[] stone_x;
  delete[] stone_f0;
  delete[] stone_time_axis;
  delete[] stone_refined_f0;

  octave_value_list retval;
  retval(0) = refined_f0;
  return retval;
}

