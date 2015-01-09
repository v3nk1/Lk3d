typedef struct handle{
                int (*canHandle) (const char *);
                void (*saveImage) (const char *);
                void (*displayImage) (const char *);
                }sh;

extern void reg_handler(sh *);
extern sh *handlers[10];
extern int no_libs;

extern int vcanHandle(const char *);
extern void vdisplayImage(const char *);
extern void vsaveImage(const char *);
//extern displayImage();
//extern saveImage(const char *)
