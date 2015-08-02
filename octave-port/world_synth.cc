#include <octave/oct.h>
#include <octave/ov-struct.h>
#include "../synthesis.h"
#include "../cheaptrick.h"

// [y] = world_synth(f0, spectrogram, aperiodicity, frame_period, fs, [fft_size])
DEFUN_DLD (world_synth, args, nargout, "") {
  int nargin = args.length();
  
  if(nargin != 5 && nargin != 6) {
    printf("5 or 6 arguments are required.\n");
    return octave_value(0);
  }

  NDArray f0            = args(0).array_value();
  Matrix  spectrogram   = args(1).matrix_value();
  Matrix  aperiodicity  = args(2).array_value();
  double  frame_period  = args(3).scalar_value();
  int     fs            = args(4).int_value();
  int f0_length = f0.length();
  int fft_size = nargin == 6 ?
    args(5).int_value() : GetFFTSizeForCheapTrick(fs);
  int spec_size = fft_size / 2 + 1;
  int y_length = static_cast<int> (
    (f0_length - 1) * frame_period / 1000.0 * fs + 1);

  double*  synth_f0 = new double[f0_length];
  double** synth_spectrogram = new double*[f0_length];
  double** synth_aperiodicity = new double*[f0_length];
  double*  synth_y = new double[y_length];
  for(int i = 0; i < f0_length; ++i) {
    synth_f0[i] = f0(i);
    synth_spectrogram[i] = new double[spec_size];
    synth_aperiodicity[i] = new double[spec_size];
    for(int j = 0; j < spec_size; ++j) {
      synth_spectrogram[i][j] = spectrogram(i, j);
      synth_aperiodicity[i][j] = aperiodicity(i, j);
    }
  }
  Synthesis(synth_f0, f0_length, synth_spectrogram, synth_aperiodicity,
      fft_size, frame_period, fs, y_length, synth_y);
  
  NDArray y;
  y.resize1(y_length);
  for(int i = 0; i < y_length; ++i)
    y(i) = synth_y[i];
  for(int i = 0; i < f0_length; ++i) {
    delete[] synth_spectrogram[i];
    delete[] synth_aperiodicity[i];
  }
  delete[] synth_f0;
  delete[] synth_spectrogram;
  delete[] synth_aperiodicity;

  octave_value_list retval;
  retval(0) = y;
  return retval;
}

