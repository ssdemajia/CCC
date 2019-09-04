// https://www.codewars.com/kata/synchronous-promise/train/javascript
// 这是一个同步的promise
function SyncPromise(resolver) {
  if (!resolver) throw new Error('must has resolver');
  this.status = "Pending";
  this.value = undefined;

  const resolve = (value) => { // 改变当前状态
    if (this.status == 'Pending') {
      this.value = value;
      this.status = 'Resolved';
    }
  }

  const reject = (value) => {
    if (this.status == 'Pending') {
      this.value = value;
      this.status = 'Rejected';
    }
  }
  try {
    resolver(resolve, reject);
  } catch (err) {
    reject(err); // 不能从rejected变为resolved
  }

  SyncPromise.prototype.then = (onResolved) => {
    if (this.status == 'Pending') throw new Error();
    if (this.status == 'Rejected') return this;
    
    try{
      this.value = onResolved(this.value);
    } catch(err) {
      this.status = 'Rejected';
      this.value = err;
    }
    return this; // 链式调用
  }

  SyncPromise.prototype.catch = (onRejected) => {
    if (this.status == 'Pending') throw new Error('status')
    if (this.status == 'Resolved') return this;
    try {
      this.value = onRejected(this.value);
      this.status = 'Resolved';  // 处理完异常后，promise的状态变为resolved
    } catch (error) {
      this.value = error;
    }
    return this;
  }
  SyncPromise.prototype.finally = (onFinally) => {
    let ret = onFinally({
      status: this.status,
      value: this.value
    });
    return ret;
  }
}
SyncPromise.resolve = function(value) {
  if (value instanceof SyncPromise) return value;
  return new SyncPromise((res => res(value)));
}
new SyncPromise((resolve, reject) => {
  throw new Error("zhupi")
  resolve(1)
}).catch(e => {
  console.log("catch:", e);
  return 1;
}).then(d => {
  console.log("then:", d);
}).finally(({ status, value }) => {
  console.log(status, value)
})

new Promise((resolve, reject) => {
  resolve(1);
}).then(data => {
  console.log("then1:", data)
}).then(data => {
  console.log("then2:", data);
})