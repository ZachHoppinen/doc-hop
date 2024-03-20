import numpy as np


def coherence(ref, sec, window_size = (9,9)):
  """
  Basically stripped down version of: https://github.com/TUDelftGeodesy/sarxarray/blob/main/sarxarray/utils.py#L83
  using rolling instead of coarsen to maintain resolution.
  """
  numerator = (ref * sec.conj()).rolling(x = window_size[0], y = window_size[1]).mean()

  ref_mean = (ref * ref.conj()).rolling(x = window_size[0], y = window_size[1]).mean()
  sec_mean = (sec * sec.conj()).rolling(x = window_size[0], y = window_size[1]).mean()

  coherence = np.abs(numerator / np.sqrt(ref_mean * sec_mean))

  return coherence
