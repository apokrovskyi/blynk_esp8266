/*
 * BlynkTimer.h
 *
 * Andy, 2017
 *
 */

#ifndef BLYNKTIMER_H
#define BLYNKTIMER_H

class BlynkTimer {
public:
        // Timer will call function 'f' every 'd' milliseconds forever
        // returns the timer number (numTimer) on success or
        // -1 on failure (f == NULL) or no free timers
        int setInterval(unsigned long d, os_timer_func_t *f){
            os_timer_disarm(&timer);
            os_timer_setfn(&timer, f, NULL);
            os_timer_arm(&timer, d, 1);
        }

        // Timer will call function 'f' with parameter 'p' every 'd' milliseconds forever
        // returns the timer number (numTimer) on success or
        // -1 on failure (f == NULL) or no free timers
        int setInterval(unsigned long d, os_timer_func_t *f, void* p){
            os_timer_disarm(&timer);
            os_timer_setfn(&timer, f, p);
            os_timer_arm(&timer, d, 1);
        }

        // Timer will call function 'f' after 'd' milliseconds one time
        // returns the timer number (numTimer) on success or
        // -1 on failure (f == NULL) or no free timers
        int setTimeout(unsigned long d, os_timer_func_t *f){
            os_timer_disarm(&timer);
            os_timer_setfn(&timer, f, NULL);
            os_timer_arm(&timer, d, 0);
        }

        // Timer will call function 'f' with parameter 'p' after 'd' milliseconds one time
        // returns the timer number (numTimer) on success or
        // -1 on failure (f == NULL) or no free timers
        int setTimeout(unsigned long d, os_timer_func_t *f, void* p){
            os_timer_disarm(&timer);
            os_timer_setfn(&timer, f, p);
            os_timer_arm(&timer, d, 0);
        }
private:
    ETSTimer timer;
};

#endif
