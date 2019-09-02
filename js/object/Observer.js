var Observer = (function() {
  let messages = {};
  return {
    regist(type, fn) {
    // 对应消息来注册方法
      if (!messages[type]) {
        messages[type] = [fn];
      } else {
        messages[type].push(fn);
      }
    },
    fire(type, args) {
    // 得到消息后通知所有订阅者
      if (!messages[type]) {
        return;
      }
      let event = {
        type,
        args: args || {}
      };
      let len = messages[type].length;
      for (let i = 0; i < len; i++) {
        messages[type][i].call(this, event);
      }
    },
    remove(type, fn) {
    // 将订阅者从消息队列中删除
      if (messages[type] instanceof Array) {
        messages[type] = messages[type].filter(f => f == fn);
      }
    }
  }
})();

Observer.regist('click', (e) => {
  console.log('click:', e);
})
let handle = (e) => {
  console.log('click:', e);
};
Observer.regist('click', handle)
Observer.fire('click', 'lalala');
Observer.remove('click', handle);
Observer.fire('click', 'lalala');