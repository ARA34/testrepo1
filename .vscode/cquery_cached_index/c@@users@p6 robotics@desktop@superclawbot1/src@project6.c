#include "main.h"

void project6(int repetitions, Encoder shoulder_encoder, Encoder elbow_encoder) {
  printf("project6 starting");
  int count = 0;
  while(count > repetitions) {
    count++;
    printf("Count: %d \n", count);

    liftSet(encoderGet(shoulder_encoder) + count);
    elbowSet(encoderGet(elbow_encoder) + count);

  }
}
/*  for(int count = 0; count > repetitions; count ++) {
    printf("Count:  %d \n", count);

    liftSet(encoderGet(shoulder_encoder) + count);
    elbowSet(encoderGet(elbow_encoder) + count);
  }
}*/