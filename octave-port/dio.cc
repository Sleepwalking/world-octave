#include <octave/oct.h>
#include <octave/ov-struct.h>
#include "../dio.h"

// [f0 time_axis] = dio(x, fs, option)
DEFUN_DLD (dio, args, nargout, "") {
  int nargin = args.length();
  
  if(nargin != 3) {
    printf("3 arguments are required.\n");
    return octave_value(0);
  }

  NDArray           x       = args(0).array_value();
  int               fs      = args(1).int_value();
  octave_scalar_map option  = args(2).scalar_map_value();
  int x_length = x.length();

  DioOption dio_option;
  InitializeDioOption(&dio_option);
  #define init_option(name) \
    if(option.contents(#name).is_defined()) \
      dio_option.name = option.contents(#name).scalar_value();
  
  init_option(frame_period);
  init_option(speed);
  init_option(f0_floor);
  init_option(allowed_range);

  int f0_length = GetSamplesForDIO(fs, x_length, dio_option.frame_period);

  double* dio_x = new double[x_length];
  double* dio_f0 = new double[f0_length];
  double* dio_time_axis = new double[f0_length];
  for(int i = 0; i < x_length; i ++)
    dio_x[i] = x(i);
  Dio(dio_x, x_length, fs, dio_option, dio_time_axis, dio_f0);
  
  NDArray f0, time_axis;
  f0.resize1(f0_length);
  time_axis.resize1(f0_length);
  for(int i = 0; i < f0_length; i ++) {
    f0(i) = dio_f0[i];
    time_axis(i) = dio_time_axis[i];
  }
  delete [] dio_x;
  delete [] dio_f0;
  delete [] dio_time_axis;

  octave_value_list retval;
  retval(0) = f0;
  retval(1) = time_axis;
  return retval;
}

