class Scheduler {
    constructor() {
        this.cur = 0;
        this.prepare = [];
    }
    run() {
        if (this.prepare.length == 0) return;
        const [task, resolve] = this.prepare.shift();
        this.cur += 1;
        task().then(_ => {
            this.cur -= 1
            resolve();
            this.run();
        })
    }
    add(promiseCreator) {
        return new Promise((res, rej) => {
            this.prepare.push([promiseCreator, res]);
            if (this.cur < 2) {
                this.run();
            }
        })
    }
}

const timeout = (time) => new Promise(resolve => {
    console.log("in timeout:", time);
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
addTask(100, '5')
// output: 2 3 1 5 4
// 一开始，1、2两个任务进入队列
// 500ms时，2完成，输出2，任务3进队
// 800ms时，3完成，输出3，任务4进队
// 1000ms时，1完成，输出1，任务5进队
// 1100ms时，5完成，输出5
// 1200ms时，4完成，输出4







