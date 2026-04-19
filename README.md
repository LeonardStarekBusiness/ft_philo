_This project has been created as part of the 42 curriculum by lstarek_

# PHILOSOPHERS by lstarek

## DESCRIPTION
Philosophers with threads and mutexes  
This project aims to teach concurrent programming, focusing on multithreading and multiprocessing.  
One or more philosophers sit at a round table.  
The philosophers take turns eating, thinking, and sleeping.  
There are also forks on the table. There are as many forks as philosophers.  
A philosopher must pick up both the fork to their right and the fork to their left before eating.  
(this makes more sense with chopsticks. 42 Paris please fix, this is unacceptable jkjk /s /j)  
<b>The simulation stops when a philosopher dies of starvation or all have eaten enough.</b>

## INSTRUCTIONS
``` BASH
git clone (link_in_eval_sheet) (eval-"your-name")
```

Makefile is present. Run:
``` Makefile
make
```

Execute like:
``` BASH
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

## RESOURCES
### Documentation  
[old 42 philos eval sheet](https://www.scribd.com/document/920831727/Philosophers-Eval-Sheet)

### Manual  
``` BASH
man pthread_create
man pthread_mutex_init
man pthread_mutex_lock
man pthread_join
```

### Tutorials  
None, credit to @kmautner (here at 42 Vienna) for explaining the concepts.  
   
### AI?  
no. (cring)
