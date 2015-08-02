#include <octave/oct.h>
#include <octave/ov-struct.h>
#include "../d4c.h"
#include "../cheaptrick.h"

// [aperiodicity] = d4c(x, fs, time_axis, f0)
DEFUN_DLD (d4c, args, nargout, "") {
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
  int fft_size = GetFFTSizeForCheapTrick(fs);
  int spec_size = fft_size / 2 + 1;

  double*  d4c_x = new double[x_length];
  double*  d4c_f0 = new double[f0_length];
  double*  d4c_time_axis = new double[f0_length];
  double** d4c_aperiodicity = new double*[f0_length];
  for(int i = 0; i < x_length; i ++)
    d4c_x[i] = x(i);
  for(int i = 0; i < f0_length; i ++) {
    d4c_f0[i] = f0(i);
    d4c_time_axis[i] = time_axis(i);
    d4c_aperiodicity[i] = new double[spec_size];
  }
  D4C(d4c_x, x_length, fs, d4c_time_axis, d4c_f0, f0_length, fft_size,
    d4c_aperiodicity);
  
  Matrix aperiodicity(f0_length, spec_size);
  for(int i = 0; i < f0_length; i ++)
  {
    for(int j = 0; j < spec_size; j ++)
        aperiodicity(i, j) = d4c_aperiodicity[i][j];
    delete [] d4c_aperiodicity[i];
  }
  delete [] d4c_x;
  delete [] d4c_f0;
  delete [] d4c_time_axis;
  delete [] d4c_aperiodicity;

  octave_value_list retval;
  retval(0) = aperiodicity;
  return retval;
}

