function PromiseAll(promises) {
  let result = Array.from({ length: promises.length });
  let count = 0;
  return new Promise((resolve, reject) => {
    promises.forEach((p, i) => {
      p.then(res => {
        count++;
        result[i] = res;  // 按顺序存放结果
        if (count == promises.length) { // 当所有都完成后，才resolve
          resolve(result);
        }
      }).catch(err => { // 一旦出现异常就使用reject结束
        reject(err);
      })
    })
  })
}
let timer = (time) => new Promise(res => setTimeout(() => res(time), time));

let now = +new Date
PromiseAll([timer(1000), timer(200), timer(300), timer(500)])
.then(data => {
  console.log(data);
  console.log(+new Date - now)
})