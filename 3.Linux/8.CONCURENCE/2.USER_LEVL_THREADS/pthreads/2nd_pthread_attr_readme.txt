See we can change the atributes of the thread by
	(i)  STATICALLY:	
	````````````````1.We have to specify and assign the required attributes to pthread_attr_t(attribute obj) before 				pthread_create, and then create a thread as required by passing &attr object as an argument of pthread_create.
			2.We can assign required attributes to a attributes object by some predefined functions in pthread.h..
			3.Those functions are like pthread_attr_(get/set)<name.of.attr>
			4.After pthread_ "attr" is present then those are static funtions, ie., at the time of pthread creation we 			must specify the attributes..
		
		STATIC-FUNC:
		````````````
			pthread_attr_init
			pthread_attr_destroy		
	
  detachstate:		pthread_attr_(get/set)detachstate

	scope:		pthread_attr_(get/set)scope

  schedparams:		pthread_attr_(get/set)inheritsched
			pthread_attr_(get/set)schedparam
			pthread_attr_(get/set)schedpolicy
			sched_setscheduler

   stack-attr:		pthread_attr_(get/set)stack  ;use it instead of below 2 functions..
			pthread_attr_(get/set)stackaddr ; DEPRECATED FUNCTION
			pthread_attr_(get/set)stacksize ; DEPRECATED FUNCTION
			pthread_attr_(get/set)guardsize
			
			Deprecated functions means in furuther extenctions these funtions are nomore.

		
	(ii) DYNAMICALLY:
	`````````````````1.These are changing the parameters at runtime.. ie., after creation of thread, thread will hav default 			behaviour and then we are changing its atributes as per requirement at runtime..
	
			pthread_attr_init
			pthread_attr_destroy

			pthread_create
			pthread_detach
			pthread_equal
			pthread_exit
			
************************pthread_getattr_np: By invoking it we can get all attributes of a specified thread to the second argument 					what we hav passed(its an outparam)..
					    and we dont know how to evaluate each attribute from the attribute obj what we hav 						passed. Thats why they hav provided some pthread_attr_getXXXXXXXXX functions, by invoking the					   required functions like "pthread_attr_getstacksize" by passing attr obj what we hav got by 					      pthread_getattr_np function..
			
			pthread_(get/set)schedparam

			pthread_join

			pthread_kill

			pthread_self

			pthread_setschedprio

	IF U WANT TO SEE ALL THE PTHREAD SUPPORTED FUNCTIONS BY PRESSING "pthread_" and then press 2 tabs(tab+tab).

	READ ALL THE ABOVE FUNC'S MAN PAGES FULLY  FROM TOP TO BOTTOM (MUST AND SHUD) VERY CAREFULLY..
