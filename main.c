#include<linux/module.h>
#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/timer.h>
#include<linux/jiffies.h>
#include<linux/hrtimer.h>
#include<linux/time.h>

MODULE_LICENSE("GPL");
ktime_t ti ;
struct hrtimer hrt;

enum hrtimer_restart fun(struct hrtimer * ptr)
{
        pr_alert( "\n in hr timer callback \n");
        hrtimer_forward_now(&hrt,ti);
        return HRTIMER_RESTART;
}

int __init startFun(void)
{
        printk(KERN_INFO "\nHello world\n");
        ti = ktime_set(1,100);
        hrtimer_init(&hrt,CLOCK_REALTIME,HRTIMER_MODE_ABS);
        hrt.function = fun;
        hrtimer_start(&hrt,ti,HRTIMER_MODE_ABS);
        return 0;
}

void __exit endFun(void)
{
        hrtimer_cancel(&hrt);
        hrtimer_try_to_cancel(&hrt);
        printk(KERN_INFO "\nbye world\n");
}

module_init(startFun);
module_exit(endFun);
