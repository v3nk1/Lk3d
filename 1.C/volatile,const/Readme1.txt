Combining C’s volatile and const Keywords
=========================================

Does it ever make sense to declare a variable in C or C++ as both 
volatile (i.e., “ever-changing”) and const (“read-only”)? If so, why? 
And how should you combine volatile and const properly?

One of the most consistently popular articles on the Netrino website is about 
C’s volatile keyword. The volatile keyword, like const, is a type qualifier. 
These keywords can be used by themselves or together in variable declarations.


C’s volatile keyword is a qualifier that is applied to a variable when it is declared. 
It tells the compiler that the value of the variable may change at any time–without 
any action being taken by the code the compiler finds nearby.

How to Use C’s volatile Keyword
-------------------------------
By declaring a variable volatile you are effectively asking the compiler to be as 
inefficient as possible when it comes to reading or writing that variable. 
Specifically, the compiler should generate object code to perform each and every read from 
a volatile variable and each and every write to a volatile variable–even if you write it 
twice in a row or read it and ignore the result. No read or write can be skipped. 
Effectively no optimizations are allowed with respect to volatile variables.

The use of volatile variables also creates additional sequence points in C and C++ programs. 
The order of accesses of volatile variables A and B in the object code must be the 
same as the order of those accesses in the source code. The compiler is not allowed to reorder 
volatile variable accesses for any reason.

Here are a couple of examples of declarations of volatile variables:
--------------------------------------------------------------------

int volatile g_flag_shared_with_isr;

uint8_t volatile * p_led_reg = (uint8_t *) 0x00080000;

The first example declares a global flag that can be shared between an ISR and 
some other part of the code (e.g., a background processing loop in main() or an RTOS task) 
without fear that the compiler will optimize (i.e., “delete”) the code you write to check 
for asynchronous changes to the flag’s value. It is important to use volatile to declare 
all variables that are shared by asynchronous software entities, which is important in any 
kind of multithreaded programming. (Remember, though, that access to global variables 
shared by tasks or with an ISR must always also be controlled via a mutex or interrupt disable, 
respectively.)

The second example declares a pointer to a hardware register at a known physical 
memory address (80000h)–in this case to manipulate the state of one or more LEDs. 
Because the pointer to the hardware register is declared volatile, the compiler must 
always perform each individual write. Even if you write C code to turn an LED on followed 
immediately by code to turn the same LED off, you can trust that the hardware really will 
receive both instructions. Because of the sequence point restrictions, you are also 
guaranteed that the LED will be off after both lines of the C code have been executed. 
The volatile keyword should always be used with creating pointers to memory-mapped I/O such as this.

How to Use C’s const Keyword
----------------------------
The const keyword is can be used to modify parameters as well as in variable declarations. 
Here we are only interested in the use of const as a type qualifier, as in:

uint16_t const max_temp_in_c = 1000;

This declaration creates a 16-bit unsigned integer value of 1,000 with a scoped name 
of max_temp_in_c. In C, this variable will exist in memory at run-time, but will typically 
be located, by the linker, in a non-volatile memory area such as ROM or flash. 
Any reference to the const variable will read from that location. 
(In C++, a const integer may no longer exist as an addressable location in run-time memory.)

Any attempt the code makes to write to a const variable directly (i.e., by its name) will 
result in a compile-time error. To the extent that the const variable is located in ROM or flash, 
an indirect write (i.e., via a pointer to its address) will also be thwarted–though at run-time, obviously.

Another use of const is to mark a hardware register as read-only. For example:

uint8_t const * p_latch_reg = 0x10000000;

Declaring the pointer this way, any attempt to write to that physical memory address 
via the pointer (e.g., *p_latch_reg = 0xFF;) should result in a compile-time error.

How to Use const and volatile Together
--------------------------------------
Though the essence of the volatile (“ever-changing”) and const (“read-only”) 
decorators may seem at first glance opposed, there are some times when it makes 
sense to use them both to declare one variable. The scenarios I’ve run across have 
involved pointers to memory-mapped hardware registers and shared memory areas.

(#1) Constant Addresses of Hardware Registers
---------------------------------------------
The following declaration uses both const and volatile in the frequently useful scenario of 
declaring a constant pointer to a volatile hardware register.

uint8_t volatile * const p_led_reg = (uint8_t *) 0x00080000;

The proper way to read a complex declaration like this is from the name of the variable back to the left, as in:

    p_led_reg IS A constant pointer TO A volatile 8-bit unsigned integer.

Reading it that way, we can see that the keyword const modifies only the pointer 
(i.e., the fixed address 80000h), which does not change at run-time. 
Whereas the keyword volatile modifies only the type of integer. This is actually quite 
useful and is a much safer version of the declaration of a p_led_reg that appears at the 
top of this article. In particular, adding const means that the simple typo of a missed pointer 
dereference (‘*’) will be caught at compile time. That is, 
the mistaken code p_led_reg = LED1_ON; won’t overwrite the address with the non-80000h value of LED1_ON. 
The compiler error leads us to correct this to *p_led_reg = LED1_ON;, 
which is almost certainly what we meant to write in the first place.

(#2) Read-Only Shared-Memory Buffer
-----------------------------------
Another use for a combination of const and volatile is where you have two processors 
communicating via a shared memory area and you are coding the side of this communications 
that will only be reading from a shared memory buffer. In this case you could declare variables such as:

int const volatile comm_flag;

uint8_t const volatile comm_buffer[BUFFER_SIZE];

Of course, you’d usually want to instruct the linker to place these global variables 
at the correct addresses in the shared memory area or to declare the above as pointers 
to specific physical memory addresses. In the case of pointers, the use of const and volatile 
may become even more complex, as in the next category.

Q.  Can a variable be both const and volatile?
Ans:
  Yes. The const modifier means that this code cannot change the value of the variable, 
but that does not mean that the value cannot be changed by means outside this code. 
For instance, in the example in  FAQ 8, the timer structure was accessed through a 
volatile const pointer. The function itself did not change the value of the timer, 
so it was declared const. However, the value was changed by hardware on the computer, 
so it was declared volatile. If a variable is both const and volatile, 
the two modifiers can appear in either order.

(#3) Read-Only Hardware Register
--------------------------------
Sometimes you will run across a read-only hardware register. In addition to enforcing 
compile-time checking so that the software doesn’t try to overwrite the memory location, 
you also need to be sure that each and every requested read actually occurs. By declaring your 
variable IS A (constant) pointer TO A constant and volatile memory location you request 
all of the appropriate protections, as in:

uint8_t const volatile * const p_latch_reg = (uint8_t *) 0x10000000;

As you can see, the declarations of variables that involve both the volatile and const 
decorators can quickly become complicated to read. But the technique of combining C’s volatile 
and const keywords can be useful and even important. This is definitely something you should 
learn to master to be a master embedded software engineer.
