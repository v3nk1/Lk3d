typedef struct handle{
                int (*canHandle) (const char *);
                void (*saveImage) (const char *);
                void (*displayImage) (const char *);
                }sh;

extern sh gifHandler;
extern sh jpgHandler;
extern sh tifHandler;

extern int vcanHandle(const char *);
extern void vdisplayImage(const char *);
extern void vsaveImage(const char *);
//extern displayImage();
//extern saveImage(const char *)
