unsigned int setrgb(byte inred, byte ingrn, byte inblue){
  inred = map(inred,0,255,0,31);
  ingrn = map(ingrn,0,255,0,31);
  inblue = map(inblue,0,255,0,31);
  return inred << 11 | ingrn << 5 | inblue;
}

