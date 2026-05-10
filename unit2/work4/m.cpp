
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define WINDOW_COUNT 3      //窗口数
#define SERVICE_TIME 5      //总服务时间
#define MAXSIZE 100         //最大客户数
typedef struct {
    int number; // 客户号码
    int service_time; // 业务办理所需时间
} Customer;
typedef struct {
    Customer queue[MAXSIZE]; // 客户队列，最多100个客户
    int front; // 队头指针
    int rear; // 队尾指针
} Queue;
typedef struct {
    int is_busy; // 窗口是否忙碌
    Customer current_customer; // 当前客户
} Window;



void QueueIn(Queue *q, Customer customer) //入队
{
   //补充代码
   if(((q->rear + 1) % MAXSIZE) == q->front)
   {
        printf("队伍已满！\n");
        return;
   }

   q->queue[q->rear] = customer;
   q->rear = (q->rear + 1) % MAXSIZE; 
  
}
Customer QueueOut(Queue *q) //出队
{
    //补充代码
    Customer e;
    if(q->front == q->rear)
    {
        printf("队伍为空！\n");
    }

    e = q->queue[q->front];
    q->front = (q->front + 1) % MAXSIZE;

    return e;
}
void printWindowStatus(int current_time, Window windows[]) 
{
    int i;
    printf("当前时刻：%d\n", current_time);
    for (i = 0; i < WINDOW_COUNT; i++) 
	{
        if (windows[i].is_busy) 
		{
            printf("窗口 %d 忙碌，当前客户号码：%d\n", i + 1, windows[i].current_customer.number);
        } 
		else 
		{
            printf("窗口 %d 空闲\n", i + 1);
        }
    }
}
void SimulateBank(Queue customer_queue)
{  
    int i, k, current_time, all_windows_idle, num_arrivals;
    Window windows[WINDOW_COUNT];     // 初始化窗口
    for (i = 0; i < WINDOW_COUNT; i++) 
        windows[i].is_busy = 0;             // 初始化为非忙碌状态

    srand((unsigned int)time(NULL));         // 设置随机种子
    current_time = 1;                      // 从时刻1开始
    while (1)                             // 以单位时间为间隔进行循环
    { 
        // 服务时间结束且队列为空且所有窗口都空闲时跳出循环
        if (current_time > SERVICE_TIME && customer_queue.front == customer_queue.rear) 
        {   
            all_windows_idle = 1;
            for (i = 0; i < WINDOW_COUNT; i++) 
            if (windows[i].is_busy) 
            {   
                all_windows_idle = 0;
                break;
            }
            if (all_windows_idle == 1) 
                break;
        }
        // 服务时间结束前，客户按一定概率抵达并进入客户队列
        if (current_time <=  SERVICE_TIME) 
        {
            num_arrivals = rand() % WINDOW_COUNT;        //在一个时间段内随机生成0~2个客户
            for (k = 0; k < num_arrivals; k++)
            {   
                Customer new_customer;
                new_customer.number = current_time * 10 + k;   // 客户号码暂时用当前时间表示
                // 随机生成客户办理业务所需的时间
	            new_customer.service_time = rand() % SERVICE_TIME + 1; 
                QueueIn(&customer_queue, new_customer);
                printf("客户%d已取号\n", new_customer.number);
		    }
        }
        // 处理各个窗口的状态
        for (i = 0; i < WINDOW_COUNT; i++) 
        {   
            if (windows[i].is_busy) 
            {    
                windows[i].current_customer.service_time--;    //客户的业务时长减少一个单位时间
                if (windows[i].current_customer.service_time == 0) 
                {   
                    windows[i].is_busy = 0; // 窗口置为空闲
                    printf("%d号办理业务完成,离开窗口%d\n", windows[i].current_customer.number, i + 1);
                }
            } 
            else if (customer_queue.front != customer_queue.rear) 
            {   
                Customer next_customer = QueueOut(&customer_queue); //下一个客户出队
                windows[i].is_busy = 1;                // 窗口置为忙碌
                windows[i].current_customer = next_customer;   // 客户至窗口办理业务
                printf("客户%d开始办理业务，进入窗口 %d\n", next_customer.number, i + 1);
            }
        }
        printWindowStatus(current_time, windows);             // 输出窗口情况
        current_time++;                      // 时间增加
    }
}
int main()
{
    // 初始化客户队列
    Queue customer_queue;
    customer_queue.front = 0;
    customer_queue.rear = 0;
    SimulateBank(customer_queue);
    printf("所有窗口均空闲，营业结束\n");
    return 0;
}