# uMove
Simple one dimensional motion planner

* Constant acceleration path planning for smooth moves
* Single move queue
* moves start and stop at zero velocity
* Low memory and computational requirements

## Functions
```
uMove( float maxVelocity, float acceleration );

void addMove( float endPoint );                    // move to end point at max speed
void addMove( float endPoint, float feedRate );    // move to end point at desired speed
void addMove( float endPoint, uint32_t timeMS );   // move to end point over desired time (will not exceed max velocity or acceleration if expected time is too small)

bool moveComplete();

void startMoving();  // added moves don't start until this is exectuted
void stopNow();      // immediately decelerate to a stop

float getPosition();
float getVelocity();

void setPosition( float x ); // set the current position

void setMinLimit( float negativeLimit ); // prevent moving to points below this limit
void setMaxLimit( float positiveLimit ); // prevent moving to points above this limit
```
