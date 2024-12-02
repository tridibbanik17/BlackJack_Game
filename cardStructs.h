#define NUM_CARDS 52
#define NUM_SUITS 4
#define NUM_RANKS 13
#define NUM_CHARLIE 5 // max hand size

// Card structure
typedef struct {
    int isDrawn;
    int value;
    char name[20];
} Card;

// Hand structure
typedef struct {
    int cardCount;
    int value;
    int bet;
    Card cards[NUM_CHARLIE];
} Hand;