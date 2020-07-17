#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

//Finish the following struct (product)
typedef struct {
  char *category; //"string", "woodwind", "brass";     
  float price;
  union {
    struct {
      //should have two chars: a char *name (violin, viola, cello, bass) and char *stringType (steel, nylon, gut)
      char *name;
      char *stringType;
    } string;

    struct {
      //should have one char: a char *name (flute, clarinet, oboe, bassoon) and one int: an int includesReed (1 for yes, 0 for no);
      char *name;
      int includesReed;
    } woodwind;

    struct {
      //should have one char: a char *name (trumpet, horn, tuba, trombone) and one int: an int includesMouthPiece (1 for yes, 0 for no);
      char *name;
      int includesMouthPiece;
    } brass;
  } item;
} product;

typedef struct {
  product items[12];
} instrumentStore;


//Finish this function
void printStoreInventory(instrumentStore *store, int numItems) {
  //print out the store inventory in the following form: 
  for (int i = 0; i < numItems; i++) {
    printf("Product id: %d, ", i);
    if (strcmp(store->items[i].category, "string") == 0) {
      //Print out:
      //Product category: %s, Price: $%.2f, Name: %s, String Type: %s\n
      printf("Product category: %s, Price: $%.2f, Name: %s, String Type: %s\n", 
      store->items[i].category, store->items[i].price, store->items[i].item.string.name, store->items[i].item.string.stringType);

    } else if (strcmp(store->items[i].category, "woodwind") == 0) {
      char *yesNo = (store->items[i].item.woodwind.includesReed == 1) ? "yes" : "no";
      //Print out:
      //Product category: %s, Price: $%.2f, Name: %s, Includes Reed?: %s\n
      printf("Product category: %s, Price: $%.2f, Name: %s, Includes Reed?: %s\n", 
      store->items[i].category, store->items[i].price, store->items[i].item.woodwind.name, yesNo);
    
    } else if (strcmp(store->items[i].category, "brass") == 0) {
      char *yesNo = (store->items[i].item.brass.includesMouthPiece == 1) ? "yes" : "no";
      //Print out:
      //Product category: %s, Price: $%.2f, Name: %s, Includes MouthPiece?: %s\n
      printf("Product category: %s, Price: $%.2f, Name: %s, Includes MouthPiece?: %s\n", 
      store->items[i].category, store->items[i].price, store->items[i].item.brass.name, yesNo);
    }
  }
}

//These 5 methods are done for you - don't change these!
void updateStringItem(instrumentStore *store, int index, float price, char *name, char *stringType) {
  store->items[index].category = "string";
  store->items[index].price = price;
  
  store->items[index].item.string.name = name;
  store->items[index].item.string.stringType = stringType;
}

void updateWoodWindItem(instrumentStore *store, int index, float price, char *name, int includesReed) {
  store->items[index].category = "woodwind";
  store->items[index].price = price;
  
  store->items[index].item.woodwind.name = name;
  store->items[index].item.woodwind.includesReed = includesReed;
}

void updateBrassItem(instrumentStore *store, int index, float price, char *name, int includesMouthPiece) {
  store->items[index].category = "brass";
  store->items[index].price = price;
  
  store->items[index].item.brass.name = name;
  store->items[index].item.brass.includesMouthPiece = includesMouthPiece;
}

float float_rand(float min, float max) {
    sleep(1);
    srand(time(NULL));
    float scale = rand() / (float) RAND_MAX; /* [0, 1.0] */
    return min + scale * ( max - min );      /* [min, max] */
}

int int_rand(int min_num, int max_num) {
    sleep(1);
    int result = 0, low_num = 0, hi_num = 0;

    if (min_num < max_num) {
        low_num = min_num;
        hi_num = max_num + 1; // include max_num in output
    } else {
        low_num = max_num + 1; // include max_num in output
        hi_num = min_num;
    }

    srand(time(NULL));
    result = (rand() % (hi_num - low_num)) + low_num;
    return result;
}
//End Completed Functions


int main(void) {
  instrumentStore store;
  printf("Generating store inventory...\n\n");
  //Don't edit this loop!  
  for (int i = 0; i < 12; i++) {
    //Random price
    float price = float_rand(100, 2000);

    //Random category
    int randCat = int_rand(0, 2);
    char *category = (randCat == 0) ? "string" : (randCat == 1) ? "woodwind" : "brass";
    
    //Random instrument name
    int randName = int_rand(0, 3);
    char *name;

    store.items[i].price = price;
    store.items[i].category = category;

    if (randCat == 0) { //String
      if (randName == 0) name = "Violin";
      if (randName == 1) name = "Viola";
      if (randName == 2) name = "Cello";
      if (randName == 3) name = "Bass";
    
      //Random string type
      int randString = int_rand(0, 2);
      char *stringType = (randString == 0) ? "steel" : (randString == 1) ? "nylon" : "gut";

      store.items[i].item.string.name = name;
      store.items[i].item.string.stringType = stringType;
    } else if (randCat == 1) { //Woodwind
      if (randName == 0) name = "Flute";
      if (randName == 1) name = "Clarinet";
      if (randName == 2) name = "Oboe";
      if (randName == 3) name = "Bassoon";

      //Randomly choose yes or no
      int includesReed = int_rand(0, 1);

      store.items[i].item.woodwind.name = name;
      store.items[i].item.woodwind.includesReed = includesReed;
    } else if (randCat == 2) { //Brass
      if (randName == 0) name = "Trumpet";
      if (randName == 1) name = "Horn";
      if (randName == 2) name = "Trombone";
      if (randName == 3) name = "Tuba";
    
      //Randomly choose yes or no
      int includesMouthPiece = int_rand(0, 1);

      store.items[i].item.brass.name = name;
      store.items[i].item.brass.includesMouthPiece = includesMouthPiece;
    }
  }

  //Call printStoreInventory below
  printStoreInventory(&store, 12);
  return 0;
}
