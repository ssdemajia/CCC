function instanceOf(lobj, rConstructor) {
    /**
     * 左边是实例，右边是构造函数.
     * 通过Object.getPrototypeOf(实例) 来获得这个实例的原型
     */
    let rProto = rConstructor.prototype;
    let lProto = Object.getPrototypeOf(lobj);
    while (lProto) {
        if (lProto === rProto) return true;
        lProto = Object.getPrototypeOf(lProto);
    }
    return false;
}

(function() {
    let ss = new SS();
    console.log(instanceOf(ss, Object))
    console.log(instanceOf(ss, SS))
})()