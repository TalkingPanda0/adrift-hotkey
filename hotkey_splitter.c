#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
#include "xhklib.h"
#include "config.h"

#define LENGTH(X)               (sizeof X / sizeof X[0])

typedef enum {
	RUNNING,
	PAUSED,
	NOT_STARTED,
} timer_state;
timer_state state;

timer_action action;

void HotkeyCallBack(xhkEvent e, void *r1, void *r2, void *r3)
{
	action = (timer_action)r1;
}

void *HotkeySetup(void *arg)
{
	xhkConfig *hkconfig;
	hkconfig = xhkInit(NULL);
	for(int i=0;i<LENGTH(keys);i++)
	{
		xhkBindKey(hkconfig, 0, keys[i].keybind, keys[i].modifiers, keys[i].event_mask, HotkeyCallBack, (void*)keys[i].action, 0, 0);
	}

	
	for(;;){
		xhkPollKeys(hkconfig, 1);
	}

	
    	xhkClose(hkconfig);
	return NULL;
}

int main(){
	pthread_t id;

	pthread_create(&id,NULL,HotkeySetup,NULL);

	//rift
	action = NOTHING;
	state= NOT_STARTED;
	struct timeval start,now;
	uint64_t timer = 0;
	for(;;)
	{
		if(state == RUNNING)
		{
			gettimeofday(&now,NULL);
			timer += ((now.tv_sec - start.tv_sec) * 1000000) + ( now.tv_usec - start.tv_usec); 
			printf("%lu ",timer);
			gettimeofday(&start,NULL);
		}
		
		switch (action){
			case START:
				if(state != NOT_STARTED)
				{
					putchar(10);
					break;
				}
				gettimeofday(&start,NULL);
				timer = 0;
				state = RUNNING;
				printf("0 BEGIN\n");
				break;
			case SPLIT:
				printf("SPLIT\n");
				break;
			case RESET:
				if(state == NOT_STARTED)
				{

					putchar(10);
					break;
				}
				timer = 0;
				printf("RESET\n");
				gettimeofday(&start,NULL);
				state = NOT_STARTED;
				break;
			case PAUSE:
				if(state != RUNNING)
				{
					putchar(10);
					break;
				}
				putchar(10);
				state = PAUSED;
				break;
			case RESUME:
				if(state != PAUSED)
				{
					putchar(10);
					break;
				}
				state = RUNNING;
				gettimeofday(&start,NULL);

				break;
			case END:
				state = NOT_STARTED;
				putchar(10);
				break;
			case NOTHING:
				if(state == RUNNING)
					putchar(10);
				break;

		}
		action = NOTHING;
		
		struct timespec sleep_tv = {
			.tv_sec = 0,
			.tv_nsec = 10000,
		};
		nanosleep(&sleep_tv, NULL);
		
	}
}
