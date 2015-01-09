#ifndef ERRNO

#define ERRNO

int errno;

enum err{

	ENODUP=-6,
        EFOUND=-5,
        EMALL=-4,
        EEPTY=-3,
        EFULL,
        FAILURE,
        SUCCESS

};

#endif
