/** \file shapemotion.c
 *  \brief This is a simple shape motion demo.
 *  This demo creates two layers containing shapes.
 *  One layer contains a rectangle and the other a circle.
 *  While the CPU is running the green LED is on, and
 *  when the screen does not need to be redrawn the CPU
 *  is turned off along with the green LED.
 */  
#include <msp430.h>
#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include <p2switches.h>
#include <shape.h>
#include <abCircle.h>

#define GREEN_LED BIT6


AbRect rect10 = {abRectGetBounds, abRectCheck, {10,10}}; /**< 10x10 rectangle */
AbRect rect15by5 = {abRectGetBounds, abRectCheck, {15,5}};

AbRect rect10by3 = {abRectGetBounds, abRectCheck, {10,3}};

AbRArrow rightArrow = {abRArrowGetBounds, abRArrowCheck, 20};

AbRect rect20 = {abRectGetBounds, abRectCheck, {10,30}}; /**< 10x10 rectangle */

AbRectOutline fieldOutline = {	/* playing field */
  abRectOutlineGetBounds, abRectOutlineCheck,   
  {screenWidth/2 - 10, screenHeight/2 - 10}
};

Layer leftArmLayer = {
  (AbShape *)&rect10by3,
  {(screenWidth/2)-25, (screenHeight/2)+10}, /**< black 10x3 rectangle */
  {0,0}, {0,0},				    /* last & next pos */
  COLOR_BLACK,
  0,
};

Layer rightArmLayer = {
  (AbShape *)&rect10by3,
  {(screenWidth/2)+25, (screenHeight/2)+10}, /**< black 10x3 rectangle */
  {0,0}, {0,0},				    /* last & next pos */
  COLOR_BLACK,
  &leftArmLayer,
};

Layer topHatLayer = {	  /* black 10x10 rectangle as a layer */
  (AbShape *) &rect10,
  {(screenWidth/2), (screenHeight/2)-35},/**< center */
  {0,0}, {0,0},				    /* last & next pos */
  COLOR_BLACK,
  &rightArmLayer,

};

Layer topSnowBallLayer = {	    /* top white circle as a layer */
  (AbShape *) &circle15,
  {(screenWidth/2), (screenHeight/2)-15},/**< center */
  {0,0}, {0,0},				    /* last & next pos */
  COLOR_WHITE,
  &topHatLayer,
};


Layer hatRimLayer = {	    /* black 15x5 rectangle as a layer */
  (AbShape *) &rect15by5,
  {(screenWidth/2), (screenHeight/2)-25},/**< center */
  {0,0}, {0,0},				    /* last & next pos */
  COLOR_BLACK,
  &topSnowBallLayer,
};

Layer noseLayer = {	    /* nose orange circle as a layer */
  (AbShape *) &circle4,
  {(screenWidth/2), (screenHeight/2)-15},/**< center */
  {0,0}, {0,0},				    /* last & next pos */
  COLOR_ORANGE,
  &hatRimLayer,
};

Layer middleSnowBallLayer = {	     /* middle white circle as a layer */
  (AbShape *) &circle20,
  {(screenWidth/2), (screenHeight/2)+10},/**< center */
  {0,0}, {0,0},				    /* last & next pos */
  COLOR_WHITE,
  &noseLayer,
};

Layer bottomButtonLayer = {		/* wreath center as a layer */
  (AbShape *) &circle4,
  {screenWidth/2, (screenHeight/2)+8},/**< center */
  {0,0}, {0,0},				    /* last & next pos */
  COLOR_BLACK,
  &middleSnowBallLayer,
};

Layer topButtonLayer = {		/* wreath center as a layer */
  (AbShape *) &circle4,
  {screenWidth/2, (screenHeight/2)+4},/**< center */
  {0,0}, {0,0},				    /* last & next pos */
  COLOR_BLACK,
  &bottomButtonLayer,
};

Layer bottomSnowBallLayer = {	    /* bottom white circle as a layer */
  (AbShape *) &circle25,
  {(screenWidth/2), (screenHeight/2)+40},/**< center */
  {0,0}, {0,0},				    /* last & next pos */
  COLOR_WHITE,
  &topButtonLayer,
};

Layer layer4 = {	     /**< Layer with white moving circle */
  (AbShape *)&circle4,
  {(screenWidth/2)+10, (screenHeight/2)-50}, /**< bit below & right of center */
  {0,0}, {0,0},				    /* last & next pos */
  COLOR_WHITE,
  &bottomSnowBallLayer,
};
  

Layer layer3 = {	  /**< Layer with white moving circle */
  (AbShape *)&circle4,
  {(screenWidth/2)-45, (screenHeight/2)-55}, /**< bit below & right of center */
  {0,0}, {0,0},				    /* last & next pos */
  COLOR_WHITE,
  &layer4,
};


Layer fieldLayer = {		/* black outline */
  (AbShape *) &fieldOutline,
  {screenWidth/2, screenHeight/2},/**< center */
  {0,0}, {0,0},				    /* last & next pos */
  COLOR_BLACK,
  &layer3,
};

Layer layer1 = {	     /**< Layer with white moving circle */
  (AbShape *)&circle4,
  {screenWidth/2,(screenHeight/2)-58}, /**< center */
  {0,0}, {0,0},				    /* last & next pos */
  COLOR_WHITE,
  &fieldLayer,
};

