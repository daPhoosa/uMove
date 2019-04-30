# uMove
Simple one dimensional motion planner

* Constant acceleration path planning for smooth moves
* Moves start and stop at zero velocity
* Low memory and computational requirements
* Multiple uMove objects can be used simultaneously for multi axis applications

## Functions
```
uMove( float maxVelocity, float acceleration );

void setMove( float endPoint );                    // move to end point at max speed
void setMove( float endPoint, float feedRate );    // move to end point at desired speed
void setMove( float endPoint, uint32_t timeMS );   // move to end point over desired time (will not exceed max velocity or acceleration if expected time is too small)

bool moveComplete(); // returns true any time a move is not being executed

void startMoving();  // added moves don't start until this is exectuted
void stopNow();      // immediately decelerate to a stop

float getPosition(); // computes the expected position at this point in time.  Should be called frequently during at move to insure smooth movement.
float getVelocity(); // returns the velocty computed at the last `getPosition()` call

void setPosition( float x ); // set the current position

void setMinLimit( float negativeLimit ); // prevent moving to points below this limit
void setMaxLimit( float positiveLimit ); // prevent moving to points above this limit
```
