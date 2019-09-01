
var asyncFn = function () {
    // 获取异步执行函数
    if (typeof process === 'object' && process !== null &&
        typeof (process.nextTick) === 'function'
    ) {
        return process.nextTick;
    } else if (typeof (setImmediate) === 'function') {
        return setImmediate;
    }
    return setTimeout;
}();

function Handler(onFulfilled, onRejected, promise) {
    // 封装resolve时的回调，reject时的回调，以及then返回的promise对象
    this.onFulfilled = onFulfilled;
    this.onRejected = onRejected;
    this.promise = promise;
}

function Promise(handle) {

    function handleResolved(promise, defered) {
        // 根据当前promise状态，调用相关回调函数，并决定返回的新promise状态
        asyncFn(() => {
            let cb = promise.status == 'FULFILLED' ? defered.onFulfilled : defered.onRejected;
            // if (cb === null) {

            // }
            let res;
            try {
                res = cb(promise.val);  // 执行回调
            } catch (e) {
                defered.promise._reject(e)
            }
            defered.promise._resolve(res);
        }, 0);
    }

    Promise.prototype._resolve = function (val) { // !!!如果使用箭头函数会使这个_resolve的this绑定在
        // _resolve主要是用于调用回调函数
        if (this.status !== 'PENDING') {
            return;
        }
        if (val && val instanceof Promise && val.then === this.then) {
            // val也是一个promise
            if (val.status === 'PENDING') {
                val.deferedCB.push(...this.deferedCB);
            } else if (val.length != 0) {
                val.deferedCB.forEach(deferedItem => {
                    handleResolved(val, deferedItem);
                })
                val.deferedCB = [];
            }
            return;
        }
        if (val)
        this.status = 'FULFILLED';
        this.val = val;
        this.deferedCB.forEach(deferedItem => { // 已完成，则处理回调函数
            handleResolved(this, deferedItem);
        });
        this.deferedCB = [];
    }

    Promise.prototype._reject = err => {
        if (this.status !== 'PENDING') {
            return;
        }
        this.status = 'REJECTED';
        this.val = err;
        this.deferedCB.forEach(callbackItem => { // 已完成，则处理回调函数
            handleResolved(this, callbackItem);
        });
        this.deferedCB = [];
    }

    Promise.prototype.catch = (onrejected) => {

    }

    Promise.prototype.then = (onFulfilled, onRejected) => {  // 箭头函数会固化this，node里面全局this是{}
        // onfulfilled是promise完成的回调， onreject是失败时的回调
        let newPromise = new Promise(function () { }); // 一个新的promise，其中的状态为pending，之所以不使用原有的promise对象是因为已有的对象状态已经转移且固定
        let defered = new Handler(onFulfilled, onRejected, newPromise);
        if (this.status == 'PENDING') { // 异步调用还在运行中
            this.deferedCB.push(defered);
            return newPromise;
        }
        handleResolved(this, defered);
        return newPromise;
    }

    if (typeof handle !== 'function') {
        throw new Error('handle必须是函数类型');
    }
    this.status = 'PENDING';
    this.deferedCB = []; // 保存多次调用then传入的回调函数
    try {
        // 因为this._resolve 是回调函数，在异步函数中执行，需要绑定this，或者用箭头函数
        handle(this._resolve.bind(this), this._reject.bind(this));  // 直接执行handle
    } catch (err) {
        this._catch(err);
    }
}



Promise.all = (promises) => {

}

Promise.race = (promises) => {

}


let p1 = new Promise((res, rej) => {
    setTimeout(function timeoutCB() {
        console.log('ss');
        res(123);
    }, 1000);
})
function f1(val) {
    console.log(val);
    return new Promise(res => {
        res(val)
    })
}
function f2(val) {
    console.log(val);
}
let p2 = p1.then(f1)
let p3 = p2.then(f2)