Layer layer0 = {	  /**< Layer with white moving circle */
  (AbShape *)&circle4,
  {(screenWidth/2)+20, (screenHeight/2)-50}, /**< bit below & right of center */
  {0,0}, {0,0},				    /* last & next pos */
  COLOR_WHITE,
  &layer1,
};

/** Moving Layer
 *  Linked list of layer references
 *  Velocity represents one iteration of change (direction & magnitude)
 */
typedef struct MovLayer_s {
  Layer *layer;
  Vec2 velocity;
  struct MovLayer_s *next;
} MovLayer;

/* initial value of {0,0} will be overwritten */
 /**< not all layers move should be violet circle too*/

MovLayer ml4 = { &layer4, {2,2}, 0};
MovLayer ml3 = { &layer3, {1,1}, &ml4 }; //violet circle
MovLayer ml1 = { &layer1, {1,2}, &ml3 }; 
MovLayer ml0 = { &layer0, {2,1}, &ml1 };//violet circle  


movLayerDraw(MovLayer *movLayers, Layer *layers)
{
  int row, col;
  MovLayer *movLayer;

  and_sr(~8);			/**< disable interrupts (GIE off) */
  for (movLayer = movLayers; movLayer; movLayer = movLayer->next) { /* for each moving layer */
    Layer *l = movLayer->layer;
    l->posLast = l->pos;
    l->pos = l->posNext;
  }
  or_sr(8);			/**< disable interrupts (GIE on) */


  for (movLayer = movLayers; movLayer; movLayer = movLayer->next) { /* for each moving layer */
    Region bounds;
    layerGetBounds(movLayer->layer, &bounds);
    lcd_setArea(bounds.topLeft.axes[0], bounds.topLeft.axes[1], 
		bounds.botRight.axes[0], bounds.botRight.axes[1]);
    for (row = bounds.topLeft.axes[1]; row <= bounds.botRight.axes[1]; row++) {
      for (col = bounds.topLeft.axes[0]; col <= bounds.botRight.axes[0]; col++) {
	Vec2 pixelPos = {col, row};
	u_int color = bgColor;
	Layer *probeLayer;
	for (probeLayer = layers; probeLayer; 
	     probeLayer = probeLayer->next) { /* probe all layers, in order */
	  if (abShapeCheck(probeLayer->abShape, &probeLayer->pos, &pixelPos)) {
	    color = probeLayer->color;
	    break; 
	  } /* if probe check */
	} // for checking all layers at col, row
	lcd_writeColor(color); 
      } // for col
    } // for row
  } // for moving layer being updated
}	  



//Region fence = {{10,30}, {SHORT_EDGE_PIXELS-10, LONG_EDGE_PIXELS-10}}; /**< Create a fence region */

/** Advances a moving shape within a fence
 *  
 *  \param ml The moving shape to be advanced
 *  \param fence The region which will serve as a boundary for ml
 */
void mlAdvance(MovLayer *ml, Region *fence)
{
  Vec2 newPos;
  u_char axis;
  Region shapeBoundary;
  for (; ml; ml = ml->next) {
    vec2Add(&newPos, &ml->layer->posNext, &ml->velocity);
    abShapeGetBounds(ml->layer->abShape, &newPos, &shapeBoundary);
    for (axis = 0; axis < 2; axis ++) {
      if ((shapeBoundary.topLeft.axes[axis] < fence->topLeft.axes[axis]) ||
	  (shapeBoundary.botRight.axes[axis] > fence->botRight.axes[axis]) ) {
	int velocity = ml->velocity.axes[axis] = -ml->velocity.axes[axis];
	newPos.axes[axis] += (2*velocity);
      }	/**< if outside of fence */
    } /**< for axis */
    ml->layer->posNext = newPos;
  } /**< for ml */
}


u_int bgColor = COLOR_BLUE;     /**< The background color */
int redrawScreen = 1;           /**< Boolean for whether screen needs to be redrawn */

Region fieldFence;		/**< fence around playing field  */


/** Initializes everything, enables interrupts and green LED, 
 *  and handles the rendering for the screen
 */
void main()
{
  P1DIR |= GREEN_LED;		/**< Green led on when CPU on */		
  P1OUT |= GREEN_LED;

  configureClocks();

  lcd_init();
    drawString5x7(20,20, "White Christmas", COLOR_GREEN, COLOR_RED);
  shapeInit();
  p2sw_init(1);


  shapeInit();

  layerInit(&layer0);
  layerDraw(&layer0);


  layerGetBounds(&fieldLayer, &fieldFence);


  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */


  for(;;) { 
    while (!redrawScreen) { /**< Pause CPU if screen doesn't need updating */
      P1OUT &= ~GREEN_LED;    /**< Green led off witHo CPU */
      or_sr(0x10);	      /**< CPU OFF */
    }
    P1OUT |= GREEN_LED;       /**< Green led on when CPU on */
    redrawScreen = 0;
    movLayerDraw(&ml0, &layer0);
  }
}

/** Watchdog timer interrupt handler. 15 interrupts/sec */
void wdt_c_handler()
{
  static short count = 0;
  P1OUT |= GREEN_LED;		      /**< Green LED on when cpu on */
  count ++;
  if (count == 15) {
    mlAdvance(&ml0, &fieldFence);
    if (p2sw_read())
      redrawScreen = 1;
    count = 0;
  }
  P1OUT &= ~GREEN_LED;		    /**< Green LED off when cpu off */
}
