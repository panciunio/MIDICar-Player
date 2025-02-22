{

}

const
  f_counter = %10000000; // prevents counting
  f_tick    = %01000000; // tick indicator
  f_flags   = %11000000; // flags mask
  f_ratio   = %00001111; // timer divider mask

  f_skipDelta = %10000000;
  f_stop      = %01000000;

  _trkRegs  = $e0;       // ZP registers for track processing

// MID file code formats
// __this player only supports 0 and 1 formats__
  MID_0 = 0;
  MID_1 = 1;

  ERR_UNSUPPORTED_FORMAT  = 100;
  ERR_NOT_ENOUGHT_MEMORY  = 101;
  ERR_NOT_A_MIDI_FILE     = 102;

  TAG_MTHD : TTag = $6468544D;
  TAG_MTRK : TTag = $6B72544D;

  sizeOf_TMIDTrack = sizeOf(TMIDTrack);