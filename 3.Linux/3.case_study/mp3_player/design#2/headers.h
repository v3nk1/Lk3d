

typedef struct handler{
         int (*mediaHandler)(char *);
         void (*loadMedia)(char *);
         void (*playMedia)(void);
         void (*stopMedia)(void);
         void (*pauseMedia)(void);
	 void (*convMedia)(void);

}sh;

extern sh mp3;
extern sh mp4;
