#include "main.h"
int stuff = 0;
void playSpeaker(void *ignore){

  while(true){
    printf("loop");
    speakerInit();
    delay(20);
    if(stuff == 0){
      speakerPlayRtttl(":d=4,o=4,b=100:16d4");
    }
    else if(stuff == 1){
      speakerPlayRtttl(":d=4,o=4,b=100:16g4");
    }
    else if(stuff == 2){
      speakerPlayRtttl(":d=4,o=4,b=100:16d5");
    }
    else if(stuff == 3){
      speakerPlayRtttl(":d=4,o=4,b=100:16g5");
    }
    delay(20);
    speakerShutdown();
    delay(100);


  }
}
