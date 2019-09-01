function New(constructor, ...args) {
    /**
     * 1.创建一个新对象
     * 2.将构造函数的作用域赋给新对象
     * 3.执行构造函数中的代码
     * 4.返回新对象
     */
    let obj = new Object();
    constructor.call(obj, ...args);
    obj.__proto__ = constructor.prototype;
    return obj;
}

function SS(a, b) {
    this.a = a;
    this.b = b;
    SS.prototype.print = function () {
        console.log(this.a, this.b);
    }
}

(function () {
    let obj = New(SS, 1, 2);
    obj.print();
    console.log(obj.constructor.prototype.__proto__.__proto__);
})()
