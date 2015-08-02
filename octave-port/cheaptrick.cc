#include <octave/oct.h>
#include <octave/ov-struct.h>
#include "../cheaptrick.h"

// [spectrogram] = cheaptrick(x, fs, time_axis, f0)
DEFUN_DLD (cheaptrick, args, nargout, "") {
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

  double*  cheaptrick_x = new double[x_length];
  double*  cheaptrick_f0 = new double[f0_length];
  double*  cheaptrick_time_axis = new double[f0_length];
  double** cheaptrick_spectrogram = new double*[f0_length];
  for(int i = 0; i < x_length; ++i)
    cheaptrick_x[i] = x(i);
  for(int i = 0; i < f0_length; ++i) {
    cheaptrick_f0[i] = f0(i);
    cheaptrick_time_axis[i] = time_axis(i);
    cheaptrick_spectrogram[i] = new double[spec_size];
  }
  CheapTrick(cheaptrick_x, x_length, fs, cheaptrick_time_axis, cheaptrick_f0,
    f0_length, cheaptrick_spectrogram);
  
  Matrix spectrogram(f0_length, spec_size);
  for(int i = 0; i < f0_length; ++i) {
    for(int j = 0; j < spec_size; ++j)
        spectrogram(i, j) = cheaptrick_spectrogram[i][j];
    delete[] cheaptrick_spectrogram[i];
  }
  delete[] cheaptrick_x;
  delete[] cheaptrick_f0;
  delete[] cheaptrick_time_axis;
  delete[] cheaptrick_spectrogram;

  octave_value_list retval;
  retval(0) = spectrogram;
  return retval;
}

