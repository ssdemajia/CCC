class Scheduler {
	add(promiseCreator) {
		if (!Array.isArray(this._runnings)) {
			this._runnings = [];
		}
		if (!Array.isArray(this._pendings)) {
			this._pendings = [];
		}
		if (!this._tick) {
			this._tick = function (idx) {
				if (this._pendings.length === 0) {
					this._runnings.splice(idx, 1);
					return;
				}
				const [promiseCreator, resolve] = this._pendings.shift();
				let ret;
				try {
					ret = promiseCreator();
				} catch (ex) {
					ret = Promise.reject(ex);
				}
				const nextTick = () => setTimeout(() => this._tick(idx), 0);
				this._runnings.splice(idx, 1, ret.then(nextTick, nextTick));
				resolve(ret);
			};
		}
		return new Promise((resolve) => {
			this._pendings.push([promiseCreator, resolve]);
			if (this._runnings.length < 2) {
				const idx = this._runnings.length;
				this._tick(idx);
			}
		});
	}
}

const timeout = (time) => new Promise(resolve => {
	console.log('in timeout:', time);
	setTimeout(resolve, time);
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