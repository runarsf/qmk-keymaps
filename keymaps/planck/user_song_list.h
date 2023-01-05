#ifdef AUDIO_ENABLE
  #undef MEGALOVANIA
  #define MEGALOVANIA \
    Q__NOTE(_D4), Q__NOTE(_D4), H__NOTE(_D5), HD_NOTE(_A4), H__NOTE(_AF4), H__NOTE(_G4), H__NOTE(_F4), \
    Q__NOTE(_D4), Q__NOTE(_F4), Q__NOTE(_G4), Q__NOTE(_C4), Q__NOTE(_C4), H__NOTE(_D5), HD_NOTE(_A4), \
    H__NOTE(_AF4), H__NOTE(_G4), H__NOTE(_F4), Q__NOTE(_D4), Q__NOTE(_F4), Q__NOTE(_G4), \
    Q__NOTE(_B3), Q__NOTE(_B3), H__NOTE(_D5), HD_NOTE(_A4), H__NOTE(_AF4), H__NOTE(_G4), H__NOTE(_F4), \
    Q__NOTE(_D4), Q__NOTE(_F4), Q__NOTE(_G4), Q__NOTE(_BF3), Q__NOTE(_BF3), H__NOTE(_D5), \
    HD_NOTE(_A4), H__NOTE(_AF4), H__NOTE(_G4), H__NOTE(_F4), Q__NOTE(_D4), Q__NOTE(_F4), \
    Q__NOTE(_G4),

  #undef RICK_ROLL
  #define RICK_ROLL \
    Q__NOTE(_F4), \
    Q__NOTE(_G4), \
    Q__NOTE(_BF4), \
    Q__NOTE(_G4), \
    HD_NOTE(_D5), \
    HD_NOTE(_D5), \
    W__NOTE(_C5), \
    S__NOTE(_REST),\
    Q__NOTE(_F4), \
    Q__NOTE(_G4), \
    Q__NOTE(_BF4), \
    Q__NOTE(_G4), \
    HD_NOTE(_C5), \
    HD_NOTE(_C5), \
    W__NOTE(_BF4), \
    S__NOTE(_REST), \
    Q__NOTE(_F4), \
    Q__NOTE(_G4), \
    Q__NOTE(_BF4), \
    Q__NOTE(_G4), \
    W__NOTE(_BF4), \
    H__NOTE(_C5), \
    H__NOTE(_A4), \
    H__NOTE(_A4), \
    H__NOTE(_G4), \
    H__NOTE(_F4), \
    H__NOTE(_F4), \
    W__NOTE(_C5), \
    W__NOTE(_BF4),

  #undef ALL_STAR
  #define ALL_STAR \
    H__NOTE(_AS4), W__NOTE(_FS4), Q__NOTE(_FS4), Q__NOTE(_DS4), H__NOTE(_FS4), W__NOTE(_FS4), Q__NOTE(_FS4), Q__NOTE(_DS4), \
    H__NOTE(_FS4), W__NOTE(_FS4), W__NOTE(_FS4), QD_NOTE(_AS4), \
    H__NOTE(_AS4), W__NOTE(_FS4), Q__NOTE(_FS4), Q__NOTE(_DS4), H__NOTE(_FS4), W__NOTE(_FS4), Q__NOTE(_FS4), Q__NOTE(_DS4), \
    H__NOTE(_FS4), W__NOTE(_FS4), W__NOTE(_FS4), W__NOTE(_AS4), H__NOTE(_REST),\
    W__NOTE(_AS4), W__NOTE(_CS5), H__NOTE(_B4),  H__NOTE(_CS5), H__NOTE(_DS5), W__NOTE(_FS5), \
    H__NOTE(_GS5), W__NOTE(_GS5), H__NOTE(_FS4), H__NOTE(_FS4), H__NOTE(_GS4), H__NOTE(_FS4), \
    H__NOTE(_AS4), W__NOTE(_GS4), W__NOTE(_GS4), W__NOTE(_FS4), W__NOTE(_GS4), \
    H__NOTE(_AS4), WD_NOTE(_DS4),

  #undef NUMBER_ONE
  #define NUMBER_ONE \
    HD_NOTE(_F4), \
    Q__NOTE(_C5), \
    E__NOTE(_B4), \
    E__NOTE(_C5), \
    E__NOTE(_B4), \
    E__NOTE(_C5), \
    Q__NOTE(_B4), \
    Q__NOTE(_C5), \
    H__NOTE(_AF4), \
    HD_NOTE(_F4), \
    Q__NOTE(_F4), \
    Q__NOTE(_AF4), \
    Q__NOTE(_C5), \
    H__NOTE(_DF5), \
    H__NOTE(_AF4), \
    H__NOTE(_DF5), \
    H__NOTE(_EF5), \
    Q__NOTE(_C5), \
    Q__NOTE(_DF5), \
    Q__NOTE(_C5), \
    Q__NOTE(_DF5), \
    H__NOTE(_C5),

  #undef COIN_SOUND
  #define COIN_SOUND \
    E__NOTE(_A5), \
    HD_NOTE(_E6),

  #undef ONE_UP_SOUND
  #define ONE_UP_SOUND \
    Q__NOTE(_E6), \
    Q__NOTE(_G6), \
    Q__NOTE(_E7), \
    Q__NOTE(_C7), \
    Q__NOTE(_D7), \
    Q__NOTE(_G7),

  #undef SONIC_RING
  #define SONIC_RING \
    E__NOTE(_E6), \
    E__NOTE(_G6), \
    HD_NOTE(_C7),

  #undef ZELDA_PUZZLE
  #define ZELDA_PUZZLE \
    Q__NOTE(_G5), \
    Q__NOTE(_FS5), \
    Q__NOTE(_DS5), \
    Q__NOTE(_A4), \
    Q__NOTE(_GS4), \
    Q__NOTE(_E5), \
    Q__NOTE(_GS5), \
    HD_NOTE(_C6),

  #undef ZELDA_TREASURE
  #define ZELDA_TREASURE \
    Q__NOTE(_A4), \
    Q__NOTE(_AS4), \
    Q__NOTE(_B4), \
    HD_NOTE(_C5),

  #undef OVERWATCH_THEME
  #define OVERWATCH_THEME \
    HD_NOTE(_A4), \
    Q__NOTE(_E4), \
    Q__NOTE(_A4), \
    HD_NOTE(_B4), \
    Q__NOTE(_E4), \
    Q__NOTE(_B4), \
    W__NOTE(_CS5),

  #undef MICHISHIRUBE
  #define MICHISHIRUBE \
    W__NOTE(_A5), H__NOTE(_A5), H__NOTE(_A5), W__NOTE(_B5), H__NOTE(_A5), H__NOTE(_B5), BD_NOTE(_CS6), W__NOTE(_E6), \
    W__NOTE(_CS6), WD_NOTE(_B5), H__NOTE(_A5), BD_NOTE(_A5), W__NOTE(_A5), H__NOTE(_A5), H__NOTE(_A5), \
    W__NOTE(_B5), H__NOTE(_A5), H__NOTE(_B5), W__NOTE(_A5), W__NOTE(_A6), W__NOTE(_GS6), H__NOTE(_CS6), \
    Q__NOTE(_E6), Q__NOTE(_CS6), W__NOTE(_B5), H__NOTE(_B5), H__NOTE(_CS6), W__NOTE(_B5), H__NOTE(_A5), \
    Q__NOTE(_B5), BD_NOTE(_A5), \
    H__NOTE(_E6), H__NOTE(_FS6), H__NOTE(_E6), H__NOTE(_B6), \
    W__NOTE(_A6), H__NOTE(_E6), H__NOTE(_B6), W__NOTE(_A6), H__NOTE(_A6), H__NOTE(_B6), \
    B__NOTE(_CS7), H__NOTE(_E6), H__NOTE(_FS6), H__NOTE(_E6), H__NOTE(_B6), W__NOTE(_A6), H__NOTE(_E6), \
    H__NOTE(_B6), W__NOTE(_A6), H__NOTE(_A6), H__NOTE(_GS6), B__NOTE(_E6), H__NOTE(_E6), \
    H__NOTE(_FS6), H__NOTE(_E6), H__NOTE(_B6), W__NOTE(_A6), H__NOTE(_E6), H__NOTE(_B6), \
    W__NOTE(_A6), H__NOTE(_A6), H__NOTE(_B6), H__NOTE(_CS7), B__NOTE(_CS7), H__NOTE(_E6), H__NOTE(_E6), \
    H__NOTE(_E6), H__NOTE(_E6), H__NOTE(_D6), H__NOTE(_D6), H__NOTE(_CS6), H__NOTE(_CS6), Q__NOTE(_B5), \
    BD_NOTE(_B5), W__NOTE(_A5), H__NOTE(_A5), H__NOTE(_A5), W__NOTE(_B5), H__NOTE(_A5), H__NOTE(_B5), \
    BD_NOTE(_CS6), W__NOTE(_E6), W__NOTE(_CS6), WD_NOTE(_B5), H__NOTE(_A5), BD_NOTE(_A5), W__NOTE(_A5), \
    H__NOTE(_A5), H__NOTE(_A5), W__NOTE(_B5), H__NOTE(_A5), H__NOTE(_B5), W__NOTE(_A5), W__NOTE(_A6), \
    W__NOTE(_GS6), H__NOTE(_CS6), Q__NOTE(_E6), Q__NOTE(_CS6), W__NOTE(_B5), H__NOTE(_B5), H__NOTE(_CS6), \
    W__NOTE(_B5), H__NOTE(_A5), Q__NOTE(_B5), BD_NOTE(_A5),

  #undef IMPERIAL_MARCH
  #define IMPERIAL_MARCH \
    HD_NOTE(_A4), HD_NOTE(_A4), HD_NOTE(_A4), QD_NOTE(_F4), QD_NOTE(_C5), \
    HD_NOTE(_A4), QD_NOTE(_F4),  QD_NOTE(_C5), WD_NOTE(_A4), \
    HD_NOTE(_E5), HD_NOTE(_E5), HD_NOTE(_E5), QD_NOTE(_F5), QD_NOTE(_C5), \
    HD_NOTE(_A4), QD_NOTE(_F4),  QD_NOTE(_C5), WD_NOTE(_A4),
#endif