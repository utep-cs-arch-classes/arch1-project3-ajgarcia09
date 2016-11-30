#ifndef layers_included
#define layers_included

/** Moving Layer
 *  Linked list of layer references
 *  Velocity represents one iteration of change (direction & magnitude)
 */
typedef struct MovLayer_s {
  Layer *layer;
  Vec2 velocity;
  struct MovLayer_s *next;
} MovLayer;

void movLayerDraw(MovLayer *movLayers, Layer *layers);

void mlAdvance(MovLayer *ml, Region *fence);

void wdt_c_handler();

void drawFireplaceScreen();

#endif
