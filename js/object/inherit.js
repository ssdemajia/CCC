/*
 * 使用原型对象的模式，缺点在于共享属性如果是引用类型就会出现问题
 */
function Parent() { }
Parent.prototype = {
    constructor: Parent,
    print: _ => console.log('parent'),
    name: 'ss',
    arr: [1, 2]
}
// 默认原型里的构造函数字段是不可枚举的
Object.defineProperty(Parent.prototype, 'constructor', {
    enumerable: false,
    value: Parent
});

(function () {
    let p1 = new Parent();
    let p2 = new Parent();
    p1.arr.push(3);
    console.log(p2.arr.length == 3);
})()


/*
动态原型模式
*/
function Person(name) {
    this.name = name;
    if (typeof Person.prototype.print !== 'function')
        Person.prototype.print = function () { }
}


/**
 * 借用构造函数实现继承
 */
function SuperType() {
    this.name = 123;
    this.arr = [];
}
function SubType() {
}
SubType.prototype = new SuperType(); // 使得SubType原型指向SuperType的原型
// 上面的方式使得this.arr会被子类共享

function SuperType() {
    this.arr = []
}

function SubType() {
    SuperType.call(this);
}
SubType.prototype = new SuperType();
SubType.prototype.constructor = SubType; // 原来是SuperType
Object.defineProperty(SubType.prototype, 'constructor', {
    enumerable: false,
    value: SubType
})

/**
 * 终极寄生组合继承
 */

 function inherit(SubType, SuperType) {
     let subPrototype = Object.create(SuperType.prototype); // 创建原型指向Supertype原型的对象
     subPrototype.constructor = SubType; // 子类原型构造函数字段
     Object.defineProperty(subPrototype, 'constructor', {
         enumerable: false,
         value: SubType
     });
     SubType.prototype = subPrototype; // 子类构造函数原型
 }

 function SuperType() {

 }
 SuperType.prototype.echo = function() {
     console.log('ss')
 }
 function SubType() {

 }
 inherit(SubType, SuperType);
 SubType.prototype.print = function() {
     console.log('123')
 };

 (function() {
    let sub = new SubType();
    sub.print();
    sub.echo();
 })();