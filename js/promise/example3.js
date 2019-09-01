class Scheduler {
  race() {
    return Promise.race([...this.main]).then((r1) => {
      console.log(r1)
      if (this.main.size < 2) {
        let willRun = this.queue.shift()();
        this.main.add(willRun);
        willRun.then((r2) => {
          console.log(r2)
          this.main.delete(willRun);
        });
        return willRun
      } else {
        // console.log('have to wait')
        return this.race();
      }
    });
  }

  add(promiseCreator) {
    if (this.queue === undefined) this.queue = [];
    if (this.main === undefined) this.main = new Set();
    this.queue.push(promiseCreator);
    if (this.queue.length && this.main.size < 2) {
      let willRun = this.queue.shift()();
      this.main.add(willRun);
      willRun.then((r1) => {
        console.log(r1)
        this.main.delete(willRun);
      });
      return willRun;
    } else {
      return this.race();
    }
  }
}

const timeout = time =>
  new Promise(resolve => {
    setTimeout(() => {
      resolve(time);
    }, time);
  });
const scheduler = new Scheduler();
const addTask = (time, order) => {
  scheduler.add(() => timeout(time)).then(() => console.log(order));
};
addTask(1000, '1');
addTask(500, '2');
addTask(300, '3');
addTask(400, '4');
addTask(100, '5')