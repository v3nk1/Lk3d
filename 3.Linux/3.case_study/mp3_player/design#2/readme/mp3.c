IN mp3.c:
`````````
In this we use some temparory registers to store the state of play or pause or resume or stop or load.

I just taken an integer "123" randomly to say that particular is HIGH(enabled) now u can disabled.

if play is going on then only u can pause or stop like that by making temp_pass=123 and temp_stop=123, once the media is stopped then the we are making temp_stop=0,temp_pass=0 like that.



In mp4.c also same way..
