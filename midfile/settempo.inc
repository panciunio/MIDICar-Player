procedure setTempo;
var
  freq:single;
  _freq:longint;
  fdiv:Byte;
  ratio:Single;
  _ratio:Byte;

begin
  _timerStatus:=_timerStatus xor $80;

// Calculation of the master counter frequency
  _freq:=(ms_per_qnote+tempoShift) div tickDiv;
  freq:=_freq/1000000;
  freq:=1/freq;
  // freq:=1/((tickDiv*ticks_per_qnote)/1000000)*8;

// Calculation of the sub-counter divisor
{ NOTE:
The master counter cannot operate directly at a frequency below ~251Hz,
so it is multiplied by the value of the sub-counter divisor.
This yields apparently lower frequencies for the main counter.
}
  ratio:=250.9803/freq; // 250.9803 Smallest possible _frequency_ for TIMER1 with 8-bit resolution
  _ratio:=1+trunc(ratio);
  if _ratio>15 then ratio:=15;

  // store timer ratio in status
  _timerStatus:=(_timerStatus and f_flags) or _ratio;
  _subCnt:=1;
  // calc frequency divider for timer
  fdiv:=round(64000/(freq*_ratio));

{$IFDEF USE_SUPPORT_VARS}
  // calc tempo (Beats Per Minutes)
  BPM:=60000000 div ms_per_qnote;
{$ENDIF}

  _timerStatus:=_timerStatus xor $80;

  asm
    sei  // disable IRQ
  // reset POKEY
    lda #$00
    ldy #$03
    sta AUDCTL
    sta AUDC1
    sty SKCTL
  // setup TIMER1
    sta AUDCTL
    mva FDIV AUDF1
  // initialize IRQ for TIMER1
    // lda irqens
    // ora #$01
    // sta irqens
    // sta irqen
  // start timer strobe
    sta stimer

    cli  // enable IRQ
  end;

end;
