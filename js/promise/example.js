class Scheduler {
    constructor() {
        this.__maxQueueSize = 2;
        this.__runningJobs = [];
        this.__pendingQueue = [];
    }

    get isJobsFull() {
        return this.__maxQueueSize <= this.__runningJobs.length;
    }

    static jobWrapper(promiseCreator) {
        Scheduler.__jobId += 1;
        const id = Scheduler.__jobId;
        const wrappedPromise = promiseCreator().then((result) => {
            return {
                id,
                result
            };
        });
        wrappedPromise.__jobId = id;
        return wrappedPromise;
    }

    removeFinishedJob(id) {
        console.log(`remove ${id}`);
        this.__runningJobs = this.__runningJobs.reduce((curr, job) => {
            if (job.__jobId !== id) {
                curr.push(job);
            }
            return curr;
        }, []);
        console.log(this.__runningJobs);
    }

    async add(promiseCreator) {
        if (!this.isJobsFull) {
            const job = Scheduler.jobWrapper(promiseCreator);
            this.__runningJobs.push(job);
            const { result, id } = await job;
            this.removeFinishedJob(id);
            return result;
        } else {
            this.__pendingQueue.unshift(promiseCreator);
            await Promise.race(this.__runningJobs);
            if (this.__pendingQueue.length > 0) {
                return this.add(this.__pendingQueue.pop());
            }
        }
    }
}

Scheduler.__jobId = 0;

const timeout = (time) => new Promise(resolve => {
    setTimeout(resolve, time)
});

const scheduler = new Scheduler();

const addTask = (time, order) => {
    scheduler.add(() => timeout(time))
             .then(() => console.log(order))
};

addTask(1000, '1')
addTask(500, '2')
addTask(300, '3')
addTask(400, '4')
// output: 2 3 1 4
// 一开始，1、2两个任务进入队列
// 500ms时，2完成，输出2，任务3进队
// 800ms时，3完成，输出3，任务4进队
// 1000ms时，1完成，输出1
// 1200ms时，4完成，输出4

   