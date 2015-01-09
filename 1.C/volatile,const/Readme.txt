Use of 'const' and 'volatile'
============================

Scenario:
---------
The correct placement of the type qualifiers const and volatile can sometimes be confusing, especially when applied to a pointer or the thing it points to.

Here is a simple rule which may help: place const (or volatile) *after* the thing you're 
saying is constant (or volatile).

    to declare a constant integer, use int const xxx, instead of const int xxx.
    to declare a pointer to a constant integer, put const after int to get int const *ptr.
    to declare a constant pointer to an integer, put const after * and get int * const ptr.
    to declare a constant pointer to a constant integer, use int const * const ptr.
    to declare a constant pointer to a volatile integer, use int volatile * const ptr.

The really nice thing about doing it this way is that you can see what the type is by simply reading *backwards* through the definition:

int const xxx;
 |    |    |
 |    |    +-----------------> xxx is a
 |    +----------------------> constant
 +---------------------------> integer
int const *ptr;
 |     |  | |
 |     |  | +----------------> ptr is a
 |     |  +------------------> pointer to a
 |     +---------------------> constant
 +---------------------------> integer
int * const ptr;
 |   | |     |
 |   | |     +---------------> ptr is a
 |   | +---------------------> constant
 |   +-----------------------> pointer to an
 +---------------------------> integer
int const * const ptr;
 |    |   |   |    |
 |    |   |   |    +---------> ptr is a
 |    |   |   +--------------> constant
 |    |   +------------------> pointer to a
 |    +----------------------> constant
 +---------------------------> integer
int volatile * const ptr;
 |     |     |   |    |
 |     |     |   |    +------> ptr is a
 |     |     |   +-----------> constant
 |     |     +---------------> pointer to a
 |     +---------------------> volatile
 +---------------------------> integer

In fact, this method works for any type qualifier, including __packed, e.g. int __packed x and int *__packed x;
