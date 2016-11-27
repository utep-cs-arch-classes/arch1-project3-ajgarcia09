#ifndef buzzer_included
#define buzzer_included

void buzzer_init();
void buzzer_set_period(short cycles);

/*       timeHigh = period / 2 = 1 / (2 * frequency)

  *
  * 
  * note   frequency         duration    timeHigh
  * C4         261 Hz         3830      1915
  * D4         294 Hz         3400      1700
  * E4         329 Hz         3038      1519
  * F4         349 Hz         2864      1432
  * G4         392 Hz         2550      1275
  * A4         440 Hz         2272       136
  * B4         493 Hz         2028      1014
  * C5        523 Hz          1912       956
   *
  *
 o  */
#define C4 3830
#define D4 3400
#define E4 3038
#define F4 2864
#define G4 2550
#define A4 2272
#define B4 2028
#define C5 1912


#endif // included

