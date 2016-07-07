#define QUEUE_SIZE	50

typedef struct {
	int x;
	int y;
	int loopNum;
} data_t;

typedef struct {
	int head;
	int num;
	data_t data[QUEUE_SIZE];
} queue_t;

int enqueue(queue_t *que, data_t enq_data);
int dequeue(queue_t *que, data_t *deq_data);
void queuePrint(queue_t *que);
void queue_init(queue_t *que);
